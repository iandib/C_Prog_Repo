#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

const char msg0[]="Hola ITBA (Direct System Call)\n";
const char msg1[]="Hola ITBA (Wraped System Call)\n";

int main(void) {
long Nwritten;
/*-----------------------------*/
/* direct system call
*/
/* SYS_write (func no. is 4) */
/*-----------------------------*/
Nwritten = syscall(SYS_write,STDOUT_FILENO,msg0,sizeof(msg0)-1);
printf ("Number of bytes written=%ld\n", Nwritten);
/*-----------------------------*/
/* "libc" wrapped system call */
/* SYS_write (Func No. is 4) */
/*-----------------------------*/
Nwritten = write(STDOUT_FILENO,msg1,sizeof(msg1)-1);
printf ("Number of bytes written=%ld\n", Nwritten);

return(0);
}
