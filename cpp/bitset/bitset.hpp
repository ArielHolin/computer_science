/*********************************************************************
* Description: BitSet
* Name: Ariel
* Reviewer - 
* Date: 3.1.22
* Versions: 1.0
* 0.1 - ready for review
*********************************************************************/
#ifndef ILRD_HRD_20_BitSet_HPP
#define ILRD_HRD_20_BitSet_HPP

#include <cstddef>      /*  size_t                  */
#include <vector>       /*  vector                  */
#include <ostream>      /*  ostream                 */
#include <climits>      /*  CHAR_BIT                */
#include <algorithm>    /* transform                */

namespace hrd20 
{

/************* Class declarations *********************************************/

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
    explicit BitSet();
    //using genereted ~, cctor, copy=
        
    BitSet& operator^=(const BitSet& _other);// XOR operation
    BitSet& operator&=(const BitSet& _other);// AND operation
    BitSet& operator|=(const BitSet& _other);// OR  operation
    bool operator==(const BitSet& _other) const;
    bool operator!=(const BitSet& _other) const;

    BitSet& operator<<=(size_t _shift);//shift ther bit set to the left
        
    size_t CountBitsOn() const;

    //Undefined behaviour if idx > length    // = 
    BitProxy operator[](size_t _idx);   
    const bool& operator[](size_t _idx) const;

private:
    std::vector<size_t> m_bit_array;

    friend std::ostream& operator<<<>(std::ostream& _os, const BitSet& _bitset); 
    bool GetBit(size_t _idx) const;
    void SetBit(bool _val, size_t _idx);
};

template<size_t Size>
class BitSet<Size>::BitProxy
{
public:
    explicit BitProxy(BitSet& _bit_set, size_t _idx);
    // depends on generated dtor, cctor
    BitProxy& operator=(bool c);
    BitProxy& operator=(const BitProxy& _other);
    operator bool() const;

private:
    BitSet& m_bitset;
    size_t m_idx;
};

/*************** End of class declarations ************************************/

/*************** Additional data needed ***************************************/

static const size_t BITS_IN_WORD = sizeof(size_t) * CHAR_BIT;

/* Enumerating operations */
enum Op
{
    XOR = 0,
    AND,
    OR
};

/* Functor for operations ^=, &=, |= */
class Operation
{
public:
    explicit Operation(Op _oper);
    // depends on generated dtor, cctor, copy =
    size_t operator()(size_t chunk1, size_t chunk2);

private:
    Op m_operation;
}; //Operation

Operation::Operation(Op _oper) : m_operation(_oper) {}

size_t Operation::operator()(size_t chunk1, size_t chunk2)
{
    switch(m_operation)
    {
        case XOR:
            return (chunk1 ^ chunk2);
        case AND:
            return (chunk1 & chunk2);
        case OR:
            return (chunk1 | chunk2);
    }

    return 0;
}

/* Functor for CountBitsOn */
class CountSetBits
{
public:
    explicit CountSetBits();
    // depends on generated dtor, cctor, copy =
    void operator()(size_t chunk);
    size_t GetMCounter() const;

private:
    size_t m_counter;
}; //CountSetBits

CountSetBits::CountSetBits() : m_counter(0) {}

void CountSetBits::operator()(size_t chunk)
{
    size_t localCounter = 0;

    while(chunk)
    {
        ++localCounter;
        chunk &= (chunk - 1);
    }

    m_counter += localCounter;
}

size_t CountSetBits::GetMCounter() const
{
    return m_counter;
}

/* Functor for shifting */
class Shift
{
public:
    explicit Shift(size_t _pos);
    size_t operator()(size_t chunk1, size_t chunk2);

private:
    size_t m_position;
}; //Shift

Shift::Shift(size_t _pos) : m_position(_pos) {}

size_t Shift::operator()(size_t chunk1, size_t chunk2)
{
    return ((chunk1 << m_position) ^ (chunk2 >> (BITS_IN_WORD - m_position)));
}

/* Function to set size_t chunks to 0 */
size_t SetToZero()
{
    return 0;
}

/* Functor for ostream */
class Print
{
public:
    Print(std::ostream& _os);
    void operator()(size_t chunk);

private:
    std::ostream& m_os;
}; //Print

Print::Print(std::ostream& _os) : m_os(_os) {}

Print::operator()(size_t chunk)
{
    size_t mask = (1 << (BITS_IN_WORD - 1));

    while(mask)
    {
        m_os << mask & chunk;
        mask >>= size_t(1);
    }
}


/*************** End Additional data needed ***********************************/

/*************** Class definitions ********************************************/

/* Class BitProxy */

template<size_t Size>
BitSet<Size>::BitProxy::BitProxy(BitSet& _bit_set, size_t _idx) : 
                                              m_bitset(_bit_set), m_idx(_idx) {}

template<size_t Size>
typename BitSet<Size>::BitProxy& BitSet<Size>::BitProxy::operator=(bool c)
{
    m_bitset.SetBit(c, m_idx);

    return *this;
}

template<size_t Size>
typename BitSet<Size>::BitProxy& BitSet<Size>::BitProxy::operator=
                                                        (const BitProxy& _other)
{
    m_bitset.SetBit(_other.m_setbit.GetBit(_other.m_idx), m_idx);

    return *this;
}

template<size_t Size>
BitSet<Size>::BitProxy::operator bool() const
{
    return m_bitset.GetBit(m_idx);
}

/* End Class BitProxy */

/* Class BitSet */

template<size_t Size>
BitSet<Size>::BitSet() : 
                 m_bit_array((Size / BITS_IN_WORD) + !!(Size % BITS_IN_WORD), 0) 
{}

template<size_t Size>
BitSet<Size>& BitSet<Size>::operator^=(const BitSet& _other)
{
    std::transform(m_bit_array.begin(), m_bit_array.end(), 
               _other.m_bit_array.begin(), m_bit_array.begin(), Operation(XOR));

    return *this;
}

template<size_t Size>
BitSet<Size>& BitSet<Size>::operator&=(const BitSet& _other)
{
    std::transform(m_bit_array.begin(), m_bit_array.end(), 
               _other.m_bit_array.begin(), m_bit_array.begin(), Operation(AND));

    return *this;
}

template<size_t Size>
BitSet<Size>& BitSet<Size>::operator|=(const BitSet& _other)
{
    std::transform(m_bit_array.begin(), m_bit_array.end(), 
                _other.m_bit_array.begin(), m_bit_array.begin(), Operation(OR));

    return *this;
}

template<size_t Size>
bool BitSet<Size>::operator==(const BitSet& _other) const
{
    return std::equal(m_bit_array.begin(), m_bit_array.end(), 
                                                    _other.m_bit_array.begin());
}

template<size_t Size>
bool BitSet<Size>::operator!=(const BitSet& _other) const
{
    return !(*this == _other);
}

template<size_t Size>
BitSet<Size>& BitSet<Size>::operator<<=(size_t _shift)
{
    size_t chunk = _shift / BITS_IN_WORD;
    size_t position = _shift % BITS_IN_WORD;

    std::transform(m_bit_array.rbegin() + chunk, m_bit_array.rend() - 1, 
                   m_bit_array.rbegin() + chunk + 1, m_bit_array.rbegin(), 
                   Shift(position));
    
    m_bit_array[chunk] = (m_bit_array[0] << position);

    std::transform(m_bit_array.begin(), m_bit_array.begin() + chunk,
                                                m_bit_array.begin(), SetToZero);

    return *this;
}

template<size_t Size>
size_t BitSet<Size>::CountBitsOn() const
{
    return std::for_each(m_bit_array.begin(), m_bit_array.end(), 
                                                  CountSetBits()).GetMCounter();    
}

template<size_t Size>
typename BitSet<Size>::BitProxy BitSet<Size>::operator[](size_t _idx)
{
    return BitProxy(*this, _idx);    
}

template<size_t Size>
const bool& BitSet<Size>::operator[](size_t _idx) const
{
    return GetBit(_idx);
}

template<size_t Size>
std::ostream& operator<<(std::ostream& _os, const BitSet<Size>& _bitset)
{
    size_t mask = (1 << (BITS_IN_WORD - 1));
    size_t remainder = Size % BITS_IN_WORD;

    std::for_each(_bitset.m_bit_array.begin(), _bitset.m_bit_array.end(), 
                                                                    Print(_os));


}

template<size_t Size>
bool BitSet<Size>::GetBit(size_t _idx) const
{
    size_t vectorInd = _idx / BITS_IN_WORD;
    size_t position = _idx % BITS_IN_WORD;

    return (m_bit_array[vectorInd] & (size_t(1) << position));
}

template<size_t Size>
void BitSet<Size>::SetBit(bool _val, size_t _idx)
{
    size_t vectorInd = _idx / BITS_IN_WORD;
    size_t position = _idx % BITS_IN_WORD;
    
    m_bit_array[vectorInd] &= ~(size_t(1) << position);
    m_bit_array[vectorInd] |= ((static_cast<size_t>(_val) << position));
}

/* End Class BitSet */

/*************** End of class definitions *************************************/

}//hrd20
#endif//ILRD_HRD_20_BitSet_HPP

