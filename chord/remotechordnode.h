#ifndef REMOTECHORDNODE_H
#define REMOTECHORDNODE_H

#include "../service/ChordService.h"

namespace chorddb { namespace middleware {

class RemoteChordNode : virtual public Node
{
public:
    RemoteChordNode();
};

}}

#endif // REMOTECHORDNODE_H
