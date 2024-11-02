/*
 * Error
 *
 * Minimal program depicting variadic version of printf.
 *
 * Depicts usage of the four main stdargs macros
 * (va_list, va_start, va_arg, va_end) alongside
 * vprintf.
 *
 *
 * 22.07 Programación I @ Instituto Tecnológico de Buenos Aires, 2017
 */

#include <stdio.h>
#include <stdarg.h>

/* Error
 * Prints errors showing file in which occurd, line number
 * and fuly formatted error message.
 *
 * Input:
 *    format: format of message to be shown, alonside
 *    all parameters needed.
 * Output:
 *    -
 */
void error(char *format, ...);


/* * * * Usage example of afforementioned functions * * * */


char *filename;		// Input file name
int lineno;			// Line number

/* Random Error
 * Not so random error just for this program
 */
int randomError(void);


int main(void){

	char *message = (char *) "#%d error encountered";
	int errorCode = randomError();

	filename = (char *) __FILE__;
	lineno = 11;

	error(message, errorCode);

	return 0;

}

void error(char *format, ...) {
	va_list argp;

	printf("%s, line %d: error: ", filename, lineno);
	va_start(argp, format);
	vprintf(format, argp);
	va_end(argp);
	printf("\n");
}

int randomError(void){
	return 42;
}