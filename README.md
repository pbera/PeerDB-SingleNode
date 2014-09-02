PeerDB-SingleNode
=================
A single datastore node accepts read/write/delete requests from multiple clients over network and persists data using leveldb or sqlite storage driver.

How to Build
============

Build Tools
-----------
+ cmake
+ Linux build tool-chain (make, g++, ld etc.)

Requirements
------------
Development rpms from CentOS & EPEL repos

+ thrift-devel
    + boost-devel
+ leveldb-devel
+ vsqlitepp-devel

Compile
-------
```sh
$ git clone https://github.com/pbera/PeerDB-SingleNode.git
$ mkdir build-PeerDB-SingleNode
$ cd build-PeerDB-SingleNode
$ cmake -DCMAKE_BUILD_TYPE=Debug ../PeerDB-SingleNode/CMakeLists.txt
$ make
```
Run datastore server
--------------------
```sh
$ ./datastore --help
Options:
  -v [ --version ]                 display version string and exit
  -h [ --help ]                    display this help message and exit
  -p [ --port ] arg                port number to listen on
  --driver arg (=leveldb)          storage driver (leveldb|sqlite|chord)
  --sqlite-file arg (=./sqlite.db) path to sqlite database file
  --leveldb-path arg (=./leveldb)  path to leveldb database folder
  --leveldb-sync [=arg(=1)] (=0)   use leveldb in synchronous mode
  --chord-port arg                 port number of the chord node
  --chord-ip arg                   IP address of the chord node
```
Run datastore client
--------------------
```sh
$ ./client --help
Options:
  -v [ --version ]      display version string and exit
  -h [ --help ]         display this help message and exit
  -p [ --port ] arg     datastore server port
  -i [ --ip ] arg       datastore server IP address
```
To Do
=====
+ Common client-side API for data operations from SingleNode server and Overlay Broker nodes
+ Logging and Benchmarking (IOPS & Latency) support in clients

