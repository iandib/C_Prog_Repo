#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // usleep
#include "nonblock.h"

#ifdef _WIN32
   #error "This program is only targeted at Linux systems"
#endif

int main(void) {
    char c;
    int quit = 0;

    nonblock(NB_ENABLE);
    while(!quit)
    {
        if (!kbhit())
		{
			usleep(500000);
			fprintf(stderr, ".");
        }
		else
        {
            c = getchar();
            quit = (c == 'q');
        }
    }
    printf("\n you hit 'q' to quit\n");
    nonblock(NB_DISABLE);

    return EXIT_SUCCESS;
}
