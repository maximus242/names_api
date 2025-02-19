#include "types.h"
#include <stdlib.h>
#include <stdio.h>

MemorySpace* create_memory_space(size_t size) {
    MemorySpace* mem = (MemorySpace*)malloc(sizeof(MemorySpace));
    if (mem == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    mem->data = (Word*)malloc(size * sizeof(Word));
    if (mem->data == NULL) {
        perror("Memory allocation failed");
        free(mem);
        exit(EXIT_FAILURE);
    }

    mem->size = size;

    // Initialize memory to 0 (optional but good practice)
    for (size_t i = 0; i < size; ++i) {
        mem->data[i] = 0;
    }

    return mem;
}

void free_memory_space(MemorySpace* mem) {
    if (mem != NULL) {
        free(mem->data); // Free allocated memory for data
        free(mem);       // Free the MemorySpace struct itself
    }
}

Word read_memory(const MemorySpace* mem, Address addr) {
    if (mem == NULL || addr >= mem->size) {
        // Handle out-of-bounds access (e.g., return 0, log an error, or exit)
        fprintf(stderr, "Error: Memory access out of bounds. Address: %llu, Memory Size: %zu\n", addr, mem->size);
        return 0; // Or any other suitable error handling
    }
    return mem->data[addr];
}

void write_memory(MemorySpace* mem, Address addr, Word value) {
    if (mem == NULL) {
        fprintf(stderr, "write_memory: MemorySpace pointer is NULL.\n");
        return; // Or handle the error as appropriate for your application
    }

    if (addr >= mem->size) {
        fprintf(stderr, "write_memory: Address 0x%llx is out of bounds (memory size: %zu).\n", addr, mem->size);
        return; // Or handle the error (e.g., by resizing the memory space)
    }

    mem->data[addr] = value;
}

Word get_register(const Word registers[REG_COUNT], Register reg) {
    if (registers == NULL) {
        fprintf(stderr, "get_register: registers array is NULL.\n");
        return 0; // Return 0 as a default/error value.  Consider a more robust error mechanism.
    }

    if (reg >= REG_COUNT) {
        fprintf(stderr, "get_register: Register index %u is out of bounds (REG_COUNT: %u).\n", (unsigned int)reg, (unsigned int)REG_COUNT);
        return 0; // Return 0 as a default/error value
    }

    return registers[reg];
}

void set_register(Word registers[REG_COUNT], Register reg, Word value) {
    if (registers == NULL) {
        fprintf(stderr, "set_register: registers array is NULL.\n");
        return; // Cannot proceed with a NULL array.
    }

    if (reg >= REG_COUNT) {
        fprintf(stderr, "set_register: Register index %u is out of bounds (REG_COUNT: %u).\n", (unsigned int)reg, (unsigned int)REG_COUNT);
        return; // Cannot write to an out-of-bounds register.
    }

    registers[reg] = value;
}
