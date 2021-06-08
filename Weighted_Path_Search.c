#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

//priority queue using min heap
typedef struct{
    int weight;
    int x, y;
} element;

typedef struct queue *queuePointer;
typedef struct queue
{
    element data;
    queuePointer link;
};

queuePointer front = NULL;

int empty()
{
    if(!front) return TRUE;
    else return FALSE;
}

void addq(element item)
{
    queuePointer temp = malloc(sizeof(*temp));
    temp->data = item;
    temp->link = NULL;

    if(front)
    {   
        if(temp->data.weight < front->data.weight)
        {
            temp->link = front;
            front = temp;
            return;
        }

        queuePointer parent = front;
        queuePointer child = front->link;
        while(child)
        {
            if( temp->data.weight<child->data.weight ) { break; }
            else if( temp->data.weight == child->data.weight )
            {
                if(temp->data.x > child->data.x) { break; }
                else if(temp->data.x == child->data.x)
                    if(temp->data.y < child->data.y) { break; }

            }
            parent = child;
            child = child->link;
        }
        parent->link = temp;
        if(child) temp->link = child;
    } 
    else front = temp;
}

element deleteq()
{
    queuePointer temp = front;
    element item;

    item = temp->data;
    front = temp->link;
    free(temp);
    return item;

}

void Dijkstra(int **cost, int row, int col, int x1, int y1, int x2, int y2)
{
    int found[row][col];
    int distance[row][col];
    int prev[row*col];

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            found[i][j] = FALSE;
            distance[i][j] = 2147483647;
            prev[i*col + j] = -1;
        }
    }
    distance[x1][y1] = 0;

    element source;
    source.weight = 0;   source.x = x1;    source.y = y1;
    addq(source);
    
    //move down-left-right-up
    int moveX[4] = {1, 0, 0, -1};
    int moveY[4] = {0, -1, 1, 0};

    while(!empty())
    {
        element cur = deleteq();
        if(found[cur.x][cur.y]) { continue; }

        found[cur.x][cur.y] = TRUE;
        if(cur.x == x2 && cur.y == y2) { break; }

        for(int i=0; i<4; i++)
        {
            int x = cur.x + moveX[i];
            int y = cur.y + moveY[i];
            if( (x<0) || (x>=row) || (y<0) || (y>=col) ) { continue; }

            int w = cost[x][y];
            if(!found[x][y] && distance[cur.x][cur.y]+w < distance[x][y])
            {
                element p;
                p.weight = distance[cur.x][cur.y] + w;
                p.x = x;  p.y = y;
                addq(p);
                prev[x*col+y] = cur.x*col + cur.y;
                distance[x][y] = distance[cur.x][cur.y] + w;
            }
        }
    }

    char* dir = malloc(row*col*sizeof(char)); 
    int idx = 0;

    int p = x2*col + y2;
    while(prev[p]!=-1)
    {
        if(p-prev[p] == col)
            dir[idx] = 'd';
        else if(p-prev[p] == -1)
            dir[idx] = 'l';
        else if(p-prev[p] == 1)
            dir[idx] = 'r';
        else if(p-prev[p] == -col)
            dir[idx] = 'u';
        else;
        p = prev[p];
        idx++;
    }
    dir[idx] = '\0';

    for(int i=idx-1; i>=0; i--)
        printf("%c ", dir[i]);

    free(dir);

}


int main()
{
    int row, col;
    scanf("%d %d", &row, &col);

    int **cost = (int**)malloc(sizeof(int*)*row);
    for(int i=0; i<row; i++)
        cost[i] = (int*)malloc(sizeof(int)*col);

    int startX, startY;     int endX, endY;
    int distance[row][col];

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            char p;
            scanf(" %c", &p);

            if(p == 'S')
            {
                startX = i;     startY = j;
                cost[startX][startY] = 0;
            }
            else if(p == 'G')
            {
                endX = i; endY = j;
                cost[endX][endY] = 0;
            }
            else { cost[i][j] = p-'0'; }
        }
    }
    
    Dijkstra(cost, row, col, startX, startY, endX, endY);

    for(int i=0; i<row; i++) free(cost[i]);

    return 0;
}
