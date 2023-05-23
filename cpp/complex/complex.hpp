/*********************************************************************
* Description: Complex numbers
* Name: HRD20 - Ariel
* Reviewer - Doron
* Date: 12.12.21
* Versions: 1.0
* 0.1 - ready for review
*********************************************************************/

#ifndef ILRD_HRD_20_COMPLEX_HPP
#define ILRD_HRD_20_COMPLEX_HPP

#include <iostream> /* operator<<, operator>> */

namespace hrd20 
{

class Complex;

// All operators will be inline (non-members and members)
const Complex operator+(const Complex& lhs, const Complex& rhs);
const Complex operator-(const Complex& lhs, const Complex& rhs);
const Complex operator*(const Complex& lhs, const Complex& rhs);
const Complex operator/(const Complex& lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);

// The streams will in/out the complex number as "(real, imaginary)"
std::ostream& operator<<(std::ostream& os, const Complex& complex);
std::istream& operator>>(std::istream& is, Complex& complex);

class Complex
{
public:
    // Non-explicit on purpose
    Complex(double _real=0, double _imag=0);
    // Generated cctor
    // Generated dtor
    // Generated copy assignment

    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);
    Complex& operator/=(const Complex& other);

    void SetReal(double real);
    void SetImag(double imag);
    double GetReal() const;
    double GetImag() const;
    
private:
    /*friend const Complex operator+(const Complex& lhs, const Complex& rhs);
    friend const Complex operator-(const Complex& lhs, const Complex& rhs);
    friend const Complex operator*(const Complex& lhs, const Complex& rhs);
    friend const Complex operator/(const Complex& lhs, const Complex& rhs);*/

    friend bool operator==(const Complex& lhs, const Complex& rhs);
    //friend bool operator!=(const Complex& lhs, const Complex& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Complex& complex);
    friend std::istream& operator>>(std::istream& is, Complex& complex);

    double m_real;
    double m_imag;
}; //class Complex

/**************** Implemantation of member functions **************************/

inline Complex::Complex(double _real, double _imag) : m_real(_real), m_imag(_imag)
{}

inline Complex& Complex::operator+=(const Complex& other)
{
    m_real += other.m_real;
    m_imag += other.m_imag;

    return *this;
}

inline Complex& Complex::operator-=(const Complex& other)
{
    m_real -= other.m_real;
    m_imag -= other.m_imag;

    return *this;
}

inline Complex& Complex::operator*=(const Complex& other)
{
    double tmpReal = this->m_real;
    this->m_real = (this->m_real * other.m_real) - (this->m_imag * other.m_imag);
    this->m_imag = (tmpReal * other.m_imag) + (this->m_imag * other.m_real);

    return *this;
}

inline Complex& Complex::operator/=(const Complex& other)
{
    double tmpReal = m_real;
    double tmpImag = m_imag;
    double denom = (tmpReal * tmpReal) + (tmpImag * tmpImag);
    m_real = (tmpReal * other.m_real) + (tmpImag * other.m_imag);
    m_imag = -(tmpReal * other.m_imag) + (tmpImag * other.m_real);

    m_real /= denom;
    m_imag /= denom;

    return *this;
}

inline bool operator==(const Complex& lhs, const Complex& rhs)
{
    return (lhs.m_real == rhs.m_real) && (lhs.m_imag == rhs.m_imag);  
}

inline std::ostream& operator<<(std::ostream& os, const Complex& complex)
{
    return os << "(" << complex.m_real << ", " << complex.m_imag << ")" << std::endl;
}

inline std::istream& operator>>(std::istream& is, Complex& complex)
{
    return is >> complex.m_real >> complex.m_imag;
}

inline void Complex::SetReal(double real)
{
    m_real = real;
}

inline void Complex::SetImag(double imag)
{
    m_imag = imag;
}

inline double Complex::GetReal() const
{
    return m_real;
}

inline double Complex::GetImag() const
{
    return m_imag;
}

/**************** Implemntation of non-member functions ***********************/

inline const Complex operator+(const Complex& lhs, const Complex& rhs)
{
    Complex res(lhs);
    res += rhs;
    return res;

    //return Complex(lhs) += rhs;
}

inline const Complex operator-(const Complex& lhs, const Complex& rhs)
{
    Complex res(lhs);
    res -= rhs;
    return res;
}

inline const Complex operator*(const Complex& lhs, const Complex& rhs)
{
    Complex res(lhs);
    res *= rhs;
    return res;
}

inline const Complex operator/(const Complex& lhs, const Complex& rhs)
{
    Complex res(lhs);
    res /= rhs;
    return res;
}

inline bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return !(lhs == rhs);
}

} // namespace hrd20

#endif //ILRD_HRD_20_COMPLEX_HPP
