#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::left;
using std::right;
using std::fixed;

struct Studentas
{
    string vardas;
    string pavarde;
    vector <int> ndpazymiai;
    int egzrezultatas;
    double galutinis;

};

// Funkcija pazymiu ivesties klaidoms gaudyti
int ivestiSkaiciu(const string& zinute, int min_pazymys = 1, int max_pazymys = 10)
{
    int skaicius;
    cout << zinute;
    if(!(cin >> skaicius))
    {
        cout << "Klaida: ivestis turi buti skaicius!" << endl;
        exit(1);
    }
    if(skaicius < min_pazymys || skaicius > max_pazymys)
    {
        cout << "Klaida: skaicius turi buti nuo " << min_pazymys << " iki " << max_pazymys << "!" <<endl;
        exit(1);
    }
    return skaicius;
}

// Funkcija vardo/pavardes ivesties klaidos gaudyti
string ivestiVarda(const string& zinute)
{
    string vardas;
    cout << zinute;
    cin >> vardas;

    for (char c : vardas)
    {
        if (!isalpha(c))
        {
            cout << "Klaida: vardas/pavarde turi buti tik is raidziu!" << endl;
            exit(1);
        }
    }

    if (vardas.empty())
    {
        cout << "Klaida: vardas/pavarde negali buti be raidziu!" << endl;
        exit(1);
    }
    return vardas;
}

// Studento duomenu ivestis
Studentas Stud_ivestis(int studentoNr)
{
    int n, laikinas_paz, sum = 0;
    Studentas pirmas;
    cout << "\nIveskite " << studentoNr << "-o studento duomenis" << endl;
    pirmas.vardas = ivestiVarda("Vardas: ");
    pirmas.pavarde = ivestiVarda("Pavarde: ");
    cout << "Kiek namu darbu pazymiu turi " << pirmas.vardas << " " << pirmas.pavarde << "? ";
    n = ivestiSkaiciu("", 0, 10);

    if (n == 0) {
        cout << "Studentas neturi namu darbu pazymiu." << endl;
    } else {
        cout << "Iveskite namu darbu pazymius (1-10):" << endl;
        for (int a = 0; a < n; a++)
        {
        laikinas_paz =ivestiSkaiciu(to_string(a + 1) + ": ");
        pirmas.ndpazymiai.push_back(laikinas_paz);
        sum += laikinas_paz;
        }
    }
    pirmas.egzrezultatas = ivestiSkaiciu("Iveskite egzamino rezultata (1-10): ");
    if (n > 0)
    {
        pirmas.galutinis = double(sum) / double(n) * 0.4 + pirmas.egzrezultatas * 0.6;

    } else {
        pirmas.galutinis = pirmas.egzrezultatas * 0.6;
    }
    return pirmas;
}

int main()
{
    cout << "Laba diena" << endl;
    vector<Studentas> Grupe;
    int m = ivestiSkaiciu("Kiek studentu grupeje?: ", 1, 100000);

    for (auto z = 0; z < m; z++)
    {
        Grupe.push_back(Stud_ivestis(z + 1));
    }

    cout << "\nStudento informacija:" << endl;
    cout << left << setw(10) << "Vardas" << "|"
         << left << setw(15) << "Pavarde" << "|"
         << left << setw(20) << "ND pazymiai" << "|"
         << left << setw(10) << "Galutinis (Vid.)" << endl;
    cout << string(70, '-') << endl;

    for (auto Past : Grupe)
    {
        cout << setw(10) << left << Past.vardas << "|"
             << setw(15) << left << Past.pavarde << "|";

        string pazymiai_str = "";
        if (Past.ndpazymiai.empty())
        {
            pazymiai_str = "nera";
        } else {
            for (auto& a : Past.ndpazymiai)
            {
                pazymiai_str += to_string(a) + " ";
            }
        }
        cout << setw(20) << left << pazymiai_str << "|"
             << fixed << setprecision(2) << setw(10) << left << Past.galutinis << endl;
    }
    return 0;
}
