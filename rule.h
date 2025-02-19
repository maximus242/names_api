// rule.h
#ifndef RULE_H
#define RULE_H

#include "types.h"

Rule* create_rule(const char* name);
void add_precondition(Rule* rule, PreconditionFunc check);
void add_postcondition(Rule* rule, PostconditionFunc apply);
void set_rule_instruction(Rule* rule, Operand source, Operand destination);
void free_rule(Rule* rule);

#endif
