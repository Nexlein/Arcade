<div align="center">
  <h1>🕹️ Arcade</h1>
  <p><strong>A modular gaming architecture built in C++</strong></p>
</div>

## Overview

Arcade is a fully modular gaming platform. It dynamically loads game logic libraries (like *Snake* or *SolarFox*) and graphics backend libraries (like *SDL2*, *Allegro5*, or *NCURSES*) at runtime using shared objects (`.so`) and `dlopen`.

This architecture allows you to swap graphics engines or switch games entirely on the fly without ever recompiling or restarting the core application.

## Features

- **Dynamic Loading:** Hot-swappable games and displays at runtime.
- **Multiple Backends:** Supports graphical (SDL2, Allegro5) and terminal-based (NCURSES) displays.
- **Classic Games:** Play modular versions of classic games Snake and SolarFox.
- **Strict OOP:** Built with rigorous Object-Oriented Programming principles using C++ interfaces.

## Installation

The project uses CMake. Build dependencies:

- `cmake`, a C++ compiler and `pkg-config`
- **ncurses** (`libncurses-dev`): required
- **SDL2**, **SDL2_image** and **SDL2_ttf** (`libsdl2-dev`, `libsdl2-image-dev`, `libsdl2-ttf-dev`)
- **Allegro 5** with its image, TTF and primitives addons (`liballegro5-dev`, `liballegro-image5-dev`, `liballegro-ttf5-dev`)
- **Criterion** (optional, for the unit tests)

If SDL2 or Allegro 5 are not found on the system, CMake downloads and builds them with `FetchContent` (slower first build, needs network access).

On Debian/Ubuntu, `setup.sh` installs the system packages (ncurses, Allegro 5, X11/Wayland/audio headers) and Criterion:

```bash
./setup.sh
```

```bash
# Generate build files
cmake -B build

# Compile the core and all modules
cmake --build build
```

## Creating a New Module

Because of its strict interface-driven design, you can easily add your own custom games or graphics libraries without changing the core!

1. **Include the Interface**: Inherit from either `IGameModule` or `IDisplayModule`.
2. **Implement the Logic**: Write your C++ logic to satisfy all virtual methods.
3. **Add the Entry Point**: You MUST provide an `extern "C"` function named `entryPoint` that returns a newly allocated instance of your class so the core can `dlopen` it.

   ```cpp
   extern "C" IGameModule* entryPoint() {
       return new MyAwesomeGame();
   }
   ```

4. **Compile to Shared Object**: Add it to the `CMakeLists.txt` using the `add_arcade_module` macro to compile it as an `arcade_xxx.so` file inside the `lib/` directory.

## How to Run

Launch the arcade by passing the path to the initial graphics library you want to use.

```bash
./arcade ./lib/arcade_sdl2.so
```

Once inside the arcade:

- Use the **Menu** to select your game and graphics backend.
- You can dynamically switch the display library or the active game while playing using the designated hotkeys [1, 2, 3, 4] !
