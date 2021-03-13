#ifndef FIRST_ASSIGNMENT_COURSE_H
#define FIRST_ASSIGNMENT_COURSE_H

#include "lecture.h"

class Course {
private:
    int courseID;
    int numOfClasses;
    Lecture** arrayLectures;
public:
    explicit Course(int courseID, int numOfClasses = 0)
            : courseID(courseID), numOfClasses(numOfClasses),
              arrayLectures(new Lecture* [numOfClasses]) {
        for (int i = 0; i < numOfClasses; i++) {
            arrayLectures[i] = nullptr;
        }
    };
    ~Course();
    Course(const Course& other);
    Course& operator=(const Course& other);
    int GetCourseID() const;
    int GetNumOfClasses() const;
    Lecture* GetPtrLecture(int classID) const;
    void SetPtrLecture(int classID, Lecture* lecture);


};

std::ostream& operator<<(std::ostream& os, const Course& course);
bool operator==(const Course& c1, const Course& c2);
bool operator<(const Course& c1, const Course& c2); ///change
bool operator>(const Course& c1, const Course& c2); ///change


#endif //FIRST_ASSIGNMENT_COURSE_H