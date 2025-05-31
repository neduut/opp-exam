#include "functions.h"
#include "constants.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <map>
#include <set>
#include <regex>
#include <vector>
#include <iostream>
#include <stdexcept>

// menu valdymas
int getMenuChoice() {
    int choice;
    while (true) {
        std::cout << MENU_TEXT;
        std::string input;
        std::cin >> input;
        try {
            choice = stoi(input);
            if (choice >= 0 && choice <= 2) break;
        } catch (const std::invalid_argument&) {
        }
        std::cout << INVALID_CHOICE;
    }
    return choice;
}

// isima nereikalingus simbolius is zodzio
inline std::string cleanWord(const std::string& word) {
    std::string cleaned;
    // palieka tik alfanumerinius simbolius, apostrofus ir bruksnelius
    for (unsigned char ch : word) {
        if (std::isalnum(ch) || ch == '\'' || ch == '-') {
            cleaned += std::tolower(ch);
        }
    }
    return cleaned;
}

// ZODZIU DAZUMO SKAICIAVIMAS
inline void countWords(const std::string& source_file, const std::string& result_file) {
    std::ifstream input(source_file);
    if (!input) throw std::runtime_error();

    std::map<std::string, int> word_counter;
    std::string token;
    
    while (input >> token) {
        std::string processed = cleanWord(token);
        if (!processed.empty()) ++word_counter[processed];
    }

    std::ofstream output(result_file);
    if (!output) throw std::runtime_error(OUTPUT_FILE_NOT_CREATED);

    for (const auto& [word, count] : word_counter) {
        if (count > 1) output << word << ": " << count << '\n';
    }
}

// CROSS-REFERENCE LENTELES GENERAVIMAS
inline void generate(const std::string& input_file, const std::string& output_file) {
    std::ifstream in_stream(input_file);
    if (!in_stream) throw std::runtime_error(FILE_NOT_FOUND);

    std::ofstream out_stream(output_file);
    if (!out_stream) throw std::runtime_error(OUTPUT_FILE_NOT_CREATED);

    std::map<std::string, std::set<int>> word_line_map;
    std::string current_line;
    int line_counter = 1;

    while (std::getline(in_stream, current_line)) {
        std::istringstream line_stream(current_line);
        std::string token;
        while (line_stream >> token) {
            std::string processed = cleanWord(token);
            if (!processed.empty()) word_line_map[processed].insert(line_counter);
        }
        line_counter++;
    }

    for (const auto& [word, lines] : word_line_map) {
        if (lines.size() > 1) {
            out_stream << word << ":";
            for (int num : lines) out_stream << " " << num;
            out_stream << '\n';
        }
    }
}

// nuskaito tdl sarasa
inline std::set<std::string> TLD(const std::string& filename) {
    std::set<std::string> tld_set;
    std::ifstream tld_file(filename);
    if (!tld_file) throw std::runtime_error(TLD_LIST_FILE_NOT_FOUND);

    std::string domain;
    while (std::getline(tld_file, domain)) {
        if (domain.empty() || domain[0] == '#') continue;
        
        std::transform(domain.begin(), domain.end(), domain.begin(),
            [](unsigned char c){ return std::tolower(c); });
        tld_set.insert(domain);
    }
    return tld_set;
}

// IESKO URL ADRESU
inline void findURLS(const std::string& input_file, 
                    const std::string& output_file,
                    const std::set<std::string>& tld_list) {
    std::ifstream in_stream(input_file);
    if (!in_stream) throw std::runtime_error(FILE_NOT_FOUND );
    
    std::ofstream out_stream(output_file);
    if (!out_stream) throw std::runtime_error(OUTPUT_FILE_NOT_CREATED);
    
    // url regex modelis
    std::regex url_pattern(
        R"((https?:\/\/)?(www\.)?([a-z0-9\-]+(\.[a-z0-9\-]+)+))", 
        std::regex::icase
    );
    
    std::set<std::string> found_urls;
    std::string text_line;
    
    while (std::getline(in_stream, text_line)) {
        auto start = std::sregex_iterator(text_line.begin(), text_line.end(), url_pattern);
        auto end = std::sregex_iterator();
        
        for (auto it = start; it != end; ++it) {
            std::string full_url = it->str();
            std::string domain = (*it)[3].str();
            
            std::transform(domain.begin(), domain.end(), domain.begin(),
                [](unsigned char c){ return std::tolower(c); });
            
            // TLD patikrinimas
            size_t last_dot = domain.find_last_of('.');
            if (last_dot == std::string::npos) continue;
            
            std::string suffix = domain.substr(last_dot + 1);
            if (tld_list.find(suffix) == tld_list.end()) continue;
            
            // sutvarko url formata
            if (full_url.find("http") == std::string::npos) {
                full_url = (full_url.find("www.") == 0) 
                    ? "http://" + full_url 
                    : "http://www." + full_url;
            }
            
            found_urls.insert(full_url);
        }
    }
    
    for (const auto& url : found_urls) {
        out_stream << url << '\n';
    }
}
