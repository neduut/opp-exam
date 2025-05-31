# Teksto Analizės Programa

Šis C++ projektas yra sukurtas pademonstruoti asociatyvių konteinerių (konkrečiai, `std::map` ir `std::set`) pranašumus ir efektyvumą, lyginant juos su tradiciniais sekos konteineriais (`std::vector` ar `std::list`), sprendžiant tam tikras teksto apdorojimo užduotis. Programa siūlo interaktyvų meniu su trimis pagrindinėmis funkcijomis, skirtomis teksto analizei.


---

## Programos Funkcijos

1. Žodžių Dažnumo Skaičiavimas
   - Suskaičiuoja, kiek kartų kiekvienas skirtingas žodis pasikartoja tekste.
   - Ignoruoja skyrybos ženklus (kablelius, taškus ir kt.).
   - Į failą (`files/frequencies.txt`) išveda tik žodžius, pasikartojusius daugiau nei vieną kartą, su jų skaičiumi.

2. Kryžminių Nuorodų Lentelės Generavimas
   - Sukuria kryžminių nuorodų lentelę (`files/references.txt`).
   - Nurodo, kuriose teksto eilutėse kiekvienas žodis, pasikartojantis daugiau nei vieną kartą, buvo paminėtas.

3. URL Adresų Ištraukimas
   - Suranda visus URL adresus (pilnu ir sutrumpintu formatu, pvz., `https://www.vu.lt/`, `www.vu.lt` ar `vu.lt`).
   - Naudoja TLD (Top-Level Domain) sąrašą validavimui (`files/domain.txt`).
   - Išveda unikalius URL į failą (`files/urls.txt`).

---

## Naudojimo instrukcijos

### 1. Paruošimas
- `files/text.txt` — įdėkite tekstą, kurį norite analizuoti (rekomenduojama ne mažiau kaip 1000 žodžių).
- Jei testuojate URL ištraukimą, `text.txt` turi turėti bent keletą URL.
- `files/domain.txt` — TLD sąrašas URL validavimui (pvz., Public Suffix List).

### 2. Kompiliavimas ir Paleidimas
Atidarykite terminalą projekto kataloge ir paleiskite: `cd build` >> `.\main.exe`

### 3. Reikalavimai
- Operacinė sistema: Windows 10 x64-bit arba naujesnė versija
- Įdiegta CMake (3.25 arba naujesnė versija)
Kompiliatorius: g++ (su C++11 arba naujesne versija)
