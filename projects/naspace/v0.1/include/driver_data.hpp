/*******************************************************************************
* Description: Driver Data 
* Name: HRD20
* Reviewer - 
* Date: 20.01.22
* Versions: 1.0
* 0.1 - ready for review
* 0.2 - after minor adjustments
*******************************************************************************/ 
#ifndef ILRD_HRD_20_DRIVER_DATA_HPP
#define ILRD_HRD_20_DRIVER_DATA_HPP

#include <cstddef> /* size_t */
#include <vector>  /* vector */

namespace hrd20 
{

struct DriverData
{

    explicit DriverData(size_t _len);
    DriverData(const DriverData& _other) = default;
    DriverData& operator=(const DriverData& _other) = default;
    ~DriverData() = default;

    
    enum ACTION_TYPE {READ, WRITE, DISCONNECT, FLUSH, TRIM};
    enum STATUS_TYPE {SUCCESS, FAILURE};

    ACTION_TYPE m_type; 
    size_t  m_offset;
    size_t m_len;
    size_t m_handle;
    STATUS_TYPE m_status;
    std::vector<char> m_buffer;

}; //DriverData

}

#endif // ILRD_HRD_20_DRIVER_DATA_HPP