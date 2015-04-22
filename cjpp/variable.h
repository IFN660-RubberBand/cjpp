#include "ast.h"

class VariableStatement : public Statement_node {
public:
    Statement_node* stmt;
    VariableStatement(const Statement_node* s) 
    {
         stmt = s;
    }

};
