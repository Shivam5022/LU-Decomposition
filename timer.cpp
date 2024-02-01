#include "timer.hpp"
#include <iomanip>
#include <iostream>

Timer::Timer() { startTime = std::chrono::high_resolution_clock::now(); }

Timer::~Timer() { stop(); }

void Timer::stop() {
    auto endTIme = std::chrono::high_resolution_clock::now();

    auto A = std::chrono::time_point_cast<std::chrono::microseconds>(startTime)
                 .time_since_epoch()
                 .count();
    auto B = std::chrono::time_point_cast<std::chrono::microseconds>(endTIme)
                 .time_since_epoch()
                 .count();

    auto duration = B - A;
    double ms = duration * 0.001;
    double sec = ms * 0.001;

    std::cout << duration << " us (" << ms << " ms) (" << std::setprecision(3)
              << sec << " seconds)\n";
}