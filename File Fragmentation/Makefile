# Nome do projeto
TARGET = build/file-fragmentation

# Compilador
CXX = g++

# Opções de compilação
CXXFLAGS = -std=c++14 -Wall -Iinclude

# Diretórios
SRC_DIR = src
OBJ_DIR = build
INCLUDE_DIR = include

# Arquivos fonte e objeto
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Regra padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
    $(CXX) -o $@ $^

# Compilação
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
    rm -f $(OBJ_DIR)/*.o $(TARGET)