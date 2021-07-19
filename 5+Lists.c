#include <stdio.h>

/* Linked Lists are
stired in memory in an arbitrary order
- Chain is
A linked list in which each node
represents one element
*/

// Represention
typedef struct listNode* listPointer;
typedef struct listNode {
    int data;
    listPointer link;
}listNode;

// Create Two Nodes
listPointer create2()
{/* Create a linked list with two nodes */
    listPointer first, second;
    MALLOC(first, sizeof(*first));
    MALLOC(second, sizeof(*second));
    second->link = NULL;
    second->data = 20;
    first->data = 10;
    first->link = second;
    return first;
}

// Insertion
void insert50(listPointer* first, listPointer x)
{ /* insert a new node with data=50 into the chain first after node x */
    listPointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->data = 50;
    if(*first) {
        temp->link = x->link;
        x->link = temp;
    }
    else { /* if(*first == NULL) */
        temp->link = NULL;
        *first = temp;
    }
}

// Deletion
void delete(listPointer *first, listPointer trail, listPointer x)
{ /* delete x from the list, trail is the preceding node 
     and *first is the front of the list */
    if (trail) 
        trail->link = x->link;
    else
        *first = (*first)->link;
    free(x);
}

// Multiple Stacks
#define MAX_STACKS 10
typedef struct { 
    int key;
    /* other fields */
} element;
typedef struct stack* stackPointer;
typedef struct stack { 
    element data;
    stackPointer link; 
};
stackPointer top[MAX_STACKS];

void push(int i, element item)
{ /* add item to the ith stack */
    stackPointer temp;
    MALLOC(temp, sizeof (*temp));
    temp->data = item;
    temp->link = top[i];
    top[i] = temp;
}

element pop(int i)
{ /* remove top element from the ith stack*/
    stackPointer temp = top[i];
    element item;
    if (!temp){
        stackEmpty();
        return;
    }
    item = temp->data;
    top[i] = temp->link;
    free(temp);
    return item;
}

// Multiple Queues
#define MAX_QUEUES 10 /* Maximum Number of Queues */
typedef struct queue* queuePointer;
typedef struct queue {
    element data;
    queuePointer link;
};
queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

void addq (int i, element item)
{ /* insert an item at the rear of queue i */
    queuePointer temp;
    MALLOC(temp, sizeof(*temp));
    temp->data = item;
    temp->link = NULL;
    if (front[i]) rear[i]->link = temp;
    else front[i] = temp; 
    rear[i] = temp;
}

element deleteq (int i)
{ /* Delete an item from queue i */
    queuePointer temp = front[i];
    element item;
    if (!temp){
        queueEmpty();
        return;
    }
    item = temp->data;
    front[i] = temp->link;
    free(temp);
    return item;
}