
/*
 * 
 *Block code for node
 *
 */

class NBlock : public NStatement {
public:
    StatementList statements;
    NBlock(
            NStatementList
            ) { }
    //virtual llvm::Value* codeGen(CodeGenContext& context);
};

