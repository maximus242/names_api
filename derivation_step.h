// derivation_step.h
#ifndef DERIVATION_STEP_H
#define DERIVATION_STEP_H

#include "types.h"
#include "rule.h"

typedef struct DerivationStep DerivationStep; // Forward declaration

DerivationStep* create_derivation_step(Rule* rule);
void add_derivation_step(DerivationStep* head, Rule* rule);
void free_derivation(DerivationStep* head);
bool verify_derivation(DerivationStep* head, MemorySpace* mem, Word registers[REG_COUNT]);

#endif
