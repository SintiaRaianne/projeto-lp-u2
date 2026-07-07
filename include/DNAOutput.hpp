#ifndef DNAOUTPUT_HPP
#define DNAOUTPUT_HPP

#include <string>
#include <map>
#include <vector>

class DNAOutput {
private:
    static const std::string RESET;
    static const std::string GREEN;
    static const std::string RED;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string CYAN;
    static const std::string MAGENTA;
    static const std::string BOLD;
    
public:
    static void showWelcome();
    static void showLoading(const std::string& fileType, const std::string& filename, bool success);
    static void showSearching();
    static void showMatchFound(const std::string& name, 
                              const std::map<std::string, int>& profile,
                              const std::string& sequence,
                              const std::vector<std::string>& strs);
    static void showNoMatch();
    static void showError(const std::string& message);
    static void showUsage();
};

#endif