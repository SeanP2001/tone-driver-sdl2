/// @file test-tone.cpp
/// @brief Tests that every note within the range plays via ToneDriverSDL2.

#include "tone-driver-sdl2/ToneDriverSDL2.h"
#include <iostream>

const int MIN_OCTAVE = 1;
const int MAX_OCTAVE = 6;
const int NOTES_PER_OCTAVE = 12;
const int NOTE_DURATION_MS = 250;
const int REST_DURATION_MS = 100;

int main() 
{
    // Initialise audio driver object
    ToneDriverSDL2 toneDriver;

    toneDriver.setAmplitude(0.5);

    //toneDriver.playNote(Note::A, 4, NOTE_DURATION_MS);

    for(int octave = MIN_OCTAVE; octave <= MAX_OCTAVE; ++octave)
    {
        for (int note = NoteName::C; note <= NoteName::B; ++note)
        {
            std::cout << "Playing Note " << toString(static_cast<NoteName>(note)) << " Octave " << octave << std::endl;
            toneDriver.playNote(static_cast<NoteName>(note), octave, NOTE_DURATION_MS);
            toneDriver.rest(REST_DURATION_MS); 
        }
    }
}