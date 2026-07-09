#include "DNAOutput.hpp"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <map>

// Definição das cores ANSI
const std::string DNAOutput::RESET = "\033[0m";
const std::string DNAOutput::GREEN = "\033[32m";
const std::string DNAOutput::RED = "\033[31m";
const std::string DNAOutput::YELLOW = "\033[33m";
const std::string DNAOutput::BLUE = "\033[34m";
const std::string DNAOutput::CYAN = "\033[36m";
const std::string DNAOutput::MAGENTA = "\033[35m";
const std::string DNAOutput::BOLD = "\033[1m";

// Função para centralizar texto
std::string centerText(const std::string& text, int width = 150) {
    int padding = (width - text.length()) / 2;
    if (padding < 0) padding = 0;
    return std::string(padding, ' ') + text;
}

void DNAOutput::showWelcome() {
    // Pula uma linha antes do welcome
    std::cout << std::endl;
    
    int terminalWidth = 150;  // Largura padrão do terminal
    
    // Linha superior de "=" centralizada
    std::string topLine = std::string(150, '=');
    std::cout << centerText(topLine, terminalWidth) << std::endl;
    
    // Welcome centralizado
    std::cout << centerText("Welcome to the C++ DNA Profiler", terminalWidth) << std::endl;
    
    // Linha inferior de "=" centralizada
    std::cout << centerText(topLine, terminalWidth) << std::endl;
    std::cout << std::endl;
    
    // Descrição do programa (também centralizada)
    std::cout << centerText("This program loads a DNA database and an unknown DNA sequence and tries", terminalWidth) << std::endl;
    std::cout << centerText("to find a match between the input DNA sequence and the DNA database.", terminalWidth) << std::endl;
    std::cout << std::endl;
}

void DNAOutput::showLoading(const std::string& fileType, 
                           const std::string& filename, 
                           bool success) {
    std::cout << "[+] Loading " << fileType << " file [" << RED << filename << RESET << "] ... ";
    if (success) {
        std::cout << GREEN << "[OK]" << RESET << std::endl;
    } else {
        std::cout << RED << "[FAILED]" << RESET << std::endl;
    }
}

void DNAOutput::showSearching() {
    std::cout << std::endl;
    std::cout << "[+] Searching the database for a match... Please wait." << std::endl;
    std::cout << "    ";
    for (int i = 0; i < 150; i++) {
        std::cout << "=";
    }
    std::cout << " [100%]" << std::endl;
    std::cout << std::endl;
}

void DNAOutput::showMatchFound(const std::string& name, 
                              const std::map<std::string, int>& profile,
                              const std::string& sequence,
                              const std::vector<std::string>& strs) {
    std::cout << std::endl;
    std::cout << BOLD << "Match ID (99.9%): " << GREEN << name << RESET << std::endl;
    std::cout << std::endl;
    
  
    struct STRInfo {
        std::string name;
        size_t startPos;
        size_t endPos;
        int count;
        size_t length;
    };
    
    std::vector<STRInfo> strInfos;
    
    for (const std::string& str : strs) {
        auto it = profile.find(str);
        if (it == profile.end()) continue;
        
        size_t firstPos = sequence.find(str);
        if (firstPos != std::string::npos) {
            STRInfo info;
            info.name = str;
            info.startPos = firstPos;
            info.count = it->second;
            info.length = str.length();
            info.endPos = firstPos + (it->second * str.length());
            strInfos.push_back(info);
        }
    }
    
    std::sort(strInfos.begin(), strInfos.end(),
              [](const STRInfo& a, const STRInfo& b) {
                  return a.startPos < b.startPos;
              });
    
 
    size_t seqLength = sequence.length();  // Mudou de int para size_t
    std::string line1(seqLength, ' ');
    std::string line2(seqLength, ' ');
    
    for (const auto& info : strInfos) {
        // LINHA 1: Nome do STR
        std::string strDisplay = info.name + " [x" + std::to_string(info.count) + "]";
        size_t pos = info.startPos;
        
        // CORRIGIDO: Usando size_t em vez de int
        for (size_t i = 0; i < strDisplay.length() && pos + i < seqLength; i++) {
            line1[pos + i] = strDisplay[i];
        }
        
        // LINHA 2: Barras "v"
        size_t currentPos = info.startPos;
        for (int rep = 0; rep < info.count; rep++) {
            // CORRIGIDO: Usando size_t em vez de int
            for (size_t i = 0; i < info.length && currentPos + i < seqLength; i++) {
                line2[currentPos + i] = 'v';
            }
            currentPos += info.length;
        }
    }
    
    // LINHA 3: Sequência com STRs em VERDE
    std::string line3 = "";
    std::vector<std::pair<size_t, size_t>> highlights;
    
    for (const auto& info : strInfos) {
        size_t pos = info.startPos;
        for (int i = 0; i < info.count; i++) {
            highlights.push_back({pos, info.length});
            pos += info.length;
        }
    }
    
    std::sort(highlights.begin(), highlights.end());
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
    
    size_t currentPos = 0;
    for (const auto& h : finalHighlights) {
        line3 += sequence.substr(currentPos, h.first - currentPos);
        line3 += GREEN + BOLD + sequence.substr(h.first, h.second) + RESET;
        currentPos = h.first + h.second;
    }
    line3 += sequence.substr(currentPos);
    
    // Adicionar cores às linhas 1 e 2
    std::string coloredLine1 = "";
    std::string coloredLine2 = "";
    
    for (char c : line1) {
        if (c == ' ') {
            coloredLine1 += ' ';
        } else {
            coloredLine1 += CYAN + std::string(1, c) + RESET;
        }
    }
    
    for (char c : line2) {
        if (c == ' ') {
            coloredLine2 += ' ';
        } else {
            coloredLine2 += CYAN + std::string(1, c) + RESET;
        }
    }
    

    std::cout << coloredLine1 << std::endl;
    std::cout << coloredLine2 << std::endl;
    std::cout << line3 << std::endl;
    std::cout << std::endl;
}

void DNAOutput::showNoMatch() {
    std::cout << std::endl;
    std::cout << BOLD << RED << ">>> Sorry, no match found in our database." << RESET << std::endl;
}

void DNAOutput::showError(const std::string& message) {
    std::cerr << RED << "[ERROR] " << RESET << message << std::endl;
}

void DNAOutput::showUsage() {
    std::cout << std::endl;
    std::cout << "Uso: ./dnaprofiler -d <database_file> -s <dna_sequence_file>" << std::endl;
    std::cout << "  Onde os argumentos são:" << std::endl;
    std::cout << "      <database_file>     O arquivo correspondente a base de DNA." << std::endl;
    std::cout << "      <dna_sequence_file> O arquivo contendo a sequência de DNA." << std::endl;
    std::cout << std::endl;
    std::cout << "Exemplo: ./dnaprofiler -d data/small/database.csv -s data/small/1.txt" << std::endl;
}