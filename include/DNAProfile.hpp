#ifndef DNAPROFILE_HPP
#define DNAPROFILE_HPP

#include <string>
#include <vector>
#include <map>
#include <algorithm>

/*
Responsável por processar uma sequência de DNA, guardar o número máximo de repetições de cada STR e gerar um perfil.
*/

class DNAProfile {
private:
    std::string dnaSequence;                             // Sequência completa do DNA
    std::map<std::string, int> strCounts;               // Mapa com as contagens de cada STR
    
    int findMaxConsecutiveRepeats(const std::string& str, size_t pos) const;                                            // Método recursivo para encontrar repetições consecutivas de um STR

    
public:
    DNAProfile();
    
    bool loadFromFile(const std::string& filename);         // Carrega a sequência de DNA de um arquivo, se carregar com sucesso, retorna True, se não, retorna False

    void setSequence(const std::string& sequence);         // Define a sequência de DNA diretamente
    
    void processSTRs(const std::vector<std::string>& strsToProcess);            // Para cada STR na lista, procura o número máximo de repetições consecutivas na sequência de DNA.
    
    int getSTRCount(const std::string& str) const;        // Retorna a contagem de um STR específico ou -1 se não encontrar
    
    std::map<std::string, int> getAllSTRCounts() const;     // Retorna todas as contagens de STRs
    
    std::string getSequence() const;        // Retorna a sequência de DNA completa como uma string

    bool matchesProfile(const std::map<std::string, int>& profile) const;           // Verifica se o perfil coincide, caso todos os STRs coincidirem, retorna True, caso não, retorna False
};

#endif