// custom_rules.c
#include "custom_rules.h"
#include "rule.h" // Needed for Rule struct and create_rule, etc.
#include "operands.h" // Needed for Operand creation
#include <stdlib.h>
#include <stdio.h> // For fprintf

// --- Helper functions for preconditions and postconditions ---

// Postcondition for load immediate: REG[dest] = value
void apply_load_immediate(MemorySpace mem, Word registers[REG_COUNT]) {
    // Minimal placeholder usage to avoid "unused parameter" warning.
    // Replace with actual LOAD_IMMEDIATE postcondition logic.
    (void)mem.size; // Using mem.size to indicate 'mem' is used. Can use any member.
    registers[REG_S] = registers[REG_S]; // Using registers to indicate 'registers' is used. No change to register.

    fprintf(stderr, "Warning: apply_load_immediate is a placeholder and does not implement correct logic yet.\n");
}

// Postcondition for load indexed: REG[dest] = MEM[REG[src] + REG[offset]]
void apply_load_indexed(MemorySpace mem, Word registers[REG_COUNT]) {
    // Minimal placeholder usage to avoid "unused parameter" warning.
    // Replace with actual LOAD_INDEXED postcondition logic.
    (void)mem.size;
    registers[REG_A] = registers[REG_A];

    fprintf(stderr, "Warning: apply_load_indexed is a placeholder and does not implement correct logic yet.\n");
}

// Postcondition for store indexed: MEM[REG[src] + REG[offset]] = REG[dest]
void apply_store_indexed(MemorySpace mem, Word registers[REG_COUNT]) {
    // Minimal placeholder usage to avoid "unused parameter" warning.
    // Replace with actual STORE_INDEXED postcondition logic.
    (void)mem.size;
    registers[REG_B] = registers[REG_B];

    fprintf(stderr, "Warning: apply_store_indexed is a placeholder and does not implement correct logic yet.\n");
}


// --- Rule creation functions ---


Rule* create_load_immediate_rule(Register dest, Word value) {
    Rule* rule = create_rule("LOAD_IMMEDIATE");
    if (rule == NULL) return NULL;

    Operand source = create_immediate_operand(value);
    Operand destination = create_register_operand(dest);
    set_rule_instruction(rule, source, destination);

    // Add postcondition
    Postcondition* postcondition = (Postcondition*)malloc(sizeof(Postcondition));
    if (postcondition == NULL) {
        free_rule(rule);
        return NULL;
    }
    postcondition->apply = (PostconditionFunc)apply_load_immediate;
    add_postcondition(rule, postcondition->apply);
    free(postcondition);

    return rule;
}


Rule* create_load_indexed_rule(Register dest, Register src, Register offset) {
    Rule* rule = create_rule("LOAD_INDEXED");
    if (rule == NULL) return NULL;

    Operand source = create_indexed_memory_operand(src, offset);
    Operand destination = create_register_operand(dest);
    set_rule_instruction(rule, source, destination);

    // Add postcondition
    Postcondition* postcondition = (Postcondition*)malloc(sizeof(Postcondition));
    if (postcondition == NULL) {
        free_rule(rule);
        return NULL;
    }

    postcondition->apply = (PostconditionFunc)apply_load_indexed;
    add_postcondition(rule, postcondition->apply);
    free(postcondition);

    return rule;
}

Rule* create_store_indexed_rule(Register dest, Register src, Register offset) {
    Rule* rule = create_rule("STORE_INDEXED");
    if (rule == NULL) return NULL;

    Operand source = create_register_operand(dest); // Source is register to store
    Operand destination = create_indexed_memory_operand(src, offset); // Destination is memory location
    set_rule_instruction(rule, source, destination);

    // Add postcondition
    Postcondition* postcondition = (Postcondition*)malloc(sizeof(Postcondition));
    if (postcondition == NULL) {
        free_rule(rule);
        return NULL;
    }
    postcondition->apply = (PostconditionFunc)apply_store_indexed;
    add_postcondition(rule, postcondition->apply);
    free(postcondition);

    return rule;
}
