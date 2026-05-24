#pragma once

#include <atomic>
#include <functional>
#include <thread>
#include <mutex>
#include <random>
#include <Windows.h>

// Class for smooth Bézier mouse movements, non-blocking, customizable, and interruptible.
class HumanMouseMover {
public:
    struct Options {
        double duration_sec = 0.7;        // Move duration in seconds
        double randomness = 0.2;          // Position randomization factor [0..1]
        double curve_strength = 0.5;      // Controls Bézier "arch"
        int    updates_per_sec = 120;     // How many updates per second (smoothness)
    };

    HumanMouseMover();
    ~HumanMouseMover();

    // Start a new movement to (x, y) with given options (interrupts current move).
    void moveTo(int x, int y, const Options& opts = Options());

    // Interrupts any current movement immediately.
    void interrupt();

    // Returns true if a movement is currently in progress.
    bool isMoving() const;

    // For testing: set callback to be called after movement finishes/interrupted
    void setOnFinish(std::function<void()> cb);

private:
    void movementThreadFn(int x, int y, Options opts);
    void stopMovementThread();

    mutable std::mutex mutex_;
    std::thread movement_thread_;
    std::atomic<bool> stop_flag_;
    std::function<void()> on_finish_cb_;
};
