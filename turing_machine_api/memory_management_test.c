// memory_management_test.c (tests)
#include "memory_management.h" // Your header
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>  // For NULL


// --- Helper functions for setup (if needed) ---
//  These are not always necessary but can make tests cleaner.
MemorySpace* setup_memory(size_t size) {
    return create_memory_space(size);
}

void teardown_memory(MemorySpace* mem) {
    free_memory_space(mem);
}


// --- Tests for create_memory_space ---

void test_create_memory_space_valid_size() {
    size_t size = 1024;
    MemorySpace* mem = create_memory_space(size);
    assert(mem != NULL);
    assert(mem->size == size);
    assert(mem->data != NULL); // Make sure data is allocated
    for (size_t i = 0; i < size; ++i) {
        mem->data[i] = (Word)i; // Write some data
    }
    for (size_t i = 0; i < size; ++i) {
        assert(mem->data[i] == (Word)i); // Verify data
    }
    free_memory_space(mem); // Important: Free the memory!
}

void test_create_memory_space_large_size() {
    size_t size = 1ULL << 30; // 1GB (adjust as needed)
    MemorySpace* mem = create_memory_space(size);
    if(mem == NULL) {
        perror("Memory allocation failed (expected for large size)");
        return; // Test passes if allocation fails for very large size.
    }
    // If allocation succeeds (unlikely), test and free:
    assert(mem != NULL);
    assert(mem->size == size);
    assert(mem->data != NULL);
    free_memory_space(mem);
}

// --- Main test runner ---

int main() {
    // create_memory_space tests
    test_create_memory_space_valid_size();
    test_create_memory_space_large_size();

    printf("All memory management tests passed!\n");
    return 0;
}
