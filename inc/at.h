#ifndef __AT_AT_H__
#define __AT_AT_H__

#include "../inc/tui.h"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <boost/timer/timer.hpp>

namespace at {

using seconds_t = std::chrono::duration<long, std::ratio<1, 1>>;

std::string human_readable_time(seconds_t duration);

/**
 * Main class holding all the logic for manipulating
 * stopwatch, terminal display, and key input.
 */
class at {
public:
    at(const std::string& title);
    ~at();

    void       input_loop();
    seconds_t final_time();

private:
    void update();
    void set_position(const tui::point& posiiton);
    void quit();
    void reset();
    void toggle_pause();

    boost::timer::cpu_timer m_sw;
    tui::point              m_position;
    std::condition_variable m_cv;
    std::thread             m_display_thread;
    std::mutex              m_mutex;
    bool                    m_running;
    bool                    m_should_update;
    std::string             m_title;
    seconds_t               m_final_time;
};

}  // namespace at

#endif
