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

class at {
public:
    at(const std::string& title);

    void      input_loop();
    seconds_t final_time();

private:
    void draw();

    void set_position(const tui::point& posiiton);
    void quit();
    void reset();
    void toggle_pause();

    boost::timer::cpu_timer m_sw;
    tui::point              m_terminal_center;
    bool                    m_running;
    std::string             m_title;
    seconds_t               m_final_time;
};

}  // namespace at

#endif
