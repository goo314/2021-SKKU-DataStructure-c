#include <stdio.h>
#include <stdlib.h>

typedef struct polyNode* polyPointer;
struct polyNode
{
    int coef;
    int expon;
    polyPointer link;
};

int compareExp(int expa, int expb)
{
    if(expa > expb) return 1;
    else if(expa == expb) return 0;
    else return -1;
}

void attach(int coefficient, int exponent, polyPointer* tail)
{
    polyPointer tmp = malloc(sizeof(*tmp));
    tmp->coef = coefficient; tmp->expon = exponent; tmp->link = NULL;
    
    (*tail)->link = tmp;
    *tail = tmp;
    
}

polyPointer paddorsub(polyPointer a, polyPointer b, char op)
{
    polyPointer addResult, tmpRear;
    int afterop;
    addResult = malloc(sizeof(*addResult));
    addResult->coef = 0; addResult->expon = 0; addResult->link = NULL;

    tmpRear = addResult;

    while(a && b)
    {
        switch (compareExp(a->expon, b->expon))
        {
            case -1:
                attach(b->coef, b->expon, &tmpRear);
                b = b->link;
                break;
            case 0:
                if(op == '-') afterop = a->coef - b->coef;
                else afterop = a->coef + b->coef;

                if(afterop) attach(afterop, a->expon, &tmpRear);
                a = a->link; b = b->link; 
                break; 
            case 1:
                attach(a->coef, a->expon, &tmpRear);
                a = a->link;
                break;
        }
    }
    for(; a; a=a->link) attach(a->coef, a->expon, &tmpRear);
    for(; b; b=b->link)
    {
        if(op == '-') attach(-(b->coef), b->expon, &tmpRear);
        else attach(b->coef, b->expon, &tmpRear);
    } 
    if(addResult->link) addResult = addResult->link;

    return addResult;
}

polyPointer pmul(polyPointer a, polyPointer b) //multiple one term of b
{
    polyPointer mulResult = malloc(sizeof(*mulResult));
    mulResult->coef = 0; mulResult->expon = 0; mulResult->link = NULL;
    if( !(b->coef) ) return mulResult;
    
    polyPointer tmpRear = mulResult;
    int mul;
    for(; a; a=a->link)
    {
        mul = (a->coef)*(b->coef);
        if(mul) attach(mul, a->expon+b->expon, &tmpRear);
    }
    mulResult = mulResult->link;
    return mulResult;
}

polyPointer initialPoly(void)
{
    polyPointer inputPoly = malloc(sizeof(*inputPoly));
    int howmanyTerm, itscoef, itsexp;
    scanf("%d", &howmanyTerm);
    scanf("%d %d", &itscoef, &itsexp);
    inputPoly->coef = itscoef; inputPoly->expon = itsexp; inputPoly->link = NULL;

    polyPointer toRear = inputPoly;
    for(int i=0; i < (howmanyTerm-1); i++)
    {
        scanf("%d %d", &itscoef, &itsexp);
        attach(itscoef, itsexp, &toRear);
    }

    return inputPoly;
    
}

void printPoly(polyPointer* polyfirst)
{
    polyPointer temp;
    while(*polyfirst)
    {
        temp = *polyfirst;
        printf("%d %d\n", temp->coef, temp->expon);
        *polyfirst = (*polyfirst)->link;
        free(temp);
    }
}

int main()
{
    char operator;
    scanf("%c", &operator);
    polyPointer poly1 = initialPoly();
    polyPointer poly2 = initialPoly();
    

    if(operator == '*')
    {
        polyPointer resultPoly = malloc(sizeof(*resultPoly));
        resultPoly->coef = 0; resultPoly->expon = 0; resultPoly->link = NULL;
        for(;poly2 ; poly2=poly2->link) resultPoly = paddorsub(resultPoly, pmul(poly1, poly2), '+');

        printPoly(&resultPoly);

    }
    else if(operator == '/')
    {
        polyPointer quotient = malloc(sizeof(*quotient));
        quotient->coef = 0; quotient->expon = 0; quotient->link = NULL;

        polyPointer remainder = poly1;
        polyPointer rearofq = quotient;

        while( (remainder->expon) >= (poly2->expon) )
        {

            attach((remainder->coef)/(poly2->coef), (remainder->expon)-(poly2->expon), &rearofq);
            remainder = paddorsub(remainder, pmul(poly2, rearofq), '-');
            
        }
        if(quotient->link) quotient = quotient->link;
        
        printf("q\n");
        printPoly(&quotient);
        printf("r\n");
        printPoly(&remainder);
    }
    
    return 0;
}
