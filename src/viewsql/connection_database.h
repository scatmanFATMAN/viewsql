#pragma once

#include "connection.h"

#define CONNECTION_DATABASE_HOST_MAX     50
#define CONNECTION_DATABASE_USER_MAX     30
#define CONNECTION_DATABASE_PASSWORD_MAX 75
#define CONNECTION_DATABASE_DATABASE_MAX 30

class ConnectionDatabase : public Connection {
public:
    ConnectionDatabase();
    virtual ~ConnectionDatabase();

    char host[CONNECTION_DATABASE_HOST_MAX + 1];
    unsigned int port;
    char user[CONNECTION_DATABASE_USER_MAX + 1];
    char password[CONNECTION_DATABASE_PASSWORD_MAX + 1]; //TODO: create an encrypted string? protect memory region from swap?? later..
    char database[CONNECTION_DATABASE_DATABASE_MAX + 1];
};