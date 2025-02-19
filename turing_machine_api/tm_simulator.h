// tm_simulator.h
#ifndef TM_SIMULATOR_H
#define TM_SIMULATOR_H

#include "types.h"

TMSimulator* create_tm_simulator(size_t memory_size, const TMTransition* transitions, size_t num_transitions);
void free_tm_simulator(TMSimulator* tm);
bool step_tm(TMSimulator* tm);
void setup_tm_transition_table(TMSimulator* tm, const TMTransition* transitions, size_t num_transitions);

#endif
