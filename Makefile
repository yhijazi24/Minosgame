# Compiler and flags
CC = gcc
CFLAGS = -I src/include -Wall -Wextra -g
LDFLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm

# Executable name
TARGET = minosgame

# Directories
DOMINOS_DIR = dominos
TRIOMINOS_DIR = triominos

# Source files
SRC = \
    menu.c \
    game.c \
    main.c \
    $(DOMINOS_DIR)/dominos_events.c \
    $(DOMINOS_DIR)/dominos_game.c \
    $(DOMINOS_DIR)/dominos_renderer.c \
    $(DOMINOS_DIR)/dominos_types.c \
    $(TRIOMINOS_DIR)/triomino_events.c \
    $(TRIOMINOS_DIR)/triomino_game.c \
    $(TRIOMINOS_DIR)/triomino_renderer.c \
    $(TRIOMINOS_DIR)/triomino_types.c \
    player_setup.c \
    game_score.c 


# Object files
OBJ = $(SRC:.c=.o)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

# Compile C files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJ) $(TARGET)
