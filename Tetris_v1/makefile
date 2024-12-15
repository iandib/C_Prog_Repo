# *****************************************************************
#    *                  MAKEFILE CONFIGURATION                   *
# *****************************************************************

# -------------------------- VARIABLES --------------------------

# Compilator
CC := gcc

# Compilator flags
CFLAGS := -g -Wall

# Linker flags for PC
LDFLAGS := -L/mingw64/lib -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

# Executable name
EXEC := tetris

# Source files
SRCS := main.c \
        th1_gamelogic.c \
        common.c \
        th2_display_sound.c

# Object files
OBJS := main.o \
        th1_gamelogic.o \
        common.o \
        th2_display_sound.o

# ---------------------- COMPILATION RULES ----------------------

# Rule to generate the executable
${EXEC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LDFLAGS} -o ${EXEC}

# Rule to generate the object files
main.o: main.c th1_gamelogic.h th2_display_sound.h
	${CC} ${CFLAGS} -c main.c -o main.o

th1_gamelogic.o: th1_gamelogic.c th1_gamelogic.h common.h
	${CC} ${CFLAGS} -c th1_gamelogic.c -o th1_gamelogic.o

common.o: common.c common.h
	${CC} ${CFLAGS} -c common.c -o common.o

th2_display_sound.o: th2_display_sound.c th2_display_sound.h common.h
	${CC} ${CFLAGS} -c th2_display_sound.c -o th2_display_sound.o

# ----------------------- CLEANING RULES -----------------------

# Rule to clean the object files
clean:
	rm -f ${OBJS}

# Rule to clean the executable
clean_all: clean
	rm -f ${EXEC}
