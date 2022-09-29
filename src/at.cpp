#include "../inc/at.h"

#include <sstream>
#include <iomanip>

namespace at {

// anonymous helpers
namespace {

tui::point get_new_center() {
    const auto x = tui::term_size();
    return { x.x / 2, x.y / 2 };
}

inline std::chrono::seconds to_seconds(boost::timer::cpu_times times) {
  return std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::nanoseconds(times.wall));
}

// print the string so that the center character of that string lands on the desired position 
// instead the first char landing at the desired position
inline void print_centered_at(const tui::point& at, const std::string& str) {
    const auto print_position = tui::point { 
        static_cast<int>(at.x - str.length() / 2),
        at.y
    };
    tui::print_at(print_position.x, print_position.y, str);
}

}  // namespace

std::string human_readable_time(seconds_t duration) {
    using namespace std::chrono;

    const auto hr = duration_cast<hours>(duration);
    duration -= hr;

    const auto min = duration_cast<minutes>(duration);
    duration -= min;

    const auto sec = duration_cast<seconds>(duration);

    std::stringstream ss;
    ss.fill('0');
    ss << std::setw(2) << hr.count() << " : " << std::setw(2) << min.count()
       << " : " << std::setw(2) << sec.count();

    return ss.str();
}

at::at(const std::string& title) :
    m_running { true },
    m_title { title } {
    m_sw.start();
    tui::init_terminal();
    set_position(get_new_center());
}

void at::input_loop() {
    while (m_running) {
        draw();
        const auto input = tui::input();
        switch (input) {
            case KEY_RESIZE:
            case 'd': set_position(get_new_center()); break;
            case 'q': quit(); break;
            case 'r': reset(); break;
            case ' ': toggle_pause(); break;
            default: break; // input timed out
        }
    }
}

void at::draw() {
    const auto time_string { human_readable_time(to_seconds(m_sw.elapsed())) };
    print_centered_at(m_terminal_center, time_string);
    tui::render();
}

void at::quit() {
    m_running    = false;
    m_final_time = to_seconds(m_sw.elapsed());
    m_sw.stop();
    tui::end_terminal();
}

void at::reset() {
    m_sw.start();
}

void at::toggle_pause() {
    if (m_sw.is_stopped()) {
        m_sw.resume();
    } else {
        m_sw.stop();
    }
}

void at::set_position(const tui::point& position) {
    m_terminal_center = position;
    tui::clear();
    auto title_position = m_terminal_center;
    title_position.y--;
    print_centered_at(title_position, m_title);
    tui::render();
}

seconds_t at::final_time() { return m_final_time; }

}  // namespace at
