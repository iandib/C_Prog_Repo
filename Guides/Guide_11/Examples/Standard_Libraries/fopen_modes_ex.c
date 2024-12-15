#include <stdio.h>

void printWholeFile(char const *path);

int main(void)
{
   	FILE *fp;
	char str[100];

   	fp = fopen("test.txt", "w"); // fopen
   	fprintf(fp, "This is testing for fprintf...\n"); // fprintf
	//fflush(fp); // fflush
   	fputs("And this is testing for fputs...\n", fp); // fputs
   	fclose(fp); // fclose

	fp = fopen("test.txt", "r");
	printf("First char: %c\n", fgetc(fp)); // fgetc
	printf("First line: %s", fgets(str, 100, fp)); // fgets
	fclose(fp);

    fp = fopen("test.txt", "r+");
    fprintf(fp, "This is new!\n");
    fclose(fp);

	return 0;
}  

