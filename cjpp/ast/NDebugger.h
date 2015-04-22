#include <iostream>

class NDebuggerStatement : public NStatement {
public:
    const NIdentifier& id;
    
    NDebuggerStatement(
                       const NIdentifier& id
                       ) : id(id) {}
};