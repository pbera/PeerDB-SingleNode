#include "chordservice.h"
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
using namespace ::chorddb::middleware;

struct ProgramArguments {
    uint16_t    port;
    string      IP;
    bool        hasPeerInfo = false;
    uint16_t    chordPort;
    string      chordIP;
    string      overlayName;
    bool        leveldbSync;
};

void parseProgramArguments(ProgramArguments& args, int const argc, char** const argv)
{
    boost::program_options::options_description desc("Options");
    desc.add_options()
            ("version,v", "display version string and exit")
            ("help,h", "display this help message and exit")
            ("port", boost::program_options::value<uint16_t>(&args.port), "port number to listen on")
            ("ip", boost::program_options::value<string>(&args.IP), "external IP address of this machine")
            ("overlay-name", boost::program_options::value<string>(&args.overlayName)->default_value("datastore"), "overlay name")
            ("leveldb-sync", boost::program_options::value<bool>(&args.leveldbSync)->default_value(false)->implicit_value(true), "use leveldb in synchronous mode")
            ("chord-port", boost::program_options::value<uint16_t>(&args.chordPort), "port number of known chord node")
            ("chord-ip", boost::program_options::value<string>(&args.chordIP), "IP address of known chord node");

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

    if(vm.count("chord-port") && vm.count("chord-ip"))
    {
        args.hasPeerInfo = true;
    }
}

int main(int argc, char** argv)
{
    ProgramArguments args;
    parseProgramArguments(args, argc, argv);

    boost::shared_ptr<ChordService> chordHandler(new ChordService(args.IP, args.port));
    if(args.hasPeerInfo)
    {
        chordHandler->join(args.chordIP, args.chordPort);
    }
    else
    {
        chordHandler->setConfiguration(args.overlayName, args.leveldbSync);
    }
    chordHandler->init();
    boost::shared_ptr<TProcessor> processor(new ChordServiceProcessor(chordHandler));
    boost::shared_ptr<TServerTransport> serverTransport(new TServerSocket(args.port));
    boost::shared_ptr<TTransportFactory> transportFactory(new TFramedTransportFactory());
    boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

    TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);
    server.serve();

    return EXIT_SUCCESS;
}
