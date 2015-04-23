#include <iostream>

class DebuggerStatement : public Statement {
public:
    const Identifier& id;
    
    DebuggerStatement(
                       const Identifier& arg_id
                       ) : id(arg_id) {}
};