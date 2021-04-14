#include "../inc/at.h"

#include <sstream>
#include <iomanip>

namespace at {

// anonymous helpers
namespace {

tui::point get_new_center() {
    auto x = tui::term_size();
    return { x.x / 2, x.y / 2 };
}

inline std::chrono::seconds to_seconds(boost::timer::cpu_times times) {
  return std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::nanoseconds(times.wall));
}

}  // namespace

std::string human_readable_time(seconds_t duration) {
    using namespace std::chrono;

    auto hr = duration_cast<hours>(duration);
    duration -= hr;

    auto min = duration_cast<minutes>(duration);
    duration -= min;

    auto sec = duration_cast<seconds>(duration);

    std::stringstream ss;
    ss.fill('0');
    ss << std::setw(2) << hr.count() << " : " << std::setw(2) << min.count()
       << " : " << std::setw(2) << sec.count();

    return ss.str();
}

at::at(const std::string& title) :
    m_display_thread { [this]() { update(); } },
    m_running { true },
    m_title { title } {
    m_sw.start();
    tui::init_terminal();
    set_position(get_new_center());
}

at::~at() { m_display_thread.join(); }

void at::input_loop() {
    while (m_running) {
        auto input = tui::input();
        switch (input) {
            case KEY_RESIZE:
            case 'd': set_position(get_new_center()); break;
            case 'q': quit(); break;
            case 'r': reset(); break;
            case ' ': toggle_pause(); break;
        }
    }
}

void at::update() {
    while (m_running) {
        std::unique_lock<std::mutex> lock(m_mutex);
        auto time_string { human_readable_time(to_seconds(m_sw.elapsed())) };
        // draw time
        tui::print_at(m_position.x - time_string.size() / 2, m_position.y,
                      time_string);
        tui::render();
        m_cv.wait_for(lock, std::chrono::seconds(1),
                    [this]() { return m_should_update; });
        m_should_update = false;
    }
}

void at::quit() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_should_update = true;
        m_running       = false;
        m_final_time    = to_seconds(m_sw.elapsed());
        m_sw.stop();
        tui::end_terminal();
    }
    m_cv.notify_one();
}

void at::reset() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_sw.start();
        m_should_update = true;
    }
    m_cv.notify_one();
}

void at::toggle_pause() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (m_sw.is_stopped()) {
            m_sw.resume();
        } else {
            m_sw.stop();
        }
        m_should_update = true;
    }
    m_cv.notify_one();
}

void at::set_position(const tui::point& position) {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_should_update = true;
        m_position      = position;
        tui::clear();
        // redraw title
        tui::print_at(m_position.x - m_title.size() / 2, m_position.y - 1,
                      m_title);
        tui::render();
    }
    m_cv.notify_one();
}

seconds_t at::final_time() { return m_final_time; }

}  // namespace at
