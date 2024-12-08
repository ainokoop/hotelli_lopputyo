

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cctype>
#include <vector>
#include <fstream>

using namespace std;

struct Varaaja
{
    string nimi;
    int yomaara;
    int loppusumma;
    int varausnumero;
    int huonenumero;
};

// alla syötteen tarkistus nimelle
bool nimitarkistus(const string& nimi) {
    for (unsigned int i = 0; i < nimi.length(); ++i) {
    char merkki = nimi[i];
        if (!isalpha(merkki) && !isspace(merkki)) {
            return false;
        }
    }
    return true;
}

//huoneen varauksen tarkistus
bool onkovarattu (int huonenumero, const vector<Varaaja>& varaukset) {
   for (vector<Varaaja>::const_iterator it = varaukset.begin(); it != varaukset.end(); ++it) {
    if (it->huonenumero == huonenumero){
            return true; // Huone on jo varattu
        }
    }
    return false; // Huone ei ole varattu
}

int main ()

{

  srand((unsigned) time(0)); 

const int huonemaara = 30 +rand() %41;
const int hinta = 80 +rand() %21;
vector<int> huoneet;
vector<Varaaja> varaukset;

for (int i=1; i<=huonemaara; ++i) {
    huoneet.push_back(i);
}

while (!huoneet.empty()) {

Varaaja tiedot;
bool virhe;

do {
virhe=false;
cout <<"Hei. Hotellissamme on " << huoneet.size() << " vapaata huonetta. ";
cout <<"Huoneen hinta on " << hinta << "euroa/yö. ";
cout <<"Jos haluat varata huoneen, kirjoita alle haluttujen öiden määrä";
cin >> tiedot.yomaara;

if(cin.fail()) {
    cout << "Jos haluat varata hotellihuoneen, ilmoita kokonaislukuina haluttu yömäärä!" << endl;
    virhe=true;
    cin.clear();
    cin.ignore(80, '\n');
    }
} while (virhe);

tiedot.loppusumma = (hinta*tiedot.yomaara);

int arvottuhuone;
do {
    arvottuhuone = rand()% huoneet.size();
} while (onkovarattu(huoneet[arvottuhuone], varaukset));

tiedot.huonenumero = huoneet[arvottuhuone];
huoneet.erase(huoneet.begin() + arvottuhuone);

tiedot.varausnumero = 1000 + rand() % 89999;

cout <<"Kiitos varauksesta! Teille on varattu huone ";
cout << tiedot.huonenumero << ". Varauksen loppusumma on ";
cout << tiedot.loppusumma << " euroa. Millä nimellä huone varataan?";

string nimi;
bool oikeanimi;

do
{
    cin.ignore(); //tyhjentää tässä välissä puskuriin jääneen välilyönnin, joka jää cin>>yomaara jälkeen
    getline(cin, tiedot.nimi);
    if(nimitarkistus(tiedot.nimi)) {
    oikeanimi=true;
    } else {
        cout <<"Kirjoitithan nimen oikein? Sen tulee sisältää vain kirjaimia ja välilyöntejä.";
        oikeanimi=false; 
    }
} while (!oikeanimi);

cout << " Hotellihuone on varattu nimellä " << tiedot.nimi << endl;
int varausnumero= 10000 + rand() %89999;
cout << "Varausnumeronne on " << tiedot.varausnumero << endl;

varaukset.push_back(tiedot);

// tekstitiedosto, josta voi nähdä varatut huoneet ja niiden tiedot
ofstream myfile("/users/ainokoop/Desktop/varaustiedot.txt", ios::app); //ios:app tallentaa tekstitiedostoon realiaikaisesti
if (myfile.is_open()) {
    myfile << "Varaus " << varaukset.size() 
           << ": Huone " << tiedot.huonenumero
           << ", Nimi: " << tiedot.nimi
           << ", Yömäärä: " << tiedot.yomaara
           << ", Loppusumma: " << tiedot.loppusumma
           << ", Varausnumero: " << tiedot.varausnumero << "\n";
    myfile.close();
} else {
    cout << "Virhe: tiedostoa ei voitu avata kirjoittamista varten.\n";
}

if (!huoneet.empty()) {
    cout << "Haluatko tehdä uuden varauksen?" << endl;
} else {
    cout <<"Hotellimme on täynnä, uutta varausta ei voi tehdä. Pahoittelut!" << endl;
    }   

} 

 return 0;

}
