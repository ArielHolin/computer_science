/*******************************************************************************
 *  string.cpp                                                                 *
 *  Author: Ariel                                                              *
 *  Reviewer: Maayan                                                           *
 * ****************************************************************************/
#include <cstring>  // strlen, memcpy, strcat, strcmp
#include <cstddef>  // size_t
#include <iostream> // <<, >>

#include "string.hpp"

namespace hrd20
{
char* String::InitResources(const char* _str)
{
    size_t len = strlen(_str) + 1;
    char* newStr = new char[len];
    memcpy(newStr, _str, len);

    return newStr;
}

void String::DelResources()
{
    delete[] m_str;
    m_str = 0;
}

String::String(const char* _str) : m_str(InitResources(_str))
{}

String::String(const String& _other) : m_str(InitResources(_other.m_str))
{}

String::~String()
{
    DelResources();
}

String& String::operator=(const String& _other)
{
    String cpy(_other);
    std::swap(m_str, cpy.m_str);
    return *this;
}

String& String::operator+=(const String& _other)
{
    size_t thisLen = this->Length();
    size_t otherLen = _other.Length();
    char* new_str = new char[thisLen + otherLen + 1];
    memcpy(new_str, m_str, thisLen + 1);
    strcat(new_str, _other.m_str);
    delete[] m_str;
    m_str = new_str;
    
    return *this;
}

size_t String::Length() const
{
    return strlen(m_str);
}

char& String::operator[](size_t _idx)
{
    return const_cast<char&>(static_cast<const String&>(*this)[_idx]);
}

const char& String::operator[](size_t _idx) const
{
    return m_str[_idx];
}

const char* String::CStr() const
{
    return m_str;
}

bool operator==(const String& _lhs, const String& _rhs)
{
    return !strcmp(_lhs.m_str, _rhs.m_str);
}

bool operator!=(const String& _lhs, const String& _rhs)
{
    return !(_lhs == _rhs);
}

bool operator>(const String& _lhs, const String& _rhs)
{
    if(strcmp(_lhs.m_str, _rhs.m_str) > 0)
    {
        return true;
    }

    return false;
}

bool operator<(const String& _lhs, const String& _rhs)
{
    if(strcmp(_lhs.CStr(), _rhs.CStr()) < 0)
    {
        return true;
    }

    return false;
}

bool operator>=(const String& _lhs, const String& _rhs)
{
    return ((_lhs > _rhs) || (_lhs == _rhs));
}

bool operator<=(const String& _lhs, const String& _rhs)
{
    return ((_lhs < _rhs) || (_lhs == _rhs));
}

const String operator+(const String& _lhs, const String& _rhs)
{
    return String(_lhs) += _rhs;
}

std::ostream& operator<<(std::ostream& _os, const String& _str)
{
    return _os << _str.m_str;    
}

std::istream& operator>>(std::istream& _is, String& _str)
{
    const size_t MAX_BUFFER_LEN = 100;
    char buffer[MAX_BUFFER_LEN] = {0};

    _is.getline(buffer, MAX_BUFFER_LEN);

    _str += buffer;

    return _is;
}

}