# tone-driver-sdl2

`tone-driver-sdl2` is a simple SDL2-based audio emulator that replicates a piezo buzzer's square wave tones. It provides a drop-in replacement for the `Sound::note(int n, int octave)` function, enabling PC playback of embedded game sounds.

## Features

- Generates square wave tones matching ATtiny frequency logic
- Plays game sound effects like `highScore()`, `gameOver()`, and `eating()`
- Cross-platform, minimal dependencies (requires SDL2)

## Directory Structure

```
├── CMakeLists.txt           # Build configuration
├── docs                     # Project documentation
│   └── html
├── Doxyfile
├── examples
│   └── test-tone.cpp        # Test by playing notes sequentially
├── include
│   ├── ToneDriver.h         # Abstract base interface
│   └── ToneDriverSDL2.h     # SDL2 implementation header
├── LICENSE
├── README.md
└── src                      # Implementation source files
    └── ToneDriverSDL2.cpp
```

## Usage

Build and run the included test program to hear sample tones:

```bash
mkdir build && cd build
cmake ..
make
./tone_driver_sdl2
```

## Integration
Replace the Sound::note method in your game code with the SDL2 implementation for PC testing without hardware.

## Dependencies
SDL2 library (https://www.libsdl.org/)

## Documentation

[View Documentation Locally](docs/html/index.html)  
**Note:** This link works when the repo is cloned locally and Doxygen docs have been generated.

[View Documentation Online](https://seanp2001.github.io/tone-driver-sdl2/)
