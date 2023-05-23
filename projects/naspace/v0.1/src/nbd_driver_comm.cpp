/*******************************************************************************
* Description: NBD Driver Communication Implementation 
* Name: HRD20
* Reviewer - 
* Date: 20.01.22
* Versions: 1.0
* 0.1 - ready for review
* 0.2 - after adjustments
*******************************************************************************/

#include "nbd_driver_comm.hpp"

namespace hrd20
{
NBDDriver::NBDDriver(const std::string& _deviceName, size_t storage_size)
{}

NBDDriver::~NBDDriver()
{}

std::shared_ptr<DriverData> NBDDriver::RetrieveRequest()
{}

void NBDDriver::SendReply(std::shared_ptr<DriverData> _data)
{}

void NBDDriver::Disconnect()
{}

int NBDDriver::GetFD() const
{}

}//hrd20