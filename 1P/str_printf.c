#include <stdio.h>

char text[] = "Washing your car to make it rain doesn't work.";
void myprint(char *p);


int main(void)
{
    char *p = text + 20;
    myprint(p+5);
    myprint(&p[16]);
    myprint(p+30);
    myprint(&text[13]);
    myprint(text+46);
    return 0;
}


void myprint(char *p)
{
    while(*p != ' ' && *p)
    {
        putchar(*p++);
        printf("  (while)  ");
    }

    putchar('\n');
}


/* Pruebo cuántos lugares se necesita para llegar al segmentation fault

int main(void) {
    char *p = text + 20;
    for (int i = 0; i < 1000000; i += 1000)
    {
        printf("Trying p + %d: ", i);
        
        Intentando acceder a p + i
        myprint(p + i);  
    }
    return 0;
}

void myprint(char *p) {
    while(*p != ' ' && *p) {
        putchar(*p++);
    }
    putchar('\n');
}
*/