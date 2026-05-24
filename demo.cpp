#include "HumanMouseMover.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand((unsigned)std::time(nullptr));

    HumanMouseMover mover;

    std::cout << "HumanMouseMover demo - Bézier, random, interruptible\n";
    std::cout << "Type target X and Y (or 'q' to quit)\n";

    for (;;) {
        std::string line;
        std::cout << "\nTarget X Y: ";
        std::getline(std::cin, line);

        if (line.empty() || line[0] == 'q')
            break;

        int tx, ty;

        if (sscanf_s(line.c_str(), "%d %d", &tx, &ty) == 2) {
            HumanMouseMover::Options opts;

            opts.duration_sec = 0.6 + 0.8 * (std::rand() / double(RAND_MAX));
            opts.randomness = 0.13;
            opts.curve_strength = 0.35;
            opts.updates_per_sec = 120;

            std::cout << "Moving mouse to: " << tx << "," << ty << "\n";
            mover.moveTo(tx, ty, opts);
        }
        else {
            std::cout << "Parse error. Usage: <x> <y>\n";
        }
    }

    mover.interrupt();
    return 0;
}