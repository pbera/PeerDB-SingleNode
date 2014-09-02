#include "../service/DatastoreService.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include <cstdlib>
#include <string>
#include <map>
#include <boost/program_options.hpp>

#define PROGRAM_VERSION "0.0.1"

using namespace std;
using namespace ::chorddb::datastore;
using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;

typedef map<string, string> kvmap_t;
typedef map<string, string>::iterator kvmap_iter_t;

kvmap_t get_kvmap()
{
    kvmap_t keyValuePairs{
        {"key0", "value0"},
        {"key1", "value1"},
        {"key2", "value2"},
        {"key3", "value3"},
        {"key4", "value4"},
        {"key5", "value5"},
        {"key6", "value6"},
        {"key7", "value7"}
    };
    return keyValuePairs;
}

struct ProgramArguments {
    uint16_t    port;
    string      IP;
};

void parseProgramArguments(ProgramArguments& args, int const argc, char** const argv)
{
    boost::program_options::options_description desc("Options");
    desc.add_options()
            ("version,v", "display version string and exit")
            ("help,h", "display this help message and exit")
            ("port,p", boost::program_options::value<uint16_t>(&args.port), "datastore server port")
            ("ip,i", boost::program_options::value<string>(&args.IP), "datastore server IP address");

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

    // Assert correctness of arguments
}

int main(int argc, char** argv)
{
    ProgramArguments args;
    parseProgramArguments(args, argc, argv);
    boost::shared_ptr<TSocket> socket(new TSocket(args.IP, args.port));
    boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    DatastoreServiceClient client(protocol);
    transport->open();
    string result;
    kvmap_t keyValuePairs = get_kvmap();

    // PUT
    for(kvmap_iter_t it = keyValuePairs.begin(); it != keyValuePairs.end(); ++it)
    {
        client.put(it->first, it->second);
        cout << "put(" << it->first << ", " << it->second << ")" << endl;
    }

    // GET
    for(kvmap_iter_t it = keyValuePairs.begin(); it != keyValuePairs.end(); ++it)
    {
        try
        {
            client.get(result, it->first);
        }
        catch(DataNotFoundException& dnfException)
        {
            continue;
        }
        cout << "get(" << it->first << ") = " << result << endl;
    }

    // REMOVE
    for(kvmap_iter_t it = keyValuePairs.begin(); it != keyValuePairs.end(); ++it)
    {
        cout << "remove(" << it->first << ")" << endl;
        client.remove(it->first);
    }

    transport->close();
    return EXIT_SUCCESS;
}
