/// @file major-scale.cpp
/// @brief Plays a major scale via ToneDriverSDL2.

#include "ToneDriverSDL2.h"
#include <iostream>

const int START_OCTAVE = 3;
const int NO_OF_OCTAVES = 2;
const int NOTES_PER_OCTAVE = 12;
const int NOTE_DURATION_MS = 150;
const int REST_DURATION_MS = 50;
const int REST_BETWEEN_SCALES_MS = 200;
const int MAJOR_SCALE_INTERVALS[] = {2, 2, 1, 2, 2, 2, 1};

void playMajorScale(ToneDriver& driver, Note root, int startOctave, int octaves = 1)
{
    int note = root;
    int octave = startOctave;

    // Complete multiple octaves of the scale
    for(int octave_no = 0; octave_no < octaves; ++octave_no)
    {   
        // Each octave consists of 7 intervals
        for (int i = 0; i < sizeof(MAJOR_SCALE_INTERVALS)/sizeof(MAJOR_SCALE_INTERVALS[0]); ++i)
        {
            // Play the note
            std::cout << "Playing Note " << note << " Octave " << octave << std::endl;
            driver.playNote(static_cast<Note>(note % NOTES_PER_OCTAVE), octave, NOTE_DURATION_MS);
            driver.rest(REST_DURATION_MS); 
            
            // And then increment the note by the given interval (wrap around)
            if(note + MAJOR_SCALE_INTERVALS[i] > Note::B)
            {
                note = (note + MAJOR_SCALE_INTERVALS[i]) % NOTES_PER_OCTAVE;
                octave++;
            }
            else
            {
                note += MAJOR_SCALE_INTERVALS[i];
            }
        }
    }
    
    // Play the highest note of the scale
    std::cout << "Playing Note " << note << " Octave " << octave << std::endl;
    driver.playNote(static_cast<Note>(note % NOTES_PER_OCTAVE), octave, NOTE_DURATION_MS);
    driver.rest(REST_DURATION_MS);

    // Complete multiple decending octaves of the scale
    for(int octave_no = octaves; octave_no > 0; --octave_no)
    {
        // Each octave consists of 7 intervals
        for (int i = sizeof(MAJOR_SCALE_INTERVALS)/sizeof(MAJOR_SCALE_INTERVALS[0]) - 1; i >= 0; --i)
        {
            // Decrement the note by the given interval (wrap around)
            if(note - MAJOR_SCALE_INTERVALS[i] < Note::C)
            {
                note = ((note - MAJOR_SCALE_INTERVALS[i]) + NOTES_PER_OCTAVE) % NOTES_PER_OCTAVE;
                octave--;
            }
            else
            {
                note -= MAJOR_SCALE_INTERVALS[i];
            }

            // And play the note
            std::cout << "Playing Note " << note << " Octave " << octave << std::endl;
            driver.playNote(static_cast<Note>(note%NOTES_PER_OCTAVE), octave, NOTE_DURATION_MS);
            driver.rest(REST_DURATION_MS); 
        }
    } 
}



int main() 
{
    // Initialise audio driver object
    ToneDriverSDL2 toneDriver;

    toneDriver.setAmplitude(0.5);

    // Play each of the 12 major scales 
    for (int root = Note::C; root <= Note::B; ++root)
    {
        playMajorScale(toneDriver, static_cast<Note>(root), START_OCTAVE, NO_OF_OCTAVES);
        toneDriver.rest(REST_BETWEEN_SCALES_MS); 
    }
}