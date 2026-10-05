#include <iostream>
#include <string>
#include <vector>

// BASE CLASS

class Angajat
{
    std::string nume;
    uint32_t data_angajarii;

    uint32_t packDataAngajarii(uint32_t day, uint32_t month, uint32_t year)
    {
        return (year << 9) | (month << 5) | day;
    }

    void unpackDataAngajarii(uint32_t& day, uint32_t& month, uint32_t& year) const
    {
        day = data_angajarii & 0x1F;
        month = (data_angajarii >> 5) & 0x0F;
        year = data_angajarii >> 9;
    }
protected:
    int salariu;
    std::string functie;

public:

    Angajat() : nume(""), data_angajarii(0), salariu(0), functie("") {}

    Angajat(const std::string& nume, uint32_t data, int salariu, const std::string& functie) :
        nume(nume), data_angajarii(data), salariu(salariu), functie(functie) {
    }

    void citire()
    {
        std::cout << "Nume: ";
        std::getline(std::cin, nume);

        uint32_t day, month, year;
        std::cout << "Data angajarii (zi luna an): ";
        std::cin >> day >> month >> year;
        data_angajarii = packDataAngajarii(day, month, year);

        std::cout << "Salariu: ";
        std::cin >> salariu;
        std::cin.ignore();

        std::cout << "Functie: ";
        std::getline(std::cin, functie);
    }

    void afisare() const
    {
        std::cout << "Nume: " << nume << "\n";
        uint32_t day, month, year;
        unpackDataAngajarii(day, month, year);
        std::cout << "Data angajarii: " << day << "/" << month << "/" << year << "\n";
        std::cout << "Salariu: " << salariu << "\n";
        std::cout << "Functie: " << functie << "\n";
    }

    uint32_t getDataAngajarii() const { return data_angajarii; }
    int getSalariu() const { return salariu; }
};


// ================= DERIVED CLASS 1 =================

class Manager : public Angajat
{
    std::string departament;
    int nr_subordonati;

public:

    Manager() : departament(""), nr_subordonati(0) {}
    Manager(const std::string& nume, uint32_t data, int salariu, const std::string& functie, const std::string& departament, int nr_subordonati) :
        Angajat(nume, data, salariu, functie), departament(departament), nr_subordonati(nr_subordonati) {
    }

    void citire()
    {
        std::cout << "Citire Manager:\n";
        Angajat::citire();
        std::cout << "Departament: ";
        std::getline(std::cin, departament);
        std::cout << "Numar subordonati: ";
        std::cin >> nr_subordonati;
        std::cin.ignore();
    }

    void afisare() const
    {
        std::cout << "Afisare Manager:\n";
        Angajat::afisare();
        std::cout << "Departament: " << departament << "\n";
        std::cout << "Numar subordonati: " << nr_subordonati << "\n";
    }

    int getNrSubordonati() const { return nr_subordonati; }
};


// DERIVED CLASS 2

class Programator : public Angajat
{
    std::string limbaj_principal;
    int nivel_experienta;

public:

    Programator() : limbaj_principal(""), nivel_experienta(0) {}
    Programator(const std::string& nume, uint32_t data, int salariu, const std::string& functie, const std::string& limbaj_principal, int nivel_experienta) :
        Angajat(nume, data, salariu, functie), limbaj_principal(limbaj_principal), nivel_experienta(nivel_experienta) {
    }

    void citire()
    {
        std::cout << "Citire Programator:\n";
        Angajat::citire();
        std::cout << "Limbaj principal: ";
        std::getline(std::cin, limbaj_principal);
        std::cout << "Nivel experienta (ani): ";
        std::cin >> nivel_experienta;
        std::cin.ignore();
    }

    void afisare() const
    {
        std::cout << "Afisare Programator:\n";
        Angajat::afisare();
        std::cout << "Limbaj principal: " << limbaj_principal << "\n";
        std::cout << "Nivel experienta: " << nivel_experienta << " ani\n";
    }

    int getNivelExperienta() const { return nivel_experienta; }
};


// ================== MENU ==================

void showActionMenu()
{
    std::cout << "\nMENU\n";
    std::cout << "1. Citire obiecte\n";
    std::cout << "2. Afisare obiecte\n";
    std::cout << "3. Sortare obiecte\n";
    std::cout << "4. Afisare dupa conditie\n";
    std::cout << "5. Modificare obiect pozitia k\n";
    std::cout << "6. Stergere obiect dupa conditie\n";
    std::cout << "7. Selecteaza alt tablou\n";
    std::cout << "0. Iesire\n";
}

void showTableSelectionMenu()
{
    std::cout << "\nSelectati tabloul:\n";
    std::cout << "1. Angajati\n";
    std::cout << "2. Manageri\n";
    std::cout << "3. Programatori\n";
    std::cout << "0. Iesire\n";
}


// ================== FUNCTII ANGAJAT ==================

void citireAngajati(Angajat angajati[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << "Angajat " << (i + 1) << ":\n";
        angajati[i].citire();
    }
}

void afisareAngajati(const Angajat angajati[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << "Angajat " << (i + 1) << ":\n";
        angajati[i].afisare();
    }
}

void sortareAngajatiDupaData(Angajat angajati[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (angajati[j].getDataAngajarii() > angajati[j + 1].getDataAngajarii())
                std::swap(angajati[j], angajati[j + 1]);
}

void sortareAngajatiDupaSalariu(Angajat angajati[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (angajati[j].getSalariu() > angajati[j + 1].getSalariu())
                std::swap(angajati[j], angajati[j + 1]);
}

void afisareAngajatiDupaData(Angajat angajati[], int size, uint32_t prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (angajati[i].getDataAngajarii() > prag) { angajati[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit angajati cu data angajarii dupa pragul specificat.\n";
}

void afisareAngajatiDupaSalariu(Angajat angajati[], int size, int prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (angajati[i].getSalariu() > prag) { angajati[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit angajati cu salariul dupa pragul specificat.\n";
}

void modificareAngajat(Angajat angajati[], int size, int pozitie)
{
    if (pozitie >= 0 && pozitie < size)
    {
        std::cout << "Modificare Angajat la pozitia " << pozitie + 1 << ":\n";
        angajati[pozitie].citire();
    }
    else std::cout << "Pozitie invalida\n";
}

void stergereAngajatiDupaData(Angajat angajati[], int& size, uint32_t prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (angajati[i].getDataAngajarii() <= prag)
            angajati[j++] = angajati[i];
    size = j;
}

void stergereAngajatiDupaSalariu(Angajat angajati[], int& size, int prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (angajati[i].getSalariu() <= prag)
            angajati[j++] = angajati[i];
    size = j;
}


// FUNCTII MANAGER 

void citireManageri(Manager manageri[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << "Manager " << (i + 1) << ":\n";
        manageri[i].citire();
    }
}

void afisareManageri(const Manager manageri[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << "Manager " << (i + 1) << ":\n";
        manageri[i].afisare();
    }
}

void sortareManageriDupaData(Manager manageri[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (manageri[j].getDataAngajarii() > manageri[j + 1].getDataAngajarii())
                std::swap(manageri[j], manageri[j + 1]);
}

void sortareManageriDupaSalariu(Manager manageri[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (manageri[j].getSalariu() > manageri[j + 1].getSalariu())
                std::swap(manageri[j], manageri[j + 1]);
}

// Extra: sort by nr_subordonati (specific to Manager)
void sortareManageriDupaNrSubordonati(Manager manageri[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (manageri[j].getNrSubordonati() > manageri[j + 1].getNrSubordonati())
                std::swap(manageri[j], manageri[j + 1]);
}

void afisareManageriDupaData(Manager manageri[], int size, uint32_t prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (manageri[i].getDataAngajarii() > prag) { manageri[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit manageri cu data angajarii dupa pragul specificat.\n";
}

void afisareManageriDupaSalariu(Manager manageri[], int size, int prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (manageri[i].getSalariu() > prag) { manageri[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit manageri cu salariul dupa pragul specificat.\n";
}

// Extra: filtrare dupa nr_subordonati (specific to Manager)
void afisareManageriDupaNrSubordonati(Manager manageri[], int size, int prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (manageri[i].getNrSubordonati() > prag) { manageri[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit manageri cu numarul de subordonati dupa pragul specificat.\n";
}

void modificareManager(Manager manageri[], int size, int pozitie)
{
    if (pozitie >= 0 && pozitie < size)
    {
        std::cout << "Modificare Manager la pozitia " << pozitie + 1 << ":\n";
        manageri[pozitie].citire();
    }
    else std::cout << "Pozitie invalida\n";
}

void stergereManageriDupaData(Manager manageri[], int& size, uint32_t prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (manageri[i].getDataAngajarii() <= prag)
            manageri[j++] = manageri[i];
    size = j;
}

void stergereManageriDupaSalariu(Manager manageri[], int& size, int prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (manageri[i].getSalariu() <= prag)
            manageri[j++] = manageri[i];
    size = j;
}

// Extra: sterge dupa nr_subordonati (specific to Manager)
void stergereManageriDupaNrSubordonati(Manager manageri[], int& size, int prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (manageri[i].getNrSubordonati() <= prag)
            manageri[j++] = manageri[i];
    size = j;
}


// FUNCTII PROGRAMATOR

void citireProgramatori(Programator programatori[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << "Programator " << (i + 1) << ":\n";
        programatori[i].citire();
    }
}

void afisareProgramatori(const Programator programatori[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << "Programator " << (i + 1) << ":\n";
        programatori[i].afisare();
    }
}

void sortareProgramatoriDupaData(Programator programatori[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (programatori[j].getDataAngajarii() > programatori[j + 1].getDataAngajarii())
                std::swap(programatori[j], programatori[j + 1]);
}

void sortareProgramatoriDupaSalariu(Programator programatori[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (programatori[j].getSalariu() > programatori[j + 1].getSalariu())
                std::swap(programatori[j], programatori[j + 1]);
}

// Extra: sortare dupa nivel_experienta (specific to Programator)
void sortareProgramatoriDupaNivelExperienta(Programator programatori[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if (programatori[j].getNivelExperienta() > programatori[j + 1].getNivelExperienta())
                std::swap(programatori[j], programatori[j + 1]);
}

void afisareProgramatoriDupaData(Programator programatori[], int size, uint32_t prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (programatori[i].getDataAngajarii() > prag) { programatori[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit programatori cu data angajarii dupa pragul specificat.\n";
}

void afisareProgramatoriDupaSalariu(Programator programatori[], int size, int prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (programatori[i].getSalariu() > prag) { programatori[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit programatori cu salariul dupa pragul specificat.\n";
}

// Extra: afisare dupa nivel_experienta (specific to Programator)
void afisareProgramatoriDupaNivelExperienta(Programator programatori[], int size, int prag)
{
    int gasiti = 0;
    for (int i = 0; i < size; ++i)
        if (programatori[i].getNivelExperienta() > prag) { programatori[i].afisare(); gasiti++; }
    if (gasiti == 0) std::cout << "Nu s-au gasit programatori cu nivelul de experienta dupa pragul specificat.\n";
}

void modificareProgramator(Programator programatori[], int size, int pozitie)
{
    if (pozitie >= 0 && pozitie < size)
    {
        std::cout << "Modificare Programator la pozitia " << pozitie + 1 << ":\n";
        programatori[pozitie].citire();
    }
    else std::cout << "Pozitie invalida\n";
}

void stergereProgramatoriDupaData(Programator programatori[], int& size, uint32_t prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (programatori[i].getDataAngajarii() <= prag)
            programatori[j++] = programatori[i];
    size = j;
}

void stergereProgramatoriDupaSalariu(Programator programatori[], int& size, int prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (programatori[i].getSalariu() <= prag)
            programatori[j++] = programatori[i];
    size = j;
}

// Extra: delete by nivel_experienta (specific to Programator)
void stergereProgramatoriDupaNivelExperienta(Programator programatori[], int& size, int prag)
{
    int j = 0;
    for (int i = 0; i < size; ++i)
        if (programatori[i].getNivelExperienta() <= prag)
            programatori[j++] = programatori[i];
    size = j;
}


// MAIN

int main()
{
    const int SIZE = 10;

    Angajat    angajati[SIZE];    int sizeAngajati = SIZE; bool angajatiModificati = false;
    Manager    manageri[SIZE];    int sizeManageri = SIZE; bool manageriModificati = false;
    Programator programatori[SIZE]; int sizeProgramatori = SIZE; bool programatoriModificati = false;

    int tableChoice = -1;
    int actionChoice = -1;

    do
    {
        showTableSelectionMenu();
        std::cin >> tableChoice;
        std::cin.ignore();

        if (tableChoice == 0) break;

        do
        {
            showActionMenu();
            std::cin >> actionChoice;
            std::cin.ignore();

            switch (actionChoice)
            {

                // -------- CASE 1: CITIRE --------
            case 1:
                if (tableChoice == 1)
                {
                    citireAngajati(angajati, sizeAngajati);
                    angajatiModificati = true;
                }
                else if (tableChoice == 2)
                {
                    citireManageri(manageri, sizeManageri);
                    manageriModificati = true;
                }
                else if (tableChoice == 3)
                {
                    citireProgramatori(programatori, sizeProgramatori);
                    programatoriModificati = true;
                }
                break;

                // -------- CASE 2: AFISARE --------
            case 2:
                if (tableChoice == 1)
                {
                    if (angajatiModificati)
                        afisareAngajati(angajati, sizeAngajati);
                    else
                        std::cout << "Nu s-au citit angajati. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 2)
                {
                    if (manageriModificati)
                        afisareManageri(manageri, sizeManageri);
                    else
                        std::cout << "Nu s-au citit manageri. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 3)
                {
                    if (programatoriModificati)
                        afisareProgramatori(programatori, sizeProgramatori);
                    else
                        std::cout << "Nu s-au citit programatori. Va rugam sa cititi mai intai.\n";
                }
                break;

                // -------- CASE 3: SORTARE --------
            case 3:
                if (tableChoice == 1)
                {
                    if (angajatiModificati)
                    {
                        std::cout << "Sortare dupa:\n1. Data angajarii\n2. Salariu\n";
                        int sortChoice; std::cin >> sortChoice; std::cin.ignore();
                        if (sortChoice == 1) { sortareAngajatiDupaData(angajati, sizeAngajati);    std::cout << "Sortati dupa data angajarii.\n"; }
                        else if (sortChoice == 2) { sortareAngajatiDupaSalariu(angajati, sizeAngajati); std::cout << "Sortati dupa salariu.\n"; }
                        else std::cout << "Optiune de sortare invalida.\n";
                    }
                    else std::cout << "Nu s-au citit angajati. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 2)
                {
                    if (manageriModificati)
                    {
                        std::cout << "Sortare dupa:\n1. Data angajarii\n2. Salariu\n3. Numar subordonati\n";
                        int sortChoice; std::cin >> sortChoice; std::cin.ignore();
                        if (sortChoice == 1) { sortareManageriDupaData(manageri, sizeManageri);           std::cout << "Sortati dupa data angajarii.\n"; }
                        else if (sortChoice == 2) { sortareManageriDupaSalariu(manageri, sizeManageri);        std::cout << "Sortati dupa salariu.\n"; }
                        else if (sortChoice == 3) { sortareManageriDupaNrSubordonati(manageri, sizeManageri);  std::cout << "Sortati dupa numar subordonati.\n"; }
                        else std::cout << "Optiune de sortare invalida.\n";
                    }
                    else std::cout << "Nu s-au citit manageri. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 3)
                {
                    if (programatoriModificati)
                    {
                        std::cout << "Sortare dupa:\n1. Data angajarii\n2. Salariu\n3. Nivel experienta\n";
                        int sortChoice; std::cin >> sortChoice; std::cin.ignore();
                        if (sortChoice == 1) { sortareProgramatoriDupaData(programatori, sizeProgramatori);           std::cout << "Sortati dupa data angajarii.\n"; }
                        else if (sortChoice == 2) { sortareProgramatoriDupaSalariu(programatori, sizeProgramatori);        std::cout << "Sortati dupa salariu.\n"; }
                        else if (sortChoice == 3) { sortareProgramatoriDupaNivelExperienta(programatori, sizeProgramatori); std::cout << "Sortati dupa nivel experienta.\n"; }
                        else std::cout << "Optiune de sortare invalida.\n";
                    }
                    else std::cout << "Nu s-au citit programatori. Va rugam sa cititi mai intai.\n";
                }
                break;

                // -------- CASE 4: AFISARE DUPA CONDITIE --------
            case 4:
                if (tableChoice == 1)
                {
                    if (angajatiModificati)
                    {
                        std::cout << "Afisare dupa:\n1. Data angajarii\n2. Salariu\n";
                        int filterChoice; std::cin >> filterChoice; std::cin.ignore();
                        if (filterChoice == 1)
                        {
                            uint32_t day, month, year;
                            std::cout << "Prag data angajarii (zi luna an): ";
                            std::cin >> day >> month >> year; std::cin.ignore();
                            uint32_t prag = (year << 9) | (month << 5) | day;
                            afisareAngajatiDupaData(angajati, sizeAngajati, prag);
                        }
                        else if (filterChoice == 2)
                        {
                            int prag; std::cout << "Prag salariu: "; std::cin >> prag; std::cin.ignore();
                            afisareAngajatiDupaSalariu(angajati, sizeAngajati, prag);
                        }
                        else std::cout << "Optiune de filtrare invalida.\n";
                    }
                    else std::cout << "Nu s-au citit angajati. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 2)
                {
                    if (manageriModificati)
                    {
                        std::cout << "Afisare dupa:\n1. Data angajarii\n2. Salariu\n3. Numar subordonati\n";
                        int filterChoice; std::cin >> filterChoice; std::cin.ignore();
                        if (filterChoice == 1)
                        {
                            uint32_t day, month, year;
                            std::cout << "Prag data angajarii (zi luna an): ";
                            std::cin >> day >> month >> year; std::cin.ignore();
                            uint32_t prag = (year << 9) | (month << 5) | day;
                            afisareManageriDupaData(manageri, sizeManageri, prag);
                        }
                        else if (filterChoice == 2)
                        {
                            int prag; std::cout << "Prag salariu: "; std::cin >> prag; std::cin.ignore();
                            afisareManageriDupaSalariu(manageri, sizeManageri, prag);
                        }
                        else if (filterChoice == 3)
                        {
                            int prag; std::cout << "Prag numar subordonati: "; std::cin >> prag; std::cin.ignore();
                            afisareManageriDupaNrSubordonati(manageri, sizeManageri, prag);
                        }
                        else std::cout << "Optiune de filtrare invalida.\n";
                    }
                    else std::cout << "Nu s-au citit manageri. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 3)
                {
                    if (programatoriModificati)
                    {
                        std::cout << "Afisare dupa:\n1. Data angajarii\n2. Salariu\n3. Nivel experienta\n";
                        int filterChoice; std::cin >> filterChoice; std::cin.ignore();
                        if (filterChoice == 1)
                        {
                            uint32_t day, month, year;
                            std::cout << "Prag data angajarii (zi luna an): ";
                            std::cin >> day >> month >> year; std::cin.ignore();
                            uint32_t prag = (year << 9) | (month << 5) | day;
                            afisareProgramatoriDupaData(programatori, sizeProgramatori, prag);
                        }
                        else if (filterChoice == 2)
                        {
                            int prag; std::cout << "Prag salariu: "; std::cin >> prag; std::cin.ignore();
                            afisareProgramatoriDupaSalariu(programatori, sizeProgramatori, prag);
                        }
                        else if (filterChoice == 3)
                        {
                            int prag; std::cout << "Prag nivel experienta (ani): "; std::cin >> prag; std::cin.ignore();
                            afisareProgramatoriDupaNivelExperienta(programatori, sizeProgramatori, prag);
                        }
                        else std::cout << "Optiune de filtrare invalida.\n";
                    }
                    else std::cout << "Nu s-au citit programatori. Va rugam sa cititi mai intai.\n";
                }
                break;

                // -------- CASE 5: MODIFICARE --------
            case 5:
                if (tableChoice == 1)
                {
                    if (angajatiModificati)
                    {
                        int pozitie;
                        std::cout << "Introduceti pozitia angajatului de modificat (1-" << sizeAngajati << "): ";
                        std::cin >> pozitie; std::cin.ignore();
                        modificareAngajat(angajati, sizeAngajati, pozitie - 1);
                    }
                    else std::cout << "Nu s-au citit angajati. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 2)
                {
                    if (manageriModificati)
                    {
                        int pozitie;
                        std::cout << "Introduceti pozitia managerului de modificat (1-" << sizeManageri << "): ";
                        std::cin >> pozitie; std::cin.ignore();
                        modificareManager(manageri, sizeManageri, pozitie - 1);
                    }
                    else std::cout << "Nu s-au citit manageri. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 3)
                {
                    if (programatoriModificati)
                    {
                        int pozitie;
                        std::cout << "Introduceti pozitia programatorului de modificat (1-" << sizeProgramatori << "): ";
                        std::cin >> pozitie; std::cin.ignore();
                        modificareProgramator(programatori, sizeProgramatori, pozitie - 1);
                    }
                    else std::cout << "Nu s-au citit programatori. Va rugam sa cititi mai intai.\n";
                }
                break;

                // CASE 6: STERGERE 
            case 6:
                if (tableChoice == 1)
                {
                    if (angajatiModificati)
                    {
                        std::cout << "Stergere dupa:\n1. Data angajarii\n2. Salariu\n";
                        int deleteChoice; std::cin >> deleteChoice; std::cin.ignore();
                        if (deleteChoice == 1)
                        {
                            uint32_t day, month, year;
                            std::cout << "Prag data angajarii (zi luna an): ";
                            std::cin >> day >> month >> year; std::cin.ignore();
                            uint32_t prag = (year << 9) | (month << 5) | day;
                            stergereAngajatiDupaData(angajati, sizeAngajati, prag);
                            std::cout << "Angajatii cu data angajarii dupa prag au fost stersi.\n";
                        }
                        else if (deleteChoice == 2)
                        {
                            int prag; std::cout << "Prag salariu: "; std::cin >> prag; std::cin.ignore();
                            stergereAngajatiDupaSalariu(angajati, sizeAngajati, prag);
                            std::cout << "Angajatii cu salariul dupa prag au fost stersi.\n";
                        }
                        else std::cout << "Optiune de stergere invalida.\n";
                    }
                    else std::cout << "Nu s-au citit angajati. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 2)
                {
                    if (manageriModificati)
                    {
                        std::cout << "Stergere dupa:\n1. Data angajarii\n2. Salariu\n3. Numar subordonati\n";
                        int deleteChoice; std::cin >> deleteChoice; std::cin.ignore();
                        if (deleteChoice == 1)
                        {
                            uint32_t day, month, year;
                            std::cout << "Prag data angajarii (zi luna an): ";
                            std::cin >> day >> month >> year; std::cin.ignore();
                            uint32_t prag = (year << 9) | (month << 5) | day;
                            stergereManageriDupaData(manageri, sizeManageri, prag);
                            std::cout << "Managerii cu data angajarii dupa prag au fost stersi.\n";
                        }
                        else if (deleteChoice == 2)
                        {
                            int prag; std::cout << "Prag salariu: "; std::cin >> prag; std::cin.ignore();
                            stergereManageriDupaSalariu(manageri, sizeManageri, prag);
                            std::cout << "Managerii cu salariul dupa prag au fost stersi.\n";
                        }
                        else if (deleteChoice == 3)
                        {
                            int prag; std::cout << "Prag numar subordonati: "; std::cin >> prag; std::cin.ignore();
                            stergereManageriDupaNrSubordonati(manageri, sizeManageri, prag);
                            std::cout << "Managerii cu numarul de subordonati dupa prag au fost stersi.\n";
                        }
                        else std::cout << "Optiune de stergere invalida.\n";
                    }
                    else std::cout << "Nu s-au citit manageri. Va rugam sa cititi mai intai.\n";
                }
                else if (tableChoice == 3)
                {
                    if (programatoriModificati)
                    {
                        std::cout << "Stergere dupa:\n1. Data angajarii\n2. Salariu\n3. Nivel experienta\n";
                        int deleteChoice; std::cin >> deleteChoice; std::cin.ignore();
                        if (deleteChoice == 1)
                        {
                            uint32_t day, month, year;
                            std::cout << "Prag data angajarii (zi luna an): ";
                            std::cin >> day >> month >> year; std::cin.ignore();
                            uint32_t prag = (year << 9) | (month << 5) | day;
                            stergereProgramatoriDupaData(programatori, sizeProgramatori, prag);
                            std::cout << "Programatorii cu data angajarii dupa prag au fost stersi.\n";
                        }
                        else if (deleteChoice == 2)
                        {
                            int prag; std::cout << "Prag salariu: "; std::cin >> prag; std::cin.ignore();
                            stergereProgramatoriDupaSalariu(programatori, sizeProgramatori, prag);
                            std::cout << "Programatorii cu salariul dupa prag au fost stersi.\n";
                        }
                        else if (deleteChoice == 3)
                        {
                            int prag; std::cout << "Prag nivel experienta (ani): "; std::cin >> prag; std::cin.ignore();
                            stergereProgramatoriDupaNivelExperienta(programatori, sizeProgramatori, prag);
                            std::cout << "Programatorii cu nivelul de experienta dupa prag au fost stersi.\n";
                        }
                        else std::cout << "Optiune de stergere invalida.\n";
                    }
                    else std::cout << "Nu s-au citit programatori. Va rugam sa cititi mai intai.\n";
                }
                break;

            case 7:
                break;
            case 0:
                break;

            default:
                std::cout << "Optiune invalida\n";
            }

        } while (actionChoice != 0 && actionChoice != 7);

    } while (tableChoice != 0);

    return 0;
}