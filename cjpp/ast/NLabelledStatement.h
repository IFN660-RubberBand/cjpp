#include <iostream>

class NLabelledStatement : public NStatement {
public:
    const NIdentifier& id;
    const NStatement& statement;
    
    NLabelledStatement(
                       const NIdentifier& id,
                       const NStatement& statement
                       ) : id(id), statement(statement)
    {}
};