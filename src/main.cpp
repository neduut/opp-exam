#include "count_words.h"
#include "cross_references.h"
#include "extract_urls.h"
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
    const std::string input_file = "text.txt";
    std::string output_file;
    do {
        std::cout << "1. Suskaičiuoti skaičių dažnuma tekste\n";
        std::cout << "2. Kurti cross-reference lentelę\n";
        std::cout << "3. Ieškoti URL adresų\n";
        std::cout << "0. Užbaigti programą\n";
        std::cin >> choice;

        try {
            switch (choice) {
                case 1:
                    output_file = "..files/frequencies.txt";
                    countWords(input_file, output_file);
                    std::cout << "Duomenys išsaugoti faile: "<< output_file << "\n";
                    break;
                    
                case 2:
                    output_file = "../files/references.txt";
                    generate(input_file, output_file);
                    std::cout << "Duomenys išsaugoti faile: " << output_file << "\n";
                    break;
                    
                case 3: {
                    std::set<std::string> tld_list = load_tld_list("../files/domain.txt");
                    output_file = "../files/urls.txt";
                    find_urls(input_file, output_file, tld_list);
                    std::cout << "Duomenys išsaugoti faile: ..files/urls.txt\n";
                    break;
                }
                    
                case 0:
                    std::cout << "Programa užbaigta.\n";
                    break;
                    
                default:
                    std::cout << "Klaida: netinkama įvestis!\n";
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Klaida: " << e.what() << std::endl;
        }
        
    } while (choice != 0);

    return 0;
}