#ifndef DRIVERINTERFACE_H
#define DRIVERINTERFACE_H

#include <string>

class DriverInterface
{
public:
    virtual ~DriverInterface() {}
    virtual void put(const std::string& key, const std::string& value) = 0;
    virtual void get(std::string& _return, const std::string& key) = 0;
    virtual void remove(const std::string& key) = 0;
};

#endif // DRIVERINTERFACE_H
