#include "leveldbdriver.h"
#include <leveldb/cache.h>
#include <leveldb/filter_policy.h>

namespace chorddb { namespace datastore {

LevelDBDriver::LevelDBDriver(std::string db, bool sync)
{
    // Setup read/write options.
    readOptions = leveldb::ReadOptions();
    writeOptions = leveldb::WriteOptions();
    writeOptions.sync = sync;

    // Open/create database at location db.
    options = leveldb::Options();
    options.create_if_missing = true;
    options.block_cache = leveldb::NewLRUCache(LEVELDBDRIVER_CACHE_SIZE);
    options.filter_policy = leveldb::NewBloomFilterPolicy(10);
    leveldb::Status status = leveldb::DB::Open(options, db, &database);

    // Assert database is usable.
    assert(status.ok());
}

LevelDBDriver::~LevelDBDriver()
{
    delete database;
    delete options.block_cache;
    delete options.filter_policy;
}

void LevelDBDriver::put(const std::string &key, const std::string &value)
{
    leveldb::Status status = database->Put(writeOptions, key, value);
    assert(status.ok());
}

void LevelDBDriver::get(std::string &_return, const std::string &key)
{
    leveldb::Status status = database->Get(readOptions, key, &_return);
    assert(status.ok());
}

void LevelDBDriver::remove(const std::string &key)
{
    leveldb::Status status = database->Delete(writeOptions, key);
    assert(status.ok());
}

}}
