#include "chordservice.h"
#include <leveldb/cache.h>
#include <leveldb/filter_policy.h>
#include <sstream>
#include <openssl/sha.h>

namespace chorddb { namespace middleware {

ChordService::ChordService(std::string ip, uint16_t port)
{
    // Setup thisNode
    thisNode.address = ip;
    thisNode.port    = port;
    std::ostringstream oss;
    oss << ip << ":" << port;
    thisNode.id      = consistentHash(oss.str());

    // Setup leveldb options
    options = leveldb::Options();
    options.create_if_missing = true;
    readOptions = leveldb::ReadOptions();
    writeOptions = leveldb::WriteOptions();

    // Setup leveldb cache and filter policy
    //cache = leveldb::NewLRUCache(16*1024*1024);
    //filterPolicy = leveldb::NewBloomFilterPolicy(10);
}

void ChordService::init()
{
    //leveldb::Status status = leveldb::DB::Open(options, overlayName, &database);
    //assert(status.ok());
}

void ChordService::join(std::string ip, uint16_t port)
{

}

void ChordService::putEntity(const Entity &entity)
{

}

void ChordService::getEntity(Entity &_return, const Entity &entity)
{

}

void ChordService::deleteEntity(const Entity &entity)
{

}

void ChordService::ping(Node &_return)
{
    _return = thisNode;
}

void ChordService::notify(Node &_return, const Node &newNode)
{

}

void ChordService::getSuccessor(GetSuccessorResponse &_return, const int64_t id)
{

}

void ChordService::getFingerTable(std::vector<Node> &_return)
{
    for(std::vector<RemoteChordNode>::iterator it = fingerTable.begin(); it != fingerTable.end(); it++)
    {
        _return.push_back(*it);
    }
}

void ChordService::getConfiguration(GetConfigurationResponse &_return)
{
    _return.overlayName = overlayName;
    _return.leveldbSync = writeOptions.sync;
}

void ChordService::setConfiguration(std::string &overlayName, bool leveldbSync)
{
    this->overlayName = overlayName;
    writeOptions.sync = leveldbSync;
}

int64_t ChordService::consistentHash(const std::string& str)
{
//    unsigned char sha1Result[20];
//    const unsigned char* c_str = reinterpret_cast<const unsigned char*>(str.c_str());
//    SHA1(c_str, str.length(), sha1Result);
//    return *result;
}

bool ChordService::isBetween(const int64_t id, const Node &a, const Node &b)
{
    return false;
}

}}


