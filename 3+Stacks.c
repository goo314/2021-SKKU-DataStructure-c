#include <stdio.h>

/* Stack is
An ordered list in which insertions and
deletions are made at one end called the top : LIFO
*/

#define MAX_STACK_SIZE 100
typedef struct {
    int key; 
    /* other fields may be added*/
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

void push (element item)
{
    /* add an item to the global stack */
    if (top >= MAX_STACK_SIZE-1) {
        stackFull();
        return;
    }
    stack[++top] = item;
}

element pop ()
{
    /* return the top element from the stack, so called ‘pop’ */
    if (top == -1){
        stackEmpty();
        return;
    } /*returns an error key */
    return stack[top--];
}

/* Application
Line editing
Bracket matching
Maze Problem
Expression evaluation
*/