#include "sqlitedriver.h"
#include <sqlite/execute.hpp>
#include <sqlite/query.hpp>
#include <sqlite/result.hpp>

namespace chorddb { namespace datastore {

SqliteDriver::SqliteDriver(std::string db) : database(db)
{
    sqlite::execute(database, "CREATE TABLE IF NOT EXISTS datastore(k TEXT, v TEXT);", true);
}

void SqliteDriver::put(const std::string &key, const std::string &value)
{
    sqlite::execute putCommand(database, "INSERT OR REPLACE INTO datastore(k,v) VALUES (?,?);");
    putCommand % key % value;
    putCommand();
}

void SqliteDriver::get(std::string &_return, const std::string &key) throw (DataNotFoundException)
{
    sqlite::query getQuery(database, "SELECT v FROM datastore WHERE k = ?;");
    getQuery % key;
    boost::shared_ptr<sqlite::result> result = getQuery.get_result();
    if(result->next_row())
    {
        _return = result->get_string(0);
    }
    else
    {
        throw DataNotFoundException();
    }
}

void SqliteDriver::remove(const std::string &key)
{
    sqlite::execute removeCommand(database, "DELETE FROM datastore WHERE k = ?;");
    removeCommand % key;
    removeCommand();
}

}}
