#include "DNAProfile.hpp"                    // Inclui a declaração da classe
#include <fstream>                          // Ler arquivos
#include <iostream>                         // Mensagens de erro
#include <sstream>                          // Funções como remove()

DNAProfile::DNAProfile() {}

// Função para carregar a sequência de DNA de um arquivo de texto
bool DNAProfile::loadFromFile(const std::string& filename) {
    // Tenta abrir o arquivo
    std::ifstream file(filename);                 
    if (!file.is_open()) {
        return false;                            // Se não conseguir abrir o arquivo, retorna false
    }
    
    //Lê a primeira linha do arquivo
    std::string line;
    if (std::getline(file, line)) {
        // Remove espaços em branco e caracteres de nova linha
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());


        dnaSequence = line;                 // Armazena a sequência de DNA limpa

        return true;                        // Retorna True se carregou com sucesso
    }
    return false;                           // Retorna False se o arquivo estiver vazio ou com erro
}

// Define a sequência de DNA diretamente
void DNAProfile::setSequence(const std::string& sequence) {
    dnaSequence = sequence;
}

int DNAProfile::findMaxConsecutiveRepeats(const std::string& str, size_t pos) const {
    // Caso base: se posição ultrapassar o tamanho da string ou não encontrar o STR
    if (pos >= dnaSequence.length() || dnaSequence.substr(pos, str.length()) != str) {
        return 0;
    }
    
    // Encontrou uma ocorrência do STR na posição atual, conta 1 e chama a função novamente na próxima posição
    int nextCount = findMaxConsecutiveRepeats(str, pos + str.length());         // Pula para depois do STR atual
    return 1 + nextCount;                   // Soma a ocorrência atual com as próximas
}

// Processa a sequência de DNA para encontrar contagens de STRs
void DNAProfile::processSTRs(const std::vector<std::string>& strsToProcess) {
    strCounts.clear(); // Limpa contagens anteriores, se já teve outros STRs antes, remove tudo
    
    for (const std::string& str : strsToProcess) {
        int maxCount = 0;
        
        // Percorre toda a sequência procurando a maior repetição consecutiva
        for (size_t i = 0; i < dnaSequence.length(); i++) {
            if (dnaSequence.substr(i, str.length()) == str) {       // Verifica se o STR começa na posição i
                int count = findMaxConsecutiveRepeats(str, i);  // Chama o método recursivo que conta quantas vezes o STR aparece consecutivamente a partir da posição i
                maxCount = std::max(maxCount, count);        //  Atualiza o máximo se encontrou mais repetições
                i += str.length() - 1;                      // Pula para frente para não contar a mesma repetição
            }
        }
        
        strCounts[str] = maxCount;
    }
}

// Retorna a contagem de um STR específico
int DNAProfile::getSTRCount(const std::string& str) const {
    auto it = strCounts.find(str);
    if (it != strCounts.end()) {
        return it->second;
    }
    return -1;                      // Se encontrou, retorna a contagem, senão retorna -1
}

// Retorna todas as contagens de STRs
std::map<std::string, int> DNAProfile::getAllSTRCounts() const {
    return strCounts;             // Retorna uma cópia do mapa
}

//Retorna a sequência de DNA completa
std::string DNAProfile::getSequence() const {
    return dnaSequence;
}

// Verifica se tem o mesmo número de STRs e se os perfis coincidem
bool DNAProfile::matchesProfile(const std::map<std::string, int>& profile) const {
    if (strCounts.size() != profile.size()) {
        return false;
    }

    // Compara cada STR e sua contagem
    for (const auto& pair : profile) {
         const std::string& strName = pair.first;    // Nome do STR
        int count = pair.second;                     // Contagem esperada
        
        auto it = strCounts.find(strName);         // Procura este STR no perfil atual
        
        // Se não encontrou OU a contagem é diferente
        if (it == strCounts.end() || it->second != count) {
            return false;  // Não é match
        }
    }
    
    return true;
}