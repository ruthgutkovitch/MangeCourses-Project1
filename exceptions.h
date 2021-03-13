#ifndef FIRST_ASSIGNMENT_EXCEPTIONS_H
#define FIRST_ASSIGNMENT_EXCEPTIONS_H

#include <iostream>

class Exceptions : public std::exception {
};

class VertexAlreadyExist : public Exceptions {
};

class VertexDoesNotExist : public Exceptions {
};

class CourseBadAlloc : public std::bad_alloc {

};

class LectureBadAlloc : public std::bad_alloc {

};

class VertexBadAlloc : public Exceptions {

};

// the exceptions are empty because we dont need to print the error message in this program
#endif //FIRST_ASSIGNMENT_EXCEPTIONS_H