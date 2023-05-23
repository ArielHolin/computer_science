/*******************************************************************************
* Description: Shared Ptr
* Name: Ariel
* Reviewer - 
* Date: 05.01.21
* Versions: 1.0
* 0.1 - ready for review
*******************************************************************************/ 
#ifndef ILRD_HRD_20_SHARED_PTR_HPP
#define ILRD_HRD_20_SHARED_PTR_HPP

#include <cstddef>      /*  size_t        */
#include <algorithm>    /*  std::swap     */

namespace hrd20 
{

// please use this syntex SharedPtr<X>ptr(new(val1, val2, ... ))
//                        SharedPtr<const X>ptr(new(val1, val2, ... ))

template<typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T* _ptr = 0);
    SharedPtr(const SharedPtr& _other);
    ~SharedPtr();
    SharedPtr& operator=(const SharedPtr& _other); // ptr1 = ptr2

    const T* Get() const; // c backwards compatability

    T* operator->() const; // ptr->foo()
    T& operator*() const;  // *ptr = X()   (equal to ptr*)
    bool operator!();      // !(ptr) equal to (ptr)! 
    bool operator==(const SharedPtr& _other);
    bool operator!=(const SharedPtr& _other);

private:
    T* m_ptr;
    size_t* m_ref_counter;  
}; // SharedPtr

template<typename T>
SharedPtr<T>::SharedPtr(T* _ptr) : m_ptr(_ptr), m_ref_counter(new size_t(1)) 
{}

template<typename T>
SharedPtr<T>::~SharedPtr()
{
    --(*m_ref_counter);

    if(0 == *m_ref_counter)
    {
        delete m_ptr;
        m_ptr = 0;

        delete m_ref_counter;
        m_ref_counter = 0;
    }
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& _other) : m_ptr(_other.m_ptr), 
                                                   m_ref_counter(_other.m_ref_counter)
{
    ++(*m_ref_counter);
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& _other)
{
    // copy and swap idiom
    SharedPtr<T> cpy(_other);
    std::swap(m_ptr, cpy.m_ptr);
    std::swap(m_ref_counter, cpy.m_ref_counter);

    return *this;
}

template<typename T>
const T* SharedPtr<T>::Get() const
{
    return m_ptr;
}

template<typename T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template<typename T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

template<typename T>
bool SharedPtr<T>::operator!()
{
    return (0 == m_ptr);
}

template<typename T>
bool SharedPtr<T>::operator==(const SharedPtr& _other)
{
    return (m_ptr == _other.m_ptr);
}

template<typename T>
bool SharedPtr<T>::operator!=(const SharedPtr& _other)
{
    return !(*this == _other);
}

}
#endif //ILRD_HRD_20_SHARED_PTR_HPP