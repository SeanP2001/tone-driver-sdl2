/// @file minor-scale.cpp
/// @brief Plays a minor scale via ToneDriverSDL2.

#include "tone-driver-sdl2/ToneDriverSDL2.h"
#include <iostream>

const int START_OCTAVE = 3;
const int NO_OF_OCTAVES = 2;
const int NOTES_PER_OCTAVE = 12;
const int NOTE_DURATION_MS = 150;
const int REST_DURATION_MS = 50;
const int REST_BETWEEN_SCALES_MS = 200;
const int MINOR_SCALE_INTERVALS[] = {2, 1, 2, 2, 1, 2, 2};

void playMinorScale(ToneDriver& driver, NoteName root, int startOctave, int octaves = 1)
{
    int note = int(root);
    int octave = startOctave;

    // Complete multiple octaves of the scale
    for(int octave_no = 0; octave_no < octaves; ++octave_no)
    {   
        // Each octave consists of 7 intervals
        for (int i = 0; i < sizeof(MINOR_SCALE_INTERVALS)/sizeof(MINOR_SCALE_INTERVALS[0]); ++i)
        {
            // Play the note
            std::cout << "Playing Note " << noteNameToString(static_cast<NoteName>(note)) << " Octave " << octave << std::endl;
            driver.playNote(static_cast<NoteName>(note % NOTES_PER_OCTAVE), octave, NOTE_DURATION_MS);
            driver.rest(REST_DURATION_MS); 
            
            // And then increment the note by the given interval (wrap around)
            if(note + MINOR_SCALE_INTERVALS[i] > int(NoteName::B))
            {
                note = (note + MINOR_SCALE_INTERVALS[i]) % NOTES_PER_OCTAVE;
                octave++;
            }
            else
            {
                note += MINOR_SCALE_INTERVALS[i];
            }
        }
    }
    
    // Play the highest note of the scale
    std::cout << "Playing Note " << noteNameToString(static_cast<NoteName>(note)) << " Octave " << octave << std::endl;
    driver.playNote(static_cast<NoteName>(note % NOTES_PER_OCTAVE), octave, NOTE_DURATION_MS);
    driver.rest(REST_DURATION_MS);

    // Complete multiple decending octaves of the scale
    for(int octave_no = octaves; octave_no > 0; --octave_no)
    {
        // Each octave consists of 7 intervals
        for (int i = sizeof(MINOR_SCALE_INTERVALS)/sizeof(MINOR_SCALE_INTERVALS[0]) - 1; i >= 0; --i)
        {
            // Decrement the note by the given interval (wrap around)
            if(note - MINOR_SCALE_INTERVALS[i] < int(NoteName::C))
            {
                note = ((note - MINOR_SCALE_INTERVALS[i]) + NOTES_PER_OCTAVE) % NOTES_PER_OCTAVE;
                octave--;
            }
            else
            {
                note -= MINOR_SCALE_INTERVALS[i];
            }

            // And play the note
            std::cout << "Playing Note " << noteNameToString(static_cast<NoteName>(note)) << " Octave " << octave << std::endl;
            driver.playNote(static_cast<NoteName>(note%NOTES_PER_OCTAVE), octave, NOTE_DURATION_MS);
            driver.rest(REST_DURATION_MS); 
        }
    } 
}



int main() 
{
    // Initialise audio driver object
    ToneDriverSDL2 toneDriver;

    toneDriver.setAmplitude(0.5);

    // Play each of the 12 minor scales 
    for (int root = int(NoteName::C); root <= int(NoteName::B); ++root)
    {
        std::cout << "-------------------------------------------------\n\n";
        std::cout << "*** " << noteNameToString(static_cast<NoteName>(root)) << " Minor Scale ***\n";
        playMinorScale(toneDriver, static_cast<NoteName>(root), START_OCTAVE, NO_OF_OCTAVES);
        toneDriver.rest(REST_BETWEEN_SCALES_MS); 
    }
}