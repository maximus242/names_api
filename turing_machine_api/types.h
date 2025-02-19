// types.h
#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef uint64_t Word;
typedef uint64_t Address;
typedef uint8_t Offset;

#define OFFSET0 ((Offset)0)
#define OFFSET1 ((Offset)1)

typedef enum {
    REG_S,  // State register
    REG_A,  // General purpose / Address register
    REG_B,  // General purpose / Value register
    REG_C,  // General purpose / Temporary register
    REG_COUNT
} Register;

typedef struct {
    Word* data;
    size_t size;
} MemorySpace;

typedef enum {
    OPERAND_REGISTER,
    OPERAND_IMMEDIATE,
    OPERAND_DIRECT_MEMORY,
    OPERAND_INDEXED_MEMORY,
    OPERAND_IMMEDIATE_OFFSET_MEMORY
} OperandType;

typedef struct {
    OperandType type;
    union {
        Register reg;
        Word immediate;
        Address direct_addr;
        struct {
            Register base;
            Register offset;
        } indexed;
        struct {
            Register base;
            Offset offset;
        } immediate_offset;
    } value;
} Operand;

typedef struct {
    Operand source;
    Operand destination;
} MovInstruction;

typedef bool (*PreconditionFunc)(const MemorySpace, const Word[REG_COUNT]);
typedef void (*PostconditionFunc)(MemorySpace, Word[REG_COUNT]);

typedef struct {
    PreconditionFunc check;
} Precondition;

typedef struct {
    PostconditionFunc apply;
} Postcondition;

typedef struct {
    const char* name;
    Precondition* preconditions;
    size_t num_preconditions;
    MovInstruction instruction;
    Postcondition* postconditions;
    size_t num_postconditions;
} Rule;

typedef struct DerivationStep {
    Rule* rule;
    struct DerivationStep* next;
} DerivationStep;

typedef struct {
    Word state;
    Word symbol;
    Word next_state;
    Word write_symbol;
    bool move_right;
} TMTransition;

typedef struct {
    MemorySpace memory;
    Word registers[REG_COUNT];
    Address head_position;
    Address transition_table;
    size_t num_transitions;
    Address jump_target;
} TMSimulator;

#endif
