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
│   ├── music-driver                      # Examples of how to use the music-driver
│   └── tone-driver-sdl2                  # Examples of how to use the tone-driver (cross-platform)
│       ├── major-scale.cpp
│       ├── precomputed-frequencies.cpp
│       ├── test-frequencies.cpp
│       └── test-tone.cpp
├── include
│   ├── music-components
│   ├── music-driver
│   ├── NoteName.h
│   ├── tone-driver              # Abstract base interface
│   │   └── ToneDriver.h
│   └── tone-driver-sdl2         # SDL2 implementation
│       └── ToneDriverSDL2.h
├── LICENSE
├── README.md
└── src                          # Implementation source files
    ├── music-components
    ├── music-driver
    └── tone-driver-sdl2
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

Install by running the following command:

```bash
sudo apt install libsdl2-dev
```

## Documentation

[View Documentation](https://raw.githack.com/SeanP2001/tone-driver-sdl2/main/docs/html/index.html)
