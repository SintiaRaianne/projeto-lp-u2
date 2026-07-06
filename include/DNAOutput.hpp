#ifndef DNAOUTPUT_HPP
#define DNAOUTPUT_HPP

#include <string>
#include <map>
#include <vector>

/*
Responsável por gerenciar todas as saídas do programa
 */

class DNAOutput {
private:
    // Cores ANSI para saída colorida
    static const std::string RESET;
    static const std::string GREEN;
    static const std::string RED;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string CYAN;
    static const std::string MAGENTA;
    static const std::string BOLD;
    
    // Métodos auxiliares para formatação 
    static void printSTRVisual(const std::string& str, int count);        // (Imprime a representação visual de um STR)
    static void highlightSequence(const std::string& sequence, 
                                 const std::map<std::string, int>& strCounts,
                                 const std::vector<std::string>& strs);    //  Destaca os STRs na sequência de DNA
    
public:
    
    static void showWelcome();          // Mostra o cabeçalho do programa
    
    // Mostra status de carregamento de um arquivo
    static void showLoading(const std::string& fileType, const std::string& filename, bool success);
    
    
    static void showSearching();       // Mostra mensagem de busca
    
    // Mostra mensagem quando um match é encontrado
    static void showMatchFound(const std::string& name, 
                              const std::map<std::string, int>& profile,
                              const std::string& sequence,
                              const std::vector<std::string>& strs);
    
    static void showNoMatch();       // Mostra mensagem quando não há match
    
    static void showError(const std::string& message);          // Mostra mensagem de erro
    
    static void showUsage();            // Mostra mensagem com instruções de uso
};

#endif