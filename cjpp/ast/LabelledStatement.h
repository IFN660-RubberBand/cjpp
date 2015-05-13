#include <iostream>

class LabelledStatement : public Statement {
public:
    const Identifier& id;
    const Statement& statement;
    
    LabelledStatement(
                       const Identifier& arg_id,
                       const Statement& arg_statement
                       ) : id(arg_id), statement(arg_statement)
    {
    	
    }
};