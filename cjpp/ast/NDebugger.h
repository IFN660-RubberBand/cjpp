#include <iostream>

class NDebuggerStatement : public NStatement {
public:
    const NIdentifier& id;
    
    NDebuggerStatement(
                       const NIdentifier& arg_id
                       ) : id(arg_id) {}
};