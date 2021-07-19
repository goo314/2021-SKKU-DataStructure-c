#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

void reverse(char *str)
{
    int c,i,j;
    for(i=0,j=strlen(str)-1; i<j; i++,j--)
    {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

typedef struct 
{
    char key;
} element;

void stackFull()
{
	fprintf(stderr, "Stack is full, cannot add element");
	exit(EXIT_FAILURE);
}

void stackEmpty()
{
	fprintf(stderr, "Stack is empty, cannot pop element");
	exit(EXIT_FAILURE);
}

void push(element *stack, int *top, element item)
{
	if(*top >= MAX_STACK_SIZE-1) stackFull();
	stack[++(*top)] = item;
}

element pop(element *stack, int *top)
{
	if(*top == -1) stackEmpty();
	return stack[(*top)--];
}

int precedure(char op1, char op2)
{
	if(op1=='+' || op1=='-')
	{
		if(op2=='+' || op2=='-') return 0; //op1 == op2
		else return -1; //op1 < op2
	}
	else
	{
		if(op2=='+' || op2=='-') return 1; //op1 > op2
		else return 0; //op1 == op2
	}
	return -1;
}

void ChangetoPostfix(char *infix, char *postfix)
{
	element operators[MAX_STACK_SIZE];
	int topO = -1;
	
	int posP = 0;

	for(int posI=0; posI<strlen(infix); posI++)
	{
		if('A'<=infix[posI] && infix[posI]<='Z')
		{
			postfix[posP] = infix[posI];
			posP++;
		}
		else
		{
			while(topO>=0 && precedure(operators[topO].key, infix[posI])>=0)
			{
				element op = pop(operators, &topO);
				postfix[posP] = op.key;
				posP++;
			}
			element opr;
			opr.key = infix[posI];
			push(operators, &topO, opr);
		}
	}
	while(topO >= 0)
	{
		element op = pop(operators, &topO);
		postfix[posP] = op.key;
		posP++;
	}

    postfix[posP] = '\0';
}


void ChangetoPrefix(char *infix, char *prefix)
{
    reverse(infix);
    ChangetoPostfix(infix, prefix);
    reverse(prefix);
}

int main() {
	char infix[MAX_STACK_SIZE];

	char *postfix = (char*)malloc(sizeof(char)*strlen(infix));
	char *prefix = (char*)malloc(sizeof(char)*strlen(infix));

	scanf("%s",infix);
	ChangetoPostfix(infix, postfix);
	ChangetoPrefix(infix, prefix);
	printf("%s\n", prefix);
	printf("%s\n", postfix);
	
	free(postfix);
	free(prefix);
	
	return 0;
}
