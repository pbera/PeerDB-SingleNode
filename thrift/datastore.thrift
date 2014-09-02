namespace cpp chorddb.datastore

exception DataNotFoundException {
 
}

service DatastoreService {	
  void put(1: string key, 2: string value),
  string get(1: string key) throws (1: DataNotFoundException e),
  void remove(1: string key)
}