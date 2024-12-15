# *****************************************************************
#    *                  MAKEFILE CONFIGURATION                   *
# *****************************************************************

# -------------------------- VARIABLES --------------------------

# Compilator
CC := gcc

# Compilator flags
CFLAGS := -g -Wall

# Linker flags for PC
LDFLAGS_PC := -L/mingw64/lib -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

# Linker flags for Raspberry
LDFLAGS_RPI := -lSDL2 -L/home/pi/tpf/libAudioSDL2.o -lpthread

# Executable name
EXEC := tetris

# Source files
SRCS_UNI := main.c \
        	Back_End/game_logic.c \
        	Back_End/utilities.c \
        	th2_display_sound.c

SRCS_RPI := ../libs/joydisp/joydrv.c \
        	../libs/joydisp/disdrv.c \
        	../libs/audio/SDL2/libAudioSDL2.c

# Object files
OBJS_UNI := main.o \
        	Back_End/game_logic.o \
        	Back_End/utilities.o \
        	th2_display_sound.o

OBJS_RPI := ../libs/joydisp/joydrv.o \
            ../libs/joydisp/disdrv.o \
            ../libs/audio/SDL2/libAudioSDL2.o

# ---------------------- DETECT PLATFORM -----------------------

# Check if PC is defined in utilities.h
IS_PC := $(shell grep -q "#define PC" Back_End/utilities.h && echo 1 || echo 0)

ifeq ($(IS_PC), 1)
    SRCS := $(SRCS_UNI)
    OBJS := $(OBJS_UNI)
    LDFLAGS := $(LDFLAGS_PC)
else
    SRCS := $(SRCS_UNI) $(SRCS_RPI)
    OBJS := $(OBJS_UNI) $(OBJS_RPI)
    LDFLAGS := $(LDFLAGS_RPI)
endif

# ---------------------- COMPILATION RULES ----------------------

# Rule to generate the executable
${EXEC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LDFLAGS} -o ${EXEC}

# Rule to generate the object files
main.o: main.c Back_End/game_logic.h th2_display_sound.h
	${CC} ${CFLAGS} -c main.c -o main.o

Back_End/game_logic.o: Back_End/game_logic.c Back_End/game_logic.h Back_End/utilities.h
	${CC} ${CFLAGS} -c Back_End/game_logic.c -o Back_End/game_logic.o

Back_End/utilities.o: Back_End/utilities.c Back_End/utilities.h
	${CC} ${CFLAGS} -c Back_End/utilities.c -o Back_End/utilities.o

th2_display_sound.o: th2_display_sound.c th2_display_sound.h Back_End/utilities.h
	${CC} ${CFLAGS} -c th2_display_sound.c -o th2_display_sound.o

../libs/joydisp/joydrv.o: ../libs/joydisp/joydrv.c ../libs/joydisp/joydrv.h
	${CC} ${CFLAGS} -c ../libs/joydisp/joydrv.c -o ../libs/joydisp/joydrv.o

../libs/joydisp/disdrv.o: ../libs/joydisp/disdrv.c ../libs/joydisp/disdrv.h
	${CC} ${CFLAGS} -c ../libs/joydisp/disdrv.c -o ../libs/joydisp/disdrv.o

../libs/audio/SDL2/libAudioSDL2.o: ../libs/audio/SDL2/libAudioSDL2.c ../libs/audio/SDL2/src/audio.h
	${CC} ${CFLAGS} -c ../libs/audio/SDL2/libAudioSDL2.c -o ../libs/audio/SDL2/libAudioSDL2.o

# ----------------------- CLEANING RULES -----------------------

# Rule to clean the object files
clean:
	rm -f ${OBJS}

# Rule to clean the executable
clean_all: clean
	rm -f ${EXEC}
