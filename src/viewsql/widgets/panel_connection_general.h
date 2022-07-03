#pragma once

#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include "../connection_database.h"

class PanelConnectionGeneral : Fl_Group {
public:
    PanelConnectionGeneral(int x, int y, int w, int h);
    virtual ~PanelConnectionGeneral();

    void new_connection();
    void save_connection(ConnectionDatabase *connection);
    void select_connection(Connection *connection);

private:
    Fl_Input *textfield_connection_name;
    Fl_Input *textfield_connection_host;
    Fl_Input *textfield_connection_port;
    Fl_Input *textfield_connection_user;
    Fl_Secret_Input *textfield_connection_password;
    Fl_Input *textfield_connection_database;
};