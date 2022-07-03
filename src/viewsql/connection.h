#pragma once

#define CONNECTION_NAME_MAX 50

typedef enum {
    CONNECTION_TYPE_INVALID,
    CONNECTION_TYPE_FOLDER,
    CONNECTION_TYPE_DATABASE
} ConnectionType;

class Connection {
public:
    Connection();
    virtual ~Connection();

    char name[CONNECTION_NAME_MAX + 1];
    ConnectionType type;
    unsigned int index; //TODO: do we need this? or just keep ordering in the vector<>?

    static const char * type_str(ConnectionType type);
};