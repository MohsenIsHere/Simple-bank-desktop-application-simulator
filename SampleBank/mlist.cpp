#include "mlist.h"

template <typename T>
MList<T>::MList() : m_size(0) , m_headNode(nullptr) , m_tailNode(nullptr) {}
template <typename T> const Node<T> * MList<T>::getHeadNode() const { return m_headNode ; }
template <typename T> const Node<T> * MList<T>::getTailNode() const { return m_tailNode ; }
template <typename T> const int & MList<T>::getSize() const { return m_size ; }
template <typename T> void MList<T>::pushBack(const T & data) {
    Node<T> * newNode = new Node<T>(data) ;
    if(m_size) {
        newNode->setPrevNode(m_tailNode) ;
        m_tailNode->setNextNode(newNode) ;
    } else { m_headNode = newNode ; }
    m_tailNode = newNode ;
    m_size ++ ;
}
template <typename T> void MList<T>::popBack() {
    Node<T> * node = m_tailNode ;
    if(m_size) {
        m_tailNode = m_tailNode->getPrevNode() ;
        if(m_tailNode) m_tailNode->setNextNode(nullptr) ;
        else m_headNode = nullptr ;
    }
    delete node ;
    m_size -- ;
}
template <typename T> MList<T>::~ MList () {
    for (int i = m_size ; i > 0 ; i--) popBack() ;
}
