#include <iostream>
using namespace std;

int main(){
    int postava, souhlas = 2;
    cout << "Vitejte na zacatku hry! Na zacatek si vyberte postavu: " << endl;
    cout << endl;
    cout << "Warlock - 1, Elf - 2, Alchemista - 3, Valecnik - 4" << endl;
    do {
    cout << "Zadejze cisolo postavy, kterou chcete zvolit:" << endl;
    cin >> postava;

        
    switch (postava) {
    case 1:
        cout << "Vase class: warlock" << endl;
        cout << endl;
        cout << "Statistiky vase postavy jsou: " << endl;
        cout << "Zivot - 2/2" << endl;
        cout << "Utok - 4" << endl;
        cout << "Mana - 7/7" << endl;

        break;
    case 2:
        cout << "Vase class: elf" << endl;
        cout << endl;
        cout << "Statistiky vase postavy jsou: " << endl;
        cout << "Zivot - 3/3" << endl;
        cout << "Utok - 5" << endl;
        cout << "Mana - 5/5" << endl;
        break;
    case 3:
        cout << "Vase class: alchemista" << endl;
        cout << endl;
        cout << "Statistiky vase postavy jsou: " << endl;
        cout << "Zivot - 3/3" << endl;
        cout << "Utok - 4" << endl;
        cout << "Mana - 6/6" << endl;
        break;
    case 4:
        cout << "Vase class: valecnik" << endl;
        cout << endl;
        cout << "Statistiky vase postavy jsou: " << endl;
        cout << "Zivot - 5/5" << endl;
        cout << "Utok - 6" << endl;
        cout << "Mana - 2/2" << endl;
        break;
    }


    cout << "Jste spokojeny se svoji volbou? ano - 1, ne - 0" << endl;
    cin >> souhlas;
    }while (souhlas != 1);

}
