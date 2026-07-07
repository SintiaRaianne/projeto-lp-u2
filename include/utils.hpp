#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
#include <sstream>

/**
 Responsável pelas funções utilitárias que divide uma string por delimitador, remove espaços em brancos, armazena e retorna os tokens em um vetor. 

split("Alice,28,42,14", ',')
retorna ["Alice", "28", "42", "14"]

 */
namespace Utils {
    // Divide uma string por um delimitador
    inline std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);               // Cria um stream com a string
        std::string token;

        // Enquanto conseguir extrair um token
        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);            // Adiciona ao vetor
        }
        return tokens;
    }
    
    // Remove espaços em branco do início e fim da string
    inline std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\r\n");    // Encontra o primeiro caractere que NÃO é espaço, tab, ou quebra de linha
        size_t end = str.find_last_not_of(" \t\r\n");      // Encontra o último caractere que NÃO é espaço, tab, ou quebra de linha

        if (start == std::string::npos) return "";         // Se a string só tem espaços, retorna vazio
        return str.substr(start, end - start + 1);        // Extrai a parte entre esses caracteres
    }
}

#endif