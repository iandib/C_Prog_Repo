# *****************************************************************
#    *                  MAKEFILE CONFIGURATION                   *
# *****************************************************************

# -------------------------- VARIABLES --------------------------

# Compiler
CC := gcc

# Compiler flags
CFLAGS := -g -Wall

# Library name
LIB := libM68HC11.a

# Executable name
EXEC := led_control

# Source files
SRCS := main.c

# Object files
OBJS := main.o

# ---------------------- COMPILATION RULES ----------------------

# Rule to generate the executable
${EXEC}: ${OBJS} ${LIB}
	${CC} ${OBJS} ${CFLAGS} -L. -lM68HC11 -o ${EXEC}

# Rule to generate the static library
${LIB}: M68HC11.o
	ar rcs ${LIB} M68HC11.o

# Rule to generate the object file for main.c
main.o: main.c M68HC11.h
	${CC} ${CFLAGS} -c main.c -o main.o

# ----------------------- CLEANING RULES -----------------------

# Rule to clean the object files and executable
clean:
	rm -f ${OBJS} ${EXEC} ${LIB} M68HC11.o

# Rule to clean only the object files
clean_objs:
	rm -f ${OBJS} 

# Rule to clean only the executable
clean_exec:
	rm -f ${EXEC}

# Rule to clean only the library
clean_lib:
	rm -f ${LIB} M68HC11.o
