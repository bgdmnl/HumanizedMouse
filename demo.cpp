#include "HumanMouseMover.h"
#include <windows.h>
#include <iostream>
#include <random>
#include <chrono>
#include <thread>

int getScreenWidth() {
    return GetSystemMetrics(SM_CXSCREEN);
}

int getScreenHeight() {
    return GetSystemMetrics(SM_CYSCREEN);
}

int main() {
    std::random_device rd;
    std::mt19937 rng(rd());
    int screenW = getScreenWidth();
    int screenH = getScreenHeight();

    std::uniform_int_distribution<int> xd(0, screenW - 1);
    std::uniform_int_distribution<int> yd(0, screenH - 1);
    std::uniform_real_distribution<double> speed_dist(0.4, 1.2);
    std::uniform_real_distribution<double> curve_dist(0.2, 0.5);

    HumanMouseMover mover;

    std::cout << "Demo: Mouse will move to random locations on screen." << std::endl;
    std::cout << "Press Ctrl+C or close this window to stop.\n" << std::endl;

    while (true) {
        int targetX = xd(rng);
        int targetY = yd(rng);

        HumanMouseMover::Options opts;
        opts.duration_sec = speed_dist(rng);   // random duration
        opts.randomness   = 0.15;              // fixed for realism
        opts.curve_strength = curve_dist(rng); // random curve
        opts.updates_per_sec = 120;

        std::cout << "Moving to: " << targetX << "," << targetY << " (duration " << opts.duration_sec << "s)\n";
        mover.moveTo(targetX, targetY, opts);

        // Wait for current move to (mostly) finish
        std::this_thread::sleep_for(std::chrono::duration<double>(opts.duration_sec + 0.1));
    }

    return 0;
}
