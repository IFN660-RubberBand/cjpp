#include "Node.h"

#ifndef VARIABLEDEC
#define VARIABLEDEC


class VariableDec : public Node {
public:
    const Identifier* i;
    const Expression* expr;
    VariableDec(Identifier* i) : i(i)
    {
        expr = NULL;
    }
    VariableDec(Identifier* i, Expression* expr) : i(i), expr(expr)
    {}		
};


#endif



