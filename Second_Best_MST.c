#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 10000000

typedef struct{
    int wt;
    int vertex;
} element;

//////////////////////////////////// PRIORITY QUEUE ////////////////////////////////////////////
element priorityQueue[MAX_ELEMENTS];    
int n = 0;

int empty(int n)
{
    if(!n) return 1;
    else return 0;
}

void push(element item, int *n)
{
    int i = ++(*n);
    while( (i!=1) && (item.wt < priorityQueue[i/2].wt) )
    {
        priorityQueue[i] = priorityQueue[i/2];
        i /= 2;
    }
    priorityQueue[i] = item;
}

element pop(int *n)
{
    int parent, child;
    element item, node;
    item = priorityQueue[1];
    node = priorityQueue[(*n)--];
    parent = 1; child = 2;
    while( child <= *n )
    {
        if( (child<*n) && (priorityQueue[child].wt > priorityQueue[child+1].wt) )
            child++;
        if( node.wt <= priorityQueue[child].wt ) break;
        priorityQueue[parent] = priorityQueue[child];
        parent = child;
        child *= 2;
    }
    priorityQueue[parent] = node;
    return item;
}
/////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct node
{
    int parent;
    int weight;
} node;

typedef struct edges
{
    int w;
    int v, u;
} edges;

int findDepth(node* Tree, int nV, int curV)
{
    int ret = 0;
    while(Tree[curV].parent != -1)
    {
        ret += 1;
        curV = Tree[curV].parent;
    }
    return ret;
}

int maxEdgeinCycle(node* Tree, int nV, int vertex, int u)
{
    int max = 0;
    int dv = findDepth(Tree, nV, vertex);
    int du = findDepth(Tree, nV, u);
    
    while(vertex != u)
    {
        if(du == dv)
        {
            if(Tree[vertex].weight < Tree[u].weight)
            {
                if(max < Tree[u].weight) { max = Tree[u].weight; }
            }                
            else
            {
                if(max < Tree[vertex].weight) { max = Tree[vertex].weight; }
            }
            vertex = Tree[vertex].parent; dv--;
            u = Tree[u].parent; du--; 
        }
        else if(dv > du)
        {
            if(max < Tree[vertex].weight) max = Tree[vertex].weight;
            vertex = Tree[vertex].parent; dv--;
        }
        else
        {
            if(max < Tree[u].weight) max = Tree[u].weight;
            u = Tree[u].parent; du--;
        }
    }

    return max;
}

void findMST(int **cost, int nV)
{
    short int visit[nV];
    node *T = malloc(nV*sizeof(*T));
    
    int nnT = 0;
    edges *nonT = malloc(nV*nV*sizeof(*nonT));
    
    for(int i=0; i<nV; i++)
    {
        visit[i] = 0;
        T[i].parent = -1;
        T[i].weight = 100000;
    }

    int MST = 0;

    element root;
    root.vertex = 0;
    root.wt = 0;
    T[root.vertex].weight = 0;
    push(root, &n);

    while(!empty(n))
    {
        element x = pop(&n);
        if(visit[x.vertex]) { continue; }

        visit[x.vertex] = 1;
        MST += x.wt;

        for(int j=0; j<nV; j++)
        {
            if(j == x.vertex) { continue; }
            int w = cost[x.vertex][j];

            if( T[j].weight < w && T[x.vertex].weight < w )
            {
                edges k;
                k.v = x.vertex; k.u = j; k.w = w;
                nonT[nnT] = k;
                nnT++;
            }
            else if(!visit[j] && w < T[j].weight)
            {
                element p;
                p.vertex = j; p.wt = w;
                push(p, &n);
                T[j].parent = x.vertex;
                T[j].weight = w;
            }
            else{}
        }
    }

    int secondMST;

    int min = 100000*nV;
    for(int i=0; i<nnT; i++)
    {
        int x, y, c;
        x = nonT[i].v;
        y = nonT[i].u;
        c = nonT[i].w;

        int m = maxEdgeinCycle(T, nV, x, y);
        if( 0 <c-m && c-m < min) min = c-m;

    }
    secondMST = MST + min;
    printf("%d\n", MST);
    printf("%d\n", secondMST);
    
    free(T);
    free(nonT);
}


int main()
{
    int nV;
    scanf("%d", &nV);

    if(nV == 1) { printf("0\n0\n"); }
    else if(nV == 2)
    {
        int vertex, u, wt;
        scanf("%d %d %d", &vertex, &u, &wt);
        printf("%d\n%d\n", wt, wt);
    }
    else
    {
        int** cost = malloc(nV*sizeof(int*));
        for(int i=0; i<nV; i++)
        { cost[i] = malloc(nV*sizeof(int)); }

        for(int i=0; i<nV; i++)
            for(int j=0; j<nV; j++)
                cost[i][j] = 0;
    
        for(int i=0; i<nV*(nV-1)/2; i++)
        {
            int vertex, u, wt;
            scanf("%d %d %d", &vertex, &u, &wt);
            cost[vertex][u] = wt;
            cost[u][vertex] = wt;
        }

        findMST(cost, nV);
        
        for(int i=0; i<nV; i++)
        { free(cost[i]); }
    } 

    return 0;
}
