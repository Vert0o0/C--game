#include <iostream>
#include <vector>
#include <thread>
using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

class Character {
public:
    string diagnoza;
    string jmeno;
    int max_vedomi;
    int vedomi;
    int max_vule;
    int vule;
    int trpelivost;
    int potencial;
    int zkusenosti;
    int agresivita;
    int presvedcivost;

    Character(string d, string j, int mbv, int sv, int t, int p, int z, int a, int pr)
        : diagnoza(d), jmeno(j), max_vedomi(mbv), vedomi(mbv), max_vule(sv), vule(sv),
          trpelivost(t), potencial(p), zkusenosti(z), agresivita(a), presvedcivost(pr) {}

    void vypis() {
        cout << "Vase diagnoza: " << diagnoza << endl << endl;
        cout << "Jmeno: " << jmeno << endl;
        cout << "Body vedomi: " << vedomi << "/" << max_vedomi << endl;
        cout << "Sila vule: " << vule << "/" << max_vule << endl;
        cout << "Trpelivost: " << trpelivost << endl;
        cout << "Potencial: " << potencial << endl;
        cout << "Zkusenosti: " << zkusenosti << endl;
        cout << "Agresivita: " << agresivita << endl;
        cout << "Presvedcivost: " << presvedcivost << endl;
        cout << "Pomalu vam zacina dochazet, kde se nachazite\n";
}


    void rana(int zraneni) {
        vedomi -= zraneni;
        cout << jmeno << " dostal ranu. Zbyle body vedomi: " << vedomi << endl;
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
    vector<Character> characters {
            Character("\nschizofrenie", "Daniel Paul Schreber", 75, 55, 40, 60, 0, 45, 65),
            Character("\nBipolarni afektivni porucha (BAP)", "Virginia Woolf", 70, 60, 40, 60, 0, 55, 55),
            Character("\nTezka depresivni porucha", "Esther Greenwood", 65, 40, 60, 60, 0, 35, 80),
            Character("\nDisociativni porucha identity (DID)", "Tyler Durden", 50, 70, 30, 60, 0, 60, 70)
    };

    vector<Enemy> Enemies {
            Enemy("\nPsychiatric_orderly", "Patric", 65, 30, 0, 60),
            Enemy("\nPsychiatr", "Jean Delay", 50, 5, 0, 60),
            Enemy("\nLoony", "Linuxofil", 35, 15, 25, 80),
    };

    int postava, souhlas = 2;
        cout << "Vy otevirate oci. Pred vasima ocima vidite bily strop a spinave steny\n";
        sleep_for(seconds(2));
        cout << "Vy se zvedate, a pomalu zkoumate ocima okoli. Jasnejsi? Sotva\n";
        sleep_for(seconds(2));
        cout << "Tichymi kroky se priblizujete ke stolu. Na stole lezi 4 slozky s dokumenty. Na prvni pohled vypadaji stejne\n";
        sleep_for(seconds(2));
    do {
        cout << "Jakou slozku vezmete do ruky? (1-4): ";
        sleep_for(seconds(2));
        cin >> postava;
        cout << endl;

    if (postava >= 1 && postava <= 4) {
            characters[postava - 1].vypis(); // napověda od taty-programatora. v poli čislovani začina od 0, takže 1 = 2, timpadem 1 = 2-1
            cout << "Privlastnit si tuto slozku? ano - 1, ne - 0\n";
            cin >> souhlas;
        } else {
            cout << "Takova slozka k dispozici neni, vyberte si jinou\n";
        }
    }while (souhlas != 1);

    characters[postava-1].rana(20); // testovani toho, jak pracovat s funkcemi při použivani classu

}
