/*********************************************************************
* Description: Implementation of a singly linked list ds in C++.
* Name: HRD20 - Ariel
* Reviewer - Liel
* Date: 9.12.21
* Versions: 1.0
* 0.1 - ready for review
* 0.2 - Mentor Approve
* 0.3 - TBD
*********************************************************************/
#ifndef ILRD_HRD_20_SLIST_HPP
#define ILRD_HRD_20_SLIST_HPP

#include <cstddef>  //size_t 
#include <cassert>  //assert

namespace hrd20 
{
template<typename T>
class SList //Uncopyable
{
public:
    explicit SList();
    ~SList();
    
    void PushFront(T data);
    //undefined behavior if the list is empty
    void PopFront();          
    //undefined behavior if the list is empty
    T Peek() const;
    bool IsEmpty() const;   
    size_t Size() const;

private:
    SList(const SList& list);
    SList& operator=(const SList& list);
    
    struct Node;

    Node* m_head;
};

template<typename T>
struct SList<T>::Node
{
    explicit Node(T data_);
    //using generated cctor, copy=, ~

    T m_data;
    Node* m_next;
};

template<typename T>
SList<T>::Node::Node(T data_) : m_data(data_), m_next(0) {}

template<typename T>
SList<T>::SList() : m_head(0) {}

template<typename T>
SList<T>::~SList()
{
    while(m_head)
    {
        PopFront();
    }
}

template<typename T>
void SList<T>::PushFront(T data)
{
    Node* newNode = new Node(data);
    newNode->m_next = m_head;
    m_head = newNode;
}

template<typename T>
void SList<T>::PopFront()
{
    assert(m_head);

    Node* tmp = m_head;
    m_head = m_head->m_next;
    delete tmp;
    tmp = 0;
}

template<typename T>
T SList<T>::Peek() const
{
    assert(m_head);

    return m_head->m_data;
}

template<typename T>
bool SList<T>::IsEmpty() const
{
    return (0 == m_head);
}

template<typename T>
size_t SList<T>::Size() const
{
    Node* runner = m_head;
    size_t counter = 0;

    while(runner)
    {
        ++counter;
        runner = runner->m_next;
    }

    return counter;
}

} //namespace hrd20 

#endif //ILRD_HRD_20_SLIST_HPP