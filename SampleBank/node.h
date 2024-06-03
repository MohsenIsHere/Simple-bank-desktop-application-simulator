#ifndef NODE_H
#define NODE_H

template <typename T>
class Node
{
public :
    Node(const T & data) ;
    const T & getData() const ;
    const Node<T> * getNextNode() const ;
    const Node<T> * getPrevNode() const ;
    void setData(const T & data) ;
    void setNextNode(const Node<T> * const nextNode) ;
    void setPrevNode(const Node<T> * const prevNode) ;
private :
    T m_data ;
    Node<T> * m_nextNode ;
    Node<T> * m_prevNode ;
} ;

#endif // NODE_H
