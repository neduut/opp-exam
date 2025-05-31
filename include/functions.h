#pragma once

#include <string>
#include <set>

int getMenuChoice();
std::string cleanWord(const std::string& word);
void countWords(const std::string& source_file, const std::string& result_file);
void generate(const std::string& input_file, const std::string& output_file);
std::set<std::string> TLD(const std::string& filename);
void findURLS(const std::string& input_file, 
               const std::string& output_file,
               const std::set<std::string>& tld_list);
