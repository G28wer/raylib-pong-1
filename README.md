# Raylib Pong

A simple Pong clone written in C++ using [Raylib](https://www.raylib.com/).
Demonstrates OOP, collision detection, and basic game mechanics.

---

## 🎮 Features

- Ball and paddle implemented as C++ classes
- Player-controlled paddle (keyboard input)
- CPU paddle (basic AI can be added)
- Score tracking for Player and CPU
- Collision detection with screen bounds and paddles
- Buildable on Linux, macOS, and Windows with Raylib included as a submodule

---


## 💻 Build Instructions

### Step 1 — Clone the repo with submodules

```bash
git clone --recursive git@github.com:void627/raylib-pong.git
cd raylib-pong
./build.sh
