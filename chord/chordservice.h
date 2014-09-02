#ifndef CHORDSERVICE_H
#define CHORDSERVICE_H

#include "../service/ChordService.h"
#include "remotechordnode.h"
#include <leveldb/db.h>

namespace chorddb { namespace middleware {

typedef std::vector<RemoteChordNode> FingerTable;

class ChordService : virtual public ChordServiceIf
{
    Node                                    thisNode;
    RemoteChordNode                         successorNode, predecessorNode;
    FingerTable                             fingerTable;

    std::string                             overlayName;

    std::unique_ptr<leveldb::DB>            database;
    std::unique_ptr<leveldb::Cache>         cache;
    std::unique_ptr<leveldb::FilterPolicy>  filterPolicy;
    leveldb::Options                        options;
    leveldb::ReadOptions                    readOptions;
    leveldb::WriteOptions                   writeOptions;
public:
    ChordService(std::string ip, uint16_t port);
    void init();
    void join(std::string ip, uint16_t port);
    void setConfiguration(std::string& overlayName, bool leveldbSync);

    // ChordServiceIf Implementation
    void putEntity(const Entity& entity);
    void getEntity(Entity& _return, const Entity& entity);
    void deleteEntity(const Entity& entity);
    void ping(Node& _return);
    void notify(Node& _return, const Node& newNode);
    void getSuccessor(GetSuccessorResponse& _return, const int64_t id);
    void getFingerTable(std::vector<Node> & _return);    
    void getConfiguration(GetConfigurationResponse &_return);

private:
    int64_t consistentHash(const std::string& str);
    bool isBetween(const int64_t id, const Node& a, const Node& b);
};

}}

#endif // CHORDSERVICE_H
