#pragma once

#include <string>
#include <set>

using std::string;

std::set<string> loadDomains(const string& failas);
void extractUrls(const string& ivestis_failas, const string& isvestis_failas, const std::set<string>& galimi_tld);