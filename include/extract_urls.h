#pragma once
#include <string>
#include <set>
#include <vector>

using std::string;

std::set<std::string> load_tld_list(const std::string& tld_file);
std::vector<std::string> split_domain(const std::string& domain);
void find_urls(const std::string& input_file, 
               const std::string& output_file,
               const std::set<std::string>& tld_list);
