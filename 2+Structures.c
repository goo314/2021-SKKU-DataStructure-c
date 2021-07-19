#include <stdio.h>

/* Structure is
A collection of data items, where each item is
identified as to its type and nema
*/

#include <string.h>
typedef struct {
    char name[10];
    int age;
    float salary;
} humanBeing;

void create()
{
    humanBeing person1;
    strcpy(person1.name, "korykang");
    person1.age = 34;
    person1.salary = 35000;
}