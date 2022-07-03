#include "connection_folder.h"

ConnectionFolder::ConnectionFolder() {
    this->type = CONNECTION_TYPE_FOLDER;
}

ConnectionFolder::~ConnectionFolder() {
    for (auto itr = this->connections.begin(); itr != this->connections.end(); itr++) {
        delete *itr;
    }
}