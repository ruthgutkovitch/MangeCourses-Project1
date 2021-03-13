#ifndef FIRST_ASSIGNMENT_AVLTREE_H
#define FIRST_ASSIGNMENT_AVLTREE_H

#include <iostream>
#include "Vertex.h"
#include "exceptions.h"

typedef enum {
    RIGHT = -3,
    LEFT = -4
} SIDE;


template <class T>
class AVLtree{
private:
    Vertex<T>* treeRoot;
public:
    AVLtree() : treeRoot(nullptr){};
    ~AVLtree();
    void DeleteAVLtree(Vertex<T>* vertex);
    void AddVertex(Vertex<T>* v, const T& data);
    Vertex<T>* AddVertexAux(Vertex<T>* v, const T& data);
    void RemoveVertex(Vertex<T>* v, const T& data);
    Vertex<T>* RemoveVertexAux(Vertex<T>* v, const T& data);

    Vertex<T>* RotationLL(Vertex<T>* v);
    Vertex<T>* RotationLR(Vertex<T>* v);
    Vertex<T>* RotationRR(Vertex<T>* v);
    Vertex<T>* RotationRL(Vertex<T>* v);

    Vertex<T>* BinarySearch(Vertex<T>* v, const T& data) const;

    Vertex<T>* GetMax(Vertex<T>* vertex) const;
    Vertex<T>* GetMin(Vertex<T>* vertex) const;

    Vertex<T>* GetRoot() const;

    void PrintTree(Vertex<T>* vertex) const;
    void Inorder(Vertex<T>* vertex, int num, int *courses, int *classes) const;
    void InorderAux(Vertex<T>* vertex, int num, SIDE indicator, int* count, int *courses, int *classes) const;
    void ReverseInorder(Vertex<T>* vertexStart, int num, int *courses, int *classes) const;
    void ReverseInorderAux(Vertex<T>* vertexStart, int num, SIDE indicator, int* count, int *courses, int *classes) const;
    int CalculateBalance(Vertex<T>* vertex) const;

};

#include "AVLtreeIMP.h"

#endif //FIRST_ASSIGNMENT_AVLTREE_H
