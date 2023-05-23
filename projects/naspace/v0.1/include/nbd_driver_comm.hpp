/*******************************************************************************
* Description: NBD Driver Communication 
* Name: HRD20
* Reviewer - 
* Date: 20.01.22
* Versions: 1.0
* 0.1 - ready for review
* 0.2 - after minor adjustments
*******************************************************************************/ 
#ifndef ILRD_HRD_20_NBD_DRIVER_COM_HPP
#define ILRD_HRD_20_NBD_DRIVER_COM_HPP

#include <cstddef> /* size_t      */
#include <memory>  /* shared_ptr  */
#include <string>  /* string      */
#include <thread>  /* std::thread */

#include "driver_data.hpp"
#include "idriver_com.hpp"

namespace hrd20 
{

class NBDDriver : public IDriverComm
{
public:
    explicit NBDDriver(const std::string& _deviceName, size_t storage_size);
    explicit NBDDriver(const std::string& _deviceName, 
                                            size_t block_size, size_t numBlock);
    ~NBDDriver() override;

    // the cctor, copy assignment blocked because of IdriverComm
    
    std::shared_ptr<DriverData> RetrieveRequest() override;
    void SendReply(std::shared_ptr<DriverData> _data) override;
    void Disconnect() override;
    int GetFD() const override;
    
private:
    size_t m_storage_size;
    int m_fd;
    std::thread m_thread; // not sure - probably  needed
    // TODO: other fields - personal for each imiplementation 
    // TODO: generic ioctl

}; //NBDDriver


/*class NBDDriverError : DriverError // TBD
{
public: 
    explicit NBDDriverError(const std::string _what);

    NBDDriverError(const NBDDriverError& _other);
    
    NBDDriverError& operator=(const NBDDriverError& _other);
    virtual ~NBDDriverError() = default;


private:
};*/

}

#endif // ILRD_HRD_20_NBD_DRIVER_COM_HPP