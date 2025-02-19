// operands.h
#ifndef OPERANDS_H
#define OPERANDS_H

#include "types.h"

Operand create_register_operand(Register reg);
Operand create_immediate_operand(Word value);
Operand create_direct_memory_operand(Address addr);
Operand create_indexed_memory_operand(Register base, Register offset);
Operand create_immediate_offset_memory_operand(Register base, Offset offset);

#endif
