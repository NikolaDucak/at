#include "../inc/at.h"

namespace at {

// anonymous helpers
namespace {

tui::point get_new_center() {
    auto x = tui::term_size();
    return { x.x / 2, x.y / 2 };
}

}  // namespace

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
        }
    }
}

void at::update() {
    while (m_running) {
        std::unique_lock<std::mutex> lock(m_mutex);
        auto time_string { human_readable_time(m_sw.elapsed_time()) };
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
        m_final_time    = m_sw.elapsed_time();
        m_sw.stop();
        tui::end_terminal();
    }
    m_cv.notify_one();
}

void at::reset() {
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_sw.reset();
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

duration_t at::final_time() { return m_final_time; }

}  // namespace at
