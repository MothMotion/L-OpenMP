CC = gcc
CCFLAGS = -Wall -Wextra -Iinclude -fopenmp

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET = program

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p obj
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
