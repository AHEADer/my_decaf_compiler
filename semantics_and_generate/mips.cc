#include "mips.h"
#include <stdarg.h>
#include <string.h>

/*
 * Registers distribution strategy:
 *  1) if that var is already in a register ("same" is determined
 *     by matching name and same scope), we use that one
 *  2) find an empty register to use for the var
 *  3) find an in-use register that is not dirty.  We don't need
 *     to write value back to memory since it's clean, so we just
 *     replace with the new var
 *  4) spill an in-use, dirty register, by writing its contents to
 *     memory and then replace with the new var
 */

Mips::Register Mips::GetRegister(Location *var, Reason reason,
                                 Register avoid1, Register avoid2)
{
    Register reg;
    if (!FindRegisterWithContents(var, reg)) {
        if (!FindRegisterWithContents(NULL, reg)) {
            reg = SelectRegisterToSpill(avoid1, avoid2);
            SpillRegister(reg);
        }
        regs[reg].var = var;
        if (reason == ForRead) {
        	Assert(var->GetOffset()%4 == 0); 	//all variables should be 4 bytes in size
        	const char *offsetFromWhere = var->GetSegment() == fpRelative?
        	regs[fp].name:regs[gp].name;
        	Emit("lw %s, %d(%s)\t# load %s from %s%+d into %s",
        		regs[reg].name, 
        		var->GetOffset(), offsetFromWhere, var->GetName(),
        		offsetFromWhere, var->GetOffset(), regs[reg].name);
        	regs[reg].isDirty = false;
        }
    }
    if (reason == ForWrite)
    {
    	regs[reg].isDirty = true;
    }
    return reg;
}

Mips::Register Mips::GetRegister(Location *var, Register avoid1)
{
	return GetRegister(var, ForRead, avoid1, zero);
}

Mips::Register Mips::GetRegisterForWrite(Location *var, Register avoid1, Register avoid2)
{
	return GetRegister(var, ForWrite, avoid1, avoid2);
}

static bool LocationAreSame(Location *var1, Location *var2)
{
	return (var1==var2 || (
		var1 && var2 &&
		!strcmp(var1->GetName(), var2->GetName()) &&
		var1->GetSegment() == var2->GetSegment() &&
		var1->GetOffset() == var2->GetOffset()
		)
	);
}

bool Mips::FindRegisterWithContents(Location *var, Register &reg)
{
    for (reg = zero; reg < NumRegs; reg = (Register)(reg+1))
        if (regs[reg].isGeneralPurpose && LocationAreSame(var, regs[reg].var))
            return true;
    return false;
}


/*
 * Method: SelectRegisterToSpill
 * -----------------------------
 * Chooses an in-use register to replace with a new variable. We
 * prefer to replace a non-dirty once since we would not have to
 * write its contents back to memory, so the first loop searches
 * for a clean one. If none found, we take a dirty one.  In both
 * loops we deliberately won't choose either of the registers we
 * were asked to avoid.  We track the last dirty register spilled
 * and advance on each subsequent spill as a primitive means of
 * trying to not throw out things we just loaded and thus are likely
 * to need.
 */
Mips::Register Mips::SelectRegisterToSpill(Register avoid1, Register avoid2)
{
    //first hunt for a non-dirty register
    for (Register i = zero; i < NumRegs; i = (Register)(i+1))
        if(i != avoid1 && i != avoid2 && regs[i].isGeneralPurpose && !regs[i].isDirty)
            return i;

    do {
        lastUsed = (Register)((lastUsed+1)%NumRegs);
    } while (lastUsed==avoid1 || lastUsed == avoid2 ||
            !regs[lastUsed].isGeneralPurpose);
    return lastUsed;
}

/* Method: SpillRegister
 * ---------------------
 * "Empties" register.  If variable is currently slaved in this register
 * and its contents are out of synch with memory (isDirty), we write back
 * the current contents to memory. We then clear the descriptor so we
 * realize the register is empty.
 */
void Mips::SpillRegister(Register reg)
{
    Location *var = regs[reg].var;
    if (var && regs[reg].isDirty) {
        const char *offsetFromWhere = var->GetSegment() == fpRelative? regs[fp].name:
                                      regs[gp].name;
        Assert(var->GetOffset()%4 == 0);    //all variables should be 4 bytes in size
        Emit("sw %s, %d(%s)\t# spill %s from %s to %s%+d", regs[reg].name,
        var->GetOffset(), offsetFromWhere, 
        var->GetName(), regs[reg].name,
        offsetFromWhere, var->GetOffset());
    }
    regs[reg].var = NULL;
}

void Mips::SpillAllDirtyRegisters()
{
	Register i;
	for (int i = zero; i < NumRegs; i = (Register)(i+1))
	{
		if (regs[i].var && regs[i].isDirty)
		{
			break;
		}
	}

	if (i!= NumRegs) //none are dirty
	{
		Emit("# (save modified registers before flow of control change)");
	}
	for (int i = zero; i < NumRegs; i = (Register)(i+1))
	{
		SpillRegister(i);
	}
}

/* Method: SpillForEndFunction
 * ---------------------------
 * Slight optimization on the above method used when spilling for
 * end of function (return/fall off). In such a case, we do not
 * need to save values for locals, temps, and parameters because the
 * function is about to exit and those variables are going away
 * immediately, so no need to bother with updating contents.
 */
void Mips::SpillForEndFunction()
{
	for (int i = zero; i < NumRegs; i = (Register)(i+1))
	{
		if (regs[i].isGeneralPurpose && regs[i].var)
		{
			if (regs[i].var->GetSegment() == gpRelative)
			{
				SpillRegister(i);
			}
			else	//eliminate things on stack
				regs[i].var = NULL;
		}
	}
}


void Mips::Emit(const char* fmt, ...)
{
	va_list args;
    char buf[1024];

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);

    char last = buf[strlen(buf)-1];
    if (last != ':') printf("\t");
    printf("%s", buf);
    if (last!='\n') printf("\n");
}

/* Method: EmitLoadConstant
 * ------------------------
 * Used to assign variable an integer constant value.  Slaves dst into
 * a register (using GetRegister above) and then emits an li (load
 * immediate) instruction with the constant value.
 */
void Mips::EmitLoadConstant(Location *dst, int val)
{
    Register reg = GetRegisterForWrite(dst);
    //li instruction save a immediate number to a register
    Emit("li %s, %d\t\t# load constant value %d into %s", regs[reg].name,
         val, val, regs[reg].name);
}

/* Method: EmitLoadStringConstant
 * ------------------------------
 * Used to assign a variable a pointer to string constant. Emits
 * assembly directives to create a new null-terminated string in the
 * data segment and assigns it a unique label. Slaves dst into a register
 * and loads that label address into the register.
 */
void Mips::EmitLoadStringConstant(Location *dst, const char *str)
{
    static int strNum = 1;
    char label[16];
    sprintf(label, "_string%d", strNum++);
    Emit(".data\t\t\t#create string constant with label");
    Emit("%s: .asciiz %s", label, str);
    Emit(".text");
    EmitLoadLabel(dst, label);
}

void Mips::EmitLoadLabel(Location *dst, const char *label)
{
    Register reg = GetRegisterForWrite(dst);
    //li instruction save a label address to a register
    Emit("la %s, %s\t# load label", regs[reg].name, label);
}

void Mips::EmitCopy(Location *dst, Location *src)
{
    Register rSrc = GetRegister(src), rDst = GetRegisterForWrite(dst, rSrc);
    Emit("move %s, %s\t\t# copy value", regs[rDst].name, regs[rSrc].name);
}

/* Method: EmitLoad
 * ----------------
 * Used to assign dst the contents of memory at the address in reference,
 * potentially with some positive/negative offset (defaults to 0).
 * Slaves both ref and dst to registers, then emits a lw instruction
 * using constant-offset addressing mode y(rx) which accesses the address
 * at an offset of y bytes from the address currently contained in rx.
 */
void Mips::EmitLoad(Location *dst, Location *reference, int offset)
{
    Register rSrc = GetRegister(reference), rDst = GetRegisterForWrite(dst, rSrc);
    Emit("lw %s, %d(%s) \t# load with offset", regs[rDst].name,
         offset, regs[rSrc].name);
}

void Mips::EmitStore(Location *reference, Location *value, int offset)
{
    Register rVal = GetRegister(value), rRef = GetRegister(reference, rVal);
    Emit("sw %s, %d(%s)\t# store with offset", regs[rVal].name,
         offset, regs[rRef].name);
}

void Mips::EmitBinaryOp(BinaryOp::OpCode code, Location *dst,
                        Location *op1, Location *op2)
{
    Register rLeft = GetRegister(op1), rRight = GetRegister(op2, rLeft);
    Register rDst = GetRegisterForWrite(dst, rLeft, rRight);
    Emit("%s %s, %s, %s\t", NameForTac(code), regs[rDst].name, regs[rLeft].name, regs[rRight].name);
}

/* Method: EmitLabel
 * -----------------
 * Used to emit label marker. Before a label, we spill all registers since
 * we can't be sure what the situation upon arriving at this label (ie
 * starts new basic block), and rather than try to be clever, we just
 * wipe the slate clean.
 */
void Mips::EmitLabel(const char *label)
{
    SpillAllDirtyRegisters();
    Emit("%s:", label);
}

/* Method: EmitGoto
 * ----------------
 * Used for an unconditional transfer to a named label. Before a goto,
 * we spill all registers, since we don't know what the situation is
 * we are heading to (ie this ends current basic block) and rather than
 * try to be clever, we just wipe slate clean.
 */
void Mips::EmitGoto(const char *label)
{
    SpillAllDirtyRegisters();
    Emit("b %s\t\t# unconditional branch", label);
}

void Mips::EmitIfZ(Location *test, const char *label)
{
    Register testReg = GetRegister(test);
    //same as goto
    SpillAllDirtyRegisters();
    Emit("beqz %s, %s\t#branch if %s is zero", regs[testReg].name, label,
    test->GetName());
}

/* Method: EmitParam
 * -----------------
 * Used to push a parameter on the stack in anticipation of upcoming
 * function call. Decrements the stack pointer by 4. Slaves argument into
 * register and then stores contents to location just made at end of
 * stack.
 */
void Mips::EmitParam(Location *arg)
{
    Emit("subu $sp, $sp, 4\t# decrement sp to make space for param");
    Register reg = GetRegister(arg);
    Emit("sw %s, 4($sp)\t#copy param value to stack");
}

/* Method: EmitCallInstr
 * ---------------------
 * Used to effect a function call. All necessary arguments should have
 * already been pushed on the stack, this is the last step that
 * transfers control from caller to callee. We issue
 * jal for a label, a jalr if address in register. Both will save the
 * return address in $ra. If there is an expected result passed, we slave
 * the var to a register and copy function return value from $v0 into that
 * register.
 */
void Mips::EmitCallInstr(Location *dst, const char *fn, bool isL)
{
    SpillAllDirtyRegisters();
    Emit("%s %-15s\t# jump to function", isL? "jal":"jalr", fn);
    if (dst!=NULL) {
        Register r1 = GetRegisterForWrite(dst);
        Emit("move %s, %s\t\t# copy function return value from $v0", regs[r1].name,
        regs[v0].name);
    }
}

void Mips::EmitLCall(Location *result, const char *label)
{
    EmitCallInstr(result, label, true);
}

void Mips::EmitACall(Location *result, Location *fnAddr)
{
    EmitCallInstr(result, regs[GetRegister(fnAddr)].name, false);
}

void Mips::EmitPopParams(int bytes)
{
    if (bytes != 0)
        Emit("add $sp, $sp, %d\t# pop params off stack", bytes);
}

void Mips::EmitReturn(Location *returnVal)
{
    if (returnVal != NULL)
        Emit("move $v0, %s\t\t# assign return value into $v0",
        regs[GetRegister(returnVal)].name);

    SpillForEndFunction();
    Emit("move $sp, $fp\t\t# pop callee frame off stack");
    Emit("lw $ra, -4($fp)\t# restore saved ra");
    Emit("lw $fp, 0($fp)\t# restore saved fp");
    Emit("jr $ra\t\t# return from current function");
}

void Mips::EmitBeginFunction(int frameSize)
{
    Assert(frameSize >= 0);
    Emit("subu $sp, $sp, 8\t# decrement sp to make space to save ra, fp");
    Emit("sw $fp, 8($sp)\t# save fp");
    Emit("sw $ra, 4($sp)\t# save ra");
    Emit("addiu $fp, $sp, 8\t# set up new fp");
    if (stackFrameSize != 0)
        Emit("subu $sp, $sp, %d\t# decrement sp to make space for locals/temps",
             stackFrameSize);
}

void Mips::EmitEndFunction()
{
    Emit("# (below handles reaching end of fn body with no explicit return)");
    EmitReturn(NULL);
}

void Mips::EmitVTable(const char *label, List<const char *> *methodLabels)
{
    Emit(".data");
    Emit(".align 2");
    Emit("%s:\t\t# label for class %s vtable", label, label);
    for (int i = 0; i < methodLabels->NumElements(); i++)
        Emit(".word %s\n", methodLabels->Nth(i));
    Emit(".text");

}

void Mips::EmitPreamble()
{
    Emit("# standard Decaf preamble ");
    EmitData();
    Emit(".text");
    Emit(".align 2");
    Emit(".globl main");
    Emit(".globl _PrintInt");
    Emit(".globl _PrintString");
    Emit(".globl _PrintBool");
    Emit(".globl _Alloc");
    Emit(".globl _StringEqual");
    Emit(".globl _Halt");
    Emit(".globl _ReadInteger");
    Emit(".globl _ReadLine");
    Emit("");
}

void Mips::EmitPrintInt()
{
    Emit("%s:", "_PrintInt");
    Emit("subu $sp, $sp, 8\t# decrement so to make space to save ra, fp");
    Emit("sw $fp, 8($sp)  \t# save fp");
    Emit("sw $ra, 4($sp)  \t# save ra");
    Emit("addiu $fp, $sp, 8\t# set up new fp");
    Emit("li $v0, 1       \t# system call code for print_int");
    Emit("lw $a0, 4($fp)");
    Emit("syscall");
    Emit("move $sp, $fp");
    Emit("lw $ra, -4($fp)");
    Emit("lw $fp, 0($fp)");
    Emit("jr $ra");
    Emit("\n");
}

void Mips::EmitPrintString()
{
    Emit("%s:", "_PrintString");
    Emit("subu $sp, $sp, 8");
    Emit("sw $fp, 8($sp)");
    Emit("sw $ra, 4($sp)");
    Emit("addiu $fp, $sp, 8");
    Emit("li $v0, 4       \t# system call for print_str");
    Emit("lw $a0, 4($fp)");
    Emit("syscall");
    Emit("move $sp, $fp");
    Emit("lw $ra, -4($fp)");
    Emit("lw $fp, 0($fp)");
    Emit("jr $ra");
    Emit("\n");
}

void Mips::EmitPrintBool()
{
    Emit("%s:", "_PrintBool");
    Emit("subu $sp, $sp, 8");
    Emit("sw $fp, 8($sp)");
    Emit("sw $ra, 4($sp)");
    Emit("addiu $fp, $sp, 8");
    Emit("lw $t1, 4($fp)");
    Emit("blez $t1, fbr");
    Emit("li $v0, 4       \t# system call for print_str");
    Emit("la $a0, TRUE");
    Emit("syscall");
    Emit("b end");
    Emit("%s:", "fbr");
    Emit("li $v0, 4       \t# system call for print_str");
    Emit("la $a0, FALSE");
    Emit("syscall");
    Emit("%s:", "end");
    Emit("move $sp, $fp");
    Emit("lw $ra, -4($fp)");
    Emit("lw $fp, 0($fp)");
    Emit("jr $ra");
    Emit("\n");
}

void Mips::EmitAlloc()
{
    Emit("%s:", "_Alloc");
    Emit("subu $sp, $sp, 8");
    Emit("sw $fp, 8($sp)");
    Emit("sw $ra, 4($sp)");
    Emit("addiu $fp, $sp, 8");
    Emit("li $v0, 9       \t# system call for sbrk");
    Emit("lw $a0, 4($fp)");
    Emit("syscall");
    Emit("move $sp, $fp");
    Emit("lw $ra, -4($fp)");
    Emit("lw $fp, 0($fp)");
    Emit("jr $ra");
    Emit("\n");
}

void Mips::EmitStringEqual()
{
    Emit("%s:", "_StringEqual");
    Emit("subu $sp, $sp, 8");
    Emit("sw $fp, 8($sp)");
    Emit("sw $ra, 4($sp)");
    Emit("addiu $fp, $sp, 8");
    Emit("subu $sp, $sp, 4\t# decrement sp to make space for return value");
    Emit("li $v0, 0");
    Emit("#Determine length string 1");
    Emit("lw $t0, 4($fp)");
    Emit("li $t3, 0");
    Emit("%s:", "bloop1");
    Emit("lb $t5, ($t0)");
    Emit("beqz $t5, eloop1");
    Emit("addi $t0, 1");
    Emit("addi $t3, 1");
    Emit("b bloop1");
    Emit("%s:", "eloop1");
    Emit("#Determine length string 2");
    Emit("lw $t1, 8($fp)");
    Emit("li $t4, 0");
    Emit("%s:", "bloop2");
    Emit("lb $t5, ($t1)");
    Emit("beqz $t5, eloop2");
    Emit("addi $t1, 1");
    Emit("addi $t4, 1");
    Emit("b bloop2");
    Emit("%s:", "eloop2");
    Emit("bne $t3, $t4, end1\t# check if string lengths are the same");
    Emit("lw $t0, 4($fp)");
    Emit("lw $t1, 8($fp)");
    Emit("li $t3, 0");
    Emit("%s:", "bloop3");
    Emit("lb $t5, ($t0)");
    Emit("lb $t6, ($t1)");
    Emit("bne $t5, $t6, end1");
    Emit("addi $t3, 1");
    Emit("addi $t0, 1");
    Emit("addi $t1, 1");
    Emit("bne $t3, $t4, bloop3");
    Emit("%s:", "eloop3");
    Emit("li $v0, 1");
    Emit("%s:", "end1");
    Emit("move $sp, $fp");
    Emit("lw $ra, -4($fp)");
    Emit("lw $fp, 0($fp)");
    Emit("jr $ra");
    Emit("\n");
}

void Mips::EmitHalt()
{
    Emit("%s:", "_Halt");
    Emit("li $v0, 10");
    Emit("syscall");
    Emit("\n");
}

void Mips::EmitReadInteger()
{
    Emit("%s:", "_ReadInteger");
    Emit("subu $sp, $sp, 8");
    Emit("sw $fp, 8($sp)");
    Emit("sw $ra, 4($sp)");
    Emit("addiu $fp, $sp, 8");
    Emit("subu $sp, $sp, 4");
    Emit("li $v0, 5");
    Emit("syscall");
    Emit("move $sp, $fp");
    Emit("lw $ra, -4($fp)");
    Emit("lw $fp, 0($fp)");
    Emit("jr $ra");
    Emit("\n");
}

void Mips::EmitReadLine()
{
    Emit("%s:", "_ReadLine");
    Emit("subu $sp, $sp, 8");
    Emit("sw $fp, 8($sp)");
    Emit("sw $ra, 4($sp)");
    Emit("addiu $fp, $sp, 8");
    Emit("li $t0, 40");
    Emit("subu $sp, $sp, 4");
    Emit("sw $t0, 4($sp)");
    Emit("jal _Alloc");
    Emit("move $t0, $v0");
    Emit("li $a1, 40");
    Emit("move $a0, $t0");
    Emit("li $v0, 8");
    Emit("syscall");
    Emit("move $t1, $t0");
    Emit("%s:", "bloop4");
    Emit("lb $t5, ($t1)");
    Emit("beqz $t5, eloop4");
    Emit("addi $t1, 1");
    Emit("b bloop4");
    Emit("%s:", "eloop4");
    Emit("addi $t1, -1"); // erase newline
    Emit("li $t6, 0");
    Emit("sb $t6, ($t1)");
    Emit("move $v0, $t0");
    Emit("move $sp, $fp");
    Emit("lw $ra, -4($fp)");
    Emit("lw $fp, 0($fp)");
    Emit("jr $ra");
    Emit("\n");
}

void Mips::EmitData()
{
    Emit(".data");
    Emit("%s:", "TRUE");
    Emit(".asciiz \"true\"");
    Emit("%s:", "FALSE");
    Emit(".asciiz \"false\"");
    Emit("\n");
}

void Mips::EmitData()
{
    Emit(".data");
    Emit("%s:", "TRUE");
    Emit(".asciiz \"true\"");
    Emit("%s:", "FALSE");
    Emit(".asciiz \"false\"");
    Emit("\n");
}

const char* Mips::NameForTac(BinaryOp::OpCode code)
{
    Assert(code >=0 && code < BinaryOp::NumOps);
    const char* name = mipsName[code];
    Assert(name!=NULL);
    return name;
}

/* Constructor
 * ----------
 * Constructor sets up the mips names and register descriptors to
 * the initial starting state.
 */
Mips::Mips() {
    mipsName[BinaryOp::Add] = "add";
    mipsName[BinaryOp::Sub] = "sub";
    mipsName[BinaryOp::Mul] = "mul";
    mipsName[BinaryOp::Div] = "div";
    mipsName[BinaryOp::Mod] = "rem";
    mipsName[BinaryOp::Eq] = "seq";
    mipsName[BinaryOp::Less] = "slt";
    mipsName[BinaryOp::And] = "and";
    mipsName[BinaryOp::Or] = "or";
    regs[zero] = (RegContents){false, NULL, "$zero", false};
    regs[at] = (RegContents){false, NULL, "$at", false};
    regs[v0] = (RegContents){false, NULL, "$v0", false};
    regs[v1] = (RegContents){false, NULL, "$v1", false};
    regs[a0] = (RegContents){false, NULL, "$a0", false};
    regs[a1] = (RegContents){false, NULL, "$a1", false};
    regs[a2] = (RegContents){false, NULL, "$a2", false};
    regs[a3] = (RegContents){false, NULL, "$a3", false};
    regs[k0] = (RegContents){false, NULL, "$k0", false};
    regs[k1] = (RegContents){false, NULL, "$k1", false};
    regs[gp] = (RegContents){false, NULL, "$gp", false};
    regs[sp] = (RegContents){false, NULL, "$sp", false};
    regs[fp] = (RegContents){false, NULL, "$fp", false};
    regs[ra] = (RegContents){false, NULL, "$ra", false};
    regs[t0] = (RegContents){false, NULL, "$t0", true};
    regs[t1] = (RegContents){false, NULL, "$t1", true};
    regs[t2] = (RegContents){false, NULL, "$t2", true};
    regs[t3] = (RegContents){false, NULL, "$t3", true};
    regs[t4] = (RegContents){false, NULL, "$t4", true};
    regs[t5] = (RegContents){false, NULL, "$t5", true};
    regs[t6] = (RegContents){false, NULL, "$t6", true};
    regs[t7] = (RegContents){false, NULL, "$t7", true};
    regs[t8] = (RegContents){false, NULL, "$t8", true};
    regs[t9] = (RegContents){false, NULL, "$t9", true};
    regs[s0] = (RegContents){false, NULL, "$s0", true};
    regs[s1] = (RegContents){false, NULL, "$s1", true};
    regs[s2] = (RegContents){false, NULL, "$s2", true};
    regs[s3] = (RegContents){false, NULL, "$s3", true};
    regs[s4] = (RegContents){false, NULL, "$s4", true};
    regs[s5] = (RegContents){false, NULL, "$s5", true};
    regs[s6] = (RegContents){false, NULL, "$s6", true};
    regs[s7] = (RegContents){false, NULL, "$s7", true};
    lastUsed = zero;
}


const char *Mips::mipsName[BinaryOp::NumOps]