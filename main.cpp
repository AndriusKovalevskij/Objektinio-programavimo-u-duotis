#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

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

void ivestiesIsvalymas()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

// Funkcija pazymiu ivesties klaidoms gaudyti
int ivestiSkaiciu(const string& zinute, int min_pazymys = 1, int max_pazymys = 10)
{
    int skaicius;

    while (true) {
        cout << zinute;
        if(!(cin >> skaicius))
        {
            cout << "Klaida: ivestis turi buti skaicius! Pabandykite dar karta." << endl;
            ivestiesIsvalymas();
            continue;
        }

        if(skaicius < min_pazymys || skaicius > max_pazymys)
        {
            cout << "Klaida: skaicius turi buti nuo " << min_pazymys << " iki " << max_pazymys << "! Pabandykite dar karta." <<endl;
            continue;
        }
        break;
    }
    return skaicius;
}

// Funkcija vardo/pavardes ivesties klaidos gaudyti
string ivestiVarda(const string& zinute)
{
    string vardas;
    while (true) {
        cout << zinute;
        cin >> vardas;

        bool tinkamas = true;

        if (vardas.empty())
        {
            cout << "Klaida: vardas/pavarde negali buti be raidziu! Pabandykite dar karta." << endl;
            tinkamas = false;
        } else {
            for (char c : vardas)
            {
                if (!isalpha(c))
                {
                    cout << "Klaida: vardas/pavarde turi buti tik is raidziu! Pabandykite dar karta." << endl;
                    tinkamas = false;
                    break;
                }
            }
        }

        if (tinkamas)
        {
            break;
        }

        ivestiesIsvalymas();
    }
    return vardas;
}

double MedianosSkaiciavimas(vector<int> pazymiai)
{
    int dydis = pazymiai.size();
    if (dydis == 0) return 0;

    sort(pazymiai.begin(), pazymiai.end());

    if (dydis % 2 == 0)
    {
        return (pazymiai[dydis / 2 - 1] + pazymiai[dydis / 2]) / 2.0;
    } else {
        return pazymiai[dydis / 2];
    }
}

void NDpazymiuivestis(vector<int>& ndpazymiai)
{
    string eilute;
    int pazymys;

    cout << "Iveskite namu darbu pazymius (1-10). Norint baigti ivedima, paspauskite ENTER 2 kartus:" << endl;

    // Praleidziama newline po ankstesnio cin
    cin.ignore();

    int numeris = 1;
    while (true)
    {
        cout << numeris << ": ";
        getline(cin, eilute);

        if (eilute.empty())
        {
            break;
        }

        stringstream ss(eilute);
        if (ss >> pazymys)
        {
            if (pazymys >= 1 && pazymys <= 10)
            {
                ndpazymiai.push_back(pazymys);
                numeris++;
            } else {
                cout << "Klaida: pazymys turi buti nuo 1 iki 10!" << endl;
            }
        }
        else {
            cout << "Klaida: ivestis turi buti skaicius!" << endl;
        }
        }
    }


// Studento duomenu ivestis
Studentas Stud_ivestis(int studentoNr)
{
    Studentas pirmas;
    cout << "\nIveskite " << studentoNr << "-o studento duomenis" << endl;
    pirmas.vardas = ivestiVarda("Vardas: ");
    pirmas.pavarde = ivestiVarda("Pavarde: ");

    NDpazymiuivestis(pirmas.ndpazymiai);

    int n = pirmas.ndpazymiai.size();
    if (n == 0) {
        cout << "Studentas neturi namu darbu pazymiu." << endl;
    } else {
        cout << "Ivesti " << n << " namu darbu pazymiai." << endl;
    }

    pirmas.egzrezultatas = ivestiSkaiciu("Iveskite egzamino rezultata (1-10): ");
    if (n > 0)
    {
        int sum = 0;
        for (int pazymys : pirmas.ndpazymiai)
        {
            sum += pazymys;
        }
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
