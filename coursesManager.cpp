#include "coursesManager.h"

//destructor
///destroy the lectures tree first so we dont need to go over the coursesTree and remove the lecture of each Course
///o(log(n)+log(M))
CoursesManager::~CoursesManager() {
    delete lecturesTree;
    delete coursesTree;
}

///o(log(n)+m)
//check if course already exist. if not ,add course to courses tree
CMResult CoursesManager::AddCourse(int courseID, int numOfClasses) {
    try {
        Course toAdd(courseID, numOfClasses);
        try{
            this->coursesTree->AddVertex(coursesTree->GetRoot(), toAdd);
        }catch(const VertexBadAlloc& e){// vertex allocation error
            return CM_ALLOCATION_ERROR;
        }
        catch(const VertexAlreadyExist& e){// course already exists
            return CM_FAILURE;
        }
    }catch(const CourseBadAlloc& e){//course allocation error
        return CM_ALLOCATION_ERROR;
    }

    this->minCourse = this->coursesTree->GetMin(coursesTree->GetRoot());//update the course with min id number
    this->totalNumOfClasses += numOfClasses;//update the total num of lectures

    return CM_SUCCESS;
}

///O(mlogM)
//check if course exist.if exist remove lectures of given course from tree lectures and then remove course from courses tree
CMResult CoursesManager::RemoveCourse(int courseID) {
    int numOfClasses = 0;
    Course courseToDelete(courseID);
    Vertex<Course>* courseVertex = coursesTree->BinarySearch(coursesTree->GetRoot(), courseToDelete);
    if(courseVertex == nullptr){
        return CM_FAILURE; ///course does not exist
    }
    numOfClasses = courseVertex->GetData()->GetNumOfClasses();
    for(int i = 0; i < numOfClasses; i++){
        Lecture* ptrLecture = courseVertex->GetData()->GetPtrLecture(i);
        if(ptrLecture != nullptr) {// if lecture number i exists in lecture tree- we need to remove
            Lecture lectureToDelete(ptrLecture->GetCourseID(), ptrLecture->GetClassID(), ptrLecture->GetLectureTime());
            this->lecturesTree->RemoveVertex(lecturesTree->GetRoot(), lectureToDelete); // remove lecture
            this->watchedClasses -= 1;//update the num of watched lectures
        }
    }
    this->coursesTree->RemoveVertex(coursesTree->GetRoot(), courseToDelete);// remove course

    this->minCourse = this->coursesTree->GetMin(coursesTree->GetRoot());//update the course with min id number
    this->maxLecture = this->lecturesTree->GetMax(lecturesTree->GetRoot());//update the lecture with max watching time
    this->totalNumOfClasses -= numOfClasses;//update the total num of lectures

    return CM_SUCCESS;
}

///O(logM)
// add watching time to a lecture
CMResult CoursesManager::WatchClass(int courseID, int classID, int time) {
    Course toSearch(courseID);
    Vertex<Course>* courseVertex = coursesTree->BinarySearch(coursesTree->GetRoot(), toSearch);
    if(courseVertex != nullptr){
        if(classID + 1 > courseVertex->GetData()->GetNumOfClasses()){
            return CM_INVALID_INPUT;// lecture does not exist
        }
    }else{
        return CM_FAILURE;//course does not exist
    }

    if(courseVertex->GetData()->GetPtrLecture(classID) == nullptr){///first time that this lecture is watched
        try{
            Lecture lectureToAdd_1(courseID, classID, time);
            this->lecturesTree->AddVertex(lecturesTree->GetRoot(), lectureToAdd_1);// add lecture to lectures tree
            Vertex<Lecture>* ptrLecture = lecturesTree->BinarySearch(lecturesTree->GetRoot(), lectureToAdd_1);
            courseVertex->GetData()->SetPtrLecture(classID, ptrLecture->GetData());
            this->watchedClasses += 1;// update the num of watched lectures
        }catch(const VertexBadAlloc& e) {
            return CM_ALLOCATION_ERROR;// vertex allocation error
        }
    }
    else{///lecture is already in lecturesTree - this lecture was watched before
       try{
           Lecture* ptrLecture = courseVertex->GetData()->GetPtrLecture(classID);
           int oldTime = ptrLecture->GetLectureTime();
           int newTime = time + oldTime;
           Lecture lectureToDelete(courseID, classID, oldTime);
           this->lecturesTree->RemoveVertex(lecturesTree->GetRoot(), lectureToDelete);//remove the lecture
           Lecture lectureToAdd_2(courseID, classID, newTime);
           this->lecturesTree->AddVertex(lecturesTree->GetRoot(), lectureToAdd_2);// add the update lecture
           Vertex<Lecture>* ptr= lecturesTree->BinarySearch(lecturesTree->GetRoot(), lectureToAdd_2);
           courseVertex->GetData()->SetPtrLecture(classID, ptr->GetData());// change the pointer to its new location
        }catch(const VertexBadAlloc& e) {
            return CM_ALLOCATION_ERROR;
        }
    }

    this->maxLecture = this->lecturesTree->GetMax(lecturesTree->GetRoot());//update the lecture with max watching time
    return CM_SUCCESS;
}

//return the watching time of a specific lecture
CMResult CoursesManager::TimeViewed(int courseID, int classID, int *timeViewed) const{
    Course toSearch(courseID);
    Vertex<Course>* v = coursesTree->BinarySearch(coursesTree->GetRoot(), toSearch);
    if(v == nullptr){
        return CM_FAILURE;//course does not exist
    }
    int numOfClasses = v->GetData()->GetNumOfClasses();
    if(classID + 1 > numOfClasses) {// lecture does not exist in the course
        return CM_INVALID_INPUT;
    }
    Lecture* lecturePtr = v->GetData()->GetPtrLecture(classID);
    if(lecturePtr == nullptr){// lecture does not exist in lecture tree - it means watching time is 0
        *timeViewed = 0;
        return CM_SUCCESS;
    }
    *timeViewed = lecturePtr->GetLectureTime();
    return CM_SUCCESS;
}

// return the most viewed lectures
CMResult CoursesManager::GetMostViewedClasses(int numOfClasses, int *courses, int *classes) {

    if (totalNumOfClasses < numOfClasses){// check if total num of lecture in CoursesManager smaller then numOfClasses
        return CM_FAILURE;
    }

    int min = 0;
    if(watchedClasses < numOfClasses){
        min = watchedClasses;
    }else{
        min = numOfClasses;
    }

    this->lecturesTree->ReverseInorder(maxLecture, min, courses, classes);// gets lectures with watching time bigger than 0

    int rest = numOfClasses - min;

    // if num of watched lectures smaller than numOfClasses we get lectures with watching time 0 from courses tree
    if(rest != 0){
        this->coursesTree->Inorder(minCourse, rest, courses + min, classes + min);
    }
    return CM_SUCCESS;
}