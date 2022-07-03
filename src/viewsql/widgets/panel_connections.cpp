#include "../../common/string.h"
#include "../config.h"
#include "widget.h"
#include "panel_connections.h"

static void callback_new(Fl_Widget *widget, void *user_data) {
    PanelConnections *panel_connections;

    panel_connections = (PanelConnections *)user_data;
    panel_connections->new_connection();
}

static void callback_save(Fl_Widget *widget, void *user_data) {
    PanelConnections *panel_connections;

    panel_connections = (PanelConnections *)user_data;
    panel_connections->save_connection();
}

static void callback_delete(Fl_Widget *widget, void *user_data) {
    PanelConnections *panel_connections;

    panel_connections = (PanelConnections *)user_data;
    panel_connections->delete_connection();
}

static void callback_connection_add(Connection *connection, void *user_data) {
    TreeConnections *tree_connections;

    tree_connections = (TreeConnections *)user_data;
    tree_connections->add_connection(connection);
}

static void callback_connection_selected(Connection *connection, void *user_data) {
    PanelConnections *panel_connections;

    panel_connections = (PanelConnections *)user_data;
    panel_connections->select_connection(connection);
}

PanelConnections::PanelConnections(Fl_Tabs *tabs) : Fl_Group(0, 0, 0, 0, "Connections") {
    int wx, wy, ww, wh;

    this->tabs = tabs;

    //set my position
    wx = tabs->x();
    wy = tabs->y() + WIDGET_TAB_HEIGHT;
    ww = tabs->w();
    wh = tabs->h() - WIDGET_TAB_HEIGHT;
    this->resize(wx, wy, ww, wh);

    //new button
    wx = this->x() + WIDGET_PADDING;                                        //normal left margin
    wy = this->y() + WIDGET_PADDING;
    ww = 75;
    wh = 20;
    this->button_new = new Fl_Button(wx, wy, ww, wh, "New");
    this->button_new->callback(callback_new, this);

    //save button
    wx = this->button_new->x() + this->button_new->w() + WIDGET_PADDING;    //next to the new button
    wy = this->button_new->y();
    ww = this->button_new->w();
    wh = this->button_new->h();
    this->button_save = new Fl_Button(wx, wy, ww, wh, "Save");
    this->button_save->callback(callback_save, this);
    this->button_save->deactivate();

    //delete button
    wx = this->button_save->x() + this->button_save->w() + WIDGET_PADDING;    //next to the save button
    wy = this->button_new->y();
    ww = this->button_new->w();
    wh = this->button_new->h();
    this->button_delete = new Fl_Button(wx, wy, ww, wh, "Delete");
    this->button_delete->callback(callback_delete, this);
    //this->button_delete->labelcolor(fl_rgb_color(255, 0, 0));
    this->button_delete->color(fl_rgb_color(255, 0, 0));
    this->button_delete->selection_color(fl_rgb_color(255, 0, 0));
    this->button_delete->down_color(fl_rgb_color(255, 0, 0));
    this->button_delete->deactivate();

    //construct the tree
    wx = this->x() + WIDGET_PADDING;                                         //normal left margin
    wy = this->button_new->y() + this->button_new->h() + WIDGET_PADDING;     //under the new button + padding
    ww = this->button_new->w() + WIDGET_PADDING + this->button_save->w() + WIDGET_PADDING + this->button_delete->w();   //width of the 3 buttons
    wh = this->h() - this->button_new->h() - (WIDGET_PADDING * 2);
    this->tree_connections = new TreeConnections(wx, wy, ww, wh);

    //the tab panel for the conenction information
    wx = this->tree_connections->x() + this->tree_connections->w()+5;                       //next to the tree
    wy = this->tree_connections->y() - WIDGET_TAB_HEIGHT;
    ww = this->w() - tree_connections->w();                 //no padding. inside widgets will do that
    wh = this->tree_connections->h() + WIDGET_TAB_HEIGHT;
    this->tabs_connection = new TabsConnection(wx, wy, ww, wh);
    this->tabs_connection->deactivate();

    this->end();

    this->tree_connections->set_callback_connection_selected(callback_connection_selected, this);
}

PanelConnections::~PanelConnections() {
}

void PanelConnections::new_connection() {
    this->tabs_connection->new_connection();
    this->tabs_connection->activate();
}

void PanelConnections::save_connection() {
    ConnectionDatabase *connection_database;

    connection_database = new ConnectionDatabase;

    this->tabs_connection->save_connection(connection_database);
    this->tree_connections->add_connection(connection_database);

    Config::add_connection(connection_database);
    Config::write();
}

void PanelConnections::select_connection(Connection *connection) {
    this->tabs_connection->select_connection(connection);
    this->tabs_connection->activate();
    this->button_save->activate();
    this->button_delete->activate();
}

void PanelConnections::update_connections() {
    Config::foreach_connection(callback_connection_add, this->tree_connections);
}

void PanelConnections::delete_connection() {
}