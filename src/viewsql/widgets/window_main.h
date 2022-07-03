#pragma once

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Tabs.H>
#include "panel_connections.h"
#include "textarea_log.h"

class WindowMain : public Fl_Window {
public:
    WindowMain(int w, int h, const char *title);
    virtual ~WindowMain();

    virtual int handle(int e);

private:
    Fl_Menu_Bar *menu;
    Fl_Tabs *tabs;
    PanelConnections *tab_panel_connections;
    TextAreaLog *text_area_log;
    bool first_show;
};