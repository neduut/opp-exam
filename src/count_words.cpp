#include "count_words.h"
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>

std::string sanitizeToken(const std::string& token) {
    std::string result;
    for (char c : token) {
        if (std::isalnum(c) || c == '\'' || c == '-') {
            result += std::tolower(c);
        }
    }
    return result;
}

void countWords(const std::string& source_file, const std::string& result_file) {
    std::ifstream input(source_file);
    if (!input.is_open()) {
        throw std::runtime_error("Klaida: nepavyko atidaryti įvesties failo.");
    }

    std::map<std::string, int> word_counts;
    std::string token;
    
    while (input >> token) {
        std::string clean = sanitizeToken(token);
        if (!clean.empty()) {
            ++word_counts[clean];
        }
    }

    std::ofstream output(result_file);
    if (!output.is_open()) {
        throw std::runtime_error("Klaida: nepavyko atidaryti išvesties failo.");
    }

    for (const auto& [word, count] : word_counts) {
        if (count > 1) {
            output << word << ": " << count << '\n';
        }
    }
}