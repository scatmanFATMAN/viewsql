#include "tree_connections.h"

static void callback_tree(Fl_Widget *widget, void *user_data) {
    Connection *connection;
    TreeConnections *tree_connections;
    Fl_Tree_Item *item;

    tree_connections = (TreeConnections *)user_data;

    switch (tree_connections->callback_reason()) {
        case FL_TREE_REASON_SELECTED:
            item = tree_connections->callback_item();
            connection = (Connection *)item->user_data();
            tree_connections->select_connection(connection);
            break;
        case FL_TREE_REASON_DESELECTED:
            break;
    }
}

TreeConnections::TreeConnections(int x, int y, int w, int h) : Fl_Tree(x, y, w, h) {
    this->showroot(0);
    this->end();

    this->callback(callback_tree, this);

    this->callback_connection_selected = NULL;
    this->callback_connection_selected_user_data = NULL;
}

TreeConnections::~TreeConnections() {
}

void TreeConnections::set_callback_connection_selected(void (*callback_connection_selected)(Connection *connection, void *user_data), void *user_data) {
    this->callback_connection_selected = callback_connection_selected;
    this->callback_connection_selected_user_data = user_data;
}

void TreeConnections::add_connection(Connection *connection) {
    Fl_Tree_Item *item;

    item = this->add(connection->name);
    item->user_data(connection);

    this->redraw();
}

void TreeConnections::select_connection(Connection *connection) {
    this->callback_connection_selected(connection, this->callback_connection_selected_user_data);
}