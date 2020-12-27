#include "../inc/at.h"

#include <iostream>

auto usage_string {
R"(Usage: at <activityName> 
Runtime: 
    p : refresh display 
    q : exit 
    r : restart stopwatch)"
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << usage_string << std::endl;
        return 1;
    }

    // run stopwatch & configure terminal
    at::at d { argv[1] };

    // loop until user quits
    d.input_loop();

    // quiting dispables ncurses terminal so regular cout
    // is fine
    std::cout << argv[1] << " -> " << at::human_readable_time(d.final_time())
              << std::endl;
}

