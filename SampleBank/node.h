#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public :
    Node(const T & data) ;
    const T & getData() const ;
    Node * getNextNode() const ;
    Node * getPrevNode() const ;
    void setData(const T & data) ;
    void setNextNode(Node * nextNode) ;
    void setPrevNode(Node * prevNode) ;
private :
    T m_data ;
    Node * m_nextNode ;
    Node * m_prevNode ;
} ;

template <typename T> Node<T>::Node(const T & data) : m_data(data) , m_nextNode(nullptr) , m_prevNode(nullptr) {}

template <typename T> const T & Node<T>::getData() const { return m_data ; }

template <typename T> Node<T> * Node<T>::getNextNode() const { return m_nextNode ; }

template <typename T> Node<T> * Node<T>::getPrevNode() const { return m_prevNode ; }

template <typename T> void Node<T>::setData(const T & data) { m_data = data ; }

template <typename T> void Node<T>::setNextNode(Node<T> * nextNode) { m_nextNode = nextNode ; }

template <typename T> void Node<T>::setPrevNode(Node<T> * prevNode) { m_prevNode = prevNode ; }

#endif // NODE_H
