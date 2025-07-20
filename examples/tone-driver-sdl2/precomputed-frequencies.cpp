/// @file precomputed-frequencies.cpp
/// @brief Looks up the note frequncies in a 2D array and plays the frequency via ToneDriverSDL2. Useful for reducing compute overhead.


#include "tone-driver-sdl2/ToneDriverSDL2.h"
#include <iostream>

const int MIN_OCTAVE = 1;
const int MAX_OCTAVE = 6;
const int NOTES_PER_OCTAVE = 12;
const int NOTE_DURATION_MS = 250;
const int REST_DURATION_MS = 100;

const float frequencies[NOTES_PER_OCTAVE][MAX_OCTAVE+1] ={
{16.35, 32.7,   65.41,  130.81, 261.63, 523.25, 1046.5 },   // C
{17.32, 34.65,  69.3,   138.59, 277.18, 554.37, 1108.73},   // C#
{18.35, 36.71,  73.42,  146.83, 293.66, 587.33, 1174.66},   // D
{19.45, 38.89,  77.78,  155.56, 311.13, 622.25, 1244.51},   // D#
{20.6,  41.2,   82.41,  164.81, 329.63, 659.25, 1318.51},   // E
{21.83, 43.65,  87.31,  174.61, 349.23, 698.46, 1396.91},   // F
{23.12, 46.25,  92.5,   185,    369.99, 739.99, 1479.98},   // F#
{24.5,  49,     98,     196,    392,    783.99, 1567.98},   // G
{25.96, 51.91,  103.83, 207.65, 415.3,  830.61, 1661.22},   // G#
{27.5,  55,     110,    220,    440,    880,    1760   },   // A
{29.14, 58.27,  116.54, 233.08, 466.16, 932.33, 1864.66},   // A#
{30.87, 61.74,  123.47, 246.94, 493.88, 987.77, 1975.53}};  // B


int main() 
{
    // Initialise audio driver object
    ToneDriverSDL2 toneDriver;

    toneDriver.setAmplitude(0.5);

    for(int octave = MIN_OCTAVE; octave <= MAX_OCTAVE; ++octave)
    {
        for (int note = int(NoteName::C); note <= int(NoteName::B); ++note)
        {
            std::cout << "Playing Note " << noteNameToString(static_cast<NoteName>(note)) << " Octave " << octave << " (" << frequencies[note][octave] << " Hz)" << std::endl;
            toneDriver.playFrequency(frequencies[note][octave], NOTE_DURATION_MS);
            toneDriver.rest(REST_DURATION_MS); 
        }
    }
}