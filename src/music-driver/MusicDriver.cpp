/// @file MusicDriver.cpp
/// @brief Implementation of the MusicDriver functions which allow higher level music component objects to be played via a ToneDriver.

#include "music-driver/MusicDriver.h"

void playNote(ToneDriver &driver, Note &note, int durationMs)
{
    driver.playNote(note.getNoteName(), note.getOctave(), durationMs);
}