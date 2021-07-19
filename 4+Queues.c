#include <stdio.h>

/* Queue is
An ordered list in which all insertions take place at
one end (rear) and all deletions take place at the
opposite end (front) : FIFO
- Circular Queue is
A queue wraps around the end of the array
rear = (rear+1) % MAX_QUEUE_SIZE
*/

#define MAX_QUEUE_SIZE 100 /*maximum queue size */
typedef struct {
    int key; 
    /* other fields may be added*/
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1; int front = -1;
void addq(element item)
{ 
    /* insert an item into a queue, so called ‘enqueue’ */ 
    if (rear == MAX_QUEUE_SIZE-1)
        queueFull(); 
    queue[++rear] = item;
}
element deleteq()
{
    /* delete an item at the front of the queue, so called ‘dequeue’ */ 
    if (front == rear){
        queueEmpty();
        return;
    } /* return an error key */
    return queue[++front];
}

// Circular Queue
element queue[MAX_QUEUE_SIZE];
int front=0, rear=0;
void addq(element item)
{
    rear = (rear+1) % MAX_QUEUE_SIZE;
    if (front == rear) 
        queueFull(rear); /* print error and exit */
    queue[rear] = item;
} 
element deleteq(){ 
    if (front == rear){
        queueEmpty();
        return;
    }
    front = (front+1) % MAX_QUEUE_SIZE;
    return queue[front];
}