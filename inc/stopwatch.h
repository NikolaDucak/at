#ifndef __AT_STOPWATCH_H__
#define __AT_STOPWATCH_H__

#include <chrono>
#include <iomanip>
#include <sstream>

namespace at {

using clock_t    = std::chrono::system_clock;
using time_t     = std::chrono::time_point<clock_t>;
using duration_t = std::chrono::duration<long, std::ratio<1, 1>>;

/**
 * Simple stopwatch class based on calculating the difference
 * between time point of stopwatch::start() call and clock_t::now();
 */
class stopwatch {
public:
    stopwatch();
    void       start();
    void       stop();
    void       reset();
    duration_t elapsed_time();

private:
    bool   m_running;
    time_t m_start, m_end;
};

/**
 * Utility function providing string represantation of `duration_t`
 * in "HH : MM : SS" format.
 */
std::string human_readable_time(duration_t duration);

}  // namespace at

#endif
