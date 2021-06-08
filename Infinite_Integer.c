#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_INPUT_SIZE 100

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

void Add(char *numA, char *numB, char *numOut)
{
    int posA = strlen(numA)-1, posB = strlen(numB)-1, k = 0;
    int sum, tens = 0;

    while(posA>=0 && posB>=0)
    {
        sum = tens + (numA[posA]-'0') + (numB[posB]-'0');
        numOut[k] = (sum%10) + '0';
        tens = sum/10;
        posA--;
        posB--;
        k++;
    }
    for(;posA>=0;posA--)
    {
        sum = (numA[posA]-'0') + tens;
        numOut[k] = sum%10 + '0';
        tens = sum/10;
        k++;
    }
    for(;posB>=0;posB--)
    {
        sum = (numB[posB]-'0') + tens;
        numOut[k] = sum%10 + '0';
        tens = sum/10;
        k++;
    }
    if(tens) numOut[k++] = tens+'0';
    numOut[k] = '\0';
    reverse(numOut);

}

// isBigger? numA-numB : -(numA-numB) 
void Subtract(char *numA, char *numB, char *numOut, int isBigger)
{
    int posA = strlen(numA)-1, posB = strlen(numB)-1, k = 0;
    int sub, tmp = 0;

    while(posA>=0 && posB>=0)
    {
        if(numA[posA]+tmp < numB[posB])
        {
            sub = 10 + (numA[posA]-'0') - (numB[posB]-'0') + tmp;
            tmp = -1;
        }
        else
        {
            sub = (numA[posA]-'0') - (numB[posB]-'0') + tmp;
            tmp = 0;
        }
        numOut[k] = sub + '0';
        posA--;
        posB--;
        k++;
    }
    for(;posA>=0; posA--)
    {
        if(numA[posA]+tmp < '0')
        {
            sub = 10 + (numA[posA]-'0') + tmp;
            tmp = -1;
        }
        else
        {
            sub = (numA[posA]-'0') + tmp;
            tmp = 0;
        }
        numOut[k] = sub + '0';
        k++;
    }
    
    while(numOut[--k]=='0' && k);

    if(!isBigger)
    {
        numOut[++k] = '-';
    }

    numOut[k+1] = '\0';
    reverse(numOut);
}

int isBigger(char *numA, char *numB)
{
    if(strlen(numA) > strlen(numB)) return 1;
    else if(strlen(numA) < strlen(numB)) return 0;
    else
    {
        for(int i=0; i<strlen(numA); i++)
        {
            if(numA[i] == numB[i]) continue;
            else if(numA[i] > numB[i]) return 1;
            else return 0;
        }
    }
    return 1;
}

int main(){
    char op;
    char num1[MAX_INPUT_SIZE];
    char num2[MAX_INPUT_SIZE];
    scanf("%c", &op);
    scanf("%s", num1);
    scanf("%s", num2);

    int rsize;
    if(strlen(num1) > strlen(num2)) rsize = strlen(num1)+1;
    else rsize = strlen(num2)+1;
    char *result = (char*)malloc(sizeof(char)*rsize);

    if(op == '+')
    {
        Add(num1, num2, result);
    }
    else
    {
        if(isBigger(num1, num2)) Subtract(num1, num2, result, 1);
        else Subtract(num2, num1, result, 0);
    }

    printf("%s\n", result);
    free(result);
    
    return 0;
}
