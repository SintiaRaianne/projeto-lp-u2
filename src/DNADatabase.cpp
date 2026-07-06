#include "DNADatabase.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

DNADatabase::DNADatabase() : loaded(false) {}

bool DNADatabase::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    std::string line;
    bool isHeader = true;
    profiles.clear();
    strNames.clear();
    
    while (std::getline(file, line)) {
        // Remove caracteres especiais
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        if (line.empty()) continue;
        
        std::vector<std::string> tokens;
        std::stringstream ss(line);
        std::string token;
        
        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
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
            
            IndividualProfile profile;
            profile.name = tokens[0];
            
            for (size_t i = 1; i < tokens.size() && i - 1 < strNames.size(); i++) {
                try {
                    int count = std::stoi(tokens[i]);
                    profile.strCounts[strNames[i - 1]] = count;
                } catch (const std::exception& e) {
                    std::cerr << "Erro ao converter valor para " << strNames[i-1] << std::endl;
                }
            }
            
            profiles.push_back(profile);
        }
    }
    
    loaded = !profiles.empty() && !strNames.empty();
    return loaded;
}

std::string DNADatabase::findProfile(const std::map<std::string, int>& profile) const {
    if (!loaded) {
        return "no match found";
    }
    
    for (const auto& individual : profiles) {
        bool match = true;
        
        // Verifica se todas as contagens de STRs coincidem
        for (const auto& strPair : profile) {
            auto it = individual.strCounts.find(strPair.first);
            if (it == individual.strCounts.end() || it->second != strPair.second) {
                match = false;
                break;
            }
        }
        
        // Verifica se o perfil tem todas as chaves da base
        if (match && profile.size() == individual.strCounts.size()) {
            return individual.name;
        }
    }
    
    return "no match found";
}

std::vector<std::string> DNADatabase::getSTRNames() const {
    return strNames;
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