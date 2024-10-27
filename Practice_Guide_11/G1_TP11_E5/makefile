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
        Back_End/calc_gen.c \
        Front_End/display_grid.c

# Archivos objeto
OBJS := main.o \
		Back_End/calc_gen.o \
		Front_End/display_grid.o

# --------------- REGLAS DE COMPILACIÓN ---------------

# Regla principal para generar el ejecutable
${EXEC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} ${LDFLAGS} -o ${EXEC}

# Regla para generar cada archivo objeto
main.o: main.c Back_End/calc_gen.h Front_End/display_grid.h
	${CC} ${CFLAGS} -c main.c -o main.o

Back_End/calc_gen.o: Back_End/calc_gen.c Back_End/calc_gen.h
	${CC} ${CFLAGS} -c Back_End/calc_gen.c -o Back_End/calc_gen.o

Front_End/display_grid.o: Front_End/display_grid.c Front_End/display_grid.h Back_End/calc_gen.h
	${CC} ${CFLAGS} -c Front_End/display_grid.c -o Front_End/display_grid.o

# --------------- REGLAS DE LIMPIEZA ---------------

# Regla para eliminar los archivos objeto
clean:
	rm -f ${OBJS}
