#include "../inc/at.h"

#include <iostream>

auto usage_string {
R"(Usage: at [title]
Runtime: 
    d : refresh display 
    q : exit 
    r : restart stopwatch)"
};

int main(int argc, char* argv[]) {
    std::string title { "" };

    if (argc == 2) {
        if (std::string { argv[1] } == "--help") {
            std::cout << usage_string << std::endl;
            return 0;
        } else {
            title = argv[1];
        }
    } else if (argc > 2) {
        std::cout << usage_string << std::endl;
        return 1;
    }

    // run stopwatch & configure terminal
    at::at d { title };

    // loop until user quits
    d.input_loop();

    // quiting dispables ncurses terminal so regular cout
    // is fine
    if (title.empty())
        std::cout << at::human_readable_time(d.final_time()) << std::endl;
    else
        std::cout <<  title << " -> " << at::human_readable_time(d.final_time())
                  << std::endl;
}

