/*******************************************************************************
* Description: Ram Storage 
* Name: HRD20
* Reviewer - 
* Date: 20.01.22
* Versions: 1.0
* 0.1 - ready for review
* 0.2 - after minor adjustments
*******************************************************************************/ 
#ifndef ILRD_HRD_20_RAM_STORAGE_HPP
#define ILRD_HRD_20_RAM_STORAGE_HPP

#include <cstddef> /* size_t     */
#include <memory>  /* shared_ptr */
#include <vector>  /* vector     */

#include "driver_data.hpp"
#include "istorage.hpp"

namespace hrd20 
{

class RAMStorage : public IStorage
{
public:
    explicit RAMStorage(size_t _size);
    virtual ~RAMStorage() = default;
    
    void Read(std::shared_ptr<DriverData> _data) override;
    void Write(std::shared_ptr<DriverData> _data) override; 
    
private:
    std::vector<char> m_buffer;
}; //RAMStorage

}

#endif // ILRD_HRD_20_RAM_STORAGE_HPP