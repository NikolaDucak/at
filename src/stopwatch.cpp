#include "../inc/stopwatch.h"

namespace at{

stopwatch::stopwatch() : m_running { false } {}

void stopwatch::start() {
    m_running = true;
    m_start   = clock_t::now();
}

void stopwatch::stop() {
    if (not m_running) return;
    m_running = false;
    m_end     = clock_t::now();
}

void stopwatch::reset() {
    if (not m_running) return;
    m_start = clock_t::now();
}

duration_t stopwatch::elapsed_time() {
    if (not m_running) return duration_t {};
    time_t curr = clock_t::now();
    return std::chrono::duration_cast<std::chrono::seconds>(curr - m_start);
}

std::string human_readable_time(duration_t duration) {
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

}  // namespace at
