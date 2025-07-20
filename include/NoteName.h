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
enum class NoteName {
    C,
    CSharp,
    D,
    DSharp,
    E,
    F,
    FSharp,
    G,
    GSharp,
    A,
    ASharp,
    B
};

/**
 * @brief Converts a NoteName enum to a const char* string literal.
 *
 * @param note The NoteName enum value.
 * @return A pointer to a string literal representing the note name.
 */
inline const char* noteNameToString(NoteName note) {
    switch (note) {
        case NoteName::C:       return "C";
        case NoteName::CSharp:  return "C#/Db";
        case NoteName::D:       return "D";
        case NoteName::DSharp:  return "D#/Eb";
        case NoteName::E:       return "E";
        case NoteName::F:       return "F";
        case NoteName::FSharp:  return "F#/Gb";
        case NoteName::G:       return "G";
        case NoteName::GSharp:  return "G#/Ab";
        case NoteName::A:       return "A";
        case NoteName::ASharp:  return "A#/Bb";
        case NoteName::B:       return "B";
        default:                return "?";
    }
}

#endif // NOTE_NAME_H