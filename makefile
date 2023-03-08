#############
#
# Makefile generico
# Autor: PaikLC
#
#############

# descomentar para hacer una compilacion de depuracion
#DEBUG = 1

# Definimos los programas que compilaran por nosotros
CC				= gcc

# Las cosas a compilara
TARGET			= main
OBJS			= $(TARGET).o .\bibliotecas\archivos\archivos.o .\bibliotecas\datos\datos.o .\bibliotecas\entrada\entrada.o .\bibliotecas\menu\sistemaaadospunto.o

# Nombre del ejecutable
NAME			= main


# Las opciones de compilacion
CFLAGS			= -Wall -Wpointer-sign -Wunused-but-set-variable
LDFLAGS			= 
DEBUG_FLAGS		= -O1 -g
RELEASE_FLAGS	= -O3

ifdef DEBUG
CFLAGS			+= $(DEBUG_FLAGS)
else
CFLAGS			+= $(RELEASE_FLAGS)
endif

all: $(NAME).exe

# Compilar el programa listo para ser un .exe
$(NAME).exe: $(OBJS)
	$(CC) -o $(NAME).exe $(OBJS) $(LDFLAGS)

# Compilar .c ¿Para que es el $*.o? ¿Renombrar?
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $*.o

# Limpiar las cosas
.PHONY clean:
	rm *.o
	rm *.exe