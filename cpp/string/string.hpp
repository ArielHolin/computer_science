/*********************************************************************
* Description: String
* Name: HRD20 - Ariel
* Reviewer - Maayan 
* Date: 14.12.21
* Versions: 1.0
* 0.1 - ready for review
*********************************************************************/

#ifndef ILRD_HRD_20_STRING_HPP
#define ILRD_HRD_20_STRING_HPP

#include <iosfwd>       /* istream, ostream fwd     */
#include <cstring>      /*  c string functions      */
#include <cstddef>      /*  size_t                  */

namespace hrd20 
{

class String;

const String operator+(const String& _lhs, const String& _rhs);

bool operator==(const String& _lhs, const String& _rhs);
bool operator!=(const String& _lhs, const String& _rhs);
bool operator<(const String& _lhs, const String& _rhs);
bool operator>(const String& _lhs, const String& _rhs);
bool operator>=(const String& _lhs, const String& _rhs);
bool operator<=(const String& _lhs, const String& _rhs);

std::ostream& operator<<(std::ostream& _os, const String& _str);
std::istream& operator>>(std::istream& _is, String& _str);

class String
{
public:
    // Non-explicit on purpose
    String(const char* _str = "");
    String(const String& _other);
    ~String();
    String& operator=(const String& _other);
    String& operator+=(const String& _other);

    size_t Length() const;

    char& operator[](size_t _idx);   //Undefined behaviour if idx > length    // = 
    const char& operator[](size_t _idx) const;   //Undefined behaviour if idx > length  // ==

    const char* CStr() const;
private:
    friend bool operator==(const String& _lhs, const String& _rhs);
    friend bool operator>(const String& _lhs, const String& _rhs);
    friend std::ostream& operator<<(std::ostream& _os, const String& _str);
    friend std::istream& operator>>(std::istream& _is, String& _str);

    static char* InitResources(const char* _str);
    void DelResources();

    char* m_str;
};

}//hrd20
#endif//ILRD_HRD_20_STRING_HPP