#include "library.h"
#include "coursesManager.h"

// allocates the new Courses Manager
void* Init() {
    CoursesManager* DS = new CoursesManager();
    return (void*)DS;
}

//add course
StatusType AddCourse(void* DS, int courseID, int numOfClasses) {
    if (DS == nullptr || courseID <= 0 || numOfClasses <= 0) {// check the given parameters
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->AddCourse(courseID, numOfClasses);
    return (StatusType)res;
}

// remove course
StatusType RemoveCourse(void* DS, int courseID) {
    if (DS == nullptr || courseID <= 0) { // check the given parameters
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->RemoveCourse(courseID);
    return (StatusType)res;
}

// add watching time to a lecture
StatusType WatchClass(void* DS, int courseID, int classID, int time) {
    if (DS == nullptr || courseID <= 0 || classID < 0 || time <= 0) { // check the given parameters
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->WatchClass(courseID, classID, time);
    return (StatusType)res;
}

// return watching time of specific lecture
StatusType TimeViewed(void* DS, int courseID, int classID, int* timeViewed) {
    if (DS == nullptr || courseID <= 0 || classID < 0) { // check the given parameters
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->TimeViewed(courseID, classID, timeViewed);
    return (StatusType)res;
}

// return most viewed lectures
StatusType GetMostViewedClasses(void* DS, int numOfClasses, int* courses, int* classes) {
    if (DS == nullptr || numOfClasses <= 0) { // check the given parameters
        return INVALID_INPUT;
    }
    CMResult res = ((CoursesManager*)DS)->GetMostViewedClasses(numOfClasses, courses, classes);
    return (StatusType)res;
}

// delete the structure
void Quit(void** DS) {
    delete (CoursesManager*)DS[0];
    *DS = nullptr;
}

#include "library.h"
