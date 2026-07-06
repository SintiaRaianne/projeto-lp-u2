#ifndef DNADATABASE_HPP
#define DNADATABASE_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

/* 
Estrutura para armazenar o perfil de um indivíduo

Cada pessoa na base de dados tem: 
 - Um nome (string)
 - Um mapa com os STRs e suas contagens
*/

struct IndividualProfile {
    std::string name;                            // Nome da pessoa
    std::map<std::string, int> strCounts;       // STR (Quantas repetições)
};

class DNADatabase {
private:
    std::vector<std::string> strNames;              // Nomes dos STRs na ordem do CSV
    std::vector<IndividualProfile> profiles;       // Lista de perfis carregados
    bool loaded;                                  // True se a base foi carregada com sucesso e False caso contrário
    
public:
    DNADatabase();
    
    bool loadFromFile(const std::string& filename);             // Carrega a base de dados do arquivo CSV
    
    std::string findProfile(const std::map<std::string, int>& profile) const;       // Busca pelo perfil na base de dados, retornando a pessoa encontrada ou "no match found"
    
    std::vector<std::string> getSTRNames() const;              // Retorna a lista de nomes dosSTRs da base
    
    bool isLoaded() const;                      // Verifica se a base foi carregada corretamente
    
    void printDatabaseInfo() const;           // Retorna informações da base
};

#endif