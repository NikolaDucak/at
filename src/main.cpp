#include "../inc/at.h"

#include <iostream>

static const auto usage_string {
    R"(Usage: at [--help] [title]
Runtime: 
    ' ' <space> : pause
    d           : redraw display 
    q           : exit 
    r            : restart stopwatch)"
};

static const bool is_help_requested(int argc, char* argv[]) {
    const auto found_at = std::find(argv, argv + argc, std::string { "--help" });
    return found_at != (argv + argc);
}

static const std::string combine_arguments_to_title(int argc, char* argv[]) {
    std::string result;
    // skip first argument
    for (int i = 1; i < argc; i++) {
        result += argv[i];
        result += ' ';
    }

    // remove trailing ' ' if added above
    if (not result.empty()) result.pop_back();

    return result;
}

int main(int argc, char* argv[]) {
    if (is_help_requested(argc, argv)) {
        std::cout << usage_string << std::endl;
        return 0;
    }
    const auto title = combine_arguments_to_title(argc, argv);

    // run stopwatch & configure terminal
    at::at app { title };

    // loop until user quits
    app.input_loop();

    // quiting dispables ncurses terminal so regular cout is fine
    if (title.empty())
        std::cout << at::human_readable_time(app.final_time()) << std::endl;
    else
        std::cout << title << " -> " << at::human_readable_time(app.final_time())
                  << std::endl;
}
