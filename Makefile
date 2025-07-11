# Makefile Corrigido e Simplificado para C++17

# 1. Compilador C++
CC = g++

# 2. Flags do Compilador C++
CXXFLAGS = -std=c++11 -Wall -g

# 3. Diretórios do Projeto
SRC_DIR = src
OBJ_DIR = build
HDR_DIR = headers


# 5. Busca automática por arquivos fonte (.cpp) e cabeçalhos (.hpp)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(HDR_DIR)/*.hpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Adiciona o diretório de headers ao caminho de inclusão do compilador
CXXFLAGS += -I$(HDR_DIR)

# "Phony" targets não representam arquivos reais
.PHONY: all clean cppcheck valgrind run

# Regra padrão: compilar tudo
all: $(TARGET)

# 6. Regra para linkar os objetos e criar o executável final
#    $@ é o nome do alvo (TARGET)
#    $^ são todas as dependências (OBJECTS)
$(TARGET): $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $@ $^

# 7. Regra para compilar cada arquivo .cpp em um arquivo .o
#    Depende do .cpp correspondente e de TODOS os arquivos de cabeçalho
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CXXFLAGS) -c $< -o $@

# Regra para executar o programa
run: all
	./$(TARGET)

# Regra do cppcheck atualizada para C++
cppcheck:
	cppcheck --enable=all --std=c++17 --language=c++ --inconclusive --quiet --force \
		-I$(HDR_DIR) $(SRC_DIR)

# Regra do valgrind
valgrind: all
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

# Regra para limpar os arquivos gerados
clean:
	@echo "Limpando arquivos gerados..."
	@rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Limpeza concluída."
