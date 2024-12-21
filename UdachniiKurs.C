#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a node in the linked list
typedef struct Node {
    int data;          // Data stored in the node
    struct Node* next; // Pointer to the next node
} Node;

// Structure for the linked list itself (optional, but can be helpful)
typedef struct {
    Node* head; // Pointer to the first node in the list
} LinkedList;


// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Handle memory allocation failure
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


// Function to insert a node at the beginning of the list
void insertAtBeginning(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

// Function to insert a node at the end of the list
void insertAtEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
        return;
    }
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// Function to delete a node with the given data
void deleteNode(LinkedList* list, int data) {
    Node* current = list->head;
    Node* previous = NULL;

    while (current != NULL && current->data != data) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        return; // Data not found
    }

    if (previous == NULL) {
        list->head = current->next; // Deleting the first node
    } else {
        previous->next = current->next; // Deleting a node in the middle or end
    }
    free(current);
}


// Function to search for a node with the given data
bool searchNode(const LinkedList* list, int data) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}


// Function to print the linked list
void printList(const LinkedList* list) {
    Node* current = list->head;
    printf("[");
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
        if (current != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

// Function to free the memory allocated for the list
void freeList(LinkedList* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    list->head = NULL;
}


int main() {
    LinkedList myList;
    myList.head = NULL; // Initialize an empty list

    insertAtBeginning(&myList, 30);
    insertAtEnd(&myList, 10);
    insertAtBeginning(&myList, 20);
    insertAtEnd(&myList, 40);


    printf("List after insertions: ");
    printList(&myList);


    deleteNode(&myList, 20);
    printf("List after deleting 20: ");
    printList(&myList);

    printf("Is 10 in the list? %s\n", searchNode(&myList, 10) ? "Yes" : "No");
    printf("Is 20 in the list? %s\n", searchNode(&myList, 20) ? "Yes" : "No");

    freeList(&myList);
    printf("Memory freed.\n");

    return 0;
}
