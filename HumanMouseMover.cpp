#include "HumanMouseMover.h"

// Utility: Gets current mouse position
static POINT getMousePos() {
    POINT pt;
    GetCursorPos(&pt);
    return pt;
}

// Utility: Moves mouse instantly to (x, y)
static void setMousePos(int x, int y) {
    SetCursorPos(x, y);
}

// Utility: Linear interpolate
static double lerp(double a, double b, double t) {
    return a + (b - a) * t;
}

// Utility: Cubic Bézier interpolation
static POINT cubicBezier(POINT p0, POINT c1, POINT c2, POINT p3, double t) {
    double u = 1.0 - t;
    double tt = t * t;
    double uu = u * u;
    double uuu = uu * u;
    double ttt = tt * t;
    double x =
        uuu * p0.x +
        3 * uu * t * c1.x +
        3 * u * tt * c2.x +
        ttt * p3.x;
    double y =
        uuu * p0.y +
        3 * uu * t * c1.y +
        3 * u * tt * c2.y +
        ttt * p3.y;
    return POINT{ LONG(x), LONG(y) };
}

HumanMouseMover::HumanMouseMover() : stop_flag_(false) {}

HumanMouseMover::~HumanMouseMover() {
    stopMovementThread();
}

void HumanMouseMover::moveTo(int x, int y, const Options& opts) {
    std::lock_guard<std::mutex> lock(mutex_);
    stopMovementThread(); // Interrupt any running movement
    stop_flag_ = false;
    movement_thread_ = std::thread(&HumanMouseMover::movementThreadFn, this, x, y, opts);
}

void HumanMouseMover::interrupt() {
    std::lock_guard<std::mutex> lock(mutex_);
    stopMovementThread();
}

bool HumanMouseMover::isMoving() const {
    return movement_thread_.joinable();
}

void HumanMouseMover::setOnFinish(std::function<void()> cb) {
    std::lock_guard<std::mutex> lock(mutex_);
    on_finish_cb_ = cb;
}

void HumanMouseMover::stopMovementThread() {
    if (movement_thread_.joinable()) {
        stop_flag_ = true;
        movement_thread_.join();
        stop_flag_ = false;
    }
}

// Core movement routine
void HumanMouseMover::movementThreadFn(int targetX, int targetY, Options opts) {
    POINT p0 = getMousePos(), p3 = { targetX, targetY };
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<> rand01(-1.0, 1.0);

    // Randomized control points between p0 and p3
    auto randomOffset = [&](double scale) {
        int dx = int(rand01(rng) * scale);
        int dy = int(rand01(rng) * scale);
        return POINT{ p0.x + dx, p0.y + dy };
    };
    auto dist = [](POINT a, POINT b) {
        double dx = a.x - b.x;
        double dy = a.y - b.y;
        return sqrt(dx*dx + dy*dy);
    };

    double main_dist = dist(p0, p3);
    // Control points along the line but with perpendicular/random offset
    double ctrl_dist = main_dist * opts.curve_strength;
    double rand_scale = main_dist * opts.randomness;

    double ang = atan2(p3.y - p0.y, p3.x - p0.x);
    double perp = ang + 3.14159265 / 2.0;
    POINT c1 = {
        LONG(lerp(p0.x, p3.x, 0.3) + cos(perp)*ctrl_dist + rand_scale*rand01(rng)),
        LONG(lerp(p0.y, p3.y, 0.3) + sin(perp)*ctrl_dist + rand_scale*rand01(rng))
    };
    POINT c2 = {
        LONG(lerp(p0.x, p3.x, 0.7) - cos(perp)*ctrl_dist + rand_scale*rand01(rng)),
        LONG(lerp(p0.y, p3.y, 0.7) - sin(perp)*ctrl_dist + rand_scale*rand01(rng))
    };

    int total_steps = int(opts.duration_sec * opts.updates_per_sec);
    if (total_steps < 1) total_steps = 1;
    int sleep_ms = int(1000.0 / opts.updates_per_sec);

    for (int i = 1; i <= total_steps; ++i) {
        if (stop_flag_)
            break;
        double t = double(i) / total_steps;
        POINT pt = cubicBezier(p0, c1, c2, p3, t);
        setMousePos(pt.x, pt.y);
        Sleep(sleep_ms);
    }
    setMousePos(p3.x, p3.y); // ensure exact target

    // Notify on finish
    if (on_finish_cb_)
        on_finish_cb_();
}
