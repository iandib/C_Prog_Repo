# *****************************************************************
#  *                    MAKEFILE CONFIGURATION                   *
# *****************************************************************

# --------------------------- VARIABLES ---------------------------

# Compilator
CC := gcc

# Compilator flags
CFLAGS := -g -Wall

# Detect Operating System
OS := $(shell uname -s)

# Folder where the Allegro library is located
ifeq ($(OS), Linux)
    FOLDER := -L/usr/lib
else
    FOLDER := -L/mingw64/lib
endif

# Linker flags for PC
LDFLAGS_PC := ${FOLDER} -lallegro -lallegro_primitives -lallegro_image -lallegro_font \
-lallegro_ttf -lallegro_audio -lallegro_acodec

# Linker flags for Raspberry
LDFLAGS_RPI := -lSDL2 -L/home/pi/tpf/libAudioSDL2.o -lpthread

# Executable names
EXEC_PC := tetris_pc
EXEC_RPI := tetris_rpi

# Source files
SRCS := main.c \
        	Back_End/game_logic.c \
        	Back_End/utilities.c \
        	th2_display_sound.c

# Object files
OBJS := main.o \
        	Back_End/game_logic.o \
        	Back_End/utilities.o \
        	th2_display_sound.o

OBJS_RPI := ../libs/joydisp/joydrv.o \
            ../libs/joydisp/disdrv.o \
            ../libs/audio/SDL2/libAudioSDL2.o

# ----------------------- COMPILATION RULES -----------------------

# Add the -DPC flag to the PC executable
${EXEC_PC}: CFLAGS += -DPC

# Rule to generate the PC executable
${EXEC_PC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LDFLAGS_PC} -o ${EXEC_PC}

# Rule to generate the Raspberry executable
${EXEC_RPI}: ${OBJS} ${OBJS_RPI}
	${CC} ${OBJS} ${OBJS_RPI} ${CFLAGS} ${LDFLAGS_RPI} -o ${EXEC_RPI}

# Rule to generate the object files
main.o: main.c Back_End/game_logic.h th2_display_sound.h
	${CC} ${CFLAGS} -c main.c -o main.o

Back_End/game_logic.o: Back_End/game_logic.c Back_End/game_logic.h Back_End/utilities.h
	${CC} ${CFLAGS} -c Back_End/game_logic.c -o Back_End/game_logic.o

Back_End/utilities.o: Back_End/utilities.c Back_End/utilities.h
	${CC} ${CFLAGS} -c Back_End/utilities.c -o Back_End/utilities.o

th2_display_sound.o: th2_display_sound.c th2_display_sound.h Back_End/utilities.h
	${CC} ${CFLAGS} -c th2_display_sound.c -o th2_display_sound.o

# ------------------------ CLEANING RULES ------------------------

# Rule to clean the object files
clean:
	rm -f ${OBJS}

# Rule to clean the object files and the executables
clean_all:
	rm -f ${OBJS} ${EXEC_PC} ${EXEC_RPI}
