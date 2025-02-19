// address_utils.h
#ifndef ADDRESS_UTILS_H
#define ADDRESS_UTILS_H

#include "types.h" // Include types.h because we use Word, Offset, Address, MovInstruction

bool is_valid_offset(Word value);
Address calculate_address(Word base, Offset offset);
bool verify_instruction(const MovInstruction* instr);

#endif // ADDRESS_UTILS_H
