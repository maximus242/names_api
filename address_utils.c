// address_utils.c
#include "address_utils.h"
#include <stdbool.h> // For bool
#include <limits.h>  // For UCHAR_MAX if needed, though direct cast is fine here

bool is_valid_offset(Word value) {
    // Check if the value fits within the range of Offset (uint8_t)
    return value <= UCHAR_MAX; // Or simply: return value <= 255;
}

Address calculate_address(Word base, Offset offset) {
    // Simple address calculation: base + offset
    return base + offset;
}

bool verify_instruction(const MovInstruction* instr) {
    if (instr == NULL) {
        return false; // Instruction pointer is NULL, consider invalid
    }

    // Basic checks on operand types.  More sophisticated checks can be added later
    if (instr->source.type < OPERAND_REGISTER || instr->source.type > OPERAND_IMMEDIATE_OFFSET_MEMORY) {
        return false; // Invalid source operand type
    }
    if (instr->destination.type < OPERAND_REGISTER || instr->destination.type > OPERAND_IMMEDIATE_OFFSET_MEMORY) {
        return false; // Invalid destination operand type
    }

    return true; // Basic checks passed, instruction considered potentially valid for now
}
