# Responsável por automatizar a compilação do programa

# Comandos disponíveis:
#   make: Compila o programa
#   make clean: Remove arquivos compilados
#   make run: Compila e executa com dados pequenos
#   make test-small: Testa todas as sequências pequenas

# Compilador e flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -Iinclude
LDFLAGS = 

# Diretórios
SRC_DIR = src				# Onde estão os arquivos .cpp
INC_DIR = include			# Onde estão os arquivos .hpp
DATA_DIR = data				# Onde estão os dados de teste

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)			# Lista todos os arquivos .cpp na pasta src/
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=%.o)			# Converte os .cpp para .o (objetos)
TARGET = dnaprofiler						# Nome do executável final

# Alvo padrão
all: $(TARGET)

# Cria o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compila cada .cpp em .o
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove arquivos compilados
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "🧹 Arquivos limpos!"

# Executa com a primeira sequência pequena
run: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/1.txt

# Executa com a segunda sequência pequena
run2: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/2.txt

# Executa com a terceira sequência pequena
run3: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/3.txt

# Executa com a quarta sequência pequena
run4: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/4.txt

# Executa com a primeira sequência grande
run-large: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/1.txt

# Executa com a décima sexta sequência grande
run-large16: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/16.txt

# Testa todas as sequências pequenas (1 a 4)
test-small: $(TARGET)
	@echo "🧪 Testando com dados pequenos..."
	@for i in 1 2 3 4; do \
		echo "\n=== Teste $$i ==="; \
		./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/$$i.txt; \
	done

# Testa todas as sequências grandes (1 a 16)
test-large: $(TARGET)
	@echo "🧪 Testando com dados grandes..."
	@for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do \
		echo "\n=== Teste $$i ==="; \
		./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/$$i.txt; \
	done

#  Diz que essas regras não são arquivos reais
.PHONY: all clean run run2 run3 run4 run-large run-large16 test-small test-large