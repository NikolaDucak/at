#include "../inc/tui.h"

#include <sstream>
#include <stdexcept>

namespace tui {

void init_terminal() {
    initscr();
    timeout(1000);
    noecho();
    curs_set(0);
    raw();
}

point term_size() {
    point p;
    getmaxyx(stdscr, p.y, p.x);
    return p;
}

std::string cursor_at(uint x, uint y) {
    std::stringstream ss;
    ss << "\33[" << y << ";" << x << "H";
    return ss.str();
}

void print_at(uint x, uint y, const std::string& str) { mvprintw(y, x, str.c_str()); }

void clear() { erase(); }

void render() { refresh(); }

int input() { return getch(); }

void end_terminal() { endwin(); }

}  // namespace tui
