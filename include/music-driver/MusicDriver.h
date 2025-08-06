/// @file MusicDriver.h
/// @brief Definition of the MusicDriver functions which allow higher level music component objects to be played via a ToneDriver.

#ifndef MUSIC_DRIVER_H
#define MUSIC_DRIVER_H

#include "tone-driver/ToneDriver.h" 
#include "music-components/Note.h"
#include "music-components/NoteEvent.h"
#include "music-components/Chord.h"
#include "music-components/ChordEvent.h"
#include "music-components/Key.h"
#include "music-components/Scale.h"
 
/**
 * @brief Plays a Note object via a ToneDriver for a given duration.
 * 
 * @param driver The ToneDriver object to use to play the note.
 * @param note A Note object which represents the note to be played.
 * @param durationMs How long to play the note for (in ms). 
 */
void playNote(ToneDriver &driver, Note &note, int durationMs);

//void playNoteEvent(ToneDriver &driver, NoteEvent &noteEvent);

//void playChord(ToneDriver &driver, Chord &chord, int durationMs);
//void playChordEvent(ToneDriver &driver, ChordEvent &chordEvent);

//void playArpeggio(ToneDriver &driver, Chord &chord, int totalDurationMs);

//void playScale(ToneDriver &driver, Key &key, int octaves);

#endif // MUSIC_DRIVER_H