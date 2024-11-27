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
#define fls_arena_push(arena, type, num) \
    (type *) fls_arena_push_((arena), sizeof(type), (num))
void fls_arena_reset(FlsArena *arena);
void fls_arena_free(FlsArena *arena);
void fls_arena_pop(FlsArena *arena);
FlsArenaHandle fls_arena_handle(FlsArena *arena);
void fls_arena_restore_from_handle(FlsArena *arena, FlsArenaHandle handle);
char *fls_arena_str_push(FlsArena *arena, const char *str);


#endif // MEMORY_H
