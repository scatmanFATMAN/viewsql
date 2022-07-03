#include <stdlib.h>
#include <stdio.h>
#include "../../common/string.h"
#include "widget.h"
#include "panel_connection_general.h"

PanelConnectionGeneral::PanelConnectionGeneral(int x, int y, int w, int h) : Fl_Group(x, y, w, h, "Connection") {
    int wx, wy, ww, wh, label_width;

    label_width = 75;

    wx = this->x() + WIDGET_PADDING + label_width;
    ww = this->w() - (WIDGET_PADDING * 4) - label_width;

    wh = WIDGET_TEXTFIELD_HEIGHT;

    wy = this->y() + WIDGET_PADDING;
    this->textfield_connection_name = new Fl_Input(wx, wy, ww, wh, "Name:");
    this->textfield_connection_name->maximum_size(CONNECTION_NAME_MAX);

    wy = this->textfield_connection_name->y() + this->textfield_connection_name->h() + WIDGET_PADDING;
    this->textfield_connection_host = new Fl_Input(wx, wy, ww, wh, "Host:");
    this->textfield_connection_host->maximum_size(CONNECTION_DATABASE_HOST_MAX);

    wy = this->textfield_connection_host->y() + this->textfield_connection_host->h() + WIDGET_PADDING;
    this->textfield_connection_port = new Fl_Input(wx, wy, ww, wh, "Port:");
    this->textfield_connection_port->maximum_size(5);

    wy = this->textfield_connection_port->y() + this->textfield_connection_port->h() + WIDGET_PADDING;
    this->textfield_connection_user = new Fl_Input(wx, wy, ww, wh, "User:");
    this->textfield_connection_user->maximum_size(CONNECTION_DATABASE_USER_MAX);

    wy = this->textfield_connection_user->y() + this->textfield_connection_user->h() + WIDGET_PADDING;
    this->textfield_connection_password = new Fl_Secret_Input(wx, wy, ww, wh, "Password:");
    this->textfield_connection_password->maximum_size(CONNECTION_DATABASE_PASSWORD_MAX);

    wy = this->textfield_connection_password->y() + this->textfield_connection_password->h() + WIDGET_PADDING;
    this->textfield_connection_database = new Fl_Input(wx, wy, ww, wh, "Database:");
    this->textfield_connection_database->maximum_size(CONNECTION_DATABASE_DATABASE_MAX);

    this->end();
}

PanelConnectionGeneral::~PanelConnectionGeneral() {
}

void PanelConnectionGeneral::new_connection() {
    this->textfield_connection_name->value("");
    this->textfield_connection_host->value("127.0.0.1");
    this->textfield_connection_port->value("3306");
    this->textfield_connection_user->value("");
    this->textfield_connection_password->value("");
    this->textfield_connection_database->value("");

    this->textfield_connection_name->take_focus();
}

void PanelConnectionGeneral::save_connection(ConnectionDatabase *connection) {
    unsigned int port;

    port = strtoul(this->textfield_connection_port->value(), NULL, 10);

    strlcpy(connection->name, this->textfield_connection_name->value(), sizeof(connection->name));
    strlcpy(connection->host, this->textfield_connection_host->value(), sizeof(connection->host));
    connection->port = port;
    strlcpy(connection->user, this->textfield_connection_user->value(), sizeof(connection->user));
    strlcpy(connection->password, this->textfield_connection_password->value(), sizeof(connection->password));
    strlcpy(connection->database, this->textfield_connection_database->value(), sizeof(connection->database));
}

void PanelConnectionGeneral::select_connection(Connection *connection) {
    ConnectionDatabase *connection_database;
    char port[5 + 1];

    switch (connection->type) {
        case CONNECTION_TYPE_DATABASE:
            connection_database = (ConnectionDatabase *)connection;

            snprintf(port, sizeof(port), "%u", connection_database->port);

            this->textfield_connection_name->value(connection_database->name);
            this->textfield_connection_host->value(connection_database->host);
            this->textfield_connection_port->value(port);
            this->textfield_connection_user->value(connection_database->user);
            this->textfield_connection_password->value(connection_database->password);
            this->textfield_connection_database->value(connection_database->database);
            break;
        case CONNECTION_TYPE_FOLDER:
        case CONNECTION_TYPE_INVALID:
            break;
    }
}