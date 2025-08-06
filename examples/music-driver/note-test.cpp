/// @file note-test.cpp
/// @brief An example of playing higher-level Note objects via the MusicDriver.

#include "music-driver/MusicDriver.h" 
#include "tone-driver-sdl2/ToneDriverSDL2.h"
#include <iostream>

Note note(NoteName::C, 0); 
ToneDriverSDL2 toneDriver;

const int NOTE_DURATION_MS = 250;
const int REST_DURATION_MS = 100;

int main() 
{ 
    toneDriver.setAmplitude(0.5);

    while(note != Note(NoteName::B, 6))
    {
        std::cout << "Playing Note " << note.getNoteNameString() << " Octave " << std::to_string(note.getOctave()) << std::endl;
        playNote(toneDriver, note, NOTE_DURATION_MS);
        toneDriver.rest(REST_DURATION_MS);

        ++note;
    }
}