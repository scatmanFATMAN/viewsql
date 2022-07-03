#pragma once

#include <FL/Fl_Group.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Button.H>
#include "../connection_database.h"
#include "tree_connections.h"
#include "tabs_connection.h"

class PanelConnections : public Fl_Group {
public:
    PanelConnections(Fl_Tabs *tabs);
    virtual ~PanelConnections();

    void new_connection();
    void save_connection();
    void select_connection(Connection *connection);
    void update_connections();
    void delete_connection();

private:
    Fl_Tabs *tabs;
    Fl_Button *button_new;
    Fl_Button *button_save;
    Fl_Button *button_delete;
    TreeConnections *tree_connections;
    TabsConnection *tabs_connection;
};