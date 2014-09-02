#ifndef SQLITEDRIVER_H
#define SQLITEDRIVER_H

#include "driverinterface.h"
#include "../service/DatastoreService.h"
#include <sqlite/connection.hpp>

namespace chorddb { namespace datastore {

class SqliteDriver : virtual public DriverInterface
{
    struct sqlite::connection::connection database;
public:
    SqliteDriver(std::string db);
    void put(const std::string &key, const std::string &value);
    void get(std::string &_return, const std::string &key) throw (DataNotFoundException);
    void remove(const std::string &key);
};

}}

#endif // SQLITEDRIVER_H
