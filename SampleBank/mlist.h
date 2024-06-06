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

#include "mlist.cpp"

#endif // MLIST_H
