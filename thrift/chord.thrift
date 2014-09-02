namespace cpp chorddb.middleware

enum ErrorCode {
  UNKNOWN
}

exception ChordException {
  1: ErrorCode errorCode,
  2: string what
}

struct Node {
  1: i64 id,
  2: i32 port,
  3: string address
}

struct GetSuccessorResponse {
  1: bool nodeIsSuccessor,
  2: Node node
}

struct GetConfigurationResponse {
  1: bool leveldbSync,
  2: string overlayName
}

struct Entity {
  1: i64 id,
  2: string key,
  3: optional string value
}

// Main thrift service
service ChordService {
  // Put operation
  void putEntity(1: Entity entity) throws (1: ChordException ce)

  // Get operation
  Entity getEntity(1: Entity entity) throws (1: ChordException ce)

  // Delete operation
  void deleteEntity(1: Entity entity) throws (1: ChordException ce)

  // Return this peer.
  Node ping() throws (1: ChordException ce)

  // Set predecessor=newNode if(predecessor is not set or newNode succeeds predecessor) and then return predecessor.
  Node notify(1: Node newNode) throws (1: ChordException ce)

  // Return successor of chord id according to it's fingertable.
  GetSuccessorResponse getSuccessor(1: i64 id) throws (1: ChordException ce)

  // Return configuration of the overlay network
  GetConfigurationResponse getConfiguration() throws (1: ChordException ce)

  // Return fingertable of this peer.
  list<Node> getFingerTable() throws (1: ChordException ce)
}
