#pragma once

#include <FL/Fl_Tree.H>
#include <vector>
#include "../connection.h"

using namespace std;

class TreeConnections : public Fl_Tree {
public:
    TreeConnections(int x, int y, int w, int h);
    virtual ~TreeConnections();

    void set_callback_connection_selected(void (*callback_connection_selected)(Connection *connection, void *user_data), void *user_data);

    void add_connection(Connection *connection);
    void select_connection(Connection *connection);

private:
    void (*callback_connection_selected)(Connection *connection, void *user_data);
    void *callback_connection_selected_user_data;
};