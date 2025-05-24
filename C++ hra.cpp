#include <iostream>
#include <vector>
#include <thread>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

class Schopnost {
public:
    string schopnost;
    int potrebna_vule;
    int zmena_vedomi;
    int zmena_neduvery;

    Schopnost(string sch, int pv, int zve, int zne)
        : schopnost(sch), potrebna_vule(pv), zmena_vedomi(zve), zmena_neduvery(zne) {}
};

class Character {
public:
    string diagnoza;
    string jmeno;
    int max_vedomi;
    int vedomi;
    int max_vule;
    int vule;
    int agresivita;
    int presvedcivost;
    vector<Schopnost> schopnosti;

    Character(string d, string j, int mbv, int sv, int a, int pr, vector<Schopnost> sch)
        : diagnoza(d), jmeno(j), max_vedomi(mbv), vedomi(mbv), max_vule(sv), vule(sv),
          agresivita(a), presvedcivost(pr), schopnosti(sch) {}

    void vypis() {
        cout << "\n=== " << jmeno << " ===\n";
        cout << "Diagnoza: " << diagnoza << endl;
        cout << "Vedomi: " << vedomi << "/" << max_vedomi << endl;
        cout << "Vule: " << vule << "/" << max_vule << endl;
        cout << "Agresivita: " << agresivita << endl;
        cout << "Presvedcivost: " << presvedcivost << endl;

        cout << "\nSchopnosti:\n";
        for (int i = 0; i < schopnosti.size(); i++) {
            cout << "  " << schopnosti[i].schopnost << endl;
            cout << "  Cena vule: " << schopnosti[i].potrebna_vule << endl;
            cout << "  Priblizni zmena vedomi cile vlivu: " << schopnosti[i].zmena_vedomi << endl;
            cout << "  Priblizni zmena neduvery cile vlivu: " << schopnosti[i].zmena_neduvery << "\n\n";
        }
        cout << "==================\n";
    }

    void rana(int zraneni) {
        vedomi -= zraneni;
        cout << "Blahoreju, " << jmeno << ", dostali jste ranu! Zbyle body vedomi: " << vedomi << endl;
}
};

class Enemy {
public:
    string klass;
    string jmeno;
    int vedomi;
    int sila;
    int nakazlivost;
    int neduverivost;


    Enemy(string k, string j, int v, int s, int n, int ne)
        : klass(k), jmeno(j), vedomi(v), sila(s), nakazlivost(n), neduverivost(ne) {}

};

int main(){

    vector<Schopnost> schreberSchopnosti = {
        Schopnost("Halucinace", 12, -20, 0),
        Schopnost("Paranoia", 8, 0, -20),
        Schopnost("Beznadeje..", 0, 0, 0)

    };
    vector<Schopnost> woolfSchopnosti = {
        Schopnost("Maniakalni faze", 15, -25, 0),
        Schopnost("Manipulace", 10, 0, -20),
        Schopnost("Beznadeje..", 0, 0, 0)

    };

    vector<Schopnost> greenwoodSchopnosti = {
        Schopnost("Sebevrazedny utok", 15, -20, 0),
        Schopnost("Nakazlivy smutek", 5, 0, -20),
        Schopnost("Beznadeje..", 0, 0, 0)

    };

    vector<Schopnost> durdenSchopnosti = {
        Schopnost("Dvojity utok", 30, -25, -15),
        Schopnost("Deziorientace", 10, 0, -20),
        Schopnost("Beznadeje..", 0, 0, 0)

    };


    vector<Character> characters {
            Character("\nSchizofrenie", "Daniel Paul Schreber", 75, 55, 45, 65, schreberSchopnosti),
            Character("\nBipolarni afektivni porucha (BAP)", "Virginia Woolf", 70, 65, 50, 55, woolfSchopnosti),
            Character("\nTezka depresivni porucha", "Esther Greenwood", 65, 60, 35, 80, greenwoodSchopnosti),
            Character("\nDisociativni porucha identity (DID)", "Tyler Durden", 50, 60, 60, 70, durdenSchopnosti)
    };

    vector<Enemy> Enemies {
            Enemy("\nPsychiatric_orderly", "Patric", 65, 30, 0, 60),
            Enemy("\nPsychiatr", "Jean Delay", 50, 5, 0, 60),
            Enemy("\nLoony", "Linuxofil", 35, 15, 25, 80),
    };

    int postava, souhlas = 2;
        cout << "Vy otevirate oci... Pred vasima ocima vidite bily strop a spinave steny...\n";
        sleep_for(seconds(2));
        cout << "Vy se zvedate, a pomalu zkoumate ocima okoli... Jasnejsi? Sotva...\n";
        sleep_for(seconds(2));
        cout << "Tichymi kroky se priblizujete ke stolu... Na stole lezi 4 slozky s dokumenty... Na prvni pohled vypadaji stejne...\n";
        sleep_for(seconds(2));
    do {
        cout << "Jakou slozku vezmete do ruky? (1-4): ";
        cin >> postava;
        cout << endl;

    if (postava >= 1 && postava <= 4) {
            characters[postava - 1].vypis(); // napověda od taty-programatora. v poli čislovani začina od 0, takže 1 = 2, timpadem 1 = 2-1
            cout << "Privlastnit si tuto slozku? ano - 1, ne - 0\n";
            cin >> souhlas;
        } else {
            cout << "Takova slozka k dispozici neni... vyberte si jinou...\n";
        }
    }while (souhlas != 1);
    cout << "Zvlastni cisla a terminy...\n";
    sleep_for(seconds(2));
    cout << "Pomalu vam zacina dochazet, kde se nachazite...\n";

    characters[postava-1].rana(20); // testovani toho, jak pracovat s funkcemi při použivani classu

}

