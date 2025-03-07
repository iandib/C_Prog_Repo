#include <stdio.h>

int main(void)
{
    char a=3, b=3, c;

    c = (a < 5) && (++b > 3);
    printf("a=%d, b=%d, c=%d\n", a, b, c);

    return 0;
}
