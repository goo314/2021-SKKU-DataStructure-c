#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    short int marked;
    int key;
    short int isBST;
} element;

void boolBST(element* tree, int k, int N)
{
    if(2*k+1 > N-1 || !tree[k].marked ) { tree[k].isBST = 1; return; }

    boolBST(tree, 2*k+1, N);
    boolBST(tree, 2*k+2, N);

    if(tree[2*k+1].isBST && tree[2*k+2].isBST 
        && tree[2*k+1].key < tree[k].key && tree[k].key < tree[2*k+2].key)
            tree[k].isBST = 1;
    
    else tree[k].isBST = 0;
}

int nodeSum(element *tree, int k, int N)
{
    int sum = 0;
    if(k < N && tree[k].marked && tree[k].isBST){
        sum += nodeSum(tree, 2*k+1, N);
        sum += tree[k].key;
        sum += nodeSum(tree, 2*k+2, N);
    }
    return sum;

}

void findMax(element *tree, int N)
{
    int max = nodeSum(tree, 0, N);
    int root=0;
    for(int i=0; i<N; i++)
    {
        if(tree[i].isBST && tree[i].marked)
        {
            if(max < nodeSum(tree, i, N))
            {
                root = i;
                max = nodeSum(tree, i, N);
            }
        }
    }

    printf("%d %d", max, tree[root].key);
}

int main(){
    char inputN[10];
    scanf("%s", inputN);
    int N = atoi(inputN);
    element tree[N];

    char inputKey[10];
    for(int i=0; i<N; i++)
    {
        scanf("%s", inputKey);

        element tmp;
        tmp.isBST = 0;
        if(*inputKey == 'x'){
            tmp.marked = 0;
            if(i==0) tmp.key = 0;
            else if(i%2) tmp.key = tree[(i-1)/2].key-1;
            else tmp.key = tree[(i-1)/2].key+1;
            tree[i] = tmp;
        }
        else
        {
            tmp.marked = 1;
            tmp.key = atoi(inputKey);
            tree[i] = tmp;
        }
    }

    boolBST(tree, 0, N);
    findMax(tree, N);


    return 0;
}
