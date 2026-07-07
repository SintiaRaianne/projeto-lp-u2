# ============================================================
# MAKEFILE - DNA Profiler (Windows com Git Bash/WSL)
# ============================================================

# Compilador
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2 -Iinclude
LDFLAGS = 

# Diretórios
SRC_DIR = src
INC_DIR = include
DATA_DIR = data

# Arquivos
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=%.o)
TARGET = dnaprofiler.exe

# Alvo padrão
all: $(TARGET)

# Linkagem
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compilação
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# LIMPEZA (COMANDOS COMPATÍVEIS COM BASH)
# ============================================================
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "🧹 Arquivos limpos!"

# ============================================================
# EXECUÇÃO
# ============================================================

run: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/1.txt

run2: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/2.txt

run3: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/3.txt

run4: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/4.txt

# ============================================================
# EXECUÇÃO - DADOS GRANDES (5 a 20)
# ============================================================

run5: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/5.txt

run6: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/6.txt

run7: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/7.txt

run8: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/8.txt

run9: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/9.txt

run10: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/10.txt

run11: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/11.txt

run12: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/12.txt

run13: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/13.txt

run14: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/14.txt

run15: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/15.txt

run16: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/16.txt

run17: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/17.txt

run18: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/18.txt

run19: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/19.txt

run20: $(TARGET)
	./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/20.txt

# ============================================================
# TESTES
# ============================================================

test-small: $(TARGET)
	@echo "🧪 Testando com dados pequenos..."
	@for i in 1 2 3 4; do \
		echo "\n=== Teste $$i ==="; \
		./$(TARGET) -d $(DATA_DIR)/small/database.csv -s $(DATA_DIR)/small/$$i.txt; \
	done

test-large: $(TARGET)
	@echo "🧪 Testando com dados grandes..."
	@for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16; do \
		echo "\n=== Teste $$i ==="; \
		./$(TARGET) -d $(DATA_DIR)/large/database.csv -s $(DATA_DIR)/large/$$i.txt; \
	done

.PHONY: all clean run run2 run3 run4 run-large run-large16 test-small test-large