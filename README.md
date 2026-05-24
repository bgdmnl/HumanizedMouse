HumanizedMouse
A tiny C++ Windows demo library to move the mouse cursor in a human-like, natural manner using randomized Bézier curves instead of robotic jumps. It is suitable for other mouse automation projects or for demonstration/educational use.

Features
Human-like mouse motion: Follows a Bézier curve path, not a straight line.
Adjustable: Duration, randomness, curve strength, and step frequency can be set.
Interruptible: A new movement cancels/replaces the old one at any time.
Non-blocking: Mouse movement happens on a background thread, so the main program stays responsive.
Clean design: Simple, reusable C++ class with Win32 API. Well-commented for easy reuse or modification.
Simple demo: A console app lets you set target points and see the effect.
What Does It Do?
The library moves the Windows mouse cursor from its current position to the target (X, Y) using a smooth, slightly-randomized cubic Bézier curve. Each movement path is unique, simulating slight imperfections like a real human might have. The speed, smoothness, and curve are all configurable. You can use this class in larger automation systems, or just play with the included demo.

Files
HumanMouseMover.h – Library header.
HumanMouseMover.cpp – Library implementation.
demo.cpp – Text-based demo for interactive usage.
Windows Build Instructions
Clone the repo

git clone https://github.com/bgdmnl/HumanizedMouse.git
cd HumanizedMouse
Build using Visual Studio Developer Command Prompt:
For a quick command-line build (for example, using MSVC):

cl /EHsc demo.cpp HumanMouseMover.cpp /link user32.lib
Or, open the folder in Visual Studio, add the three files to a new Console Application project, and build.

Run the demo:

demo.exe
Enter a target X and Y coordinate in the console (e.g. 600 400), hit enter, and watch the mouse move smoothly to that point.

Usage Example (Library)
#include "HumanMouseMover.h"

int main() {
    HumanMouseMover mover;

    HumanMouseMover::Options opts;
    opts.duration_sec = 1.0;
    opts.randomness = 0.15;
    opts.curve_strength = 0.4;
    opts.updates_per_sec = 120;

    // Move mouse to (800, 450)
    mover.moveTo(800, 450, opts);

    // Optionally interrupt movement
    // mover.interrupt();
}
License
MIT 
