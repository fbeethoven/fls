#ifndef MEMORY_H
#define MEMORY_H

#include <stdio.h>
#include <stdbool.h>


typedef struct FlsArenaNode FlsArenaNode;
struct FlsArenaNode {
    FlsArenaNode *next;
    char *data;
    char *cursor;
    size_t capacity;
};

typedef struct FlsArena {
    FlsArenaNode *first;
    size_t counter;
    FlsArenaNode *first_free;
} FlsArena;

typedef struct FlsArenaHanle {
    FlsArenaNode *node;
    char *cursor;
} FlsArenaHandle;

bool fls_arena_init(FlsArena *arena);
bool fls_arena_init_capacity(FlsArena *arena, size_t capacity);
void *fls_arena_push_(FlsArena *arena, size_t type_size, int num);
#define fls_arena_alloc_many(arena, type, num) \
    (type *) __fls_arena_alloc_many((arena), sizeof(type), (num))
void fls_arena_reset(FlsArena *arena);
void fls_arena_free(FlsArena *arena);
void fls_arena_pop(FlsArena *arena);
FlsArenaHandle fls_arena_handle(FlsArena *arena);
void fls_arena_restore_from_handle(FlsArena *arena, FlsArenaHandle handle);
char *fls_arena_str_push(FlsArena *arena, const char *str);


#endif // MEMORY_H


#ifdef MEMORY_IMPLEMENTATION
#include <stdlib.h>
#include <string.h>

#include <fls/memory.h>


#define FLS_ARENA_CAPACITY (1 << 12)


static bool arena_push_node(FlsArena *arena, size_t capacity) {
    FlsArenaNode *node = (FlsArenaNode *)calloc(1, sizeof(FlsArenaNode));
    if (node == NULL) {
        return false;
    }

    char *data = (char *)calloc(1, capacity);
    if (data == NULL) {
        return false;
    }
    node->data = data;
    node->cursor = node->data;
    node->capacity = capacity;

    node->next = arena->first;
    arena->first = node;
    arena->counter++;

    return true;
}

bool fls_arena_init_capacity(FlsArena *arena, size_t capacity) {
    return arena_push_node(arena, capacity);
}


bool fls_arena_init(FlsArena *arena) {
    return fls_arena_init_capacity(arena, FLS_ARENA_CAPACITY);
}


void *__fls_arena_alloc_many(FlsArena *arena, size_t type_size, int num) {
    if (!arena){
        return malloc(num * type_size);
    }

    FlsArenaNode *node = arena->first;
    size_t capacity = num * type_size;

    if (node->cursor + capacity > node->data + node->capacity) {
        size_t new_capacity = capacity<node->capacity ? node->capacity:capacity;
        if (!arena_push_node(arena, new_capacity)) {
            return NULL;
        }
    }

    void *result = node->cursor;
    memset(result, 0, capacity);
    node->cursor += capacity;

    return result;
}

void fls_arena_pop(FlsArena *arena) {
    FlsArenaNode *node = arena->first;
    if (node == NULL) {
        arena->counter = 0;
        return;
    }

    node->cursor = node->data;

    arena->first = node->next;
    node->next = arena->first_free;
    arena->first_free = node;
    if (arena->counter > 0) {
        arena->counter--;
    }
}

void fls_arena_reset(FlsArena *arena) {
    while (arena->counter > 0) {
        fls_arena_pop(arena);
    }
}

void fls_arena_free(FlsArena *arena) {
    fls_arena_reset(arena);
    FlsArenaNode *node = arena->first_free;
    FlsArenaNode *current = arena->first_free;
    while(node) {
        node = node->next;
        free(current->data);
        free(current);
        current = node;
    }
}

FlsArenaHandle fls_arena_handle(FlsArena *arena) {
    FlsArenaHandle handle = {0};
    FlsArenaNode *node = arena->first;
    if (node == NULL) {
        return handle;
    }

    handle.node = node;
    handle.cursor = node->cursor;

    return handle;
}

void fls_arena_restore_from_handle(FlsArena *arena, FlsArenaHandle handle) {
    while (arena->first && arena->first != handle.node) {
        fls_arena_pop(arena);
    }

    if (arena->first == handle.node && handle.cursor < arena->first->cursor) {
        arena->first->cursor = handle.cursor;
    }
}

char *fls_arena_str_push(FlsArena *arena, const char *str) {
    int str_len = strlen(str);
    char *result = fls_arena_push(arena, char, str_len); 
    memcpy(result, str, str_len);

    return result;
}
#endif  // MEMORY_IMPLEMENTATION
