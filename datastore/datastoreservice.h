#ifndef DATASTORESERVICE_H
#define DATASTORESERVICE_H

#include "../service/DatastoreService.h"
#include "driverinterface.h"

namespace chorddb { namespace datastore {

class DataStoreService : virtual public DatastoreServiceIf
{
    DriverInterface* driver;
public:
    DataStoreService(DriverInterface* storageDriver) : driver(storageDriver) {}
    ~DataStoreService();
    void put(const std::string& key, const std::string& value);
    void get(std::string& _return, const std::string& key);
    void remove(const std::string& key);
};

}}

#endif // DATASTORESERVICE_H
