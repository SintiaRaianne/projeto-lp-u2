#ifndef DNADATABASE_HPP
#define DNADATABASE_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

// Estrutura para armazenar o perfil de um indivíduo
struct IndividualProfile {
    std::string name;
    std::map<std::string, int> strCounts;
};

class DNADatabase {
private:
    std::vector<std::string> strNames;  // Nomes dos STRs na ordem do CSV
    std::vector<IndividualProfile> profiles;  // Lista de perfis de indivíduos
    bool loaded;
    
public:
    DNADatabase();
    
    // Carrega a base de dados de um arquivo CSV
    bool loadFromFile(const std::string& filename);
    
    // Busca por um perfil na base de dados
    std::string findProfile(const std::map<std::string, int>& profile) const;
    
    // Retorna a lista de STRs da base
    std::vector<std::string> getSTRNames() const;
    
    // Verifica se a base foi carregada
    bool isLoaded() const;
    
    // Retorna informações da base
    void printDatabaseInfo() const;
};

#endif