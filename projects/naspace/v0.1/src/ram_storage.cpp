/*******************************************************************************
* Description: Ram Storage Implementations
* Name: HRD20
* Reviewer - 
* Date: 20.01.22
* Versions: 1.0
* 0.1 - ready for review
*******************************************************************************/ 

#include "ram_storage.hpp"

namespace hrd20
{
IStorage::IStorage(size_t _size) : m_size(_size)
{}

IStorage::~IStorage()
{}

RAMStorage::RAMStorage(size_t _size) : IStorage(_size), m_buffer(_size, 0)
{}

void RAMStorage::Read(std::shared_ptr<DriverData> _data)
{}

void RAMStorage::Write(std::shared_ptr<DriverData> _data)
{}

} //hrd20