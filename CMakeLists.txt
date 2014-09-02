project(ChordDB)
cmake_minimum_required(VERSION 2.8)

add_definitions(-DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H)
set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

# DATASTORE SERVER
set(DATASTORE_THRIFT_SRC service/datastore_constants.cpp  service/datastore_types.cpp service/DatastoreService.cpp)
set(DATASTORE_IMPL_SRC datastore/server.cpp datastore/datastoreservice.cpp datastore/sqlitedriver.cpp datastore/leveldbdriver.cpp)

add_executable(datastore ${DATASTORE_THRIFT_SRC} ${DATASTORE_IMPL_SRC})
target_link_libraries(datastore vsqlitepp leveldb boost_program_options thrift)

# CHORD STORAGE NODE
#set(CHORD_THRIFT_SRC service/chord_constants.cpp service/chord_types.cpp service/ChordService.cpp)
#set(CHORD_IMPL_SRC chord/chordservice.cpp chord/remotechordnode.cpp chord/chordnode.cpp)

#add_executable(chord ${CHORD_IMPL_SRC} ${CHORD_THRIFT_SRC})
#target_link_libraries(chord boost_program_options thrift crypto leveldb)

# DATASTORE CLIENT
add_executable(client datastore/client.cpp ${DATASTORE_THRIFT_SRC})
target_link_libraries(client boost_program_options thrift)

