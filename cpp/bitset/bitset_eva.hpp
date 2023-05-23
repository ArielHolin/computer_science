/*******************************************************************************
* Description: Bit Set
* 
* Name: HRD20
* 
* Wariten by : Eva De-Botton
* 
* Reviewer : Ariel Holin
* 
* Date : 05/01/2022                                                           
* 
*******************************************************************************/
#ifndef ILRD_HRD_20_BitSet_HPP
#define ILRD_HRD_20_BitSet_HPP

#include <cstddef>      /*  size_t                  */
#include <cassert>      /*  assert                  */
#include <vector>       /*  vector                  */
#include <ostream>      /*  ostream                 */
#include <climits>      /*  CHAR_BIT                */
#include <algorithm>    /*  for_each transfore      */

namespace hrd20 
{

static const size_t BIT_IN_SIZE_T = sizeof(size_t) * CHAR_BIT;

////////////////////////////////////////////////////////////////////////////////
                            // <  class BitSet  >   
////////////////////////////////////////////////////////////////////////////////


template<size_t Size>
class BitSet;

template<size_t Size>
std::ostream& operator<<(std::ostream& _os, const BitSet<Size>& _bitset); 

template<size_t Size>
class BitSet
{
private:
    class BitProxy;
    

public:
    explicit BitSet(); // Calls to BitSet ctor may throw. 
    // using genereted ~, cctor, copy=
        
    BitSet& operator^=(const BitSet& _other); // XOR operation
    BitSet& operator&=(const BitSet& _other); // AND operation
    BitSet& operator|=(const BitSet& _other); // OR  operation
    bool operator==(const BitSet& _other) const;
    bool operator!=(const BitSet& _other) const;

    BitSet& operator<<=(size_t _shift); //shift ther bit set to the left
        
    size_t CountBitsOn() const;

    // Undefined behaviour if idx > length  // = 
    BitProxy operator[](size_t _idx);   
    const bool& operator[](size_t _idx) const;  // if (m_bitset[7])

private:
    std::vector<size_t> m_element;

    friend std::ostream& operator<<<>(std::ostream& _os, const BitSet& _bitset);

    bool GetBit(size_t _idx);
    void SetBit(bool _val, size_t _idx);
};

/******************************** Ctor BitSet *********************************/
template<size_t Size>
BitSet<Size>::BitSet(): m_element(((Size + BIT_IN_SIZE_T - 1) / BIT_IN_SIZE_T), 0)
{}

/******************************** operator ^= *********************************/

size_t XorAssignment(size_t left_element, size_t right_element)
{        
   return left_element ^= right_element; 

    //TODO
    /* I think that ^= is problematic, because then you change left_element.
       However, remember that transform function is already placing the result
       of ^ in m_element.begin() for you.
       
       So consider using return left_element ^ right_element;
    */

}

template<size_t Size>
BitSet<Size>& BitSet<Size>::operator^=(const BitSet& _other)
{
    return  std::transform( m_element.begin(), 
                            m_element.end(), 
                            _other.m_element.begin(),
                            m_element.begin(),
                            XorAssignment);
}

/******************************** operator &= *********************************/

struct AndAssignment 
{
    size_t operator()(size_t left_element, size_t right_element);
};

size_t AndAssignment::operator()(size_t left_element, size_t right_element)
{        
   return left_element &= right_element; 
   // TODO   same comment as ^
}

template<size_t Size>
BitSet<Size>& BitSet<Size>::operator&=(const BitSet& _other)
{
    return  std::transform( m_element.begin(), 
                            m_element.end(), 
                            _other.m_element.begin(),
                            m_element.begin(),
                            AndAssignment());
}

/********************************* operator |= ********************************/
template<size_t Size>
BitSet<Size>& BitSet<Size>::operator|=(const BitSet& _other)
{
    // TODO  What about this implementation ?
    return 0;
}

/******************************** operator == *********************************/
template<size_t Size>
bool BitSet<Size>::operator==(const BitSet& _other) const 
{
    return (m_element == _other.m_element);
}

/******************************** operator != *********************************/
template<size_t Size>
bool BitSet<Size>::operator!=(const BitSet& _other) const
{
    return !(m_element == _other.m_element);
}

/******************************** operator <<= ********************************/

size_t SetToZero(size_t _element)
{
    return 0; 
}

struct ShiftRes
{
    ShiftRes(size_t _shift);
    size_t operator()(size_t left_element, size_t right_element);

    size_t m_shift;
};

ShiftRes::ShiftRes(size_t _shift) : m_shift(_shift)
{}

size_t ShiftRes::operator()(size_t left_element, size_t right_element)
{
    return ((right_element >> (BIT_IN_SIZE_T - m_shift)) ^
            (left_element << m_shift));
}


template<size_t Size>
BitSet<Size>& BitSet<Size>::operator<<=(size_t _shift)
{
    size_t chank_to_shift = _shift / BIT_IN_SIZE_T;
    size_t res_to_shift   = _shift % BIT_IN_SIZE_T; 

    assert(chank_to_shift > m_element.size());

    std::transform( m_element.rbegin() + chank_to_shift,
                    m_element.rend() -1, 
                    m_element.rbegin() + chank_to_shift + 1,
                    m_element.rbegin(),
                    ShiftRes(res_to_shift));

    m_element[chank_to_shift] ^= (m_element[0] << res_to_shift);

    std::transform( m_element.begin(),
                    m_element.begin() + chank_to_shift, 
                    m_element.begin(),
                    SetToZero);
    return *this;
}

/******************************** Count Bits On *******************************/

struct HemingwayBitOn
{
    explicit HemingwayBitOn();
    void operator()(size_t _element);

    size_t counter;
    size_t mask1;
    size_t mask2;
    size_t mask4;
    size_t mask7f;
};

HemingwayBitOn::HemingwayBitOn() :  counter(0), 
                                    mask1(0x5555555555555555),
                                    mask2(0x3333333333333333),
                                    mask4(0x0f0f0f0f0f0f0f0f),
                                    mask7f(127)
{}

void HemingwayBitOn::operator()(size_t element)
{
    element = ((element + (element >> 1))  & mask1);
    element = ((element + (element >> 2))  & mask2); 
    element = ((element + (element >> 4))  & mask4); 
    element += element >> 8;
    element += element >> 16;
    element += element >> 32;

    counter += element & 0x7f; 
}

template<size_t Size>
size_t BitSet<Size>::CountBitsOn() const
{
    return (std::for_each(  m_element.begin(), 
                            m_element.end(), 
                            HemingwayBitOn())).counter;
}

/******************************** operator [] *********************************/
template<size_t Size>
typename BitSet<Size>::BitProxy BitSet<Size>::operator[](size_t _idx) 
{
    return BitProxy(*this, _idx);
}

/******************************** operator [] *********************************/
template<size_t Size>
const bool& BitSet<Size>::operator[](size_t _idx) const 
{
    return GetBit(_idx);
}

/*********************************** Set Char *********************************/
template<size_t Size>
void BitSet<Size>::SetBit(bool bit_state, size_t _idx)
{
    size_t chenk = _idx / BIT_IN_SIZE_T;
    size_t position = _idx % BIT_IN_SIZE_T;

    m_element[chenk] &= ~(size_t(1) << position);   
    m_element[chenk] |= (size_t(bit_state) << position); 
}

/*********************************** Get Char *********************************/
template<size_t Size>
bool BitSet<Size>::GetBit(size_t _idx)
{
    size_t chenk = _idx / BIT_IN_SIZE_T;
    size_t position = _idx % BIT_IN_SIZE_T;

    return (m_element[chenk] & (size_t(1) << position));
}

/******************************* friend ostream *******************************/

struct PrintBits
{
    explicit PrintBits(std::ostream& _os);
    void operator()(size_t element, size_t size = BIT_IN_SIZE_T);

    std::ostream& m_os;
};

PrintBits::PrintBits(std::ostream& _os) : m_os(_os)
{}

void PrintBits::operator()(size_t element, size_t size)
{
    size_t mask = size_t(1) << (size -1);

    while(mask)
    { 
        m_os << static_cast<bool>(element & mask);
        mask >>= 1; // TODO size_t(1)
    }
}

template<size_t Size>
std::ostream& operator<<(std::ostream& _os, const BitSet<Size>& _bitset)
{
    const size_t reminder = Size % BIT_IN_SIZE_T;

    PrintBits print_bits(_os);
    print_bits.operator()(_bitset.m_element[0], reminder);

    return std::for_each(_bitset.m_element.rbegin(), 
                         _bitset.m_element.rend() -1, print_bits).m_os;
}

////////////////////////////////////////////////////////////////////////////////
                            // <  class BitProxy  >   
////////////////////////////////////////////////////////////////////////////////

template<size_t Size>
class BitSet<Size>::BitProxy
{
public:
    explicit BitProxy(BitSet& _bit_set, size_t _idx);
    // depends on generated dtor, cctor
    BitProxy& operator=(bool c);  //m_bitset[7] = true
    BitProxy& operator=(const BitProxy& _other);
    operator bool() const;

private:
    BitSet& m_bitset;
    size_t m_idx;
};

/******************************* Ctor BitProxy ********************************/
template<size_t Size>
BitSet<Size>::BitProxy::BitProxy(BitSet& _bit_set, size_t _idx) :  
                                            m_bitset(_bit_set), m_idx(_idx) 
{} 

/********************************* operator = *********************************/
template<size_t Size>
typename BitSet<Size>::BitProxy& BitSet<Size>::BitProxy::operator=(bool state)
{
    m_bitset.SetBit(state, m_idx);

    return *this;
}

/********************************* operator = *********************************/
template<size_t Size>
typename BitSet<Size>::BitProxy& BitSet<Size>::BitProxy::operator=(const BitProxy& _other)
{
    return *this = static_cast<bool>(_other);
}

/************************************ bool ************************************/
template<size_t Size>
BitSet<Size>::BitProxy::operator bool() const 
{
    return m_bitset.GetBit(m_idx);
}

}//hrd20
#endif//ILRD_HRD_20_BitSet_HPP

 