#pragma once
#include <string>
#include <set>
#include <vector>

int getMenuChoice()
void count_words(const std::string& source_file, const std::string& result_file);
void generate_cross_reference(const std::string& input_file, const std::string& output_file);
std::set<std::string> load_tld_list(const std::string& tld_file);
std::vector<std::string> split_domain(const std::string& domain);
void find_urls(const std::string& input_file, 
               const std::string& output_file,
               const std::set<std::string>& tld_list);
