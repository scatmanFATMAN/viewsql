#pragma once

#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

class TextArea : public Fl_Text_Display {
public:
    TextArea(int x, int y, int w, int h);
    virtual ~TextArea();

    void print(const char *text);
    void printf(const char *fmt, ...);

private:
    Fl_Text_Buffer buf;
};