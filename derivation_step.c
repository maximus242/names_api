// derivation_step.c
#include "derivation_step.h"
#include <stdlib.h>

DerivationStep* create_derivation_step(Rule* rule) {
    DerivationStep* step = (DerivationStep*)malloc(sizeof(DerivationStep));
    if (step == NULL) {
        return NULL; // Memory allocation failed
    }
    step->rule = rule;
    step->next = NULL;
    return step;
}

void add_derivation_step(DerivationStep* head, Rule* rule) {
    DerivationStep* new_step = create_derivation_step(rule);
    if (new_step == NULL) {
        return; // Memory allocation failed, handle as needed
    }
    if (head == NULL) {
        // If head is NULL, the new step becomes the head (this case might not be intended by the function signature, usually you'd modify head pointer itself, but following the given signature)
        // In typical linked list add to tail, we assume head is the start of the list.
        // Let's assume the intention is to add to the end of the list pointed to by head, or if head is null, do nothing (or handle differently based on expected usage).
        free(new_step); // if head is null, we should probably not add and free the allocated step. Or maybe, if head is null, the new step *becomes* the head. Let's assume for now, we add to the end of the list pointed to by head if head is not null, otherwise do nothing.
        return; // Or handle head == NULL case as needed, e.g., return new_step if it's meant to become the new head. For now, doing nothing if head is NULL as per function signature suggesting 'add to existing list'.
    }

    DerivationStep* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_step;
}

void free_derivation(DerivationStep* head) {
    DerivationStep* current = head;
    while (current != NULL) {
        DerivationStep* next = current->next;
        free(current);
        current = next;
    }
}

bool verify_derivation(DerivationStep* head, MemorySpace* mem, Word registers[REG_COUNT]) {
    DerivationStep* current_step = head;
    while (current_step != NULL) {
        Rule* rule = current_step->rule;
        if (rule == NULL) {
            return false; // Invalid rule in derivation step
        }

        // Check preconditions
        if (rule->preconditions != NULL) {
            for (size_t i = 0; i < rule->num_preconditions; ++i) {
                if (!rule->preconditions[i].check(*mem, registers)) {
                    return false; // Precondition failed
                }
            }
        }

        // Apply postconditions
        if (rule->postconditions != NULL) {
            for (size_t i = 0; i < rule->num_postconditions; ++i) {
                rule->postconditions[i].apply(*mem, registers);
            }
        }

        current_step = current_step->next;
    }
    return true; // All steps verified successfully
}
