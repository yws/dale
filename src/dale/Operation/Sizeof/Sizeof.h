#ifndef DALE_OPERATION_SIZEOF
#define DALE_OPERATION_SIZEOF

#include "../../ParseResult/ParseResult.h"
#include "../../Context/Context.h"
#include "../../Element/Type/Type.h"
#include "../../Node/Node.h"
#include "../../Unit/Unit.h"

#include "../../llvm_Module.h"
#include "../../llvm_Function.h"
#include "../../llvm_IRBuilder.h"

namespace dale
{
namespace Operation
{
namespace Sizeof
{
bool execute(Context *ctx,
             llvm::BasicBlock *block,
             Element::Type *type,
             ParseResult *pr);
size_t get(Unit *unit,
           Element::Type *type);
}
}
}

#endif
