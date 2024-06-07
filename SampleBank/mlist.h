#ifndef MLIST_H
#define MLIST_H
#include "node.h"


template <typename T>
class MList
{
public :
    MList() ;
    const Node<T> * getHeadNode() const ;
    const Node<T> * getTailNode() const ;
    const int & getSize() const ;
    void pushBack(const T & data) ;
    void popBack() ;
    ~ MList () ;
private :
    Node<T> * m_headNode ;
    Node<T> * m_tailNode ;
    int m_size ;
} ;

// Implementation of MList methods
template <typename T>
MList<T>::MList() : m_headNode(nullptr), m_tailNode(nullptr) , m_size(0) {}

template <typename T>
const Node<T> * MList<T>::getHeadNode() const { return m_headNode; }

template <typename T>
const Node<T> * MList<T>::getTailNode() const { return m_tailNode; }

template <typename T>
const int & MList<T>::getSize() const { return m_size; }

template <typename T>
void MList<T>::pushBack(const T & data) {
    Node<T> * newNode = new Node<T>(data);
    if (m_size) {
        newNode->setPrevNode(m_tailNode);
        m_tailNode->setNextNode(newNode);
    } else {
        m_headNode = newNode;
    }
    m_tailNode = newNode;
    m_size++;
}

template <typename T>
void MList<T>::popBack() {
    Node<T> * node = m_tailNode;
    if (m_size) {
        m_tailNode = m_tailNode->getPrevNode();
        if (m_tailNode) m_tailNode->setNextNode(nullptr);
        else m_headNode = nullptr;
    }
    delete node;
    m_size--;
}

template <typename T>
MList<T>::~MList() {
    while (m_size > 0) popBack();
}

#endif // MLIST_H
