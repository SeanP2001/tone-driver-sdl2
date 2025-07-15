/// @file ToneDriverSDL2.h
/// @brief Definition of the SDL2 implementation of the ToneDriver interface.

/*
ORIGINAL NOTE LOGIC
void Sound::note (int n, int octave)
{
  int prescaler = 8 + Clock - (octave + n/12);
  if (prescaler<1 || prescaler>15 || octave==0) prescaler = 0;
  DDRB = (DDRB & ~(1<<buzzerPin)) | (prescaler != 0)<<buzzerPin;
  OCR1C = pgm_read_byte(&scale[n % 12]) - 1;
  GTCCR = (buzzerPin == 4)<<COM1B0;
  TCCR1 = 1<<CTC1 | (buzzerPin == 1)<<COM1A0 | prescaler<<CS10;  
}
*/

// buzzerPin is used in the embedded constructor. Do I need my constructor to follow the same arguments despite not having a buzzer pin? NO, not needed

#ifndef TONE_DRIVER_SDL2_H
#define TONE_DRIVER_SDL2_H

#include <SDL2/SDL.h>
#include "tone-driver/ToneDriver.h"

/**
 * @class ToneDriverSDL2
 * @brief SDL2-based implmentation of the ToneDriver interface.
 * 
 * This implementation uses SDL's audio system to synthesize square waves
 * at given frequencies and amplitudes. It allows playing tones, notes,
 * chords, and arpeggios on desktop systems.
 */
class ToneDriverSDL2 : public ToneDriver
{
public:
    /** @brief Constructor. Initializes the SDL audio system. */
    ToneDriverSDL2();

    /** @copydoc ToneDriver::playFrequency(float) */
    void playFrequency(float freq) override;

    /** @copydoc ToneDriver::playFrequency(float, int) */
    void playFrequency(float freq, int durationMs) override;

    /** @copydoc ToneDriver::playNote(NoteName, int) */
    void playNote(NoteName note, int octave) override;

    /** @copydoc ToneDriver::playNote(NoteName, int, int) */
    void playNote(NoteName note, int octave, int durationMs) override;

    /** @copydoc ToneDriver::playChord */
    void playChord(const NoteName notes[5], const int octaves[5], int count) override;

    /** @copydoc ToneDriver::playArpeggio */
    void playArpeggio(const NoteName notes[5], const int octaves[5], int count, int noteDurationMs = DEFAULT_NOTE_DURATION_MS, int delayMs = DEFAULT_ARPEGGIO_DELAY_MS) override;

    /** @copydoc ToneDriver::playArpeggio */
    void stop() override;

    /** @copydoc ToneDriver::stopAfter */
    void stopAfter(int durationMs) override;

    /** @copydoc ToneDriver::rest */
    void rest(int durationMs) override;

    /**
     * @brief Set frequency directly.
     * 
     * @param freq Frequency in Hertz.
     */
    void setNoteFrequency(float freq);

    /**
     * @brief Set frequency from note and octave.
     * 
     * @param note Note (0–11).
     * @param octave Octave number (0–6).
     */
    void setNoteFrequency(NoteName note, int octave);

    /**
     * @brief Set the amplitude (volume) of the output tone.
     * 
     * @param amplitude Float from 0.0 to 1.0.
     */
    void setAmplitude(float amplitude);

    /** @copydoc ToneDriver::isValidNote */
    bool isValidNote(NoteName note, int octave) override;

    /** @brief Destructor. Closes SDL audio subsystem. */
    ~ToneDriverSDL2();

private:
    /**
     * @brief SDL audio callback function used to fill the audio buffer.
     * 
     * @param userdata Pointer to the ToneDriverSDL2 instance.
     * @param stream   Buffer to be filled with audio data.
     * @param len      Length of the buffer in bytes.
     * 
     * @details This function is passed to SDL and called repeatedly by the audio subsystem.
     */
    static void audioCallback(void* userdata, Uint8* stream, int len);

    /**
     * @brief Fills the audio buffer with a square wave based on current frequency and amplitude.
     *
     * @param stream Audio buffer to write to.
     * @param len    Length of the audio buffer in bytes.
     */
    void generateSquareWave(Uint8* stream, int len);

    /**
     * @brief Computes the semitone distance between two notes across octaves.
     *
     * @param note1 The note of the first frequency
     * @param octave1 the octave of the first frequency
     * @param note2 The note of the second frequency
     * @param octave2 The octave of the second frequency
     * 
     * @returns Positive or negative number of semitones between the two pitches.
     */
    int getSemitonesDiff(NoteName note1, int octave1, NoteName note2, int octave2);

    float currentFrequency = 0.0f;  ///< Currently playing frequency (Hz).
    float currentAmplitude = 0.85f; ///< Current volume (0.0 to 1.0).
    int remainingSamples = 0;       ///< Remaining samples for timed playback.
    int timeIndex = 0;              ///< Sample index used to track waveform phase.

    const static int SAMPLE_RATE;   ///< Audio sample rate in Hz.
    const static int REF_FREQ;      ///< Frequency reference (usually A4 = 440Hz).
    const static NoteName REF_NOTE; ///< Reference note (usually A).
    const static int REF_OCTAVE;    ///< Octave of reference note (usually 4).
};

#endif // TONE_DRIVER_SDL2_H