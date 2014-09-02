#include "datastoreservice.h"

namespace chorddb { namespace datastore {

DataStoreService::~DataStoreService()
{
    delete driver;
}

void DataStoreService::put(const std::string& key, const std::string& value)
{
    driver->put(key, value);
}

void DataStoreService::get(std::string& _return, const std::string& key)
{
    driver->get(_return, key);
}

void DataStoreService::remove(const std::string& key)
{
    driver->remove(key);
}

}}
