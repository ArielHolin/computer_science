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

#include <cstddef> /* size_t */

namespace hrd20 
{
class SList //Uncopyable
{
public:
    explicit SList();
    ~SList();
    
    void PushFront(int data);
    //undefined behavior if the list is empty
    void PopFront();          
    //undefined behavior if the list is empty
    int Peek() const;
    bool IsEmpty() const;   
    size_t Size() const;

private:
    SList(const SList& list);
    SList& operator=(const SList& list);
    
    struct Node;

    Node* m_head;
};

} //namespace hrd20 

#endif //ILRD_HRD_20_SLIST_HPP