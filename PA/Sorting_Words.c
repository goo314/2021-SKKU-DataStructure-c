#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode* listPointer;

struct listNode {
	char data[51];
	int frequency;
 	listPointer link;
};

void insert(listPointer* first, listPointer previous, char* word, int freq)
{
	listPointer temp = malloc(sizeof(*temp));
	strcpy(temp->data, word);
	temp->frequency = freq;

	if(*first && previous)
	{
		temp->link = previous->link;
		previous->link = temp;
	}
	else if(!previous)
	{
		temp->link = *first;
		*first = temp;
	}
	else
	{
		temp->link = NULL;
		*first = temp;
	}
}

void delete(listPointer* first, listPointer previous, listPointer x)
{
	if(previous) previous->link = x->link;
	else *first = (*first)->link;
	free(x);
}

listPointer findPrev(listPointer *first, char* str, int freq)
{
	listPointer prev = NULL;
	listPointer cmp = *first;
	
	for(; cmp && ((cmp->frequency) > freq); prev=cmp, cmp=cmp->link )
		if(strcmp(str, cmp->data) == 0) return prev;
	
	for( ;cmp && ( strcmp(str, cmp->data) > 0 ); prev=cmp, cmp=cmp->link )
		if((cmp->frequency) < freq) return prev;
	
	return prev;
}

void printNode(listPointer* first)
{	
	listPointer temp;
	while(*first)
	{
		temp = *first;
		printf("%s\n", temp->data);
		*first = (*first)->link;
		free(temp);
	}
}


int main() {
	int N;
	scanf("%d", &N);
	
	char input[51];
	scanf("%s", input);
	
	listPointer first;
	first = malloc(sizeof(*first));
	strcpy(first->data, input);
	first->frequency = 1;
	first->link = NULL;
	
	for(int i=0; i<N-1; i++)
	{
		scanf("%s", input);

		listPointer previous = findPrev(&first, input, 1);
		listPointer current;
		if(!previous) current = first;
		else current = previous->link;
		
		if(!current)
		{
			insert(&first, previous, input, 1);
		}
		else if(strcmp(current->data, input) == 0)
		{
			int freq = (current->frequency) + 1;
			
			if(current == first) current->frequency = freq;
			
			else
			{
				delete(&first, previous, current);
				previous = findPrev(&first, input, freq);
				insert(&first, previous, input, freq);
			}
			
		}
		else
		{
			insert(&first, previous, input, 1);
		}

	}

	printNode(&first);
	return 0;
}
