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
- **Classic Games:** Play modular versions of classic games like Snake, Pacman, or SolarFox.
- **Strict OOP:** Built with rigorous Object-Oriented Programming principles using C++ interfaces.

## Installation

The project uses CMake for easy compilation. Make sure you have `cmake` and your preferred graphics libraries installed (e.g., `libsdl2-dev`, `libncurses-dev`).

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
