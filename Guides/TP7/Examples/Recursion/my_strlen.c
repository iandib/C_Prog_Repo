#include <stdio.h>

int my_strlen(const char* str);

int main(void)
{
    int len;
    len = my_strlen("Hoy");
    printf("len = %d\n", len);
    return 0;
}

int my_strlen(const char* str)
{
  if (*str == '\0')
  {
    printf("CASO BASE! Salgo...\n");
    return 0;
  }
  else
  {
    int len;
    printf("Entro con *str = %c\n", *str);
    len = 1 + my_strlen(str+1);
    printf("Salgo con *str = %c\n", *str);
    return len;
  }
}
