#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <fstream>

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

// Ivesties isvalymas (naudojamas, kai ivedamas netinkamas irasas)
void ivestiesIsvalymas()
{
    cin.clear();
    cin.ignore(10000, '\n');    //Isvaloma tiek simboliu, arba iki tol kol randa \n
}

// Funkcija pazymiu ivesties klaidoms gaudyti
int ivestiSkaiciu(const string& zinute, int min_pazymys = 1, int max_pazymys = 10)
{
    int skaicius;

    while (true) {
        cout << zinute;
        if(!(cin >> skaicius))  // Jeigu ivestis nera skaicius
        {
            cout << "Klaida: ivestis turi buti skaicius! Pabandykite dar karta." << endl;
            ivestiesIsvalymas();
            continue;
        }

        if(skaicius < min_pazymys || skaicius > max_pazymys)    // Tikrinamos ivesties ribos
        {
            cout << "Klaida: skaicius turi buti nuo " << min_pazymys << " iki " << max_pazymys << "! Pabandykite dar karta." <<endl;
            continue;
        }
        break;
    }
    return skaicius;
}

// Funkcija vardo/pavardes ivesties klaidoms gaudyti
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
            // Tikriname, kad visi simboliai butu raides
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

        if (eilute.empty()) //jeigu eilute tuscia, ciklas baigiamas
        {
            break;
        }

        stringstream ss(eilute);    //Objektas, kuris naudoja eilute, kaip ivesties saltini
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

int AtsitiktinioPazymioGeneravimas()
{
    return rand() % 10 + 1;
}

void NDPazymiuGeneravimas(vector<int>& ndpazymiai)
{
    int kiekis = ivestiSkaiciu("Kiek namu darbu pazymiu generuoti? ");

    if (kiekis == 0)
    {
        cout << "Negeneruojami namu darbu pazymiai."<< endl;
        return;
    }

    cout << "Sugeneruoti namu darbu pazymiai: ";
    for (int i = 0; i < kiekis; i++)
    {
        int  pazymys = AtsitiktinioPazymioGeneravimas();
        ndpazymiai.push_back(pazymys);
        cout << pazymys << " ";
    }
    cout << endl;
}

bool skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<Studentas>& studentai)
{
    ifstream failas(failoPavadinimas);  //Atidaromas failas skaitymui
    if (!failas.is_open())
    {
        cout << "Klaida: nepavyko atidaryti failo " << failoPavadinimas << endl;
        return false;
    }

    string eilute;

    // Praleidziame antraste
    if (!getline(failas, eilute))
    {
        cout << "Klaida: failas tuscias arba pazeistas" << endl;
        failas.close();
        return false;
    }

    int studentuSkaicius = 0;
    while (getline(failas, eilute))
    {
        if (eilute.empty()) continue;

        stringstream ss(eilute);
        Studentas studentas;

        // Skaitome varda ir pavarde
        if (!(ss >> studentas.vardas >> studentas.pavarde))
        {
            cout << "Klaida skaitant eilute: " << eilute << endl;
            continue;
        }

        // Skaitome namu darbu pazymius ir egzamino rezultata
        int pazymys;
        vector<int> visi_pazymiai;

        while (ss >> pazymys)
        {
            if (pazymys < 1 || pazymys > 10)
            {
                cout << "Netinkamas pazymys " << pazymys << " studentui "
                     << studentas.vardas << " " << studentas.pavarde << endl;
                continue;
            }
            visi_pazymiai.push_back(pazymys);
        }

        if (visi_pazymiai.empty())
        {
            cout << "Studentas " << studentas.vardas << " " << studentas.pavarde
                 << " neturi pazymiu" << endl;
            continue;
        }

        // Paskutinis pazymys yra egzamino rezultatas
        studentas.egzrezultatas = visi_pazymiai.back(); //Grazina paskutine elemento reiksme
        visi_pazymiai.pop_back();   //Pasalina paskutini elementa is vektoriaus

        // Like pazymiai yra namu darbai
        studentas.ndpazymiai = visi_pazymiai;

        // Skaiciuojame galutini pazymi
        if (studentas.ndpazymiai.size() > 0)
        {
            int sum = 0;
            for (int nd_pazymys : studentas.ndpazymiai)
            {
                sum += nd_pazymys;
            }
            studentas.galutinis_vidurkis = double(sum) / double(studentas.ndpazymiai.size()) * 0.4 + studentas.egzrezultatas * 0.6;
            studentas.galutine_mediana = MedianosSkaiciavimas(studentas.ndpazymiai) * 0.4 + studentas.egzrezultatas * 0.6;
        } else {
            studentas.galutinis_vidurkis = studentas.egzrezultatas * 0.6;
            studentas.galutine_mediana = studentas.egzrezultatas * 0.6;
        }

        studentai.push_back(studentas);
        studentuSkaicius++;
    }

    failas.close();
    cout << "Sekmingai nuskaityta " << studentuSkaicius << " studentu duomenys. " << endl;
    return true;
}

// Studento duomenu ivestis (rankinis ivedimas)
Studentas Stud_ivestis(int studentoNr, bool atsitiktinai = false)
{
    Studentas pirmas;
    cout << "\nIveskite " << studentoNr << "-o studento duomenis" << endl;
    pirmas.vardas = ivestiVarda("Vardas: ");
    pirmas.pavarde = ivestiVarda("Pavarde: ");

    if (atsitiktinai)
    {
        NDPazymiuGeneravimas(pirmas.ndpazymiai);
        pirmas.egzrezultatas = AtsitiktinioPazymioGeneravimas();
        cout << "Sugeneruotas egzamino pazymys: " << pirmas.egzrezultatas << endl;
    } else {
        NDpazymiuivestis(pirmas.ndpazymiai);
        pirmas.egzrezultatas = ivestiSkaiciu("Iveskite egzamino rezultata (1-10): ");
    }

    int n = pirmas.ndpazymiai.size();
    if (n == 0) {
        cout << "Studentas neturi namu darbu pazymiu." << endl;
    } else {
        cout << "Ivesti " << n << " namu darbu pazymiai." << endl;
    }

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

// RIkiavimo funkcija pagal varda
bool palyginimasPagalVarda(const Studentas& a, const Studentas& b)
{
    return a.vardas < b.vardas;
}

// Rikiavimo funkcija pagal pavarde
bool palyginimasPagalPavarde(const Studentas& a, const Studentas& b)
{
    return a.pavarde < b.pavarde;
}

int rodytiMeniu()
{
    cout << "\n PROGRAMOS MENIU" << endl;
    cout << "1 - Ivesti duomenis rankiniu budu" << endl;
    cout << "2 - Generuoti duomenis atsitiktinai" << endl;
    cout << "3 - Nuskaityti duomenis is failo" << endl;
    cout << "4 - Baigti programa" << endl;

    return ivestiSkaiciu("Pasirinkite buda (1-4): ", 1, 4);
}

void rodytiRezultatus(const vector<Studentas>& Grupe)
{
    if (Grupe.empty()) {
        cout << "Nera ivestos informacijos apie studentus!" << endl;
        return;
    }

    int rusiuotiPagal = ivestiSkaiciu("\nKaip norite rusiuoti studentus?\n1 - Pagal varda\n2 - Pagal pavarde\nPasirinkimas: ", 1, 2);

    // Vektoriaus kopija rikiavimui pagal studento varda
    vector<Studentas> surusiuotiStudentai = Grupe;
    if (rusiuotiPagal == 1)
    {
        sort(surusiuotiStudentai.begin(), surusiuotiStudentai.end(), palyginimasPagalVarda);
    } else {
        sort(surusiuotiStudentai.begin(), surusiuotiStudentai.end(), palyginimasPagalPavarde);
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

    for (const auto& studentas : surusiuotiStudentai)
    {
        cout << setw(20) << left << studentas.vardas << "|"
             << setw(20) << left << studentas.pavarde;

        if (pasirinkimas == 1)
        {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis;
        } else if (pasirinkimas == 2){
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        } else {
            cout << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutinis_vidurkis
                 << "|" << fixed << setprecision(2) << setw(20) << left << studentas.galutine_mediana;
        }
        cout << endl;
    }
}

int main()
{
    srand(time(0)); //Atsitiktiniu skaiciu generatoriaus inicializacija

    cout << "Laba diena" << endl;
    vector<Studentas> Grupe;

    while (true)
    {
        int pasirinkimas = rodytiMeniu();

        switch (pasirinkimas)
        {
            case 1: {
                // Rankinis duomenu ivedimas
                int m = ivestiSkaiciu("Kiek studentu grupeje?: ", 1, 100000);
                for (int z = 0; z < m; z++) {
                    Grupe.push_back(Stud_ivestis(z + 1, false));
                }
                rodytiRezultatus(Grupe);
                break;
            }
            case 2: {
                // Atsitiktinis duomenu generavimas
                int m = ivestiSkaiciu("Kiek studentu grupeje?: ", 1, 100000);
                for (int z = 0; z < m; z++) {
                    Grupe.push_back(Stud_ivestis(z + 1, true));
                }
                rodytiRezultatus(Grupe);
                break;
            }
            case 3: {
                // Skaitymas iš failo
                cout << "Iveskite failo pavadinima (pvz., kursiokai.txt): ";
                string failoPavadinimas;
                cin >> failoPavadinimas;

                if (skaitytiDuomenisIsFailo(failoPavadinimas, Grupe))
                {
                    rodytiRezultatus(Grupe);
                } else {
                    cout << "Nepavyko nuskaityti duomenu is failo." << endl;
                }
                break;
            }
            case 4: {
                // Baigti programa
                cout << "Geros dienos!" << endl;
                return 0;
            }
        }

        cout << "\nAr norite testi programos darba? (1 - taip, 2 - ne): ";
        int testi = ivestiSkaiciu("", 1, 2);
        if (testi == 2)
        {
            cout << "Geros dienos!" << endl;
            break;
        }

        // Isvaloma grupe naujam ciklui
        Grupe.clear();
    }
    return 0;
}
