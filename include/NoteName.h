/// @file NoteName.h
/// @brief Definition of the NoteName enum

#ifndef NOTE_NAME_H
#define NOTE_NAME_H

/**
 * @enum NoteName
 * @brief Represents the 12 chromatic musical notes from C to B.
 * 
 * Used to reference musical notes semantically rather than by raw index.
 * 
 * @note These map directly to integers (0–11) and represent chromatic semitone steps.
 */
enum NoteName {
    C,
    C_SHARP,
    D,
    D_SHARP,
    E,
    F,
    F_SHARP,
    G,
    G_SHARP,
    A,
    A_SHARP,
    B
};

/**
 * @brief Converts a NoteName enum to a const char* string literal.
 *
 * @param note The NoteName enum value.
 * @return A pointer to a string literal representing the note name.
 */
inline const char* toString(NoteName note) {
    switch (note) {
        case C:       return "C";
        case C_SHARP: return "C#/Db";
        case D:       return "D";
        case D_SHARP: return "D#/Eb";
        case E:       return "E";
        case F:       return "F";
        case F_SHARP: return "F#/Gb";
        case G:       return "G";
        case G_SHARP: return "G#/Ab";
        case A:       return "A";
        case A_SHARP: return "A#/Bb";
        case B:       return "B";
        default:      return "?";
    }
}

#endif // NOTE_NAME_H