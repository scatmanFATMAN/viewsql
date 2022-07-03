#include "connection.h"

Connection::Connection() {
    this->name[0] = '\0';
    this->type = CONNECTION_TYPE_INVALID;
    this->index = 0;
}

Connection::~Connection() {
}

const char * Connection::type_str(ConnectionType type) {
    switch (type) {
        case CONNECTION_TYPE_FOLDER:
            return "Folder";
        case CONNECTION_TYPE_DATABASE:
            return "Database";
        case CONNECTION_TYPE_INVALID:
            return "Invalid";
    }

    return "Unknown";
}