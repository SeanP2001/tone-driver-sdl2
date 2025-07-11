# tone-driver-sdl2

`tone-driver-sdl2` is a simple SDL2-based audio emulator that replicates the ATTiny piezo buzzer's square wave tones. It provides a drop-in replacement for the `Sound::note(int n, int octave)` function, enabling PC playback of embedded game sounds.

## Features

- Generates square wave tones matching ATTiny frequency logic
- Plays game sound effects like `highScore()`, `gameOver()`, and `eating()`
- Cross-platform, minimal dependencies (requires SDL2)

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
