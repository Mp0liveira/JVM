CC = gcc
CFLAGS = -std=c99 -Wall -g -Iheaders
SRC_DIR = src
OBJ_DIR = build
HDR_DIR = headers
TARGET = jvm

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

.PHONY: all clean cppcheck valgrind run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

cppcheck:
	cppcheck --enable=all --std=c99 --language=c --inconclusive --quiet --force \
		-I$(HDR_DIR) $(SRC_DIR) $(HDR_DIR)

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)
