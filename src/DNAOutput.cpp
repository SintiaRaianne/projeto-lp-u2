#include "DNAOutput.hpp"
#include <iostream>                                 // Cout e Cerr
#include <iomanip>                                  // Formatação
#include <algorithm>                                // Funções como min()

// Definição das cores ANSI
const std::string DNAOutput::RESET = "\033[0m";
const std::string DNAOutput::GREEN = "\033[32m";
const std::string DNAOutput::RED = "\033[31m";
const std::string DNAOutput::YELLOW = "\033[33m";
const std::string DNAOutput::BLUE = "\033[34m";
const std::string DNAOutput::CYAN = "\033[36m";
const std::string DNAOutput::MAGENTA = "\033[35m";
const std::string DNAOutput::BOLD = "\033[1m";


// O cabeçalho é mostrado sempre que o programa é executado
void DNAOutput::showWelcome() {
    std::cout << BOLD << "Welcome to the C++ DNA Profiler, v1.0" << RESET << std::endl;
    std::cout << "Copyright (C) 2024, Danilo Curvelo" << std::endl;
    std::cout << std::endl;
    std::cout << "This program loads a DNA database and an unknown DNA sequence and tries" << std::endl;
    std::cout << "to find a match between the input DNA sequence and the DNA database." << std::endl;
    std::cout << std::endl;
}

// Mostra o status de carregamento de um arquivo (Tipo, Nome, [OK] se carregou e [FAILED] se falhou)
void DNAOutput::showLoading(const std::string& fileType, const std::string& filename, bool success) {
    std::cout << "[+] Loading " << fileType << " file [" << filename << "] ... ";
    if (success) {
        std::cout << GREEN << "[OK]" << RESET << std::endl;
    } else {
        std::cout << RED << "[FAILED]" << RESET << std::endl;
    }
}

// Mostra mensagem de busca, quando o programa esta analisando o DNA e procurando na base de dados
void DNAOutput::showSearching() {
    std::cout << std::endl;
    std::cout << "[+] Searching the database for a match... Please wait." << std::endl;
    std::cout << std::endl;
}

// Imprime a representação visual de um STR
void DNAOutput::printSTRVisual(const std::string& str, int count) {
    
    std::cout << CYAN << str << RESET << " ";           // Imprime o nome do STR em ciano
    
    // Alinhamento para 10 caracteres
    for (int i = 0; i < 10 - (int)str.length(); i++) {
        std::cout << " ";
    }
    
    std::cout << "[x" << count << "]    ";             // Imprime a contagem
    
    // Desenha barras visuais para cada repetição
    int barLength = std::min(count, 30);
    for (int i = 0; i < barLength; i++) {
        if (count > 0) {
            std::cout << YELLOW << "▮" << RESET;
        }
    }
    
    // Se a contagem for maior que 30, mostra "..."
    if (count > 30) {
        std::cout << "...";
    }
    
    std::cout << std::endl;
}

// Destaca os STRs na sequência de DNA
void DNAOutput::highlightSequence(const std::string& sequence, 
                                 const std::map<std::string, int>& strCounts,
                                 const std::vector<std::string>& strs) {
    std::cout << std::endl;
    
    
    std::vector<std::pair<size_t, size_t>> highlights;                  // Encontra todas as ocorrências de STRs 
    

    // Para cada STR na lista, guarda a posição e o comprimento
    for (const std::string& str : strs) {
        size_t pos = 0;
        while ((pos = sequence.find(str, pos)) != std::string::npos) {
            highlights.push_back({pos, str.length()});
            pos += str.length();
        }
    }
    
    std::sort(highlights.begin(), highlights.end());           // Ordena os highlights por posição
    
    // Remove highlights sobrepostos (mantém o primeiro)
    std::vector<std::pair<size_t, size_t>> finalHighlights;
    for (const auto& h : highlights) {
        bool overlap = false;
        for (const auto& f : finalHighlights) {
            if (h.first >= f.first && h.first < f.first + f.second) {
                overlap = true;
                break;
            }
        }
        if (!overlap) {
            finalHighlights.push_back(h);
        }
    }
    
    // Mostra a sequência com destaque
    size_t currentPos = 0;
    for (const auto& h : finalHighlights) {
        
        std::cout << sequence.substr(currentPos, h.first - currentPos);         // Parte normal (sem destaque)
        
        std::cout << GREEN << BOLD << sequence.substr(h.first, h.second) << RESET;          // Parte destacada
        currentPos = h.first + h.second;                    // Atualiza a posição atual
    }
    // Mostra o restante da sequencia depois do ultimo destaque
    std::cout << sequence.substr(currentPos);
    std::cout << std::endl;
}

// Mostra quando um match é encontrado
void DNAOutput::showMatchFound(const std::string& name, 
                              const std::map<std::string, int>& profile,
                              const std::string& sequence,
                              const std::vector<std::string>& strs) {
                        
    // Mostra o nome da pessoa encontrada                             
    std::cout << BOLD << "Match ID (99.9%): " << GREEN << name << RESET << std::endl;  
    std::cout << std::endl;
    
    // Mostra visualização dos STRs, com barras visuais para cada um na lista
    for (const std::string& str : strs) {
        auto it = profile.find(str);
        if (it != profile.end()) {
            printSTRVisual(str, it->second);
        }
    }
    
    // Mostra a barra separadora
    std::cout << std::endl;
    for (int i = 0; i < 50; i++) {
        std::cout << CYAN << "v" << RESET;
    }
    std::cout << std::endl << std::endl;
    
    // Mostra a sequência com destaque
    highlightSequence(sequence, profile, strs);
    
    // Mostra porcentagem
    std::cout << std::endl;
    std::cout << BOLD << GREEN << "100 %" << RESET << std::endl;
}

// Mostra quando não há match encontrado
void DNAOutput::showNoMatch() {
    std::cout << std::endl;
    std::cout << BOLD << RED << ">>> Sorry, no match found in our database." << RESET << std::endl;
}

// Mostra mensagens de erro com cerr em vez de cout
void DNAOutput::showError(const std::string& message) {
    std::cerr << RED << "[ERROR] " << RESET << message << std::endl;
}

// Mostra instruções de uso do programa
void DNAOutput::showUsage() {
    std::cout << std::endl;
    std::cout << "Uso: ./dnaprofiler -d <database_file> -s <dna_sequence_file>" << std::endl;
    std::cout << "  Onde os argumentos são:" << std::endl;
    std::cout << "      <database_file>     O arquivo correspondente a base de DNA." << std::endl;
    std::cout << "      <dna_sequence_file> O arquivo contendo a sequência de DNA." << std::endl;
    std::cout << std::endl;
    std::cout << "Exemplo: ./dnaprofiler -d data/small/database.csv -s data/small/1.txt" << std::endl;
}