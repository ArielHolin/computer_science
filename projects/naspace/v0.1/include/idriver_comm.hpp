/*******************************************************************************
* Description: IDriver Communication 
* Name: HRD20
* Reviewer - 
* Date: 20.01.22
* Versions: 1.0
* 0.1 - ready for review
* 0.2 - after minor adjustments
*******************************************************************************/ 
#ifndef ILRD_HRD_20_IDRIVER_COM_HPP
#define ILRD_HRD_20_IDRIVER_COM_HPP

#include <cstddef>   /* size_t   */
#include <stdexcept> /* run_time */
#include <string>    /* string   */

#include "driver_data.hpp"

namespace hrd20 
{

class IDriverComm
{
public:
    explicit IDriverComm() = default;
    virtual ~IDriverComm() = default;

    IDriverComm(const IDriverComm& _other) = delete;
    IDriverComm& operator=(const IDriverComm& _other) = delete;

    virtual std::shared_ptr<DriverData> RetrieveRequest() = 0;
    virtual void SendReply(std::shared_ptr<DriverData> _data) = 0;
    virtual void Disconnect() = 0;
    virtual int GetFD() const = 0;
}; //IDriverComm


/*class DriverError : std::runtime_error // TBD - up to anyone 
{
public:
    explicit DriverError(const std::string& what_arg);
    DriverError(const DriverError& _other);
    
    DriverError& operator=(const DriverError& _other);
    virtual ~DriverError() = default;

private:
    // TBD
};*/



}

#endif // ILRD_HRD_20_IDRIVER_COM_HPP