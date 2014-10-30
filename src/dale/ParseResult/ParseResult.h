#ifndef DALE_PARSERESULT
#define DALE_PARSERESULT

#include "../llvm_Module.h"
#include "../llvm_Function.h"
#include "llvm/PassManager.h"
#include "../llvm_CallingConv.h"
#include "llvm/Analysis/Verifier.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "../llvm_IRBuilder.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"

#include "../Element/Type/Type.h"
#include "../Context/Context.h"

namespace dale
{
class ParseResult
{
public:
    Element::Type *type;
    Element::Type *type_of_address_of_value;
    llvm::BasicBlock *block;
    llvm::Value *value;
    llvm::Value *address_of_value;
    int treat_as_terminator;
    int do_not_destruct;
    int do_not_copy_with_setf;
    int freshly_copied;
    int value_is_lvalue;

    llvm::Value *retval;
    Element::Type *retval_type;
    bool retval_used;

    ParseResult();
    ParseResult(llvm::BasicBlock *new_block,
                Element::Type *new_type,
                llvm::Value *new_value);
    ~ParseResult();

    int copyTo(ParseResult *x);
    void set(llvm::BasicBlock *new_block,
            Element::Type *new_type,
            llvm::Value *new_value);
    bool getAddressOfValue(Context *ctx, ParseResult *pr);
    bool setAddressOfValue(Context *ctx);
    llvm::Value *getValue(Context *ctx);
};
}

#endif
