// minimal_tm_example.c
#include <stdio.h>
#include <stdlib.h>
#include "tm_simulator.h"
#include "types.h"
#include "rule.h"
#include "derivation_step.h"

// --- In-place Condition and Postcondition Definitions ---

// Precondition function that always returns true
bool always_true_condition(const MemorySpace mem, const Word *registers) { // Changed to const Word *registers
    return true; // This condition is always true
}


// Postcondition function to increment REG_A
void increment_reg_a_postcondition(MemorySpace mem, Word registers[REG_COUNT]) {
    registers[REG_A]++; // Increment register A
}

// --- Main Function ---
int main() {
    // 1. Define TM Transitions
    TMTransition transitions[] = {
        { .state = 0, .symbol = 0, .next_state = 1, .write_symbol = 1, .move_right = true }
    };
    size_t num_transitions = sizeof(transitions) / sizeof(transitions[0]);

    // 2. Create a TM Simulator
    size_t memory_size = 1024; // Example memory size
    TMSimulator* tm = create_tm_simulator(memory_size, transitions, num_transitions);
    if (tm == NULL) {
        fprintf(stderr, "Error creating TM simulator\n");
        return 1;
    }

    // 3. Initialize TM State (Optional, but good practice)
    tm->registers[REG_S] = 0; // Set initial state to 0
    tm->head_position = 0;    // Start at the beginning of the tape
    tm->registers[REG_A] = 0; // Initialize REG_A to 0

    // 4. Set initial tape content (Optional, assuming memory is initialized to 0)

    printf("Initial TM state:\n");
    printf("State Register (REG_S): %llu\n", tm->registers[REG_S]);
    printf("State Register (REG_A): %llu\n", tm->registers[REG_A]);
    printf("Head Position: %llu\n", tm->head_position);
    printf("Memory at Head Position: %llu\n", tm->memory.data[tm->head_position]);
    printf("\n");

    // --- Rule and Derivation Example ---
    // 1. Create a Rule
    Rule* my_rule = create_rule("IncrementRegARule");
    if (my_rule == NULL) {
        fprintf(stderr, "Error creating rule\n");
        free_tm_simulator(tm);
        return 1;
    }

    // 2. Add the always true precondition (using the in-place definition)
    add_precondition(my_rule, always_true_condition);

    // 3. Add the postcondition to increment REG_A (using the in-place definition)
    add_postcondition(my_rule, increment_reg_a_postcondition);

    // 4. Create a Derivation Step
    DerivationStep* step = create_derivation_step(my_rule);
    if (step == NULL) {
        fprintf(stderr, "Error creating derivation step\n");
        free_rule(my_rule);
        free_tm_simulator(tm);
        return 1;
    }

    // 5. Verify the Derivation (which will apply postconditions if preconditions are met)
    printf("Verifying derivation step...\n");
    if (verify_derivation(step, &tm->memory, tm->registers)) {
        printf("Derivation verified successfully!\n");
    } else {
        printf("Derivation verification failed!\n"); // This should not happen as precondition is always true
    }
    printf("\n");


    printf("TM state after derivation step:\n");
    printf("State Register (REG_S): %llu\n", tm->registers[REG_S]);
    printf("State Register (REG_A): %llu\n", tm->registers[REG_A]); // REG_A should be incremented to 1
    printf("Head Position: %llu\n", tm->head_position);
    printf("Memory at Head Position: %llu\n", tm->memory.data[tm->head_position]);
    printf("\n");


    // 6. Step the TM once (original TM step, for comparison)
    if (step_tm(tm)) {
        printf("TM stepped successfully!\n");
    } else {
        printf("TM step failed or no transition found.\n");
    }

    printf("\nTM state after one TM step:\n");
    printf("State Register (REG_S): %llu\n", tm->registers[REG_S]);
    printf("State Register (REG_A): %llu\n", tm->registers[REG_A]); // REG_A remains as 1 (unaffected by TM step)
    printf("Head Position: %llu\n", tm->head_position);
    printf("Memory at Head Position: %llu\n", tm->memory.data[tm->head_position]);
    printf("Memory at Previous Head Position (0): %llu\n", tm->memory.data[0]); // Should be '1' now
    printf("\n");


    // 7. Free memory
    free_derivation(step);
    free_rule(my_rule);
    free_tm_simulator(tm);

    return 0;
}
