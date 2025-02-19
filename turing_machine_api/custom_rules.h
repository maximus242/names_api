// custom_rules.h
#ifndef CUSTOM_RULES_H
#define CUSTOM_RULES_H

#include "rule.h" // Include rule.h because we are creating and returning Rule*

Rule* create_load_immediate_rule(Register dest, Word value);
Rule* create_load_indexed_rule(Register dest, Register src, Register offset);
Rule* create_store_indexed_rule(Register dest, Register src, Register offset);

#endif
