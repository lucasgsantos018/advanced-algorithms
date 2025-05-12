CC = g++
CFLAGS = -Wall -Wextra -std=c++17 -Iinclude
SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
TARGET = garden

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET) < $(TEST_DIR)/input.txt

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all test clean