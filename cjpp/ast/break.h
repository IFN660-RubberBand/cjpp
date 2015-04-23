#include "ast.h"

class BreakStatement : public Statement_node {
public:
    Statement_node* stmt;
    BreakStatement(const Statement_node* s) 
    {
         stmt = s;
    }

};
