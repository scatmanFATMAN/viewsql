#pragma once

#include <FL/Fl_Tabs.H>
#include "../connection_database.h"
#include "panel_connection_general.h"

class TabsConnection : public Fl_Tabs {
public:
    TabsConnection(int x, int, int w, int h);
    virtual ~TabsConnection();

    void new_connection();
    void save_connection(ConnectionDatabase *connection_database);
    void select_connection(Connection *connection);

private:
    PanelConnectionGeneral *panel_connection_general;
};