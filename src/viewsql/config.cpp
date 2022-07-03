#include <jansson.h>
#include <vector>
#include "../common/log.h"
#include "../common/os.h"
#include "../common/string.h"
#include "connection_folder.h"
#include "connection_database.h"
#include "version.h"
#include "config.h"

using namespace std;

#define CONFIG_FILE "viewsql.json"

typedef struct {
    vector<Connection *> connections;
} config_t;

static config_t config;

void Config::init() {
}

void Config::free() {
    for (auto itr = config.connections.begin(); itr != config.connections.end(); itr++) {
        delete *itr;
    }
}

static void config_add_connection(ConnectionFolder *connection_folder_parent, Connection *connection) {
    if (connection_folder_parent != NULL) {
        connection_folder_parent->connections.push_back(connection);
    }
    else {
        config.connections.push_back(connection);
    }
}

static void config_read_connection(ConnectionFolder *connection_folder_parent, json_t *json_connection, unsigned int index) {
    json_t *json_name, *json_host, *json_port, *json_user, *json_password, *json_database, *json_connections, *json_type, *json_connection_child;
    size_t json_index;
    ConnectionFolder *connection_folder;
    ConnectionDatabase *connection_database;

    json_type = json_object_get(json_connection, "type");
    if (json_is_string(json_type)) {
        if (strcmp(json_string_value(json_type), "Folder") == 0) {
            json_name = json_object_get(json_connection, "name");
            json_connections = json_object_get(json_connection, "connections");

            connection_folder = new ConnectionFolder;
            strlcpy(connection_folder->name, json_string_value(json_name), sizeof(connection_folder->name));
            connection_folder->index = index;
            config_add_connection(connection_folder_parent, connection_folder);

            //parse the child connections!
            json_array_foreach(json_connections, json_index, json_connection_child) {
                config_read_connection(connection_folder_parent, json_connection_child, (unsigned int)json_index);
            }
        }
        else if (strcmp(json_string_value(json_type), "Database") == 0) {
            json_name = json_object_get(json_connection, "name");
            json_host = json_object_get(json_connection, "host");
            json_port = json_object_get(json_connection, "port");
            json_user = json_object_get(json_connection, "user");
            json_password = json_object_get(json_connection, "password");
            json_database = json_object_get(json_connection, "database");

            connection_database = new ConnectionDatabase;
            strlcpy(connection_database->name, json_string_value(json_name), sizeof(connection_database->name));
            strlcpy(connection_database->host, json_string_value(json_host), sizeof(connection_database->host));
            connection_database->port = (unsigned int)json_integer_value(json_port);
            strlcpy(connection_database->user, json_string_value(json_user), sizeof(connection_database->user));
            strlcpy(connection_database->password, json_string_value(json_password), sizeof(connection_database->password));
            strlcpy(connection_database->database, json_string_value(json_database), sizeof(connection_database->database));
            connection_database->index = index;
            config_add_connection(connection_folder_parent, connection_database);
        }
        else {
            Log::error("Error reading '%s': Unknown connection type '%s'", CONFIG_FILE, json_string_value(json_type));
        }
    }
    else {
        Log::error("Error reading '%s': Expected connection type", CONFIG_FILE);
    }
}

static void config_read_connections(json_t *json_connections) {
    json_t *json_connection;
    size_t json_index;

    if (json_is_array(json_connections)) {
        json_array_foreach(json_connections, json_index, json_connection) {
            config_read_connection(NULL, json_connection, (unsigned int)json_index);
        }
    }
}

bool Config::read() {
    json_t *json_root, *json_connections;
    json_error_t json_error;

    if (access(CONFIG_FILE, F_OK) != 0) {
        Log::warn("%s does not exist, creating one", CONFIG_FILE);
        return Config::write();
    }

    json_root = json_load_file(CONFIG_FILE, 0, &json_error);
    if (json_root == NULL) {
        Log::error("Error reading %s: %s", CONFIG_FILE, json_error.text);
        return false;
    }

    json_connections = json_object_get(json_root, "connections");

    config_read_connections(json_connections);

    json_decref(json_root);
    return true;
}

static void config_write_connection(json_t *json_connections, Connection *connection);

static void config_write_connection_database(json_t *json_connection, ConnectionDatabase *connection_database) {
    json_t *json_host, *json_port, *json_user, *json_password, *json_database;

    json_host = json_string(connection_database->host);
    json_port = json_integer(connection_database->port);
    json_user = json_string(connection_database->user);
    json_password = json_string(connection_database->password);
    json_database = json_string(connection_database->database);

    json_object_set(json_connection, "host", json_host);
    json_object_set(json_connection, "port", json_port);
    json_object_set(json_connection, "user", json_user);
    json_object_set(json_connection, "password", json_password);
    json_object_set(json_connection, "database", json_database);
}

static void config_write_connection_folder(json_t *json_connection, ConnectionFolder *connection_folder) {
    json_t *json_connections;

    json_connections = json_array();
    json_object_set(json_connection, "connections", json_connections);

    for (auto itr = connection_folder->connections.begin(); itr != connection_folder->connections.end(); itr++) {
        config_write_connection(json_connections, *itr);
    }
}

static void config_write_connection(json_t *json_connections, Connection *connection) {
    json_t *json_connection;

    json_connection = json_object();
    json_object_set(json_connection, "name", json_string(connection->name));
    json_object_set(json_connection, "type", json_string(Connection::type_str(connection->type)));
    json_array_append_new(json_connections, json_connection);

    if (connection->type == CONNECTION_TYPE_FOLDER) {
        config_write_connection_folder(json_connection, (ConnectionFolder *)connection);
    }
    else if (connection->type == CONNECTION_TYPE_DATABASE) {
        config_write_connection_database(json_connection, (ConnectionDatabase *)connection);
    }
}

static void config_write_connections(json_t *json_connections) {
    for (auto itr = config.connections.begin(); itr != config.connections.end(); itr++) {
        config_write_connection(json_connections, *itr);
    }
}

bool Config::write() {
    json_t *json_root, *json_connections;
    char version[32];
    bool success = true;

    snprintf(version, sizeof(version), "%d.%d.%d", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
    json_connections = json_array();

    json_root = json_object();
    json_object_set(json_root, "version", json_string(version));
    json_object_set(json_root, "connections", json_connections);

    config_write_connections(json_connections);

    if (json_dump_file(json_root, CONFIG_FILE, JSON_INDENT(4)) != 0) {
        Log::error("Error writing %s", CONFIG_FILE);
        success = false;
    }

    json_decref(json_root);
    return success;
}

void Config::add_connection(Connection *connection) {
    config.connections.push_back(connection);
}

void Config::foreach_connection(void (*func)(Connection *connection, void *user_data), void *user_data) {
    for (auto itr = config.connections.begin(); itr != config.connections.end(); itr++) {
        func(*itr, user_data);
    }
}