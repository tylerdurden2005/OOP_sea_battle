#ifndef OOPLABEL1_ERRORS_H
#define OOPLABEL1_ERRORS_H
#include <iostream>
#include <vector>
#include <queue>
#include <map>
class ProgramErrors : public std::exception{
private:
    std::string message;
public:
    ProgramErrors(const char* message);
    const char* what() const noexcept override;
};
class AttackError : public ProgramErrors{
public:
    AttackError(const char* message);
};
class AbilityError : public ProgramErrors{
public:
    AbilityError(const char* message);
};
class CoordinatesError : public ProgramErrors{
public:
    CoordinatesError(const char* message);
};
class PlacementError : public ProgramErrors{
public:
    PlacementError(const char* message);
};
class CannotOpenFileError : public ProgramErrors{
public:
    CannotOpenFileError(const char* message);
};
#endif //OOPLABEL1_ERRORS_H
