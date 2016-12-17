#include "tac.h"
#include "mips.h"
#include <string.h>

Location::Location(Segment seg, int offset, const char *name):
        variableName(strdup(name)), segment(s), offset(offset){}

void Instruction::Print() {
    printf("\t%s ;\n", printed);
}

void Instruction::Emit(Mips *mips) {

}