#pragma once

#include <vector>
#include "connection.h"

using namespace std;

class ConnectionFolder : public Connection {
public:
    ConnectionFolder();
    virtual ~ConnectionFolder();

    vector<Connection *> connections;
};