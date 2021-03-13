#ifndef FIRST_ASSIGNMENT_VERTEX_H
#define FIRST_ASSIGNMENT_VERTEX_H

template <class T>
class AVLtree;

template <class T>
class Vertex{
private:
    T* data;
    Vertex* leftSon;
    Vertex* rightSon;
    Vertex* father;
    int height;

public:
    explicit Vertex(): data(nullptr), leftSon(nullptr), rightSon(nullptr), father(nullptr), height(0){};
    ~Vertex() = default;
    Vertex(const Vertex<T>& other);
    Vertex& operator=(const Vertex<T>& other);
    T* GetData();
    T* GetData() const;
    int GetVertexHeight() const;
    friend class AVLtree<T>;
};

// compare two vertex
template <class T>
bool operator>(const Vertex<T>& v1, const Vertex<T>& v2) {
    if (v1.GetData() > v2.GetData()){
        return true;
    }
    return false;
}


// compare two vertex
template <class T>
bool operator<(const Vertex<T>& v1, const Vertex<T>& v2){
    if (v1.GetData() < v2.GetData()){
        return true;
    }
    return false;

}

// check if two vertex are equal
template <class T>
bool operator==(const Vertex<T>& v1, const Vertex<T>& v2) {
    if (v1.GetData() == v2.GetData()){
        return true;
    }
    return false;

}

// return height
template<class T>
int Vertex<T>::GetVertexHeight() const {
    return this->height;
}

// return pointer to data
template <class T>
T* Vertex<T>::GetData(){
    return this->data;
}

// return pointer to data - the function is const
template<class T>
T* Vertex<T>::GetData() const {
    return this->data;
}

// copy constructor
template<class T>
Vertex<T>::Vertex(const Vertex<T> &other) : data(other.data), leftSon(other.leftSon),
                                            rightSon(other.rightSon), father(other.father), height(other.height){
}

// operator assignment
template<class T>
Vertex<T>& Vertex<T>::operator=(const Vertex<T> &other) {
    if(this == &other){
        return *this;
    }
    data = other.data;
    leftSon = other.leftSon;
    rightSon = other.rightSon;
    father = other.father;
    height = other.height;
    return *this;
}



#endif //FIRST_ASSIGNMENT_VERTEX_H