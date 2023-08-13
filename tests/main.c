#include "klib/linked_list.h"
#include <stdio.h>

struct Saske {
    int s;
};

void print_list(struct KLIB_LinkedList *list) {
    for (struct KLIB_LinkedListNode *current = list->tail; current != NULL;
         current = current->next) {
        printf("%d\n", ((struct Saske *)current->data)->s);
    }
}

void print_list_desc(struct KLIB_LinkedList *list) {
    for (struct KLIB_LinkedListNode *current = list->tail; current != NULL;
         current = current->previous) {
        printf("%d\n", ((struct Saske *)current->data)->s);
    }
}

int main() {
    struct KLIB_LinkedList *list = KLIB_create_linked_list();

    KLIB_LINKED_LIST_PUSH_BACK(list, struct Saske, (struct Saske){32});
    KLIB_LINKED_LIST_PUSH_BACK(list, struct Saske, (struct Saske){9});
    KLIB_LINKED_LIST_PUSH_BACK(list, struct Saske, (struct Saske){55});
    KLIB_LINKED_LIST_PUSH_FRONT(list, struct Saske, (struct Saske){1111});
    KLIB_LINKED_LIST_PUSH_FRONT(list, struct Saske, (struct Saske){0});

    print_list(list);
    printf("\n");

    KLIB_free_linked_list(list);

    return 0;
}
