#ifndef CHORDDRIVER_H
#define CHORDDRIVER_H

#include "driverinterface.h"

namespace chorddb { namespace datastore {

class ChordDriver : virtual public DriverInterface
{
public:
    ChordDriver(std::string &ip, uint16_t &port);
    void put(const std::string &key, const std::string &value);
    void get(std::string &_return, const std::string &key);
    void remove(const std::string &key);
};

}}

#endif // CHORDDRIVER_H
