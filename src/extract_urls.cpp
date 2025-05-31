#include "extract_urls.h"
#include <fstream>
#include <regex>
#include <set>
#include <string>
#include <stdexcept>
#include <cctype>
#include <vector>
#include <sstream>

// Load the TLD list from a file
std::set<std::string> load_tld_list(const std::string& tld_file) {
    std::set<std::string> tld_set;
    std::ifstream tld_stream(tld_file);
    
    if (!tld_stream) {
        throw std::runtime_error("TLD list file not found");
    }

    std::string tld;
    while (std::getline(tld_stream, tld)) {
        if (tld.empty() || tld[0] == '#') continue;
        
        // Normalize TLD to lowercase
        std::transform(tld.begin(), tld.end(), tld.begin(),
            [](unsigned char c){ return std::tolower(c); });
        
        tld_set.insert(tld);
    }
    
    return tld_set;
}

// Function to split domain into labels
std::vector<std::string> split_domain(const std::string &domain) {
    std::vector<std::string> labels_list;
    std::istringstream ss(domain);
    std::string label;
    
    while (std::getline(ss, label, '.')) {
        labels_list.push_back(label);
    }
    
    return labels_list;
}

// Main URL extraction function
void find_urls(const std::string& input_file, 
               const std::string& output_file,
               const std::set<std::string>& tld_list) {
    std::ifstream input_stream(input_file);
    if (!input_stream) {
        throw std::runtime_error("Failed to open input file");
    }
    
    std::ofstream output_stream(output_file);
    if (!output_stream) {
        throw std::runtime_error("Failed to create output file");
    }
    
    // URL regex pattern with various options
    std::regex url_regex(R"((https?:\/\/)?(www\.)?([a-z0-9\-]+\.[a-z0-9\-\.]+\.[a-z0-9]+|[a-z0-9\-]+\.[a-z0-9]+))", 
                         std::regex::icase);
                      
    std::set<std::string> detected_urls;
    std::string text_line;
    
    while (std::getline(input_stream, text_line)) {
        auto match_start = std::sregex_iterator(text_line.begin(), 
                                                text_line.end(), 
                                                url_regex);
        auto match_end = std::sregex_iterator();
        
        for (auto it = match_start; it != match_end; ++it) {
            std::string full_url = it->str();
            std::string domain = (*it)[3].str();
            
            // Normalize domain to lowercase
            std::transform(domain.begin(), domain.end(), domain.begin(),
                [](unsigned char c){ return std::tolower(c); });
            
            // Check domain structure
            auto labels_list = split_domain(domain);
            if (labels_list.size() < 2) continue;
            
            // Validate TLD
            bool tld_found = false;
            std::string suffix;
            
            for (auto rit = labels_list.rbegin(); rit != labels_list.rend(); ++rit) {
                suffix = suffix.empty() ? *rit : *rit + "." + suffix;
                
                if (tld_list.find(suffix) != tld_list.end()) {
                    tld_found = true;
                    break;
                }
            }
            
            if (!tld_found) continue;
            
            // Normalize URL format
            if (full_url.find("http") == std::string::npos) {
                full_url = "http://" + full_url;
            }
            
            detected_urls.insert(full_url);
        }
    }
    
    // Output results
    for (const auto& url : detected_urls) {
        output_stream << url << '\n';
    }
}
