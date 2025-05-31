#include "functions.h"
#include "constants.h"
#include <iostream>
#include <exception>
#ifdef _WIN32
#include <windows.h>
#endif

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(65001); 
    #endif

    int choice;
    do {
        choice = getMenuChoice();
        try {
            switch (choice) {
                case 1:
                    std::string output_file = "..files/frequencies.txt";
                    countWords(input_file, output_file);
                    std::cout << RESULTS_SAVED_SUCCESSFULLY << output_file << "\n";
                    break;
                    
                case 2:
                    std::string output_file = "../files/references.txt";
                    generate(input_file, output_file);
                    std::cout << RESULTS_SAVED_SUCCESSFULLY << output_file << "\n";
                    break;
                    
                case 3: {
                    std::set<std::string> tld_list = load_tld_list("../files/domain.txt");
                    std::string output_file = "../files/urls.txt";
                    find_urls(input_file, output_file, tld_list);
                    std::cout << RESULTS_SAVED_SUCCESSFULLY << "..files/urls.txt\n";
                    break;
                }
                    
                case 0:
                    std::cout << "Programa užbaigta.\n";
                    break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Klaida: " << e.what() << std::endl;
        }
    } while (choice != 0);

    return 0;
}