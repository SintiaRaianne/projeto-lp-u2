#include "DNADatabase.hpp"            // Inclui a declaração da classe
#include <fstream>                    // Ler arquivos (ifstream)
#include <iostream>                   // Mensagens de erro (cerr)
#include <sstream>                    // Processar strings (stringstream)
#include <algorithm>                  // Funções como remove()


DNADatabase::DNADatabase() : loaded(false) {}           // Inicializa a base como não carregada

// Função para ler o arquivo CSV e preencher a base de dados
bool DNADatabase::loadFromFile(const std::string& filename) {
    // Tenta abrir o arquivo
    std::ifstream file(filename);
    if (!file.is_open()) {                   
        return false;                       // Se não conseguir abrir o arquivo, retorna false
    }
    
    // Prepara para ler o arquivo e armazena cada linha lida
    std::string line;                       
    bool isHeader = true;
    profiles.clear();                       // Remove os perfis antigos
    strNames.clear();                       // Remove os STRs antigos
    
    // Lê o arquivo linha por linha
    while (std::getline(file, line)) {
        
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());     // Limpa a linha
        if (line.empty()) continue;         // Pula linhas vazias
        
        // Divide a linha em partes (separando por ',')
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        
        while (std::getline(ss, token, ',')) {         
            tokens.push_back(token);            // Adiciona cada parte à lista
        }
        
        if (isHeader) {
            // Primeira linha: cabeçalho
            for (size_t i = 1; i < tokens.size(); i++) {
                strNames.push_back(tokens[i]);
            }
            isHeader = false;
        } else {
            // Linhas de dados
            if (tokens.size() < 2) continue;
            
            IndividualProfile profile;          // Cria o perfil da pessoa
            profile.name = tokens[0];           // Coloca o primeiro token como o nome
            
            for (size_t i = 1; i < tokens.size() && i - 1 < strNames.size(); i++) {
                try {
                    int count = std::stoi(tokens[i]);
                    profile.strCounts[strNames[i - 1]] = count;
                } catch (const std::exception& e) {
                    std::cerr << "Erro ao converter valor para " << strNames[i-1] << std::endl;
                }
            }
            
            profiles.push_back(profile);        // Adiciona o perfil criado à lista
        }
    }
    
    // Verifica se carregou algo, ou seja, se tem pelo menos uma pessoa e pelo menos um STR
    loaded = !profiles.empty() && !strNames.empty();
    return loaded;
}

/* Função para procurar um perfil na base de dados

- 
- 
- Se todas coincidirem, retorna o nome
- Se nenhuma coincidir, retorna "no match found"

*/
std::string DNADatabase::findProfile(const std::map<std::string, int>& profile) const {
    if (!loaded) {          // Verifica se a base foi carregada
        return "no match found";
    }

    // 
    for (const auto& individual : profiles) {
        bool match = true;
        
        // Para cada STR no perfil procurado, compara com a pessoa da base de dados
        for (const auto& strPair : profile) {
            auto it = individual.strCounts.find(strPair.first);
            if (it == individual.strCounts.end() || it->second != strPair.second) {
                match = false;          // Não é um match
                break;
            }
        }
        
        // Se todas as contagens coincidiram, verifica tambem se o perfil tem o mesmo numero de STRs
        if (match && profile.size() == individual.strCounts.size()) {
            return individual.name;             // Retorna o nome da pessoa
        }
    }
    
    return "no match found";       // Caso nenhum match seja encontrado
}

std::vector<std::string> DNADatabase::getSTRNames() const {
    return strNames;              //Retorna a lista de STRs
}

bool DNADatabase::isLoaded() const {
    return loaded;
}

void DNADatabase::printDatabaseInfo() const {
    std::cout << "Base de dados carregada: " << profiles.size() << " indivíduos" << std::endl;
    std::cout << "STRs analisados: ";
    for (size_t i = 0; i < strNames.size(); i++) {
        std::cout << strNames[i];
        if (i < strNames.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
}