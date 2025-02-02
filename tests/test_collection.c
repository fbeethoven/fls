#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../src/collections.h"


// TODO:
#define list_init(arena, list, capacity)
#define list_append(arena, list, item)
#define list_delete(list, item)
#define list_slice(list, i, j)
#define list_concat(list, other)
#define list_from_queue(arena, queue)
#define list_from_stack(arena, stack)
#define stack_from_list(arena, list)
#define queue_from_list(arena, list)

typedef struct IntNode IntNode;
struct IntNode {
    IntNode *prev;
    IntNode *next;
    int value;
};

typedef struct {
    IntNode *first;
    IntNode *last;
} IntList;

fls_queue_register(int);
fls_stack_register(int);


void test_begin(const char *text) {
    int len = strlen(text);
    printf("\033[36m***********");
    for (int i=0; i<len; i++) {
        printf("*");
    }
    printf("***********\n");
    printf("*          %s          *\n", text);
    printf("***********");
    for (int i=0; i<len; i++) {
        printf("*");
    }
    printf("***********\033[0m\n");
}

void test_end() {
    printf("\n\n");
}

void test_queue_append_left() {
    test_begin("TEST QUEUE APPEND PUSH LEFT");
    IntList queue = {0};
    IntList *queue_ptr = &queue;
    IntNode items[10] = {0};

    for (int i=0; i<10; i++) {
        IntNode *item = &items[i];
        item->value = i;
        fls_queue_append_left(queue_ptr, item);
    }

    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    test_end();
}

void test_queue_append_right() {
    test_begin("TEST QUEUE APPEND PUSH RIGHT");
    IntList queue = {0};
    IntList *queue_ptr = &queue;
    IntNode items[10] = {0};
    for (int i=0; i<10; i++) {
        IntNode *item = &items[i];
        item->value = i;
        fls_queue_append_right(queue_ptr, item);
    }

    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    test_end();
}

void test_queue_remove() {
    test_begin("TEST QUEUE REMOVE");
    IntList queue = {0};
    IntList *queue_ptr = &queue;
    IntNode items[10] = {0};
    for (int i=0; i<10; i++) {
        IntNode *item = &items[i];
        item->value = i;
        fls_queue_append_right(queue_ptr, item);
    }

    printf("before remove:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }

    IntNode *node = &items[5];
    fls_queue_delete_node(node, queue_ptr->first, queue_ptr->last);
    printf("\nafter removing item 5:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }

    fls_queue_remove_first(queue_ptr);
    printf("\nafter remove:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    fls_queue_remove_first(queue_ptr);
    printf("\nafter remove:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    fls_queue_remove_first(queue_ptr);
    printf("\nafter remove:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    fls_queue_remove_last(queue_ptr);
    printf("\nafter remove:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    fls_queue_remove_last(queue_ptr);
    printf("\nafter remove:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    fls_queue_remove_last(queue_ptr);
    printf("\nafter remove:\n");
    for (IntNode *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    test_end();
}

void test_queue_register() {
    test_begin("TEST QUEUE REGISTER");
    FlsQueue(int) queue = {0};
    FlsQueue(int) *queue_ptr = &queue;
    FlsQueueNode(int) items[10] = {0};

    for (int i=0; i<10; i++) {
        FlsQueueNode(int) *item = &items[i];
        item->value = i;
        fls_queue_append_left(queue_ptr, item);
    }

    for (FlsQueueNode(int) *it=queue.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    test_end();
}

void test_stack_append() {
    test_begin("TEST STACK APPEND");
    IntList stack = {0};
    IntList *stack_ptr = &stack;
    IntNode items[10] = {0};

    for (int i=0; i<10; i++) {
        IntNode *item = &items[i];
        item->value = i;
        fls_stack_append(stack_ptr, item);
    }

    for (IntNode *it=stack.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    test_end();
}

void test_stack_remove() {
    test_begin("TEST STACK REMOVE");
    IntList stack = {0};
    IntList *stack_ptr = &stack;
    IntNode items[10] = {0};

    for (int i=0; i<10; i++) {
        IntNode *item = &items[i];
        item->value = i;
        fls_stack_append(stack_ptr, item);
    }

    printf("Before remove:\n");
    for (IntNode *it=stack.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }

    fls_stack_remove(stack_ptr);
    IntNode *prev = &items[5];
    IntNode *node = &items[4];
    fls_stack_delete_node(node, stack_ptr->first, prev);

    printf("\nAfter remove:\n");
    for (IntNode *it=stack.first; it; it=it->next) {
        printf("Value %d -> ", it->value);
    }
    test_end();
}

fls_stack_register(FlsStack(int));

void test_stack_register() {
    test_begin("TEST STACK REGISTER");
    FlsStack(FlsStack(int)) stack = {0};
    FlsStack(FlsStack(int)) *stack_ptr = &stack;
    FlsStackNode(FlsStack(int)) items[10] = {0};
    FlsStackNode(int) node_items[20] = {0};

    for (int i=0; i<10; i++) {
        FlsStackNode(FlsStack(int)) *item = &items[i];
        FlsStack(int) *queue_item = &item->value;
        FlsStackNode(int) *node_item_1 = &node_items[i*2];
        FlsStackNode(int) *node_item_2 = &node_items[i*2 + 1];
        node_item_1->value = i*2;
        node_item_2->value = i*2 + 1;
        fls_stack_append(queue_item, node_item_1);
        fls_stack_append(queue_item, node_item_2);
        fls_stack_append(stack_ptr, item);
    }

    for (FlsStackNode(FlsStack(int)) *it=stack.first; it; it=it->next) {
        printf("->");
        for (FlsStackNode(int) *j=it->value.first; j; j=j->next) {
            printf(" Value %d -> ", j->value);
        }
        printf("\n");
    }
    test_end();
}


fls_slice_register(int);

void test_slice_append() {
    test_begin("TEST SLICE APPEND");
    FlsSlice(int) slice = {0};

    for (int i=0; i<10; i++) {
        fls_slice_append(&slice, i);
    }

    for (int i=0; i<slice.count; i++) {
        printf("Value %d -> ", slice.items[i]);
    }

    free(slice.items);
    test_end();
}

int main() {
    test_queue_append_left();
    test_queue_append_right();
    test_queue_remove();
    test_queue_register();
    test_stack_append();
    test_stack_remove();
    test_stack_register();
    test_slice_append();
}
