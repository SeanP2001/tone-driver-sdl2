#ifndef TONE_DRIVER_H
#define TONE_DRIVER_H

/**
 * @class ToneDriver
 * @brief Abstract interface for generating tones.
 */
class ToneDriver {
public:
    /**
     * @brief Play a note from the scale.
     * @param n Note index (0-11)
     * @param octave Octave number (1-6)
     */
    virtual void note(int n, int octave) = 0;

    /// Stop the currently playing note
    virtual void stop() = 0;

    virtual ~ToneDriver() = default;
};

#endif // TONE_DRIVER_H