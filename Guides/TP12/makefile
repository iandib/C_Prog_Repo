# *****************************************************************
#    *                  MAKEFILE CONFIGURATION                   *
# *****************************************************************

# -------------------------- VARIABLES --------------------------

# Compilator
CC := gcc

# Compilator flags
CFLAGS := -g -Wall 

# Executable name
EXEC := R_Pi

# Source files
SRCS := main.c \
        hardware.c \
        port_read.c

# Object files
OBJS := main.o \
		hardware.o \
		port_read.o

# ---------------------- COMPILATION RULES ----------------------

# Rule to generate the executable
${EXEC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LDFLAGS} -o ${EXEC}

# Rule to generate the object files
main.o: main.c hardware.h port_read.h
	${CC} ${CFLAGS} -c main.c -o main.o

Back_End/calc_gen.o: hardware.c hardware.h
	${CC} ${CFLAGS} -c hardware.c -o hardware.o

Front_End/display_grid.o: port_read.c port_read.h
	${CC} ${CFLAGS} -c port_read.c -o port_read.o

# ----------------------- CLEANING RULES -----------------------

# Rule to clean the object files
clean:
	rm -f ${OBJS}
