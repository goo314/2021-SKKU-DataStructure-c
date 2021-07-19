#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;

typedef struct{
    int key;
} element;

struct node {
    element data;
    treePointer leftChild;
    treePointer rightChild;
};

treePointer modifiedSearch(treePointer tree, int k)
{
    treePointer ptr = tree;
    while (tree){
        if(k < tree->data.key){
            ptr = tree;
            tree = tree->leftChild;
        }
        else{
            ptr = tree;
            tree = tree->rightChild;
        }
    }
    return ptr;
}

void insert(treePointer *node, int k)
{
    treePointer ptr, temp = modifiedSearch(*node, k);
    if(temp || !(*node)){
        ptr = malloc(sizeof(*ptr));
        ptr->data.key = k;
        ptr->leftChild = ptr->rightChild = NULL;
        if(*node){
            if(k < temp->data.key){
                temp->leftChild = ptr;
            } else {
                temp->rightChild = ptr; }
        }else { *node = ptr; }
    }
}

int findMax(treePointer tree)
{
    if(!tree) return -1;
    else
    {
        int leftD = findMax(tree->leftChild);
        int rightD = findMax(tree->rightChild);
        if(leftD > rightD) return (leftD+1);
        else return (rightD+1);
    }
}

int main() {
    int N, input;
    scanf("%d", &N);

    treePointer tree = NULL;
    for(int i=0; i<N; i++)
    {
        scanf("%d", &input);
        insert(&tree, input);
    }

    printf("%d", findMax(tree));

	return 0;
}
