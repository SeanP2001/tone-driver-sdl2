/// @file Note.cpp
/// @brief Implementation of the Note class.

#include "music-components/Note.h"


// ------------------------------------ C O N S T R U C T O R S ------------------------------------
Note::Note() : Note(DEFAULT_NOTE, DEFAULT_OCTAVE) {}
Note::Note(NoteName note) : Note(note, DEFAULT_OCTAVE) {}
Note::Note(NoteName note, uint8_t octave) : note_(note), octave_(octave) 
{
    if(!isValidNote(note_, octave_))
    {
        note_ = DEFAULT_NOTE;
        octave_ = DEFAULT_OCTAVE;
    }
}


// ----------------------------------------- H E L P E R S -----------------------------------------
// NOTE: Uses static buffer; not safe for multiple simultaneous calls (fine if output is immediately printed)
const char* Note::toString() const
{
    static char noteStr[6];  
    const char* noteNameStr = getNoteNameString();
    snprintf(noteStr, sizeof(noteStr), "%s%d", noteNameStr, octave_);
    
    return noteStr;
}

bool Note::isValidNote(const NoteName note, const int octave)
{
    if (note < NoteName::C || note > NoteName::B) return false;
    
    if (octave < 0 || octave > Note::MAX_OCTAVE) return false;
    
    return true;
}


// ------------------------------------- C O M P A R I S O N S -------------------------------------
bool Note::operator==(const Note& other) const
{
    return ((note_ == other.getNoteName()) && (octave_ == other.getOctave()));
}

bool Note::operator!=(const Note& other) const
{
    return !(*this == other);
}


// ---------------------------- A R I T H M E T I C   O P E R A T O R S ----------------------------
Note Note::operator+(int semitones) const
{
    int total = (octave_ * NOTES_PER_OCTAVE) + int(note_) + semitones;  
    
    NoteName newNote = NoteName(total % NOTES_PER_OCTAVE);
    int newOctave = total / NOTES_PER_OCTAVE;
    
    if(isValidNote(newNote, newOctave))
    {
        return Note(newNote, newOctave);
    }
    else
    {
        return Note(DEFAULT_NOTE, DEFAULT_OCTAVE);
    }
}

Note Note::operator-(int semitones) const
{
    int total = (octave_ * NOTES_PER_OCTAVE) + int(note_) - semitones;

    // Only calculate note if total isn't negative to prevent invalid negative modulo
    if(total >= 0)
    {
        NoteName newNote = NoteName(total % NOTES_PER_OCTAVE);
        int newOctave = total / NOTES_PER_OCTAVE;
        
        if(isValidNote(newNote, newOctave))
        {
            return Note(newNote, newOctave);
        }
    }
    
    // Invalid notes get reset to default (C4)
    return Note(DEFAULT_NOTE, DEFAULT_OCTAVE);
}


// prefix ++n increments and returns self ref
Note& Note::operator++()
{
    *this = *this + 1;
    return *this;
} 

Note& Note::operator--()
{
    *this = *this - 1;
    return *this;
}

// postfix n++ copies, increments and returns the copy
Note Note::operator++(int)
{
    Note temp = *this;
    ++(*this);
    return temp;
} 

Note Note::operator--(int)
{
    Note temp = *this;
    --(*this);
    return temp;
}


Note Note::operator+=(int semitones)
{
    *this = *this + semitones;
    return *this;
}

Note Note::operator-=(int semitones)
{
    *this = *this - semitones;
    return *this;
}



// ----------------------------------------- S E T T E R S -----------------------------------------
void Note::setNoteName(const NoteName newNote)
{
    if (isValidNote(newNote, octave_))
    {
        note_ = newNote;
    }
}

void Note::setOctave(const uint8_t newOctave)
{
    if (isValidNote(note_, newOctave))
    {
        octave_ = newOctave;
    }
}

void Note::change(const NoteName newNote, const uint8_t newOctave)
{
    if (isValidNote(newNote, newOctave))
    {
        note_ = newNote;
        octave_ = newOctave;
    }
}


// ----------------------------------------- G E T T E R S -----------------------------------------
NoteName Note::getNoteName() const
{
    return note_;
}

const char* Note::getNoteNameString() const
{
    return noteNameToString(note_);
}

uint8_t Note::getOctave() const
{
    return octave_;
}

