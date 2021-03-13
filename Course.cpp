#include "Course.h"

//destructor
Course::~Course() {
    delete[] arrayLectures;
}

// copy constructor
Course::Course(const Course& other) : courseID(other.courseID), numOfClasses(other.numOfClasses),
                                      arrayLectures(new Lecture* [other.numOfClasses]) {
    for (int i = 0; i < other.numOfClasses; i++) {
        arrayLectures[i] = other.arrayLectures[i];
    }
}

// operator assighment
Course& Course::operator=(const Course& other) {
    if (this == &other) {
        return *this;
    }
    Lecture** tempArray = new Lecture * [other.numOfClasses];
    for (int i = 0; i < other.numOfClasses; i++) {
        tempArray[i] = other.arrayLectures[i];
    }
    delete[] arrayLectures;
    arrayLectures = tempArray;
    courseID = other.courseID;
    numOfClasses = other.numOfClasses;
    return *this;
}


int Course::GetCourseID() const {
    return this->courseID;
}

int Course::GetNumOfClasses() const {
    return this->numOfClasses;
}

//operator output
std::ostream& operator<<(std::ostream& os, const Course& course) {
    int arraySize = course.GetNumOfClasses();
    for (int i = 0; i < arraySize; i++) {
        os << course.GetCourseID() << " " << i << std::endl;
    }
    return os;
}


Lecture* Course::GetPtrLecture(int classID) const {
    return this->arrayLectures[classID];
}

void Course::SetPtrLecture(int classID, Lecture* lecture) { ///const?
    this->arrayLectures[classID] = lecture;
}

//check if both courses are equal
bool operator==(const Course& c1, const Course& c2) {
    if (c1.GetCourseID() == c2.GetCourseID()) {
        return true;
    }
    return false;
}

//compare between two courses
bool operator>(const Course& c1, const Course& c2) {
    if (c1.GetCourseID() > c2.GetCourseID()) {
        return true;
    }
    return false;
}

//compare between two courses
bool operator<(const Course& c1, const Course& c2) {
    if (c1.GetCourseID() < c2.GetCourseID()) {
        return true;
    }
    return false;
}

