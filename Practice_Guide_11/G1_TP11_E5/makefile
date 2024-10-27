# ************************************************************
#    * CONFIGURACIÓN DEL MAKEFILE *
# ************************************************************

# --------------- VARIABLES GENERALES ---------------

# Compilador a utilizar
CC := gcc

# Flags de compilación
CFLAGS := -g -Wall -I/mingw64/include

# Flags de enlace
LDFLAGS := -L/mingw64/lib -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf

# Nombre del ejecutable final
EXEC := GoL

# Archivos fuente
SRCS := main.c \
        Front_End/get_input.c \
        Back_End/calc_gen.c \
        Back_End/display_grid.c

# Archivos objeto
OBJS := main.o \
		Front_End/get_input.o \
		Back_End/calc_gen.o \
		Back_End/display_grid.o

# --------------- REGLAS DE COMPILACIÓN ---------------

# Regla principal para generar el ejecutable
${EXEC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LDFLAGS} -o ${EXEC}

# Regla para generar cada archivo objeto
main.o: main.c Front_End/get_input.h Back_End/display_grid.h Back_End/calc_gen.h
	${CC} ${CFLAGS} -c main.c -o main.o

Front_End/get_input.o: Front_End/get_input.c Front_End/get_input.h
	${CC} ${CFLAGS} -c Front_End/get_input.c -o Front_End/get_input.o

Back_End/calc_gen.o: Back_End/calc_gen.c Back_End/calc_gen.h
	${CC} ${CFLAGS} -c Back_End/calc_gen.c -o Back_End/calc_gen.o

Back_End/display_grid.o: Back_End/display_grid.c Back_End/display_grid.h Back_End/calc_gen.h
	${CC} ${CFLAGS} -c Back_End/display_grid.c -o Back_End/display_grid.o

# --------------- REGLAS DE LIMPIEZA ---------------

# Regla para eliminar los archivos objeto
clean:
	rm -f ${OBJS}
