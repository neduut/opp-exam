#pragma once
#include <string>

constexpr char MENU_TEXT[] = 
    "\nPasirinkite, ką norite daryti:\n"
    "1 - Suskaičiuoti žodžių dažnuma tekste\n"
    "2 - Kurti cross-reference lentelę\n"
    "3 - Ieškoti URL adresų\n"
    "0 - Užbaigti programą\n";

const std::string input_file = "text.txt";
const std::string FILE_NOT_FOUND = "Klaida: nepavyko atidaryti įvesties failo.";
const std::string TLD_LIST_FILE_NOT_FOUND = "Klaida: TLD sąrašo failas nerastas.";
const std::string OUTPUT_FILE_NOT_CREATED = "Klaida: nepavyko atidaryti išvesties failo.";
const std::string INVALID_INPUT_FILE = "Klaida : nepavyko atidaryti įvesties failo";
const std::string INVALID_OUTPUT_FILE = "Klaida: nepavyko atidaryti išvesties failo.";
const std::string RESULTS_SAVED_SUCCESSFULLY = "Duomenys išsaugoti faile: \n";
const std::string INVALID_CHOICE = "Klaida: netinkamas pasirinkimas. Bandykite dar kartą.\n";

