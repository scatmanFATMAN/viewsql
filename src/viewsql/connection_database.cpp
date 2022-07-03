#include "connection_database.h"

ConnectionDatabase::ConnectionDatabase() {
    this->type = CONNECTION_TYPE_DATABASE;
    this->host[0] = '\0';
    this->port = 0;
    this->user[0] = '\0';
    this->password[0] = '\0';
    this->database[0] = '\0';
}

ConnectionDatabase::~ConnectionDatabase() {
}