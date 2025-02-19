// memory_management.h
#ifndef MEMORY_MANAGEMENT_H
#define MEMORY_MANAGEMENT_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h> // For size_t

typedef uint64_t Word;
typedef uint64_t Address;

typedef struct {
    Word* data;
    size_t size;
} MemorySpace;

MemorySpace* create_memory_space(size_t size);
void free_memory_space(MemorySpace* mem);
Word read_memory(const MemorySpace* mem, Address addr); // Add read_memory declaration
void write_memory(MemorySpace* mem, Address addr, Word value); // Good practice to include

#endif
