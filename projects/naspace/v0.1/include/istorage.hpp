/*******************************************************************************
* Description: Interface Storage 
* Name: HRD20
* Reviewer - 
* Date: 20.01.22
* Versions: 1.0
* 0.1 - ready for review
* 0.2 - after minor adjustments
*******************************************************************************/ 
#ifndef ILRD_HRD_20_ISTORAGE_HPP
#define ILRD_HRD_20_ISTORAGE_HPP

#include <cstddef> /* size_t     */
#include <memory>  /* shared_ptr */
#include <string>  /* string     */

#include "driver_data.hpp"

namespace hrd20 
{

class IStorage 
{
public:
    explicit IStorage(size_t _size);
    virtual ~IStorage() = default;
    
    IStorage(const IStorage& _other) = delete;
    IStorage& operator=(const IStorage& _other) = delete;

    virtual void Read(std::shared_ptr<DriverData> _data) = 0; 
    virtual void Write(std::shared_ptr<DriverData> _data) = 0;

private:
    size_t m_size;
}; //IStorage

}

#endif // ILRD_HRD_20_ISTORAGE_HPP