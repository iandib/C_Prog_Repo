# *****************************************************************
#   *                CONFIGURACIÓN DEL MAKEFILE                  *
#  *****************************************************************

# --------------------- VARIABLES GENERALES ---------------------

# Compilador a utilizar
CC := gcc

# Flags de compilación
CFLAGS := -g -Wall

# Nombre del ejecutable final
EXEC := calculator

# Archivos fuente
SRCS := main.c \
        Front_End/get_input.c \
        Back_End/operate.c

# Archivos objeto
OBJS := main.o Front_End/get_input.o Back_End/operate.o

# -------------------- REGLAS DE COMPILACIÓN --------------------

# Regla principal para generar el ejecutable
${EXEC}: ${OBJS}
	${CC} ${OBJS} ${CFLAGS} -o ${EXEC}

# Regla para generar cada archivo objeto
main.o: main.c Front_End/get_input.h Back_End/operate.h
	${CC} ${CFLAGS} -c main.c -o main.o

Front_End/get_input.o: Front_End/get_input.c Front_End/get_input.h Back_End/operate.h
	${CC} ${CFLAGS} -c Front_End/get_input.c -o Front_End/get_input.o

Back_End/operate.o: Back_End/operate.c Back_End/operate.h
	${CC} ${CFLAGS} -c Back_End/operate.c -o Back_End/operate.o

# --------------------- REGLAS DE LIMPIEZA ---------------------

# Regla para eliminar los archivos objeto
clean:
	rm -f ${OBJS}
