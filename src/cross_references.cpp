#include "cross_references.h"
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <string>
#include <stdexcept>
#include <cctype>

// Helper function to clean words
std::string clean_word(const std::string& word) {
    std::string cleaned_word;
    for (char ch : word) {
        unsigned char u_ch = static_cast<unsigned char>(ch);
        // Keep letters, digits, apostrophes and hyphens
        if (std::isalnum(u_ch) || ch == '\'' || ch == '-') {
            cleaned_word += std::tolower(u_ch);
        }
    }
    return cleaned_word;
}

void generate_cross_reference(const std::string& input_file, const std::string& output_file) {
    // Open input file
    std::ifstream input_stream(input_file);
    if (!input_stream) {
        throw std::runtime_error("Klaida: nepavyko atidaryti įvesties failo.");
    }

    // Create output file
    std::ofstream output_stream(output_file);
    if (!output_stream) {
        throw std::runtime_error("Klaida: nepavyko atidaryti išvesties failo.");
    }

    std::map<std::string, std::set<int>> word_occurrences;
    std::string current_line;
    int line_number = 1;

    // Read file line by line
    while (std::getline(input_stream, current_line)) {
        std::istringstream line_content(current_line);
        std::string word;
        // Process all words in the line
        while (line_content >> word) {
            std::string real_word = clean_word(word);
            if (!real_word.empty()) {
                word_occurrences[real_word].insert(line_number);
            }
        }
        line_number++;
    }

    // Format results
    for (const auto& entry : word_occurrences) {
        if (entry.second.size() > 1) {
            output_stream << entry.first << ":";
            for (int line : entry.second) {
                output_stream << " " << line;
            }
            output_stream << '\n';
        }
    }
}
