/*******************************************************************************
 *  rcstring.cpp                                                               *
 *  Author: Ariel                                                              *
 *  Reviewer: Maayan                                                           *
 * ****************************************************************************/
#include <cstring> // strcmp, strcpy, strcat
#include <iostream>

#include "rcstring.hpp"
namespace hrd20
{

class RCString::RCData
{
public:
    
    ~RCData();

    void IncreaseRef();
    void DecreaseRef();

    size_t GetRefNum();
    size_t Length();
    const char* CStr();

    char& operator[](size_t _idx);
    const char& operator[](size_t _idx) const;

    static RCData* CreateInstance(const char* _str = " ", size_t _ref = 1);
    static void DestroyInstance(RCString::RCData* _instance);
private:
    explicit RCData(const char* _str = " ", size_t _ref = 1);
    size_t m_ref;
    char m_str[1];    
};


RCString::RCData::RCData(const char* _str, size_t _ref):  m_ref(_ref)
{
    strcpy(m_str, _str);
}

RCString::RCData::~RCData()
{}

/**************************CreatingAndDestroying*******************************/
RCString::RCData* RCString::RCData::CreateInstance(const char* _str, size_t _ref)
{
    
    void* buffer = ::operator new(strlen(_str) + 1 + sizeof(RCString::RCData));

    RCString::RCData* newInstance = new(buffer)RCData(_str, _ref);

    return newInstance;
}

void RCString::RCData::DestroyInstance(RCString::RCData* _instance)
{
    _instance->~RCData();

    ::operator delete(static_cast<void*>(_instance));
}
/**************************OperatorsAndFunctionality***************************/
char& RCString::RCData::operator[](size_t _idx)
{
    return const_cast<char&>(static_cast<const RCString::RCData*>(this)->m_str[_idx]);
}

const char& RCString::RCData::operator[](size_t _idx) const
{
    return m_str[_idx];
}

size_t RCString::RCData::Length()
{
    return strlen(m_str);
}   

const char* RCString::RCData::CStr()
{
    return m_str;
}

void RCString::RCData::IncreaseRef()
{
    ++m_ref;
}

void RCString::RCData::DecreaseRef()
{
    --m_ref;
}

size_t RCString::RCData::GetRefNum()
{
    return m_ref;
}
/**************************CharProxyImplementation*****************************/
RCString::CharProxy::CharProxy(RCString& _str, size_t _idx): m_str_ref(_str), m_idx(_idx)
{}

RCString::CharProxy& RCString::CharProxy::operator=(char c)
{
    m_str_ref.SetChar(m_idx, c);

    return *this;
}

RCString::CharProxy& RCString::CharProxy::operator=(const 
                                                    RCString::CharProxy& _other)
{

    m_str_ref.SetChar(m_idx, _other.m_str_ref.GetChar(_other.m_idx));

    return *this;
}                                                    


RCString::CharProxy::operator char() const
{
    return (m_str_ref.GetChar(m_idx));
}

/**************************RCStringImpelmentation******************************/
RCString::RCString(const char* _str): m_rc_data(RCString::RCData::CreateInstance(_str))
{}

RCString::~RCString()
{
    if (1 == m_rc_data->GetRefNum())
    {
        RCString::RCData::DestroyInstance(m_rc_data);
    }
    else
    {
        m_rc_data->DecreaseRef();
    }
}

RCString::RCString(const RCString& _other): m_rc_data(_other.m_rc_data)
{
    m_rc_data->IncreaseRef();
}

RCString& RCString::operator=(const RCString& _other)
{
    //copy and swap idiom
    RCString cpy(_other);
    std::swap(this->m_rc_data, _other.m_rc_data);
    return *this;
}

size_t RCString::Length() const
{
    return m_rc_data->Length();
}

const char* RCString::CStr() const
{
    return static_cast<const char*>(m_rc_data->CStr());
}
/******************PrivateBracketsCOWfunctionality*****************************/
void RCString::SetChar(size_t _idx, char c)
{
    // copy on write mechanism 
    if (1 == m_rc_data->GetRefNum())
    {
        (*m_rc_data)[_idx] = c;
    }
    else
    {
        m_rc_data->DecreaseRef();
        const char* dataStr = m_rc_data->CStr();

        m_rc_data = RCString::RCData::CreateInstance(dataStr);
        (*m_rc_data)[_idx] = c;
    }

}

char RCString::GetChar(size_t _idx) const
{
    return (*m_rc_data)[_idx];
}
/*******************************RCStringOperators******************************/
RCString::CharProxy RCString::operator[](size_t _idx)
{
    return CharProxy(*this, _idx);
}

const char& RCString::operator[](size_t _idx) const
{
    return (m_rc_data->CStr())[_idx];
}
RCString& RCString::operator+=(const RCString& _other)
{
    char* tempBuffer = new char[strlen(_other.m_rc_data->CStr()) + 1 + m_rc_data->Length()];
    strcpy(tempBuffer, m_rc_data->CStr());
    strcat(tempBuffer, _other.m_rc_data->CStr());

    if (1 == m_rc_data->GetRefNum())
    {
        RCString::RCData::DestroyInstance(m_rc_data);
    }
    else
    {
        m_rc_data->DecreaseRef();
    }
    m_rc_data = RCString::RCData::CreateInstance(tempBuffer);
    delete[] tempBuffer;

    return *this;

}

const RCString operator+(const RCString& _lhs, const RCString& _rhs)
{
    return (RCString(_lhs) += _rhs);
}

bool operator==(const RCString& _lhs, const RCString& _rhs)
{
    return (strcmp(_lhs.m_rc_data->CStr(), _rhs.m_rc_data->CStr()) == 0);
}

bool operator!=(const RCString& _lhs, const RCString& _rhs)
{
    return !(_lhs == _rhs);
}

bool operator>(const RCString& _lhs, const RCString& _rhs)
{
    return (strcmp(_lhs.m_rc_data->CStr(), _rhs.m_rc_data->CStr()) > 0);
}

bool operator<(const RCString& _lhs, const RCString& _rhs)
{
    return (_rhs > _lhs);
}

bool operator>=(const RCString& _lhs, const RCString& _rhs)
{
    return ((_lhs > _rhs) || (_lhs == _rhs));
}

bool operator<=(const RCString& _lhs, const RCString& _rhs)
{
    return ((_lhs < _rhs) || (_lhs == _rhs));
}

std::ostream& operator<<(std::ostream& os, const RCString& _str)
{
    return os << _str.m_rc_data->CStr();
}

std::istream& operator>>(std::istream& is, RCString& _str)
{
    _str = RCString();
    char tempStr[2];
    tempStr[1] = '\0';

    while((is.get(tempStr[0])) && ('\n' != tempStr[0]))
    {
        _str += RCString(tempStr);
    }

    return is;
}





/******************************ImplementationForWhiteBoxTesting****************/
size_t RCString::GetRCDataSize()
{
    return m_rc_data->GetRefNum();
}

} 