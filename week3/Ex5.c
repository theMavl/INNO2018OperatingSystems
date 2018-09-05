#include <stdio.h>
#include <malloc.h>

typedef struct Node {
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LinkedList {
    Node *head;
} LinkedList;

LinkedList *new_list() {
    return (LinkedList *) malloc(sizeof(LinkedList));
}

void init_list(LinkedList *list, int value) {
    list->head = (Node *) malloc(sizeof(Node));
    list->head->value = value;
}

LinkedList *new_list_init(int value) {
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
    init_list(list, value);
    return list;
}

Node *new_node(int value) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void insert_node(LinkedList *list, Node *node, Node *newNode) {
    if (list->head == NULL) {
        printf("Error! List is not initialised");
        return;
    } else {
        // Check if given node exists in list
        Node *current = list->head;
        while (current != NULL) {
            if (current == node) {
                Node *next = current->next;
                current->next = newNode;
                newNode->prev = current;
                newNode->next = next;
                if (next != NULL)
                    next->prev = newNode;
                break;
            }
            current = current->next;
        }

    }
}

void delete_node(LinkedList *list, Node *node) {
    Node *current = list->head;
    while (current != NULL) {
        if (node == list->head) {
            list->head = node->next;
            if (list->head != NULL)
                list->head->prev = NULL;
            break;
        } else if (current == node) {
            Node *parent = current->prev;
            Node *child = current->next;
            free(current);
            parent->next = child;
            if (child != NULL)
                child->prev = parent;
            break;
        }
        current = current->next;
    }
}

void print_list(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    LinkedList *list = new_list();
    Node *myNewNode2 = new_node(2);
    Node *myNewNode3 = new_node(3);
    Node *myNewNode4 = new_node(4);
    print_list(list);
    init_list(list, 1); // Or use new_list_init() straightaway
    print_list(list);
    insert_node(list, list->head, myNewNode2);
    print_list(list);
    insert_node(list, list->head->next, myNewNode3);
    print_list(list);
    insert_node(list, list->head, myNewNode4);
    print_list(list);
    delete_node(list, myNewNode3);
    print_list(list);
    delete_node(list, list->head);
    print_list(list);
    delete_node(list, myNewNode4);
    print_list(list);
    delete_node(list, myNewNode2);
    print_list(list);
    printf("Done");
    return 0;
}

