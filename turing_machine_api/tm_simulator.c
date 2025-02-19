// tm_simulator.c
#include "tm_simulator.h"
#include <stdlib.h>
#include <string.h>

TMSimulator* create_tm_simulator(size_t memory_size, const TMTransition* transitions, size_t num_transitions) {
    TMSimulator* tm = (TMSimulator*)malloc(sizeof(TMSimulator));
    if (tm == NULL) {
        return NULL; // Memory allocation failed
    }

    tm->memory.data = (Word*)malloc(sizeof(Word) * memory_size);
    if (tm->memory.data == NULL) {
        free(tm);
        return NULL; // Memory allocation failed for memory space
    }
    tm->memory.size = memory_size;
    memset(tm->memory.data, 0, sizeof(Word) * memory_size); // Initialize memory to 0

    for (int i = 0; i < REG_COUNT; ++i) {
        tm->registers[i] = 0; // Initialize registers to 0
    }

    tm->head_position = 0; // Initialize head position to 0
    tm->transition_table = 100; // Arbitrary address for now, can be configurable or dynamically allocated.  Let's assume transition table starts at address 100.
    tm->num_transitions = 0; // Will be set in setup_tm_transition_table
    tm->jump_target = 0; // Initialize jump target

    setup_tm_transition_table(tm, transitions, num_transitions); // Setup the transition table

    return tm;
}

void free_tm_simulator(TMSimulator* tm) {
    if (tm != NULL) {
        free(tm->memory.data);
        free(tm);
    }
}

void setup_tm_transition_table(TMSimulator* tm, const TMTransition* transitions, size_t num_transitions) {
    if (tm == NULL || transitions == NULL) {
        return; // Handle null pointers
    }

    size_t transition_table_size_bytes = num_transitions * sizeof(TMTransition); // Calculate total size in bytes for transition table

    if (tm->transition_table + (transition_table_size_bytes / sizeof(Word)) > tm->memory.size) { // Check for overflow in terms of Word units
        // Transition table would overflow memory, handle error.
        // For now, we'll just truncate, but a better error handling is needed in real scenario.
        num_transitions = (tm->memory.size - tm->transition_table) * sizeof(Word) / sizeof(TMTransition); // Calculate max transitions that fit
        if (num_transitions < 0) num_transitions = 0;
        transition_table_size_bytes = num_transitions * sizeof(TMTransition); // Recalculate size after truncation
    }

    for (size_t i = 0; i < num_transitions; ++i) {
        memcpy(&tm->memory.data[tm->transition_table + i * (sizeof(TMTransition) / sizeof(Word))], &transitions[i], sizeof(TMTransition));
    }
    tm->num_transitions = num_transitions;
}


bool step_tm(TMSimulator* tm) {
    if (tm == NULL) {
        return false; // Handle null simulator
    }

    if (tm->head_position >= tm->memory.size) {
        return false; // Head position out of bounds
    }

    Word current_state = tm->registers[REG_S];
    Word current_symbol = tm->memory.data[tm->head_position];

    // Find transition - simple linear search for now.  For performance, consider hash table or sorted array.
    TMTransition* transitions_in_memory = (TMTransition*)&tm->memory.data[tm->transition_table]; // Treat memory as array of TMTransition structs

    TMTransition* found_transition = NULL;
    for (size_t i = 0; i < tm->num_transitions; ++i) {
        TMTransition* transition = &transitions_in_memory[i];
        if (transition->state == current_state && transition->symbol == current_symbol) {
            found_transition = transition;
            break;
        }
    }

    if (found_transition == NULL) {
        return false; // No transition found for current state and symbol - Halting condition or error.
    }

    tm->registers[REG_S] = found_transition->next_state;
    tm->memory.data[tm->head_position] = found_transition->write_symbol;
    if (found_transition->move_right) {
        tm->head_position++;
    } else {
        if (tm->head_position > 0) {
            tm->head_position--; // Move left, but don't go below 0
        }
    }
    // jump_target is not used in this basic step function, it would be relevant for more complex TM models with jump/call instructions in transitions.

    return true;
}
