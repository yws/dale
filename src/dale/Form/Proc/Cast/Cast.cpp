#include "../../../Generator/Generator.h"
#include "../../../Node/Node.h"
#include "../../../ParseResult/ParseResult.h"
#include "../../../Element/Function/Function.h"
#include "../../../Operation/Cast/Cast.h"
#include "../../Type/Type.h"
#include "../Inst/Inst.h"
#include "../../../llvm_Function.h"

namespace dale
{
namespace Form
{
namespace Proc
{
namespace Cast
{
bool parse(Generator *gen,
           Element::Function *fn,
           llvm::BasicBlock *block,
           Node *node,
           bool get_address,
           bool prefixed_with_core,
           ParseResult *pr)
{
    Context *ctx = gen->ctx;

    assert(node->list && "must receive a list!");

    symlist *lst = node->list;

    if (!ctx->er->assertArgNums("cast", node, 2, 2)) {
        return false;
    }

    /* Get the value that is being cast. */

    ParseResult pr_value;
    bool res =
        Form::Proc::Inst::parse(gen, fn, block, (*lst)[1], false, 
                                    false, NULL,
                                    &pr_value);

    if (!res) {
        return false;
    }

    /* Get the type to which it is being cast. (It is allowable to
     * cast to a bitfield type, because there's no other way to
     * set a bitfield value.) */

    Element::Type *type = Form::Type::parse(gen, (*lst)[2], false, true);
    if (!type) {
        return false;
    }

    /* If the type of the value and the target type are the same,
     * return the original value. */

    if (pr_value.type->isEqualTo(type)) {
        pr_value.copyTo(pr);
        return true;
    }

    ParseResult temp;
    res = Operation::Cast::execute(ctx,
                pr_value.block,
                pr_value.value,
                pr_value.type,
                type,
                node,
                0,
                &temp);
    if (!res) {
        return false;
    }
    pr_value.block = temp.block;
    ParseResult temp2;
    res = gen->destructIfApplicable(&pr_value, NULL, &temp2);
    temp.block = temp2.block;

    pr->set(temp.block, temp.type, temp.value);
    return true;
}
}
}
}
}
