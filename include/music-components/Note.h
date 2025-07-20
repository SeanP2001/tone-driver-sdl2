/// @file Note.h
/// @brief Definition of the Note class which represents a musical note with a pitch class and octave. 

#ifndef NOTE_H
#define NOTE_H

#include <stdint.h>    // for uint8_t
#include <cstdio>      // for snprintf
#include "NoteName.h"


/// @class Note
/// @brief Represents a musical note with a pitch class and octave (C0 to B6).
///
/// Provides support for arithmetic operations, comparisons, and conversion to string.
class Note
{
public:
// ------------------------------------ C O N S T R U C T O R S ------------------------------------
    /// @brief Default constructor. Initialises to middle C (C4).
    Note();

    /// @brief Constructs a Note with the given pitch class at default octave (4).
    /// @param note The pitch class (C through B).
    /// If the note is not valid, it will be reset to the default (C)
    Note(NoteName note);

    /// @brief Constructs a Note with the given pitch class and octave.
    /// @param note The pitch class (C through B).
    /// @param octave The octave (0–6). 
    /// If the note or octave is not valid, it will be reset to to the default (C4)
    Note(NoteName note, uint8_t octave);


// ----------------------------------------- H E L P E R S -----------------------------------------
    /// @brief Returns a string representation of the note (e.g. "C#4").
    /// @return C-style string, valid until next call.
    /// @note Uses static buffer; not safe for multiple simultaneous calls (fine if output is immediately printed).
    const char* toString() const;

    /// @brief Checks whether a given pitch class and octave form a valid note within range.
    /// @param note The pitch class.
    /// @param octave The octave.
    /// @return True if the note is valid, false otherwise.
    static bool isValidNote(const NoteName note, const int octave);


// ------------------------------------- C O M P A R I S O N S -------------------------------------
    /// @brief Equality comparison.
    bool operator==(const Note& other) const;

    /// @brief Inequality comparison.
    bool operator!=(const Note& other) const;


// ---------------------------- A R I T H M E T I C   O P E R A T O R S ----------------------------
    /// @brief Adds a number of semitones to the note.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note operator+(int semitones) const;

    /// @brief Subtracts a number of semitones from the note.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note operator-(int semitones) const; 

    /// @brief Prefix increment (e.g. ++n). Moves up by one semitone.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note& operator++();  

    /// @brief Prefix decrement (e.g. --n). Moves down by one semitone.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note& operator--();
    
    /// @brief Postfix increment (e.g. n++). Moves up by one semitone.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note operator++(int);  

    /// @brief Postfix decrement (e.g. n--). Moves down by one semitone.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note operator--(int);

    /// @brief Adds semitones in-place.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note operator+=(int semitones);

    /// @brief Subtracts semitones in-place.
    /// If the resulting note is out of range, it will be reset to the default (C4).
    Note operator-=(int semitones);
 
    
// ----------------------------------------- S E T T E R S -----------------------------------------
    /// @brief Sets the pitch class of the note.
    /// @param newNote The new pitch class.
    /// 
    /// Only updates if the new pitch class and current octave are considered a valid note by isValidNote().
    void setNoteName(const NoteName newNote);

    /// @brief Sets the octave of the note.
    /// @param newOctave The new octave.
    /// 
    /// Only updates if the current pitch class and new octave are considered a valid note by isValidNote().
    void setOctave(const uint8_t newOctave);

    /// @brief Changes both pitch class and octave.
    /// @param newNote The new pitch class.
    /// @param newOctave The new octave. 
    /// 
    /// Only updates if the new pitch class and octave are considered a valid note by isValidNote().
    void change(const NoteName newNote, const uint8_t newOctave);


// ----------------------------------------- G E T T E R S -----------------------------------------
    /// @brief Gets the pitch class.
    /// @return The pitch class as a NoteName enum.
    NoteName getNoteName() const;

    /// @brief Returns a string representation of the pitch class (e.g. "F#").
    const char* getNoteNameString() const;

    /// @brief Gets the octave.
    /// @return The octave (0–6).
    uint8_t getOctave() const;



    static constexpr int MAX_OCTAVE = 6;           ///< Maximum octave index supported (inclusive). Valid range: 0–6.
    static constexpr  int NOTES_PER_OCTAVE = 12;   ///< The number of semitones in an octave.

private:
    NoteName note_;     ///< The pitch class of the note (C through B)
    uint8_t octave_;    ///< The octave index of the note (0-6)

    static constexpr NoteName DEFAULT_NOTE = NoteName::C;   ///< Default pitch class (C). Set when the pitch class isn't specified or is invalid.
    static constexpr int DEFAULT_OCTAVE = 4;                ///< Default octave (4). Set when the octave isn't specified or is invalid.
};

#endif // NOTE_H