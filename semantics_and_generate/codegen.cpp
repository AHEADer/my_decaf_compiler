//
// Created by david on 12/22/16.
//

#include "codegen.h"
#include <string.h>
#include "tac.h"
#include "mips.h"

CodeGenerator::CodeGenerator()
{
    code = new List<Instruction*>;
}

char *CodeGenerator::NewLabel()
{
    static labelNum = 0;
    char temp[10];
    sprintf(temp, "_L%d", labelNum++);
    return strdup(temp);
}

Location* CodeGenerator::GenVar(Segment segment, int localOffset, const char *name)
{
    static int nextTempNum = 0;
    char temp[10];

    Location *result = NULL;

    //no need to assign a location here
    if (localOffset == 0 && segment != gpRelative)
        return result;

    if (name)
        result = new Location(segment, localOffset, name);
    else
    {
        sprintf(temp, "_tmp%d", nextTempNum++);
        result = new Location(segment, localOffset, temp);
    }
    return result;
}

Location* CodeGenerator::GenLoadConstant(const char *str, int localOffset)
{
    Location *result = GenVar(fpRelative, localOffset);
    code->Append(new LoadConstant(result, str));
    return result;
}

Location* CodeGenerator::GenLoadConstant(int value, int localOffset)
{
    Location *result = GenVar(fpRelative, localOffset);
    code->Append(new LoadConstant(result, value));
    return result;
}

Location *CodeGenerator::GenLoadLabel(const char *label, int localOffset)
{
    Location *result = GenVar(fpRelative, localOffset);
    code->Append(new LoadLabel(result, label));
    return result;
}

void CodeGenerator::GenAssign(Location *dst, Location *src)
{
    code->Append(new Assign(dst, src));
}

Location *CodeGenerator::GenLoad(Location *ref, int localOffset, int offset, const char*name)
{
    Location *result = GenVar(fpRelative, localOffset, name);
    code->Append(new Load(result, ref, offset));
    return result;
}

void CodeGenerator::GenStore(Location *dst,Location *src, int offset)
{
    code->Append(new Store(dst, src, offset));
}

Location *CodeGenerator::GenBinaryOp(const char *opName, Location *op1, Location *op2, int localOffset)
{
    Location *result = GenVar(fpRelative, localOffset);
    code->Append(new BinaryOp(BinaryOp::OpCodeForName(opName), result, op1, op2));
    return result;
}

void CodeGenerator::GenLabel(const char *label)
{
    code->Append(new Label(label));
}

void CodeGenerator::GenIfZ(Location *test, const char *label)
{
    code->Append(new IfZ(test, label));
}

void CodeGenerator::GenGoto(const char *label)
{
    code->Append(new Goto(label));
}

void CodeGenerator::GenReturn(Location *val)
{
    code->Append(new Return(val));
}

BeginFunc* CodeGenerator::GenBeginFunc()
{
    BeginFunc *result = new BeginFunc;
    code->Append(result);
    return result;
}

void CodeGenerator::GenEndFunc()
{
    code->Append(new EndFunc());
}

void CodeGenerator::GenPushParam(Location *param)
{
    code->Append(new PushParam(param));
}

void CodeGenerator::GenPopParams(int numBytesOfParams)
{
    Assert(numBytesOfParams >= 0 && numBytesOfParams % VarSize == 0);

    code->Append(new PopParams(numBytesOfParams));
}

Location* CodeGenerator::GenLCall(const char *label, bool fnHasReturnValue, int localOffset)
{
    Location* result = fnHasReturnValue?GenVar(fpRelative, localOffset) : NULL;
    code->Append(new LCall(label, result));
    return result;
}

Location *CodeGenerator::GenACall(Location *fnAddr, bool fnHasReturnValue, int localOffset)
{
    Location *result = fnHasReturnValue ? GenVar(fpRelative, localOffset) : NULL;
    code->Append(new ACall(fnAddr, result));
    return result;
}

static struct _builtin {
    const char *label;
    int numArgs;
    bool hasReturn;
} builtins[] =
        {{"_Alloc", 1, true},
         {"_ReadLine", 0, true},
         {"_ReadInteger", 0, true},
         {"_StringEqual", 2, true},
         {"_PrintInt", 1, false},
         {"_PrintString", 1, false},
         {"_PrintBool", 1, false},
         {"_Halt", 0, false}};

Location* CodeGenerator::GenBuiltInCall(BuiltIn bn, Location *arg1, Location *arg2,
                                        int localOffset, const char *name)
{
    Assert(bn >= 0 && bn < NumBuiltIns);
    struct _builtin *b = &builtins[bn];
    Location* result = NULL;

    if (b->hasReturn)
        result = GenVar(fpRelative, localOffset, name);
    Assert((b->numArgs == 0 && !arg1 && !arg2)
           || (b->numArgs == 1 && arg1 && !arg2)
           || (b->numArgs == 2 && arg1 && arg2));
    if (arg2)
        code->Append(new PushParam(arg2));
    if (arg1)
        code->Append(new PushParam(arg1));
    code->Append(new LCall(b->label, result));
    GenPopParams(VarSize * b->numArgs);
    return result;

}

void CodeGenerator::GenVTable(const char *className, List<const char *> *methodlabels)
{
    code->Append(new VTable(className, methodlabels));
}

void CodeGenerator::DoFinalCodeGen()
{
    if (0)
    {
        for (int i = 0; i < code->NumElements(); i++)
            code->Nth(i)->Print();
    } else {
        Mips mips;
        mips.EmitPreamble();
        mips.EmitPrintInt();
        mips.EmitPrintBool();
        mips.EmitPrintString();
        mips.EmitAlloc();
        mips.EmitStringEqual();
        mips.EmitHalt();
        mips.EmitReadInteger();
        mips.EmitReadLine();

        for (int i = 0; i < code->NumElements(); ++i) {
            code->Nth(i)->Emit(&mips);
        }
    }
}