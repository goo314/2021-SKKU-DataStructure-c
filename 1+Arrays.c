# include <stdio.h>

/* Array is
- A set of consecutive memory location
- A collection of data of the same type
- A set of pairs <index, value>, such that each index
that is defined has a value associated with it
*/

// Representation
int list[5];
int x[3][5];

// Dynamically Allocated Arrays
int* make1dArray(int n)
{
    int* list;
    list = malloc(n * sizeof(int));
    return list;
}

int** make2dArray(int rows, int cols)
{ 
    int** x, i;
    MALLOC(x, rows * sizeof (*x));
    for (i = 0; i < rows; i++)
        MALLOC(x[i], cols * sizeof(**x));
    return x;
}


/* Applications
Ordered list : one dimansional array (polynomial, string)
Matrix : multi-dimensional array (sparse matrix) */