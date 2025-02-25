#Compiler
CC = gcc

#Flags
CFLAGS = -Wall -Wextra -std=c11 -lncurses

#Header files
#HDR = tetris.h

#Source files
SRC = main.c #tetris.c

#Object files
OBJ = $(SRC:.c=.o)

#Executable file
TARGET = target

#default 
all: $(TARGET)

#Rules to build executable 
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

#Rules to run executable
%.o: %.c #$(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

#command to remove object and executable files
clean:
	$(RM) $(TARGET) $(OBJ)
