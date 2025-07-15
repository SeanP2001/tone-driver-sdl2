/// @file ToneDriver.h
/// @brief Definition of the abstract base class for the ToneDriver interface.

#ifndef TONE_DRIVER_H
#define TONE_DRIVER_H

#include "NoteName.h"

/**
 * @class ToneDriver
 * @brief Abstract interface for tone generation across platforms.
 *
 * This interface defines a set of virtual methods for playing individual tones,
 * notes, chords, arpeggios, and silences across a variety of implementations.
 * 
 * It provides a consistent API for both embedded systems and desktop environments.
 *
 * Concrete implementations (e.g., ToneDriverSDL2) must override all methods.
 */
class ToneDriver 
{
public:
    /**
     * @brief Plays a tone at a specific frequency indefinitely.
     * 
     * @param freq Frequency in Hertz.
     * 
     * @note Must be manually stopped via stop() or stopAfter().
     */
    virtual void playFrequency(float freq) = 0;

    /**
     * @brief Play a tone at a given frequency for a fixed duration.
     * 
     * @param freq Frequency in Hertz.
     * @param durationMs Note duration in milliseconds.
     */
    virtual void playFrequency(float freq, int durationMs) = 0;

    /**
     * @brief Play a musical note at a specific octave indefinitely.
     * 
     * @param note Note value (0–11) using the NoteName enum.
     * @param octave Octave number (0–6).
     */
    virtual void playNote(NoteName note, int octave) = 0;

    /**
     * @brief Play a musical note for a specific duration.
     * 
     * @param note Note value (0–11) using the NoteName enum.
     * @param octave Octave number (0–6).
     * @param durationMs Note duration in milliseconds.
     */
    virtual void playNote(NoteName note, int octave, int durationMs) = 0;

    /**
     * @brief Play a chord consisting of up to MAX_POLYPHONY notes.
     * 
     * @param notes    Array of notes to play.
     * @param octaves  Array of octave values corresponding to each note.
     * @param count    Number of notes (1 to MAX_POLYPHONY).
     * 
     * @note The actual implementation may simulate chords as fast arpeggios.
     */
    virtual void playChord(const NoteName notes[5], const int octaves[5], int count) = 0;

    /**
     * @brief Play a sequence of notes in succession to simulate an arpeggio.
     * 
     * @param notes    Array of notes to play.
     * @param octaves  Array of octave values corresponding to each note.
     * @param count    Number of notes (1 to MAX_POLYPHONY).
     * @param noteDurationMs Duration of each note in milliseconds.
     * @param delayMs Delay between each note in milliseconds. 
     */
    virtual void playArpeggio(const NoteName notes[5], const int octaves[5], int count, int noteDurationMs = DEFAULT_NOTE_DURATION_MS, int delayMs = DEFAULT_ARPEGGIO_DELAY_MS) = 0;

    /**
     * @brief Immediately stop playing any current tone.
     */
    virtual void stop() = 0;

    /**
     * @brief Stop playing after a set delay.
     * 
     * @param durationMs Delay in milliseconds before stopping.
     */
    virtual void stopAfter(int durationMs) = 0;

    /**
     * @brief Pause sound for a given amount of time.
     * 
     * @param durationMs Duration of silence in milliseconds.
     */
    virtual void rest(int durationMs) = 0;

    /**
     * @brief Check if a note-octave combination is within valid range.
     * 
     * @param note Note value.
     * @param octave Octave value.
     * 
     * @return true if the note is valid, false otherwise.
     */
    virtual bool isValidNote(NoteName note, int octave) = 0;

    /**
     * @brief Virtual default destructor for the ToneDriver interface.
     *
     * This destructor is declared as `virtual` to ensure that when an object
     * derived from ToneDriver is deleted through a base class pointer,
     * the correct destructor for the derived class is invoked.
     *
     * This is critical for proper cleanup in polymorphic class hierarchies,
     * especially when the derived class allocates resources that need to be
     * released during destruction. Without a virtual destructor, only the base
     * class's destructor would be called, leading to undefined behavior and
     * potential memory/resource leaks.
     *
     * The `= default` specifier tells the compiler to generate a default
     * destructor implementation, which is appropriate here because the base
     * class does not manage any resources itself and does not require custom
     * destruction logic.
     *
     * Even though the class does not currently perform cleanup, explicitly
     * declaring a virtual destructor makes the interface safe and extensible
     * for future implementations and derived classes.
     */
    virtual ~ToneDriver() = default;



protected:
    static constexpr int DEFAULT_CHORD_ARPEGGIO_DELAY_MS = 10; /// Delay between notes when using an arpeggio to simulate playing a chord
    static constexpr int DEFAULT_NOTE_DURATION_MS = 100;       /// Default note duration
    static constexpr int DEFAULT_ARPEGGIO_DELAY_MS = 100;      /// Delay between notes in an arpeggio
    static constexpr int MAX_POLYPHONY = 5;                    /// Maximum number of notes supported in a chord or arpeggio
    static constexpr int MAX_OCTAVE = 6;                       /// Maximum octave index supported (inclusive). Valid range: 0–6.
};

#endif // TONE_DRIVER_H