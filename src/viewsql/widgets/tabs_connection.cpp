#include "widget.h"
#include "tabs_connection.h"

TabsConnection::TabsConnection(int x, int y, int w, int h) : Fl_Tabs(x, y, w, h) {
    int wx, wy, ww, wh;

    wx = this->x();
    wy = this->y() + WIDGET_TAB_HEIGHT;
    ww = this->w();
    wh = this->h() - WIDGET_TAB_HEIGHT;
    this->panel_connection_general = new PanelConnectionGeneral(wx, wy, ww, wh);

    this->end();
}

TabsConnection::~TabsConnection() {
}

void TabsConnection::new_connection() {
    this->panel_connection_general->new_connection();
}

void TabsConnection::save_connection(ConnectionDatabase *connection_database) {
    this->panel_connection_general->save_connection(connection_database);
}

void TabsConnection::select_connection(Connection *connection) {
    this->panel_connection_general->select_connection(connection);
}