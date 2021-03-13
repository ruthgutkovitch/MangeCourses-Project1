#ifndef FIRST_ASSIGNMENT_COURSESMANAGER_H
#define FIRST_ASSIGNMENT_COURSESMANAGER_H

#include "AVLtree.h"
#include "Course.h"
#include "lecture.h"

typedef enum {
    CM_SUCCESS = 0,
    CM_FAILURE = -1,
    CM_ALLOCATION_ERROR = -2,
    CM_INVALID_INPUT = -3
} CMResult;

class CoursesManager {
private:
    AVLtree<Course>* coursesTree;
    AVLtree<Lecture>* lecturesTree;
    Vertex<Course>* minCourse;
    Vertex<Lecture>* maxLecture;
    int totalNumOfClasses;
    int watchedClasses;

public:
    CoursesManager() : coursesTree(new AVLtree<Course>), lecturesTree(new AVLtree<Lecture>),
                       minCourse(nullptr), maxLecture(nullptr),
                       totalNumOfClasses(0), watchedClasses(0) {
    };

    ~CoursesManager();

    CMResult AddCourse(int courseID, int numOfClasses);

    CMResult RemoveCourse(int courseID);

    CMResult WatchClass(int courseID, int classID, int time);

    CMResult TimeViewed(int courseID, int classID, int* timeViewed) const;

    CMResult GetMostViewedClasses(int numOfClasses, int* courses, int* classes);

};

#endif //FIRST_ASSIGNMENT_COURSESMANAGER_H