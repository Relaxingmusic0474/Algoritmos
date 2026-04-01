CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude/

SRC = src/main.c src/fibonacci.c
OBJ = obj/main.o obj/fibonacci.o

TARGET = programa

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf obj/*.o $(TARGET)