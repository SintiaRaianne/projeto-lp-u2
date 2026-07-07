# 🧬 Projeto: DNA Profiler

## 📋 Descrição do Projeto

O **DNA Profiler** é um sistema desenvolvido em C++ para análise de perfis de DNA usando **STRs (Short Tandem Repeats)**. O programa recebe uma base de dados de DNA e uma sequência desconhecida, processa a sequência e tenta encontrar uma correspondência na base.

### 🎯 Objetivo

O objetivo é implementar um sistema chamado `dnaprofiler` capaz de:
1. Ler uma base de dados de DNA em formato CSV
2. Ler uma sequência de DNA desconhecida
3. Analisar a sequência para encontrar repetições de STRs
4. Comparar o perfil encontrado com a base de dados
5. Identificar a pessoa ou informar que não há correspondência

## 📂 Estrutura do Projeto

- `projeto/`: Projeto principal da unidade
  - `include/`: Cabeçalhos (.hpp)
  - `src/`: Implementações (.cpp)
  - `data/`: Dados de teste
    - `small/`: Dataset pequeno
    - `large/`: Dataset grande
  - `Makefile`: Compilação
  - `README.md`: Documentação

## 🛠️ Requisitos do Sistema

### 📦 Compilador
- **C++17** ou superior
- **g++** (GNU Compiler Collection) ou **clang**

### 🔧 Dependências
- **Make** (para automação de compilação)
- **Terminal com suporte a cores ANSI** (para saída colorida)

### 💻 Sistema Operacional
- **Linux** (recomendado)
- **macOS** (compatível)
- **Windows** (com WSL ou Cygwin)

## 🚀 Como Compilar

### Compilação Básica

```bash
# Compila o programa
make

# Limpa arquivos compilados
make clean

# Compila e executa com dados pequenos
make run

# Compila e executa com dados grandes
make run-large