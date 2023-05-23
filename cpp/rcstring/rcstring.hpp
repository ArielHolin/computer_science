/*********************************************************************
* Description: RCString
* Name: Ariel
* Reviewer - Maayan
* Date: 26.12.21
* Versions: 1.0
* 0.1 - ready for review
*********************************************************************/

#ifndef ILRD_HRD_20_RCSTRING_HPP
#define ILRD_HRD_20_RCSTRING_HPP

#include <iosfwd>       /*  istream, ostream fwd     */
#include <cstring>      /*  c string functions        */
#include <cstddef>      /*  size_t                  */

namespace hrd20 
{

class RCString;

const RCString operator+(const RCString& _lhs, const RCString& _rhs);

bool operator==(const RCString& _lhs, const RCString& _rhs);
bool operator!=(const RCString& _lhs, const RCString& _rhs);
bool operator< (const RCString& _lhs, const RCString& _rhs);
bool operator> (const RCString& _lhs, const RCString& _rhs);
bool operator>=(const RCString& _lhs, const RCString& _rhs);
bool operator<=(const RCString& _lhs, const RCString& _rhs);

std::ostream& operator<<(std::ostream& _os, const RCString& _str);
std::istream& operator>>(std::istream& _is, RCString& _str);

class RCString
{
private:
    class CharProxy;
public:
    
    // Non-explicit on purpose
    RCString(const char* _str = "");
    RCString(const RCString& _other);
    ~RCString();
    RCString& operator=(const RCString& _other);
    RCString& operator+=(const RCString& _other);
    
    size_t Length() const;
    CharProxy operator[](size_t _idx); //Undefined behaviour if idx > length 

    const char& operator[](size_t _idx) const;  //Undefined behaviour if idx > length  // ==

    const char* CStr() const;

    // for gray box testing
    size_t GetRCDataSize();
private:
    class RCData;

    void SetChar(size_t _idx, char c);
    char GetChar(size_t _idx) const;

    friend bool operator==(const RCString& _lhs, const RCString& _rhs);
    friend bool operator>(const RCString& _lhs, const RCString& _rhs);
    friend std::ostream& operator<<(std::ostream& os, const RCString& _str);
    friend std::istream& operator>>(std::istream& is, RCString& _str);

    RCData* m_rc_data;    
};

// nothing to see here mr.
class RCString::CharProxy
{
public:
    explicit CharProxy(RCString& _str, size_t _idx);
    // depends on generated dtor, cctor
    CharProxy& operator=(char c); // S1[i] = 'a'
    CharProxy& operator=(const CharProxy& _other); // s1[i] = s2[m]
    operator char() const; // char c = s1[i]
private:
    RCString& m_str_ref;
    size_t m_idx;
};

}//hrd20
#endif//ILRD_HRD_20_RCSTRING_HPP