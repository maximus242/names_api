// minimal_tm_example.c
#include <stdio.h>
#include <stdlib.h>
#include "tm_simulator.h"
#include "types.h"

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

    // 4. Set initial tape content (Optional, assuming memory is initialized to 0)

    printf("Initial TM state:\n");
    printf("State Register (REG_S): %llu\n", tm->registers[REG_S]);
    printf("Head Position: %llu\n", tm->head_position);
    printf("Memory at Head Position: %llu\n", tm->memory.data[tm->head_position]);
    printf("\n");

    // 5. Step the TM once
    if (step_tm(tm)) {
        printf("TM stepped successfully!\n");
    } else {
        printf("TM step failed or no transition found.\n");
    }

    printf("\nTM state after one step:\n");
    printf("State Register (REG_S): %llu\n", tm->registers[REG_S]);
    printf("Head Position: %llu\n", tm->head_position);
    printf("Memory at Head Position: %llu\n", tm->memory.data[tm->head_position]);
    printf("Memory at Previous Head Position (0): %llu\n", tm->memory.data[0]); // Should be '1' now
    printf("\n");


    // 6. Free TM Simulator
    free_tm_simulator(tm);

    return 0;
}
