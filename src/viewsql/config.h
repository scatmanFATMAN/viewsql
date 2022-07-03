#pragma once

#include "connection.h"

namespace Config {
    void init();
    void free();

    bool read();
    bool write();

    void add_connection(Connection *connection);
    void foreach_connection(void (*func)(Connection *connection, void *user_data), void *user_data);
};