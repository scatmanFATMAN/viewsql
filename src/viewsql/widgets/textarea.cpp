#include <stdio.h>
#include <stdarg.h>
#include "../../common/stdio.h"
#include "textarea.h"

TextArea::TextArea(int x, int y, int w, int h) : Fl_Text_Display(x, y, w, h) {
    this->buffer(&this->buf);
}

TextArea::~TextArea() {
}

void TextArea::print(const char *text) {
    this->buf.append(text);
}

void TextArea::printf(const char *fmt, ...) {
    va_list ap;
    char *text;

    va_start(ap, fmt);
    vasprintf(&text, fmt, ap);
    va_end(ap);

    print(text);
    free(text);
}