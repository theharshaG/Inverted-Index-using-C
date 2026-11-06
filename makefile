# Compiler and compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Target executable name
TARGET = a.out

# All source files in your project
SRCS = main.c validation.c create_DB.c display_DB.c search.c save_DB.c update_DB.c free_db.c

# Object files (.o) corresponding to each source file
OBJS = $(SRCS:.c=.o)

# Header dependency
DEPS = inverted.h

# Default target
all: $(TARGET)

# Link object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file into a .o file
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean