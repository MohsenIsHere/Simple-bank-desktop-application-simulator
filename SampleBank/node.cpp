#include "node.h"

template <typename T>
Node<T>::Node(const T & data) : m_data(data) , m_nextNode(nullptr) , m_prevNode(nullptr) {}
template <typename T> const T & Node<T>::getData() const { return m_data ; }
template <typename T> const Node<T> * Node<T>::getNextNode() const { return m_nextNode ; }
template <typename T> const Node<T> * Node<T>::getPrevNode() const { return m_prevNode ; }
template <typename T> void Node<T>::setData(const T & data) { m_data = data ; }
template <typename T> void Node<T>::setNextNode(const Node<T> * const nextNode) { nextNode = m_nextNode ; }
template <typename T> void Node<T>::setPrevNode(const Node<T> * const prevNode) { prevNode = m_prevNode ; }
