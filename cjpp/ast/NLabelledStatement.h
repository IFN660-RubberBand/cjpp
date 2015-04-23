#include <iostream>

class NLabelledStatement : public NStatement {
public:
    const NIdentifier& id;
    const NStatement& statement;
    
    NLabelledStatement(
                       const NIdentifier& arg_id,
                       const NStatement& arg_statement
                       ) : id(arg_id), statement(arg_statement)
    {
    	
    }
};