/// @file ToneDriverSDL2.cpp
/// @brief SDL2 implementation of the ToneDriver interface.

#include <iostream>   
#include "tone-driver-sdl2/ToneDriverSDL2.h"

const int ToneDriverSDL2::SAMPLE_RATE = 44100;
const int ToneDriverSDL2::REF_FREQ = 440;
const NoteName ToneDriverSDL2::REF_NOTE = NoteName::A;
const int ToneDriverSDL2::REF_OCTAVE = 4;


ToneDriverSDL2::ToneDriverSDL2()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init failed: " << SDL_GetError() << std::endl;
        //return 1;
    }

    SDL_AudioSpec spec;
    SDL_zero(spec);
    spec.freq = SAMPLE_RATE;
    spec.format = AUDIO_S16SYS;
    spec.channels = 1;
    spec.samples = 1024;
    spec.callback = audioCallback;
    spec.userdata = this; 

    if (SDL_OpenAudio(&spec, NULL) < 0) {
        std::cerr << "SDL_OpenAudio failed: " << SDL_GetError() << std::endl;
        //return 1;
    }
}

void ToneDriverSDL2::playFrequency(float freq)
{
    timeIndex = 0;          // Reset playback phase
    setNoteFrequency(freq); // Set the note frequency
    SDL_PauseAudio(0);      // Start audio playback
}

void ToneDriverSDL2::playFrequency(float freq, int durationMs)
{
    timeIndex = 0;          // Reset playback phase 
    setNoteFrequency(freq); // Set the note frequency
    SDL_PauseAudio(0);      // Start audio playback
    stopAfter(durationMs);  // Stop audio playback after a given duration
}

void ToneDriverSDL2::playNote(NoteName note, int octave)
{
    if (isValidNote(note, octave))
    {
        timeIndex = 0;                  // Reset playback phase
        setNoteFrequency(note, octave); // Set the note frequency
        SDL_PauseAudio(0);              // Start audio playback
    }
}

void ToneDriverSDL2::playNote(NoteName note, int octave, int durationMs)
{  
    if (isValidNote(note, octave))
    {
        timeIndex = 0;                  // Reset playback phase 
        setNoteFrequency(note, octave); // Set the note frequency
        SDL_PauseAudio(0);              // Start audio playback
        stopAfter(durationMs);          // Stop audio playback after a given duration
    }
}

void ToneDriverSDL2::playChord(const NoteName notes[MAX_POLYPHONY], const int octaves[MAX_POLYPHONY], int count)
{
    playArpeggio(notes, octaves, count, DEFAULT_CHORD_ARPEGGIO_DELAY_MS);
}

void ToneDriverSDL2::playArpeggio(const NoteName notes[MAX_POLYPHONY], const int octaves[MAX_POLYPHONY], int count, int noteDurationMs, int delayMs)
{
    if(count > 0 && count <= MAX_POLYPHONY)
    {
        for(int i = 0; i < count; ++i)
        {
            playNote(notes[i], octaves[i], noteDurationMs);
            rest(delayMs);                              
        }
    }
    else
    {
        std::cerr << count << " is not a valid number of notes! Chords and arpeggios can have between 1 and " << MAX_POLYPHONY << " notes." << std::endl;
    }
}

void ToneDriverSDL2::stop()
{
    SDL_PauseAudio(1);     // Pause audio playback
    //SDL_CloseAudio();    // Stop audio playback
}

void ToneDriverSDL2::stopAfter(int durationMs)
{
    SDL_Delay(durationMs); // Play for the given duration (blocks thread. Aim to either use non-blocking timer or spawn thread to sleep and then call stop) (SDL_AddTimer()?)
    stop();                // Stop audio playback
}

void ToneDriverSDL2::rest(int durationMs)
{
    stop();                   // Stop audio playback
    SDL_Delay(durationMs);    // Wait for a given delay (Temporary solution - might implement with non-blocking timer)
}

void ToneDriverSDL2::audioCallback(void* userdata, Uint8* stream, int len)
{
    auto* driver = static_cast<ToneDriverSDL2*>(userdata);
    driver->generateSquareWave(stream, len);
}

void ToneDriverSDL2::generateSquareWave(Uint8* stream, int len)
{
    Sint16* buffer = (Sint16*)stream;
    int samples = len / 2; // 2 bytes per sample (16-bit audio)

    for (int i = 0; i < samples; ++i, ++timeIndex) {
        double t = (double)timeIndex / SAMPLE_RATE;
        double wave = (sin(2.0 * M_PI * currentFrequency * t) > 0) ? 1.0 : -1.0;
        buffer[i] = (Sint16)(32767 * currentAmplitude * wave);
    }
}

int ToneDriverSDL2::getSemitonesDiff(NoteName note1, int octave1, NoteName note2, int octave2)
{
    return (int(note2) + (12 * octave2)) - (int(note1) + (12 * octave1));
}

void ToneDriverSDL2::setNoteFrequency(float freq)
{
    currentFrequency = freq;
}

void ToneDriverSDL2::setNoteFrequency(NoteName note, int octave)
{
    // should isValidNote be happening in here rather than in playNote?
    currentFrequency = REF_FREQ * pow(2, getSemitonesDiff(REF_NOTE, REF_OCTAVE, note, octave) / 12.0);
}

void ToneDriverSDL2::setAmplitude(float amplitude)
{
    if (amplitude < 0.0f) amplitude = 0.0f;
    if (amplitude > 1.0f) amplitude = 1.0f;
    currentAmplitude = amplitude;
}

bool ToneDriverSDL2::isValidNote(NoteName note, int octave)
{
    if (note < NoteName::C || note > NoteName::B) {
        std::cerr << int(note) << " is not a valid note! Notes range from 0 to 11 (C to B)" << std::endl;
        return false;
    }
    if (octave < 0 || octave > MAX_OCTAVE) {
        std::cerr << octave << " is not a valid octave! Octaves range from 0 to " << MAX_OCTAVE << std::endl;
        return false;
    }

    return true;
}

ToneDriverSDL2::~ToneDriverSDL2()
{
    // Shut down the SDL audio subsystem
    SDL_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}