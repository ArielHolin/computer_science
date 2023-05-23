/*******************************************************************************
 *   slist.cpp                                                                 *
 *   Author: Ariel                                                             *
 *   Reviewer: Liel                                                                *
 * ****************************************************************************/
#include <cstddef> // size_t 
#include <cassert> // assert

#include "slist.hpp"

namespace hrd20 
{
struct SList::Node
{
    explicit Node(int data_);
    //using generated cctor, copy=, ~

    int m_data;
    Node* m_next;
};

SList::Node::Node(int data_) : m_data(data_), m_next(0) {}

SList::SList() : m_head(0) {}

SList::~SList()
{
    while(m_head)
    {
        PopFront();
    }
}

void SList::PushFront(int data)
{
    Node* newNode = new Node(data);
    newNode->m_next = m_head;
    m_head = newNode;
}

void SList::PopFront()
{
    assert(m_head);

    Node* tmp = m_head;
    m_head = m_head->m_next;
    delete tmp;
    tmp = 0;
}

int SList::Peek() const
{
    assert(m_head);

    return m_head->m_data;
}

bool SList::IsEmpty() const
{
    return (0 == m_head);
}

size_t SList::Size() const
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