#include "Errors.h"
ProgramErrors::ProgramErrors(const char* message) : message(message){}

const char *ProgramErrors::what() const noexcept {
    return message.c_str();
}

AttackError::AttackError(const char* message) : ProgramErrors(message){}

AbilityError::AbilityError(const char *message) : ProgramErrors(message){}

CoordinatesError::CoordinatesError(const char *message) : ProgramErrors(message){}

PlacementError::PlacementError(const char *message) : ProgramErrors(message){}

CannotOpenFileError::CannotOpenFileError(const char *message) : ProgramErrors(message){}