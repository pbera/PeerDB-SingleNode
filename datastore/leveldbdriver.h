#ifndef LEVELDBDRIVER_H
#define LEVELDBDRIVER_H

#include "driverinterface.h"
#include "../service/DatastoreService.h"
#include <leveldb/db.h>

#define LEVELDBDRIVER_CACHE_SIZE (50*1024*1024)

namespace chorddb { namespace datastore {

class LevelDBDriver : virtual public DriverInterface
{
    leveldb::DB* database;
    leveldb::Options options;
    leveldb::ReadOptions readOptions;
    leveldb::WriteOptions writeOptions;
public:
    LevelDBDriver(std::string db, bool sync);
    ~LevelDBDriver();
    void put(const std::string &key, const std::string &value);
    void get(std::string &_return, const std::string &key);
    void remove(const std::string &key);
};

}}

#endif // LEVELDBDRIVER_H
