
#include "Node.h"

class Block : public Statement {
public:
    StatementList statements;
    Block(
            StatementList
            ) { }
    //virtual llvm::Value* codeGen(CodeGenContext& context);
};

