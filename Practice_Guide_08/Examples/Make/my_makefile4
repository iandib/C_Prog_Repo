CC := gcc
OPTIONS := -O2 -g -Wall
# -g for debug, -O2 for optimise and -Wall additional messages
OBJS := hello.o print.o


# Target principal
hello: ${OBJS}
	${CC} ${OBJS} ${OPTIONS} -o hello

hello.o: hello.c print.h
	${CC} hello.c -c ${OPTIONS}

print.o: print.c print.h
	${CC} print.c -c ${OPTIONS}

# Borro todos los objetos
clean:
	rm *.o 
