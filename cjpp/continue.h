#include "ast.h"

class ContinueStatement : public Statement_node {
public:
    Statement_node* stmt;
    ContinueStatement(const Statement_node* s) 
    {
         stmt = s;
    }

};
