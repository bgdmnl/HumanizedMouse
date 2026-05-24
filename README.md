# 🖱️ HumanizedMouse

A lightweight C++ Windows library that simulates realistic, human-like mouse movement using randomized Bézier curves instead of robotic linear jumps.

Built for automation projects, input simulation, research, and educational purposes.

---

## ✨ Features

* 🎯 **Human-Like Movement**
  Smooth mouse paths generated using randomized cubic Bézier curves.

* ⚡ **Highly Configurable**
  Adjust movement duration, randomness, curve intensity, and update frequency.

* 🔄 **Interruptible Movements**
  Start a new movement at any time and automatically replace the previous one.

* 🧵 **Non-Blocking Architecture**
  Mouse movement runs on a background thread, keeping your main application responsive.

* 🛠️ **Clean & Reusable Design**
  Minimal Win32-based C++ implementation with clear structure and comments.

* 🧪 **Interactive Demo Included**
  Simple console application to test and visualize movement behavior.

---

# 📸 What Does It Do?

Instead of instantly teleporting the cursor or moving in perfectly straight robotic lines, **HumanizedMouse** generates smooth, slightly imperfect motion paths that resemble real human mouse movement.

Each movement:

* Starts from the current cursor position
* Generates randomized Bézier control points
* Creates a natural curved trajectory
* Updates cursor position smoothly over time

Every path is slightly unique, making movement appear much more natural.

---

# 📂 Project Structure

```text
HumanMouseMover.h      → Library header
HumanMouseMover.cpp    → Library implementation
demo.cpp               → Interactive console demo
```

---

# 🚀 Build Instructions (Windows)

## 1️⃣ Clone the Repository

```bash
git clone https://github.com/bgdmnl/HumanizedMouse.git
cd HumanizedMouse
```

---

## 2️⃣ Build Using MSVC

Open a **Visual Studio Developer Command Prompt** and run:

```bash
cl /EHsc demo.cpp HumanMouseMover.cpp /link user32.lib
```

---

## 3️⃣ Run the Demo

```bash
demo.exe
```

Enter target coordinates such as:

```text
600 400
```

The cursor will smoothly move to that position using a randomized human-like path.

---

# 💻 Usage Example

```cpp
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

    // Optional:
    // mover.interrupt();

    return 0;
}
```

---

# ⚙️ Configuration Options

| Option            | Description                          |
| ----------------- | ------------------------------------ |
| `duration_sec`    | Total movement duration              |
| `randomness`      | Random variation applied to the path |
| `curve_strength`  | Intensity of Bézier curve bending    |
| `updates_per_sec` | Cursor update frequency              |

---

# 🧠 How It Works

The library uses:

* Cubic Bézier interpolation
* Randomized control point generation
* Time-based cursor interpolation
* Background worker threading
* Win32 cursor APIs

This creates smooth, believable cursor motion instead of perfectly linear automation patterns.

---

# 📌 Use Cases

* Automation tools
* Input simulation research
* UI testing
* Accessibility experiments
* Human-like interaction systems
* Educational graphics/math demos

---

# ⚠️ Disclaimer

This project is intended for:

* Educational purposes
* Research
* Accessibility experiments
* Automation testing

Use responsibly and in compliance with all applicable software terms and policies.

---

# 📜 License

MIT License

See the `LICENSE` file for more information.

---

# ⭐ Contributing

Pull requests, improvements, and ideas are welcome.

If you find the project useful, consider giving it a star ⭐
