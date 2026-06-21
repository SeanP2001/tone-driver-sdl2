/// @file chord-scale.cpp
/// @brief Plays a major scale of chords via ToneDriverSDL2.

#include "tone-driver-sdl2/ToneDriverSDL2.h"
#include <iostream>

const int START_OCTAVE = 3;
const int NOTES_PER_CHORD = 3;
const int NOTES_PER_OCTAVE = 12;
const int REST_DURATION_MS = 100;
const int MAJOR_SCALE_INTERVALS[] = {2, 2, 1, 2, 2, 2, 1};


void incrementNote(NoteName& note, int& octave, int interval)
{
    int intNote = int(note);

    // Increment the note by the given interval (wrap around)
    if(intNote + interval > int(NoteName::B))
    {
        note = NoteName((intNote + interval) % NOTES_PER_OCTAVE);
        octave++;
    }
    else
    {
        note = NoteName(intNote + interval);
    }
}


void decrementNote(NoteName& note, int& octave, int interval)
{
    int intNote = int(note);

    // Decrement the note by the given interval (wrap around)
    if(intNote - interval < int(NoteName::C))
    {
        note = NoteName(((intNote - interval) + NOTES_PER_OCTAVE) % NOTES_PER_OCTAVE);
        octave--;
    }
    else
    {
        note = NoteName(intNote - interval);
    }
}


void printChordNotes(const NoteName notes[5], int noteCount)
{
    std::cout << "Playing Chord: ";
    for (int j = 0; j < noteCount; ++j)
    {
        std::cout << noteNameToString(notes[j]) << " ";
    }
    std::cout << std::endl;
}


int main() 
{
    // Initialise audio driver object
    ToneDriverSDL2 toneDriver;
    toneDriver.setAmplitude(0.5);

    // NoteName and octave arrays are expected to be of length 5
    // Only the first 3 notes will be used
    NoteName chordNotes[5] = {
        NoteName::C, 
        NoteName::E, 
        NoteName::G,
        NoteName::B,
        NoteName::D
    };
    int chordOctaves[5] = {
        START_OCTAVE, 
        START_OCTAVE, 
        START_OCTAVE,
        START_OCTAVE,
        START_OCTAVE + 1
    };

    // 7 Ascending intervals
    for (int i = 0; i < sizeof(MAJOR_SCALE_INTERVALS)/sizeof(MAJOR_SCALE_INTERVALS[0]); ++i)
    {
        // Print the notes in the chord
        printChordNotes(chordNotes, NOTES_PER_CHORD);

        // Play the chord
        toneDriver.playChord(chordNotes, chordOctaves, NOTES_PER_CHORD);
        toneDriver.rest(REST_DURATION_MS); 
        
        // Increment the notes to the next chord
        for (int j = 0; j < NOTES_PER_CHORD; ++j)
        {
            int interval = MAJOR_SCALE_INTERVALS[(i + (j*2)) % 7];
            incrementNote(chordNotes[j], chordOctaves[j], interval);
        }
    }

    // Print the notes in the chord
    printChordNotes(chordNotes, NOTES_PER_CHORD);

    // Play the tonic chord at the end of the ascending scale
    toneDriver.playChord(chordNotes, chordOctaves, NOTES_PER_CHORD);
    toneDriver.rest(REST_DURATION_MS * 4);

    std::cout << "-----------------------------" << std::endl;

    // Print the notes in the chord
    printChordNotes(chordNotes, NOTES_PER_CHORD);

    // Play the tonic chord again to start the descending scale
    toneDriver.playChord(chordNotes, chordOctaves, NOTES_PER_CHORD);
    toneDriver.rest(REST_DURATION_MS); 

    // 7 Descending intervals
    for (int i = sizeof(MAJOR_SCALE_INTERVALS)/sizeof(MAJOR_SCALE_INTERVALS[0]) - 1; i >= 0; --i)
    {
        // Decrement the notes to the next chord
        for (int j = 0; j < NOTES_PER_CHORD; ++j)
        {
            int interval = MAJOR_SCALE_INTERVALS[(i + (j*2)) % 7];
            decrementNote(chordNotes[j], chordOctaves[j], interval);
        }

        // Print the notes in the chord
        printChordNotes(chordNotes, NOTES_PER_CHORD);

        // Play the chord
        toneDriver.playChord(chordNotes, chordOctaves, NOTES_PER_CHORD);
        toneDriver.rest(REST_DURATION_MS); 
    }
}