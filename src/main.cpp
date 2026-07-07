#include "DNADatabase.hpp"          // Inclui a classe da base de dados
#include "DNAProfile.hpp"          // Inclui a classe de processamento de DNA
#include "DNAOutput.hpp"          // Incluiu a classe de saída
#include <iostream>              
#include <string>
#include <vector>

/*
 Responsável pelo função principal do programa:

- Mostra o cabeçalho do programa
- Lê os argumentos da linha de comando
- Carrega a base de dados
- Carrega a sequência de DNA
- Processa a sequência para encontrar STRs
- Busca o perfil na base de dados
- Mostra o resultado (caso encontre ou nao)

 */

int main(int argc, char* argv[]) {
    
    DNAOutput::showWelcome();           // Mostra o cabeçalho do programa
    
    // Verifica argumentos da linha de comando, o pograma espera exatamente 5 argumentos (nome, -d, caminho do database .csv, -s e caminho do arquivo .txt). 
    if (argc != 5) {
        DNAOutput::showUsage();         // Se não tiver os 5 argumentos mostra instruçõs de uso
        return 1;                       // Sai com erro
    }
    
    // Extrai os argumentos e guarda os caminhos dos arquivos 
    std::string databaseFile;
    std::string sequenceFile;
    
    // Lê e interpreta os argumentos
    for (int i = 1; i < argc; i += 2) {
        std::string arg = argv[i];
        if (arg == "-d" && i + 1 < argc) {
            databaseFile = argv[i + 1];
        } else if (arg == "-s" && i + 1 < argc) {
            sequenceFile = argv[i + 1];
        }
    }
    
    // Verifica se os arquivos foram especificados de forma correta
    if (databaseFile.empty() || sequenceFile.empty()) {
        DNAOutput::showError("Parâmetros inválidos");
        DNAOutput::showUsage();
        return 1;
    }
    
    // Cria um objeto DNADatabase e tenta carregar o arquivo CSV (base de dados)
    DNAOutput::showLoading("DNA database", databaseFile, true);
    DNADatabase database;
    if (!database.loadFromFile(databaseFile)) {
        DNAOutput::showLoading("DNA database", databaseFile, false);
        DNAOutput::showError("Falha ao carregar base de dados: " + databaseFile);
        return 1;
    }
    
    // Cria um objeto DNAProfile e tenta carregar o arquivo TXT (sequência de DNA)
    DNAOutput::showLoading("unknown DNA sequence", sequenceFile, true);
    DNAProfile dnaProfile;
    if (!dnaProfile.loadFromFile(sequenceFile)) {
        DNAOutput::showLoading("unknown DNA sequence", sequenceFile, false);
        DNAOutput::showError("Falha ao carregar sequência de DNA: " + sequenceFile);
        return 1;
    }
    
    // Processa a sequência de DNA para encontrar as contagens de STRs
    DNAOutput::showSearching();
    std::vector<std::string> strsToProcess = database.getSTRNames();    // Pega os nomes dos STRs da base
    dnaProfile.processSTRs(strsToProcess);                          // Processa o DNA para encontrar contagens
    
    // Encontra o perfil gerado
    auto profile = dnaProfile.getAllSTRCounts();    
    auto sequence = dnaProfile.getSequence();
    
    // Busca o perfil encontrado na base de dados e compara
    std::string result = database.findProfile(profile);
    
    // Mostra o resultado se encontrou e deu match (com detalhes) ou se não encontrou 
    if (result != "no match found") {
        DNAOutput::showMatchFound(result, profile, sequence, strsToProcess);
    } else {
        DNAOutput::showNoMatch();
    }
    
    return 0;
}
