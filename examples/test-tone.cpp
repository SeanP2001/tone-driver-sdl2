/// @file test-tone.cpp
/// @brief Tests that every note within the range plays via ToneDriverSDL2.

#include "ToneDriverSDL2.h"
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
        for (int note = Note::C; note <= Note::B; ++note)
        {
            std::cout << "Playing Note " << note << " Octave " << octave << std::endl;
            toneDriver.playNote(static_cast<Note>(note), octave, NOTE_DURATION_MS);
            toneDriver.rest(REST_DURATION_MS); 
        }
    }
}