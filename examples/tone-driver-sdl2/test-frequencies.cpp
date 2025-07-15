/// @file test-frequencies.cpp
/// @brief Sweeps through a range of frequencies and plays them via ToneDriverSDL2. 

#include "tone-driver-sdl2/ToneDriverSDL2.h"
#include <iostream>

const int MIN_FREQ = 16;
const int MAX_FREQ = 1975;
const int NOTE_DURATION_MS = 10;

int main() 
{
    // Initialise audio driver object
    ToneDriverSDL2 toneDriver;

    toneDriver.setAmplitude(0.5);

    //toneDriver.playNote(Note::A, 4, NOTE_DURATION_MS);

    for(int freq = MIN_FREQ; freq <= MAX_FREQ; ++freq)
    {
        if(freq % 10 == 0)
        {
            std::cout << freq << " Hz\n";
        }
        
        toneDriver.playFrequency(freq, NOTE_DURATION_MS);
    }
}