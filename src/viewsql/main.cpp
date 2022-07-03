#include "widgets/window_main.h"
#include "../common/log.h"
#include "config.h"

int main(int argc, char **argv) {
    WindowMain *window;
    int ret;

    Log::init();
    Config::init();

    window = new WindowMain(1000, 600, "ViewSQL");
    window->show(argc, argv);

    ret = Fl::run();

    //TODO: Do these actually get called after Fl::run()?
    Config::free();
    Log::free();

    return ret;
}