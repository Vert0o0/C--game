#include <iostream>
using namespace std;

int main(){
    int postava, souhlas = 2;
    cout << "Vy otevirate oci. Pred vasima ocima vidite bily strop a spinave steny" << endl;
    cout << "Vy se zvedate, a pomalu zkoumate ocima okoli. Jasnejsi? Sotva" << endl;
    cout << "Tichymi kroky se priblizujete ke stolu. Na stole lezi 4 slozky s dokumenty. Na prvni pohled vypadaji stejne" << endl;
    do {
    cout << "Jakou slozku vezmete do ruky?" << endl;
    cin >> postava;

<<<<<<< HEAD

=======
>>>>>>> cbb19ff47678e9cdd6c01958c04ccbbb6846b415
    switch (postava) {
    case 1:
        cout << "Vase diagnoza: schizofrenie" << endl;
        cout << endl;
        cout << "Jmeno: Daniel Paul Schreber" << endl;
        cout << "Body vedomi: 75/75" << endl;
        cout << "Sila vule: 55/55" << endl;
        cout << "Trpelivost: 40" << endl;
        cout << "Potencial: 60" << endl;
        cout << "Zkusenosti: 0" << endl;
        cout << "Agresivita: 45" << endl;
        cout << "Presvedcivost: 65" << endl;
<<<<<<< HEAD
        cout << "Pomalu vam zacina dochazet, kde se nachazite" << endl;
        cout << "Privlastnit si tuto slozku? ano - 1, ne - 0" << endl;
        cin >> souhlas;

=======
>>>>>>> cbb19ff47678e9cdd6c01958c04ccbbb6846b415
        break;
        
    case 2:
        cout << "Vase diagnoza: Bipolarni afektivni porucha (BAP)" << endl;
        cout << endl;
        cout << "Jmeno: Virginia Woolf" << endl;
        cout << "Body vedomi: 70/70" << endl;
        cout << "Sila vule: 60/60" << endl;
        cout << "Trpelivost: 40" << endl;
        cout << "Potencial: 60" << endl;
        cout << "Zkusenosti: 0" << endl;
        cout << "Agresivita: 55" << endl;
        cout << "Presvedcivost: 55" << endl;
<<<<<<< HEAD
        cout << "Pomalu vam zacina dochazet, kde se nachazite" << endl;
        cout << "Privlastnit si tuto slozku? ano - 1, ne - 0" << endl;
        cin >> souhlas;
=======
>>>>>>> cbb19ff47678e9cdd6c01958c04ccbbb6846b415
        break;
        
    case 3:
        cout << "Vase diagnoza: Tezka depresivni porucha" << endl;
        cout << endl;
        cout << "Jmeno: Esther Greenwood" << endl;
        cout << "Body vedomi: 65/65" << endl;
        cout << "Sila vule: 4040" << endl;
        cout << "Trpelivost: 60" << endl;
        cout << "Potencial: 60" << endl;
        cout << "Zkusenosti: 0" << endl;
        cout << "Agresivita: 35" << endl;
        cout << "Presvedcivost: 80" << endl;
<<<<<<< HEAD
        cout << "Pomalu vam zacina dochazet, kde se nachazite" << endl;
        cout << "Privlastnit si tuto slozku? ano - 1, ne - 0" << endl;
        cin >> souhlas;
=======
>>>>>>> cbb19ff47678e9cdd6c01958c04ccbbb6846b415
        break;
        
    case 4:
<<<<<<< HEAD
        cout << "Vase diagnoza: Disociativní porucha identity (DID)" << endl;
=======
        cout << "Vase diagnoza: DisociativnÃ­ porucha identity (DID)" << endl;
>>>>>>> cbb19ff47678e9cdd6c01958c04ccbbb6846b415
        cout << endl;
        cout << "Jmeno: Tyler Durden" << endl;
        cout << "Body vedomi: 50/50" << endl;
        cout << "Sila vule: 70/70" << endl;
        cout << "Trpelivost: 30" << endl;
        cout << "Potencial: 60" << endl;
        cout << "Zkusenosti: 0" << endl;
        cout << "Agresivita: 60" << endl;
        cout << "Presvedcivost: 70" << endl;
<<<<<<< HEAD
        cout << "Pomalu vam zacina dochazet, kde se nachazite" << endl;
        cout << "Privlastnit si tuto slozku? ano - 1, ne - 0" << endl;
        cin >> souhlas;
        break;
    default:
        cout << "Takova slozka k dispozici neni, vyberte si jinou" << endl;
        break;
    }

=======
        break;
    }

    cout << "Pomalu vam zacina dochazet, kde se nachazite" << endl;
    cout << "Privlastnit si tuto slozku? ano - 1, ne - 0" << endl;
    cin >> souhlas;
>>>>>>> cbb19ff47678e9cdd6c01958c04ccbbb6846b415
    }while (souhlas != 1);

}
