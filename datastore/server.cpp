#include "datastoreservice.h"
#include "driver.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <cstdlib>
#include <string>
#include <boost/program_options.hpp>

#define PROGRAM_VERSION "0.0.1"

using namespace std;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::chorddb::datastore;

struct ProgramArguments {
    uint16_t    port;
    string      driver;
    string      sqliteFile;
    string      leveldbPath;
    bool        leveldbSync;
    uint16_t    chordPort;
    string      chordIP;
};

void parseProgramArguments(ProgramArguments& args, int const argc, char** const argv)
{
    boost::program_options::options_description desc("Options");
    desc.add_options()
            ("version,v", "display version string and exit")
            ("help,h", "display this help message and exit")
            ("port,p", boost::program_options::value<uint16_t>(&args.port), "port number to listen on")
            ("driver", boost::program_options::value<string>(&args.driver)->default_value("leveldb"), "storage driver (leveldb|sqlite|chord)")
            ("sqlite-file", boost::program_options::value<string>(&args.sqliteFile)->default_value("./sqlite.db"), "path to sqlite database file")
            ("leveldb-path", boost::program_options::value<string>(&args.leveldbPath)->default_value("./leveldb"), "path to leveldb database folder")
            ("leveldb-sync", boost::program_options::value<bool>(&args.leveldbSync)->default_value(false)->implicit_value(true), "use leveldb in synchronous mode")
            ("chord-port", boost::program_options::value<uint16_t>(&args.chordPort), "port number of the chord node")
            ("chord-ip", boost::program_options::value<string>(&args.chordIP), "IP address of the chord node");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
    boost::program_options::notify(vm);

    if(vm.count("version"))
    {
        cout << PROGRAM_VERSION << endl;
        exit(EXIT_SUCCESS);
    }

    if(vm.count("help"))
    {
        cout << desc << endl;
        exit(EXIT_SUCCESS);
    }

    if(args.driver == "chord")
    {
        if(!(vm.count("chord-port") && vm.count("chord-ip")))
        {
            cout << "Error: chord-port and chord-ip not provided." << endl;
            cout << desc << endl;
            exit(EXIT_SUCCESS);
        }
    }
}

int main(int argc, char** argv)
{
    ProgramArguments args;
    parseProgramArguments(args, argc, argv);

    DriverInterface* storageDriver;
    if(args.driver == "sqlite")
    {
        storageDriver = new SqliteDriver(args.sqliteFile);
    }
    else if(args.driver == "leveldb")
    {
        storageDriver = new LevelDBDriver(args.leveldbPath, args.leveldbSync);
    }
//    else if(args.driver == "chord")
//    {
//        storageDriver = new ChordDriver(args.chordIP, args.chordPort);
//    }
    else
    {
        cout << "Unknown storage driver: " << args.driver << endl;
        return EXIT_FAILURE;
    }

    boost::shared_ptr<DataStoreService> handler(new DataStoreService(storageDriver));
    boost::shared_ptr<TProcessor> processor(new DatastoreServiceProcessor(handler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(args.port));
    boost::shared_ptr<TTransportFactory> transportFactory(new TFramedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());
    TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();

    return EXIT_SUCCESS;
}
