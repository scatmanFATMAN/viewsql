#include "../../common/log.h"
#include "../config.h"
#include "widget.h"
#include "window_main.h"

#include "../version.h" //TMP?

static void callback_log(LogType type, const char *text, void *user_data) {
    TextAreaLog *text_area_log;

    text_area_log = (TextAreaLog *)user_data;
    text_area_log->print(text);
}

static void callback_quit(Fl_Widget *widget, void *user_data) {
    exit(EXIT_SUCCESS);
};

WindowMain::WindowMain(int w, int h, const char *title) : Fl_Window(w, h, title) {
    int wx, wy, ww, wh;

    //menu at the top
    wx = 0;
    wy = 0;
    ww = this->w();
    wh = WIDGET_MENU_HEIGHT;
    this->menu = new Fl_Menu_Bar(wx, wy, ww, wh, NULL);
    this->menu->add("File/Quit", 0, callback_quit, NULL);

    //text area logger at the bottom
    wx = 0 + WIDGET_PADDING;
    wy = this->h() - 100;
    ww = this->w() - (WIDGET_PADDING * 2);
    wh = 100 - WIDGET_PADDING;
    this->text_area_log = new TextAreaLog(wx, wy, ww, wh);

    //tab panel in the middle.
    //don't put horizontal padding around the tab panel itself so that the tab area extends the full width
    //the panels inside the tab will need to do padding
    wx = 0;
    wy = this->menu->y() + this->menu->h() + WIDGET_PADDING;
    ww = this->w();
    wh = this->h() - wy - this->text_area_log->h() - (WIDGET_PADDING * 2);
    this->tabs = new Fl_Tabs(wx, wy, ww, wh);
    this->tab_panel_connections = new PanelConnections(this->tabs);
    this->tabs->end();

    this->end();

    //this->when(FL_SHOW);

    this->first_show = false;
}

WindowMain::~WindowMain() {
}

int WindowMain::handle(int e) {
    switch (e) {
        case FL_SHOW:
            if (!this->first_show) {
                this->first_show = true;
                
                Log::set_callback(callback_log, this->text_area_log);
                Log::info("Started. Version %d.%d.%d.\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);

                //do all the config loading in the first show so that we can report errors properly
                Config::read();
                this->tab_panel_connections->update_connections();
            }
            return 1;
        default:
            return Fl_Window::handle(e);
    }
}