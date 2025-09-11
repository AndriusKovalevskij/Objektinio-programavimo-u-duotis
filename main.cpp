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
    double galutinis_vidurkis;
    double galutine_mediana;

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

void Rusiavimas(vector<int>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                int temp = vec[j];
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
}

double MedianosSkaiciavimas(vector<int> pazymiai)
{
    int dydis = pazymiai.size();
    if (dydis == 0) return 0;

    Rusiavimas(pazymiai);

    if (dydis % 2 == 0)
    {
        return (pazymiai[dydis / 2 - 1] + pazymiai[dydis / 2]) / 2.0;
    } else {
        return pazymiai[dydis / 2];
    }
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
        pirmas.galutinis_vidurkis = double(sum) / double(n) * 0.4 + pirmas.egzrezultatas * 0.6;
        pirmas.galutine_mediana = MedianosSkaiciavimas(pirmas.ndpazymiai) * 0.4 + pirmas.egzrezultatas *0.6;
    } else {
        pirmas.galutinis_vidurkis = pirmas.egzrezultatas * 0.6;
        pirmas.galutine_mediana = pirmas.egzrezultatas * 0.6;
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

    int pasirinkimas;
    cout << "\nPasirinkite galutinio ivertinimo tipa:" << endl;
    cout << "1 - Pagal vidurki" << endl;
    cout << "2 - Pagal mediana" << endl;
    cout << "3 - Rodyti abu" << endl;
    pasirinkimas = ivestiSkaiciu("Jusu pasirinkimas: ", 1, 3);

    cout << "\nStudento informacija:" << endl;
    cout << left << setw(20) << "Vardas" << "|"
         << left << setw(20) << "Pavarde";

    if (pasirinkimas == 1)
    {
        cout << "|" << left << setw(20) << "Galutinis (vid.)";
    } else if (pasirinkimas == 2) {
        cout << "|" << left << setw(20) << "Galutinis (Med.)";
    } else {
        cout << "|" << left << setw(20) << "Galutinis (Vid.)"
             << "|" << left << setw(20) << "Galutinis (Med.)";
    }
    cout << endl;

    if (pasirinkimas == 3)
    {
        cout << string(80, '-') << endl;
    } else {
        cout << string(60, '-') << endl;
    }

    for (const auto Past : Grupe)
    {
        cout << setw(20) << left << Past.vardas << "|"
             << setw(20) << left << Past.pavarde;

        if (pasirinkimas == 1)
        {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << Past.galutinis_vidurkis;
        } else if (pasirinkimas == 2){
            cout << "|" << fixed << setprecision(2) << setw(20) << left << Past.galutine_mediana;
        } else {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << Past.galutinis_vidurkis
                 << "|" << fixed << setprecision(2) << setw(20) << left << Past.galutine_mediana;
        }
        cout << endl;
    }
    return 0;
}
