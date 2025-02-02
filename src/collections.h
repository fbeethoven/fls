#ifndef COLLECTIONS_H
#define COLLECTIONS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FLS_TO_STRING_(type) #type
#define FLS_TO_STRING(type) FLS_TO_STRING_(type)
#define FLS_CONCAT_(a, b) a##b
#define FLS_CONCAT(a, b) FLS_CONCAT_(a, b)

#define fls_queue_push_left_node_np(i, f, l, p, next, prev) \
    (f)==NULL ?                                             \
        ((f)=(l)=(i), (i)->next=(i)->prev=NULL):            \
        (i->next=(p), (p)->prev=(i),                        \
            (p)==(f) ? ((f)=(i), (i)->prev=NULL): (0))
#define fls_queue_push_right_node_np(i, f, l, p, next, prev)    \
    fls_queue_push_left_node_np(i, l, f, p, prev, next)
#define fls_queue_push_left_node(i, f, l, p)                    \
    fls_queue_push_left_node_np(i, f, l, p, next, prev)
#define fls_queue_push_right_node(i, f, l, p)                   \
    fls_queue_push_right_node_np(i, f, l, p, next, prev)
#define fls_queue_push_left_np(i, f, l, next, prev)             \
    fls_queue_push_left_node_np(i, f, l, f, next, prev)
#define fls_queue_push_right_np(i, f, l, next, prev)            \
    fls_queue_push_right_node_np(i, f, l, l, next, prev)
#define fls_queue_push_left(i, f, l)                            \
    fls_queue_push_left_node_np(i, f, l, f, next, prev)
#define fls_queue_push_right(i, f, l)                           \
    fls_queue_push_right_node_np(i, f, l, l, next, prev)

#define fls_queue_delete_node_np(i, f, l, next, prev)           \
    (f)==NULL ? (0) :                                           \
    (((i)==(f) ? ((f)=(i)->next, (f)->prev=NULL):               \
    (((i)==(l) ? ((l)=(i)->prev, (l)->next=NULL):               \
    (((i)->prev==NULL?(0) : ((i)->prev->next=(i)->next)),       \
    ((i)->next==NULL?(0) : ((i)->next->prev=(i)->prev)))))))
#define fls_queue_delete_node(i, f, l)                              \
    fls_queue_delete_node_np(i, f, l, next, prev)
#define fls_queue_delete_left_np(f, l, next, prev)                  \
    fls_queue_delete_node_np(f, f, l, next, prev)
#define fls_queue_delete_left(f, l)                                 \
    fls_queue_delete_node_np(f, f, l, next, prev)
#define fls_queue_delete_right_np(f, l, next, prev)                 \
    fls_queue_delete_node_np(l, f, l, next, prev)
#define fls_queue_delete_right(f, l)                                \
    fls_queue_delete_node_np(l, f, l, next, prev)

#define fls_queue_append_right(queue, node)                 \
    fls_queue_push_right(node, queue->first, queue->last)
#define fls_queue_append_left(queue, node)                  \
    fls_queue_push_left(node, queue->first, queue->last)
#define fls_queue_remove_first(queue)                       \
    fls_queue_delete_left(queue->first, queue->last)
#define fls_queue_remove_last(queue)                        \
    fls_queue_delete_right(queue->first, queue->last)

#define FlsQueueNode(type) FLS_CONCAT(FlsQueueNode, type)
#define FlsQueue(type) FLS_CONCAT(FlsQueue, type)
#define fls_queue_register(type)                        \
typedef struct FlsQueueNode(type) FlsQueueNode(type);   \
struct FlsQueueNode(type) {                             \
    FlsQueueNode(type) *prev;                           \
    FlsQueueNode(type) *next;                           \
    type value;                                         \
};                                                      \
typedef struct FlsQueue(type) FlsQueue(type);           \
struct FlsQueue(type) {                                 \
    FlsQueueNode(type) *first;                          \
    FlsQueueNode(type) *last;                           \
}

#define fls_stack_push_node_n(i, f, p, n, next)     \
    ((f) == NULL ?                                  \
        ((f) = (i), (i)->next=NULL):                \
        ((i)->next=(n),                             \
        ((f)==(n) ? ((f)=(i)) : ((p)->next=(i)))))
#define fls_stack_push_node(i, f, p, n)                 \
    fls_stack_push_node_n(i, f, p, n, next)
#define fls_stack_push_n(i, f, next)                    \
    fls_stack_push_node_n(i, f, f, f, next)
#define fls_stack_push(i, f)                            \
    fls_stack_push_node_n(i, f, f, f, next)
#define fls_stack_append(stack, node)                   \
    fls_stack_push(node, stack->first)

#define fls_stack_delete_node_n(i, f, p, next)  \
    (f)==NULL ? (0) :                           \
    ((i)==(f) ? ((f)=(i)->next) :               \
    ((p)->next = (i)->next))
#define fls_stack_delete_node(i, f, p)          \
    fls_stack_delete_node_n(i, f, p, next)
#define fls_stack_delete(f)                     \
    fls_stack_delete_node_n(f, f, f, next)
#define fls_stack_remove(stack)                 \
    fls_stack_delete(stack->first)

#define FlsStackNode(type) FLS_CONCAT(FlsStackNode, type)
#define FlsStack(type) FLS_CONCAT(FlsStack, type)
#define fls_stack_register(type)                        \
typedef struct FlsStackNode(type) FlsStackNode(type);   \
struct FlsStackNode(type) {                             \
    FlsStackNode(type) *next;                           \
    type value;                                         \
};                                                      \
typedef struct FlsStack(type) FlsStack(type);           \
struct FlsStack(type) {                                 \
    FlsStackNode(type) *first;                          \
}

// TODO:
#define list_slice(list, i, j)
#define list_concat(list, other)
#define list_from_queue(arena, queue)
#define list_from_stack(arena, stack)



#define FLS_SLICE_CAPACITY (1<<8)
#define FlsSlice(type) FLS_CONCAT(FLSSlice, type)
#define fls_slice_register(type)                \
typedef struct FlsSlice(type){                  \
    type *items;                                \
    size_t count;                               \
    size_t capacity;                            \
} FlsSlice(type)

#define fls_slice_reserve(slice, new_capacity)                                                      \
    do {                                                                                            \
        if ((new_capacity) > (slice)->capacity) {                                                   \
            if ((slice)->capacity == 0) {                                                           \
                (slice)->capacity = FLS_SLICE_CAPACITY;                                             \
            }                                                                                       \
            while ((new_capacity) > (slice)->capacity) {                                            \
                (slice)->capacity *= 2;                                                             \
            }                                                                                       \
            (slice)->items = realloc((slice)->items, (slice)->capacity * sizeof(*(slice)->items));  \
        }                                                                                           \
    } while (0)

#define fls_slice_append(slice, item)                       \
    do {                                                    \
        fls_slice_reserve((slice), (slice)->count + 1);     \
        (slice)->items[(slice)->count++] = (item);          \
    } while (0)

#define fls_slice_append_many(slice, items, count)                                          \
    do {                                                                                    \
        fls_slice_reserve((slice), (slice)->count + (count));                               \
        memcpy((slice)->items + (slice)->count, (count), (count)*sizeof(*(slice)->items));  \
        (da)->count += (count);                                                             \
    } while (0)

#endif  // COLLECTIONS_H
