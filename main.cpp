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

struct Studentas
{
    string vardas;
    string pavarde;
    vector <int> ndpazymiai;
    int egzrezultatas;
    double galutinis;

};

Studentas Stud_ivestis()
{
    int n, laikinas_paz, sum = 0;
    Studentas pirmas;
    cout << "Iveskite duomenis" << endl;
    cout << "Vardas: ";
    cin >> pirmas.vardas;
    cout << "Pavarde: ";
    cin >> pirmas.pavarde;
    cout << "Kiek namu darbu pazymiu turi " << pirmas.vardas << " " << pirmas.pavarde << "? ";
    cin >> n;

    for (int a = 0; a < n; a++)
    {
        cout << a + 1 << ": ";
        cin >> laikinas_paz;
        pirmas.ndpazymiai.push_back(laikinas_paz);
        sum += laikinas_paz;
    }

    cout << "Iveskite egzamino rezultata: ";
    cin >> pirmas.egzrezultatas;
    pirmas.galutinis = double(sum) / double(n) * 0.4 + pirmas.egzrezultatas * 0.6;
    return pirmas;
}

int main()
{
    cout << "Laba diena" << endl;
    vector<Studentas> Grupe;
    cout << "Kiek studentu grupeje?: ";
    int m;
    cin >> m;

    for (auto z = 0; z < m; z++)
    {
        Grupe.push_back(Stud_ivestis());
    }

    cout << "\nStudento informacija:" << endl;

    return 0;
}
