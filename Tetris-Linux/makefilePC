# *****************************************************************
#    *                  MAKEFILE CONFIGURATION                   *
# *****************************************************************

# -------------------------- VARIABLES --------------------------

# Compilator
CC := gcc

# Compilator flags
CFLAGS := -g -Wall

# Linker flags
LDFLAGS := -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

# Executable name
EXEC := tetris

# Source files
SRCS := main.c \
        gameLogic.c \
        handler.c \
        allegro.c \
        common.c

# Object files
OBJS := main.o \
        gameLogic.o \
        handler.o \
        allegro.o \
        common.o

# ---------------------- COMPILATION RULES ----------------------

# Rule to generate the executable
${EXEC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LDFLAGS} -o ${EXEC}

# Rule to generate the object files
main.o: main.c gameLogic.h common.h
	${CC} ${CFLAGS} -c main.c -o main.o

gameLogic.o: gameLogic.c gameLogic.h handler.h common.h
	${CC} ${CFLAGS} -c gameLogic.c -o gameLogic.o

handler.o: handler.c handler.h allegro.h
	${CC} ${CFLAGS} -c handler.c -o handler.o

allegro.o: allegro.c allegro.h common.h
	${CC} ${CFLAGS} -c allegro.c -o allegro.o

common.o: common.c common.h
	${CC} ${CFLAGS} -c common.c -o common.o

# ----------------------- CLEANING RULES -----------------------

# Rule to clean the object files
clean:
	rm -f ${OBJS}
