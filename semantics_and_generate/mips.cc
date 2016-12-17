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
    }
}

bool Mips::FindRegisterWithContents(Location *var, Register &reg)
{
    for (reg = zero; reg < NumRegs; reg = (Register)(reg+1))
        if (regs[reg].isGeneralPurpose && LocationAreSame(var, regs[reg].var))
            return true;
    return false;
}


/*
 * I have some questions about this!
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

void Mips::SpillRegister(Register reg)
{
    Location *var = regs[reg].var;
    if (var && regs[reg].isDirty) {
        //const char *offsetFromWhere = var->
    }
}