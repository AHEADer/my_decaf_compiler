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

Mips:Register Mips::GetRegisterForWrite(Location *var, Register avoid1, Register avoid2)
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
}