#include <iostream>
#include <vector>
#include <thread>
#include <random>
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

    int agresivita_upgrady;
    int presvedcivost_upgrady;

    Character(string d, string j, int mbv, int sv, int a, int pr, vector<Schopnost> sch)
        : diagnoza(d), jmeno(j), max_vedomi(mbv), vedomi(mbv), max_vule(sv), vule(sv),
          agresivita(a), presvedcivost(pr), schopnosti(sch) {
        agresivita_upgrady = 4;
        presvedcivost_upgrady = 4;
    }

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
        if (vedomi < 0) vedomi = 0;
        cout << "Blahoreju, " << jmeno << ", dostali jste ranu! Zbyle body vedomi: " << vedomi << endl;
    }

    bool zije() {
        return vedomi > 0;
    }

    void vypisBojInfo() {
        cout << "\n=== " << jmeno << " ===\n";
        cout << "Vedomi: " << vedomi << "/" << max_vedomi << endl;
        cout << "Vule: " << vule << "/" << max_vule << endl;
        cout << "Agresivita: " << agresivita << endl;
        cout << "Presvedcivost: " << presvedcivost << endl;
        cout << "==================\n";
    }

    void vypisSchopnosti() {
        cout << "\nVase schopnosti:\n";
        for (int i = 0; i < schopnosti.size(); i++) {
            cout << (i + 1) << ". " << schopnosti[i].schopnost << " (cena: " << schopnosti[i].potrebna_vule << ")\n";
        }
    }

    bool ZastraseniPsychiatric_orderly() {
        return agresivita >= 85;
    }

    bool PremluveniPsychiatra() {
        return presvedcivost >= 85;
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

    void rana(int zraneni) {
        vedomi -= zraneni;
        if (vedomi < 0) vedomi = 0;
    }

    bool zije() {
        return vedomi > 0;
    }

    void snizNeduverivost(int hodnota) {
        neduverivost -= hodnota;
        if (neduverivost < 0) neduverivost = 0;
    }

    bool jePremluveny() {
        return neduverivost <= 10;
    }
};

int nahodne(int min, int max) {
    return rand() % (max - min + 1) + min;
}

Enemy vytvorLoony(int cislo) {
    int vedomi = nahodne(12, 22);
    int sila = nahodne(5, 8);
    int nakazlivost = nahodne(4, 10);
    int neduverivost = nahodne(25, 45);

    return Enemy("\nLoony", "Loony " + to_string(cislo), vedomi, sila, nakazlivost, neduverivost);
}

Enemy vytvorPsychiatric_orderly(int cislo) {
    int vedomi = nahodne(25, 40);
    int sila = nahodne(10, 15);
    int nakazlivost = 0;
    int neduverivost = nahodne(20, 35);

    return Enemy("\nPsychiatric_orderly", "Psychiatric_orderly " + to_string(cislo), vedomi, sila, nakazlivost, neduverivost);
}

Enemy vytvorPsychiatra(int cislo) {
    int vedomi = nahodne(20, 30);
    int sila = nahodne(3, 6);
    int nakazlivost = 0;
    int neduverivost = nahodne(35, 55);

    return Enemy("\nPsychiatr", "Psychiatr " + to_string(cislo), vedomi, sila, nakazlivost, neduverivost);
}

void checkpoint(Character& hrac) {
    if (hrac.vule < 8) {
        cout << "Nemate dostatek vule pro checkpoint (potreba 8).\n";
        return;
    }

    cout << "\n=== CHECKPOINT ===\n";
    cout << "Aktualni vule: " << hrac.vule << "/" << hrac.max_vule << "\n";
    cout << "Aktualni vedomi: " << hrac.vedomi << "/" << hrac.max_vedomi << "\n";
    cout << "1. Zvysit agresivitu (+12, cena: 18) - zbyva: " << hrac.agresivita_upgrady << "\n";
    cout << "2. Zvysit presvedcivost (+12, cena: 18) - zbyva: " << hrac.presvedcivost_upgrady << "\n";
    cout << "3. Obnovit vedomi (cena: 8)\n";
    cout << "4. Obnovit vuli (cena: 10)\n";
    cout << "0. Pokracovat\n";

    int volba;
    cout << "Vyberte (0-4): ";
    cin >> volba;

    switch (volba) {
        case 1:
            if (hrac.agresivita_upgrady > 0 && hrac.vule >= 18) {
                hrac.agresivita += 12;
                hrac.vule -= 18;
                hrac.agresivita_upgrady--;
                cout << "Agresivita zvysena!\n";
            } else {
                cout << "Mas smulu, neni cas ztracet cas!!\n";
            }
            break;

        case 2:
            if (hrac.presvedcivost_upgrady > 0 && hrac.vule >= 18) {
                hrac.presvedcivost += 12;
                hrac.vule -= 18;
                hrac.presvedcivost_upgrady--;
                cout << "Presvedcivost zvysena!\n";
            } else {
                cout << "Mas smulu, neni cas ztracet cas!!\n";
            }
            break;

        case 3:
            if (hrac.vule >= 8) {
                hrac.vedomi = hrac.max_vedomi;
                hrac.vule -= 8;
                cout << "Vedomi obnoveno!\n";
            } else {
                cout << "Mas smulu, neni cas ztracet cas!!\n";
            }
            break;

        case 4:
            if (hrac.vule >= 10) {
                hrac.vule = hrac.max_vule;
                hrac.vule -= 10;
                cout << "Vule obnovena!\n";
            } else {
                cout << "Mas smulu, neni cas ztracet cas!!\n";
            }
            break;

        case 0:
            cout << "Pokracujete...\n";
            break;

        default:
            cout << "Mas smulu, neni cas ztracet cas!!\n";
            break;
    }

    sleep_for(seconds(2));
}

bool zkusUhnout(Character& hrac, Enemy& nepritel) {
    if (nepritel.klass == "\nPsychiatric_orderly" && hrac.ZastraseniPsychiatric_orderly()) {
        cout << "Zastrasili jste pracovnika lecebnice svoji agresi!\n";
        hrac.presvedcivost += 3;
        hrac.vule += 5;
        if (hrac.vule > hrac.max_vule) hrac.vule = hrac.max_vule;
        return true;
    }

    if (nepritel.klass == "\nPsychiatr" && hrac.PremluveniPsychiatra()) {
        cout << "Presvedcili jste psychiatra, ze jste normalni!\n";
        hrac.agresivita += 3;
        hrac.vule += 5;
        if (hrac.vule > hrac.max_vule) hrac.vule = hrac.max_vule;
        return true;
    }

    return false;
}

void boj(Character& hrac, vector<Enemy>& nepratele) {
    cout << "\n=== ZACINA BOJ ===\n";
    cout << "Setkavate se s neprateli:\n";
    for (int i = 0; i < nepratele.size(); i++) {
        cout << "- " << nepratele[i].jmeno << "\n";
    }

    if (nepratele.size() == 1 && zkusUhnout(hrac, nepratele[0])) {
        return;
    }

    int pouzita_prvni = 0;
    int pouzita_druha = 0;
    int pouzita_treti = 0;

    while (hrac.zije()) {
        bool nekdo_zivy = false;
        for (int i = 0; i < nepratele.size(); i++) {
            if (nepratele[i].zije()) {
                nekdo_zivy = true;
                break;
            }
        }
        if (!nekdo_zivy) break;

        cout << "\n--- VAS TAH ---\n";
        hrac.vypisBojInfo();

        for (int i = 0; i < nepratele.size(); i++) {
            if (nepratele[i].zije() && nepratele[i].klass == "\nLoony") {
                int dmg = nahodne(1, nepratele[i].nakazlivost);
                cout << nepratele[i].jmeno << " vas nakazuje jenom svoji pritomnosti! -" << dmg << " vedomi\n";
                hrac.rana(dmg);
            }
        }

        if (!hrac.zije()) break;

        bool platny_tah = false;
        while (!platny_tah) {
            hrac.vypisSchopnosti();
            cout << "Vyberte schopnost (1-" << hrac.schopnosti.size() << "): ";

            int volba_schopnosti;
            cin >> volba_schopnosti;

            if (volba_schopnosti < 1 || volba_schopnosti > hrac.schopnosti.size()) {
                cout << "Spatna volba!\n";
                continue;
            }

            Schopnost& schopnost = hrac.schopnosti[volba_schopnosti - 1];

            if (hrac.vule < schopnost.potrebna_vule) {
                cout << "Malo vule!\n";
                continue;
            }

            hrac.vule -= schopnost.potrebna_vule;
            cout << "Pouzivate: " << schopnost.schopnost << "!\n";

            switch (volba_schopnosti) {
                case 1:
                    pouzita_prvni++;
                    break;
                case 2:
                    pouzita_druha++;
                    break;
                case 3:
                    pouzita_treti++;
                    break;
                default:
                    break;
            }

            vector<int> zivi_nepratele;
            for (int i = 0; i < nepratele.size(); i++) {
                if (nepratele[i].zije()) {
                    zivi_nepratele.push_back(i);
                }
            }

            bool platny_cil = false;
            while (!platny_cil) {
                cout << "Vyberte cil:\n";
                for (int i = 0; i < zivi_nepratele.size(); i++) {
                    cout << (i + 1) << ". " << nepratele[zivi_nepratele[i]].jmeno << "\n";
                }

                int volba_cile;
                cin >> volba_cile;

                if (volba_cile < 1 || volba_cile > zivi_nepratele.size()) {
                    cout << "Spatny cil!\n";
                    continue;
                }

                Enemy& cil = nepratele[zivi_nepratele[volba_cile - 1]];

                if (schopnost.zmena_vedomi < 0) {
                    int dmg = abs(schopnost.zmena_vedomi) + nahodne(-3, 3);
                    if (dmg < 0) dmg = 0;
                    cil.rana(dmg);
                    cout << cil.jmeno << " dostal " << dmg << " poskozeni!\n";
                    if (!cil.zije()) {
                        cout << cil.jmeno << " je porazen!\n";
                    }
                }

                if (schopnost.zmena_neduvery < 0) {
                    int snizeni = abs(schopnost.zmena_neduvery);
                    cil.snizNeduverivost(snizeni);
                    cout << "Neduvera snizena!\n";
                    if (cil.jePremluveny()) {
                        cout << cil.jmeno << " se vzdava!\n";
                        cil.vedomi = 0;
                    }
                }

                platny_cil = true;
            }
            platny_tah = true;
        }

        sleep_for(seconds(2));

        cout << "\n--- TAH NEPRATELU ---\n";
        for (int i = 0; i < nepratele.size(); i++) {
            if (nepratele[i].zije()) {
                int dmg = nepratele[i].sila + nahodne(-1, 1);
                if (dmg < 1) dmg = 1;
                cout << nepratele[i].jmeno << " utoci -" << dmg << " body vedomi!\n";
                hrac.rana(dmg);
                if (!hrac.zije()) break;
            }
        }

        sleep_for(seconds(2));
    }

    if (hrac.zije()) {
        cout << "\n=== VITEZSTVI ===\n";
        cout << "Porazili jste vsechny nepratele!\n";

        if (pouzita_prvni > pouzita_druha && pouzita_prvni > pouzita_treti) {
            int bonus = nahodne(3, 6);
            hrac.agresivita += bonus;
            cout << "Agresivita +" << bonus << "! (za castejsi pouziti prvni schopnosti)\n";
        } else if (pouzita_druha > pouzita_prvni && pouzita_druha > pouzita_treti) {
            int bonus = nahodne(3, 7);
            hrac.presvedcivost += bonus;
            cout << "Presvedcivost +" << bonus << "! (za castejsi pouziti druhe schopnosti)\n";
        } else {
            if (nahodne(1, 2) == 1) {
                int bonus = nahodne(2, 8);
                hrac.agresivita += bonus;
                cout << "Agresivita +" << bonus << "!\n";
            } else {
                int bonus = nahodne(2, 9);
                hrac.presvedcivost += bonus;
                cout << "Presvedcivost +" << bonus << "!\n";
            }
        }
        int vedomi_bonus = nahodne(7, 15);
        hrac.max_vedomi += vedomi_bonus;
        cout << "Max vedomi +" << vedomi_bonus << "!\n";

        int vule_bonus = nahodne(3, 14);
        hrac.max_vule += vule_bonus;
        cout << "Max vule +" << vule_bonus << "!\n";

        int obnoveni = nahodne(6, 12);
        hrac.vule += obnoveni;
        if (hrac.vule > hrac.max_vule) hrac.vule = hrac.max_vule;
        cout << "Obnoveno " << obnoveni << " vule.\n";

    } else {
        cout << "\n=== PROHRA ===\n";
        cout << "Byli jste porazeni!\n";
        cout << "KONEC HRY\n";
        exit(0);
    }
}

int main(){
    srand(time(0));

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
        Schopnost("Dvojity utok", 20, -25, -15),
        Schopnost("Deziorientace", 10, 0, -20),
        Schopnost("Beznadeje..", 0, 0, 0)
    };

    vector<Character> characters {
            Character("\nSchizofrenie", "Daniel Paul Schreber", 75, 70, 45, 65, schreberSchopnosti),
            Character("\nBipolarni afektivni porucha (BAP)", "Virginia Woolf", 70, 70, 50, 65, woolfSchopnosti),
            Character("\nTezka depresivni porucha", "Esther Greenwood", 65, 65, 50, 75, greenwoodSchopnosti),
            Character("\nDisociativni porucha identity (DID)", "Tyler Durden", 50, 60, 60, 75, durdenSchopnosti)
    };

    vector<Enemy> Enemies {
            Enemy("\nPsychiatric_orderly", "1/1", 65, 30, 0, 60),
            Enemy("\nPsychiatr", "1/2", 50, 5, 0, 60),
            Enemy("\nLoony", "1/3", 35, 15, 25, 80),
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
            characters[postava - 1].vypis();
            cout << "Privlastnit si tuto slozku? ano - 1, ne - 0\n";
            cin >> souhlas;
        } else {
            cout << "Takova slozka k dispozici neni... vyberte si jinou...\n";
        }
    }while (souhlas != 1);

    cout << "Zvlastni cisla a terminy...\n";
    sleep_for(seconds(2));
    cout << "Pomalu vam zacina dochazet, kde se nachazite...\n\n";
    sleep_for(seconds(2));

    Character& hrac = characters[postava-1];

    cout << "\n" << string(30, '=') << "\n";
    cout << "SETKANI 1\n";
    cout << string(30, '=') << "\n";

    vector<Enemy> nepratele1;
    nepratele1.push_back(vytvorLoony(1));
    boj(hrac, nepratele1);

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 2\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele2;
        nepratele2.push_back(vytvorLoony(2));
        boj(hrac, nepratele2);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 3\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele3;
        nepratele3.push_back(vytvorLoony(3));
        boj(hrac, nepratele3);
    }

    if (hrac.zije()) {
        cout << "\n--- CHECKPOINT ---\n";
        checkpoint(hrac);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 4\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele4;
        nepratele4.push_back(vytvorPsychiatric_orderly(1));
        boj(hrac, nepratele4);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 5\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele5;
        nepratele5.push_back(vytvorLoony(4));
        boj(hrac, nepratele5);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 6\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele6;
        nepratele6.push_back(vytvorPsychiatra(1));
        boj(hrac, nepratele6);
    }


    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 7\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele7;
        nepratele7.push_back(vytvorPsychiatra(2));
        boj(hrac, nepratele7);
    }


    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 8\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele8;
        nepratele8.push_back(vytvorLoony(5));
        boj(hrac, nepratele8);
    }

    if (hrac.zije()) {
        cout << "\n--- CHECKPOINT ---\n";
        checkpoint(hrac);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 9 - DVA PSYCHOVE!\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele9;
        nepratele9.push_back(vytvorLoony(6));
        nepratele9.push_back(vytvorLoony(7));
        boj(hrac, nepratele9);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 10\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele10;
        nepratele10.push_back(vytvorLoony(8));
        boj(hrac, nepratele10);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 11\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele11;
        nepratele11.push_back(vytvorPsychiatric_orderly(2));
        boj(hrac, nepratele11);
    }



    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 12\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele12;
        nepratele12.push_back(vytvorLoony(9));
        boj(hrac, nepratele12);
    }


    if (hrac.zije()) {
        cout << "\n--- CHECKPOINT ---\n";
        checkpoint(hrac);

    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 13\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele13;
        nepratele13.push_back(vytvorLoony(10));
        boj(hrac, nepratele13);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 14\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele14;
        nepratele14.push_back(vytvorPsychiatric_orderly(3));
        boj(hrac, nepratele14);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 15\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele15;
        nepratele15.push_back(vytvorLoony(11));
        boj(hrac, nepratele15);
    }

    if (hrac.zije()) {
        cout << "\n--- CHECKPOINT ---\n";
        checkpoint(hrac);
    }


    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 16 - TRI PSYCHOVE!\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele16;
        nepratele16.push_back(vytvorLoony(12));
        nepratele16.push_back(vytvorLoony(13));
        nepratele16.push_back(vytvorLoony(14));
        boj(hrac, nepratele16);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 17\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele17;
        nepratele17.push_back(vytvorLoony(15));
        boj(hrac, nepratele17);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 18\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele18;
        nepratele18.push_back(vytvorLoony(16));
        boj(hrac, nepratele18);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 19\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele19;
        nepratele19.push_back(vytvorPsychiatric_orderly(4));
        boj(hrac, nepratele19);
    }


    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 20\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele20;
        nepratele20.push_back(vytvorPsychiatric_orderly(5));
        boj(hrac, nepratele20);
    }

    if (hrac.zije()) {
        cout << "\n" << string(30, '=') << "\n";
        cout << "SETKANI 21\n";
        cout << string(30, '=') << "\n";
        vector<Enemy> nepratele21;
        nepratele21.push_back(vytvorPsychiatra(3));
        boj(hrac, nepratele21);
    }

    if (hrac.zije()) {
        cout << "\n" << string(50, '=') << "\n";
        cout << "GRATULUJEME! DOKONCILI JSTE VSECHNY BOJE A DOSTALI SE Z LECEBNY!\n";
        cout << "16 psychu + 5 sanitaru/psychiatru = 21 boju celkem\n";
        cout << string(50, '=') << "\n";
        hrac.vypis();
    }

    return 0;
}
