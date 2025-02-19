// rule.c
#include "rule.h"
#include <stdlib.h>
#include <string.h>

Rule* create_rule(const char* name) {
    Rule* rule = (Rule*)malloc(sizeof(Rule));
    if (rule == NULL) {
        return NULL; // Memory allocation failed
    }
    rule->name = strdup(name); // Use strdup to allocate and copy the name
    if (rule->name == NULL) {
        free(rule); // Free already allocated rule struct
        return NULL; // Memory allocation failed for name
    }
    rule->preconditions = NULL;
    rule->num_preconditions = 0;
    rule->postconditions = NULL;
    rule->num_postconditions = 0;
    return rule;
}

void add_precondition(Rule* rule, PreconditionFunc check) {
    Precondition* new_preconditions = (Precondition*)realloc(rule->preconditions, sizeof(Precondition) * (rule->num_preconditions + 1));
    if (new_preconditions == NULL) {
        // Handle realloc failure, maybe set an error flag in the rule struct if you add error handling
        return;
    }
    rule->preconditions = new_preconditions;
    rule->preconditions[rule->num_preconditions].check = check;
    rule->num_preconditions++;
}

void add_postcondition(Rule* rule, PostconditionFunc apply) {
    Postcondition* new_postconditions = (Postcondition*)realloc(rule->postconditions, sizeof(Postcondition) * (rule->num_postconditions + 1));
    if (new_postconditions == NULL) {
        // Handle realloc failure
        return;
    }
    rule->postconditions = new_postconditions;
    rule->postconditions[rule->num_postconditions].apply = apply;
    rule->num_postconditions++;
}

void set_rule_instruction(Rule* rule, Operand source, Operand destination) {
    rule->instruction.source = source;
    rule->instruction.destination = destination;
}

void free_rule(Rule* rule) {
    if (rule != NULL) {
        free((void*)rule->name); // Cast to void* for free, even though const char*
        free(rule->preconditions);
        free(rule->postconditions);
        free(rule);
    }
}
