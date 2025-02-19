// operand.c
#include "types.h"  // Include your type definitions
#include <stdio.h>   // For potential error handling (though not strictly needed here)
#include "operands.h"

Operand create_register_operand(Register reg) {
    Operand operand;
    operand.type = OPERAND_REGISTER;
    operand.value.reg = reg;
    return operand;
}

Operand create_immediate_operand(Word value) {
    Operand operand;
    operand.type = OPERAND_IMMEDIATE;
    operand.value.immediate = value;
    return operand;
}

Operand create_direct_memory_operand(Address addr) {
    Operand operand;
    operand.type = OPERAND_DIRECT_MEMORY;
    operand.value.direct_addr = addr;
    return operand;
}

Operand create_indexed_memory_operand(Register base, Register offset) {
    Operand operand;
    operand.type = OPERAND_INDEXED_MEMORY;
    operand.value.indexed.base = base;
    operand.value.indexed.offset = offset;
    return operand;
}

Operand create_immediate_offset_memory_operand(Register base, Offset offset) {
    Operand operand;
    operand.type = OPERAND_IMMEDIATE_OFFSET_MEMORY;
    operand.value.immediate_offset.base = base;
    operand.value.immediate_offset.offset = offset;
    return operand;
}
