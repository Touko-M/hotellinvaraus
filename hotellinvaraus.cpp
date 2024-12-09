#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  //Tuodaan tämä randomlukujen generointia varte
#include <ctime>    //satunnaislukugeneraattorin siemen alustetaan aikaan

using namespace std;

//rakennetaan yksittäinen huone
struct Huone {
    int numero; //Huoneen numero
    int koko; //1=yhden henkilön ja 2=kahden henkilön
    bool varattu; //jos tosi niin varattu ja jos epätosi niin vapaa
    int hinta; //paljonko huone maksaa yöltä
    string varaaja; //kuka varaa huoneen
    int varaus_numero; //luodaan randomisti varausnumero
    vector<string> lisapalvelut; //lista lisäpalveluista
};

//hotellin vakiot
const int min_huoneet = 40;     //vähintään 40 huonetta
const int max_huoneet = 300;    //enintään 300 huonetta
const int hinta_1hh = 100;      //yhden henkilö huoneen hinta 100
const int hinta_2hh = 150;      //kahden henkilön huoneen hinta 150

//Funktio alustaa huoneet random arvoilla
//&-merkki mahdollistaa alkuperäisen vektorin muokkaamisen kopioimisen sijaan
void alusta_huoneet(vector<Huone>& huoneet){
    srand(time(0)); //käytetään randomlukugeneraattorissa nykyaikaa
    //arvotaan huoneiden määrä välillä min ja max huoneet
    int huoneiden_maara = (rand() % (max_huoneet-min_huoneet+1))+min_huoneet;
    //alustetaan kaikki huoneet
    for(int i = 0; i < huoneiden_maara; i++){
        Huone uusi_huone; //Luodaan uusi huone
        uusi_huone.numero = i + 1; //huoneen numero
        //määritetään huoneen koko puolet yhden huoneen ja puolet kahden
        uusi_huone.koko=(i<huoneiden_maara/2)?1:2;
        //tehdään uudesta huoneesta vapaa
        uusi_huone.varattu = false;
        //määritetään huoneen hinta
        uusi_huone.hinta=(uusi_huone.koko == 1) ? hinta_1hh : hinta_2hh;
        uusi_huone.varaaja=""; //Varaajalle asetetaan tyhjä merkkijono, koska ei vielä varausta
        uusi_huone.varaus_numero=0; //Varausnumero asetetaan nollaksi
        huoneet.push_back(uusi_huone); //lisätään huone hotellin huoneiden listaan
    }

    
}
//Tehdään eeppinen valikko
void valikko()  {
    cout << " Tervetuloa Majatalo mahtavaan! " << endl;
    cout << "1. Näytä huoneet" << endl;
    cout << "2. Luo varaus" << endl;
    cout << "3. Katso omia varauksia" << endl;
    cout << "4. Osta lisäpalveluita varattuun huoneeseen" << endl;
    cout << "5. Soita pilapuhelu naapuriin" << endl;
    cout << "6. lopeta ohjelma" << endl;
    cout << "Valitse (1-6): ";
}

//Tulostetaan KAIKKI huoneet ja niiden informaatio
//"huoneet" on viite huonevektrooin jossa on kaikki huoneet
void tulosta_huoneet(const vector<Huone>& huoneet)  {
    cout << "Huoneet:" << endl;
    for (const Huone& h : huoneet) {
        cout << "Varaustilanne: " << (h.varattu ? "Varattu" : "Vapaa") << " / ";
        cout << "Huone #" << h.numero << " / ";
        cout << "Koko: " << (h.koko == 1 ? "1hh" : "2hh") << " / ";
        cout << "Hinta: " << h.hinta << " € / " << endl;
    }
}
//Tämä aliohjelma on huoneen varaamista varten
//"huoneet" viitataan taas huonevektoriin
void varaus(vector<Huone>& huoneet) {
    int huonenumero; //käyttäjän huonenumero
    string varaajan_nimi; 

    //kysytään käyttäjältä huonenumeron
    cout << "Anna varattavan huoneen numero kiitos: ";
    cin >> huonenumero;
    //tehdään tarkistus (onko huonenumero olemassa)
    if (huonenumero < 1 || huonenumero > huoneet.size()) {
        cout << "Virhe: Huonetta " << huonenumero << " Ei ole olemassa! Ethän vaan koita kaataa ohjelmaa??" << endl;
        return; //palataan, jos ei löydy
    }
    //Tarkistuksen jälkeen tehdään valittu huone
    Huone& valittu_huone = huoneet[huonenumero - 1];
    //Onko huone jo varattu?
    if (valittu_huone.varattu) {
        cout << "Huone #" << huonenumero << " on jo varattu!!" << endl;
        return; // palataan jos on jo varattu
    }
    //pyydetään käyttäjän nimi
    cin.ignore(); //Tyhjentää syötteen puskuriin jääneet merkit, jotta getline toimii
    cout << "Kirjoita varaajan nimi: ";
    getline(cin, varaajan_nimi); //luetaan koko rivi käyttäjältä

    // Alennuksen arvonta
    int alennus_prosentti = (rand() % 3) * 10; // Arvotaan alennus: 0 %, 10 %, tai 20 %
    double lopullinen_hinta = valittu_huone.hinta * (1.0 - alennus_prosentti / 100.0);

    // Päivitetään varauksen tiedot
    valittu_huone.varattu = true;
    valittu_huone.varaaja = varaajan_nimi;
    valittu_huone.varaus_numero = (rand() % 90000) + 10000;

    // Tallennetaan alennettu hinta huoneen hintaan
    valittu_huone.hinta = static_cast<int>(lopullinen_hinta);

    // Näytetään varauksen ja alennuksen tiedot
    cout << "Varasit huoneen onnistuneesti!" << endl;
    cout << "Huone #" << valittu_huone.numero << " on nyt " << varaajan_nimi << " varaama." << endl;
    cout << "Varausnumero: " << valittu_huone.varaus_numero << endl;
    cout << "Alennus: " << alennus_prosentti << "%." << endl;
    cout << "Lopullinen hinta alennuksen jälkeen: " << valittu_huone.hinta << " €." << endl;

    // Huomautukset varaukseen liittyen
    cout << "HUOM! Peruutuksen on tapahduttava viimeistään 24h ennen varattua huonetta." << endl;
    cout << "Saman vuorokauden aikana peruutetuista sekä peruuttamattomista huoneista" << endl;
    cout << "laskutamme 100 prosenttia huoneen hinnasta sekä lisäämme laskuun 5 euron laskutuslisän." << endl;
}
void ihaile_varauksia(vector<Huone>& huoneet) {
    string varaajan_nimi; // Varaajan nimi
    cin.ignore(); // Tyhjennetään syötteen puskuri getlinea varten
    cout << "Kirjoita varaajan nimi: ";
    getline(cin, varaajan_nimi); // Luetaan koko rivi
    bool loytyi_varauksia = false;

    cout << "Etsitään varauksiasi..." << endl;

    // Tarkistetaan kaikki huoneet
    for (const Huone& h : huoneet) {
        if (h.varattu && h.varaaja == varaajan_nimi) {
            // Jos huone on varattu ja varaaja on käyttäjän nimi
            cout << "Huone #" << h.numero
                 << " | Koko: " << (h.koko == 1 ? "1hh" : "2hh")
                 << " | Hinta: " << h.hinta << " €"
                 << " | Varausnumero: " << h.varaus_numero << endl;
            loytyi_varauksia = true; // Merkitään, että varauksia löytyi
        }
    }

    if (!loytyi_varauksia) {
        cout << "Emme löytäneet varauksia nimellä: " << varaajan_nimi << endl;
        return;
    }

    // Kysytään, haluaako käyttäjä poistaa jonkin varauksen
    char valinta;
    do {
        cout << "Haluatko poistaa jonkin varauksesi? (k/e): ";
        cin >> valinta;

        // Tarkistetaan, onko syöte hyväksyttävä
        if (valinta != 'k' && valinta != 'K' && valinta != 'e' && valinta != 'E') {
            cout << "Virheellinen valinta! Syötä 'k' (kyllä) tai 'e' (ei)." << endl;
        }
    } while (valinta != 'k' && valinta != 'K' && valinta != 'e' && valinta != 'E');

    if (valinta == 'k' || valinta == 'K') {
        int huonenumero;
        cout << "Anna poistettavan huoneen numero: ";
        cin >> huonenumero;

        // Tarkistetaan, onko huone olemassa
        if (huonenumero < 1 || huonenumero > huoneet.size()) {
            cout << "Virhe: Huonetta #" << huonenumero << " ei ole olemassa!" << endl;
            return;
        }

        // Viitataan valittuun huoneeseen
        Huone& valittu_huone = huoneet[huonenumero - 1];

        // Tarkistetaan, onko huone varattu ja onko varaaja oikea
        if (!valittu_huone.varattu || valittu_huone.varaaja != varaajan_nimi) {
            cout << "Varausta ei löydy valitsemallasi huoneella ja nimellä." << endl;
            return;
        }

        // Poistetaan varauksen tiedot
        valittu_huone.varattu = false;
        valittu_huone.varaaja = "";
        valittu_huone.varaus_numero = 0;
        valittu_huone.hinta = (valittu_huone.koko == 1) ? hinta_1hh : hinta_2hh;
        valittu_huone.lisapalvelut.clear(); // Tyhjennetään mahdolliset lisäpalvelut

        cout << "Varaus huoneesta #" << huonenumero << " on poistettu onnistuneesti." << endl;
    } else {
        cout << "Ei poistettu varauksia." << endl;
    }
}
//luodaan lisäpalvelu aliohjelma
void lisa_palvelut(vector<Huone>& huoneet) {
    int huonenumero;
    cout << "Anna huoneen numero, johon haluat tilata lisäpalveluita:";
    cin >> huonenumero;
    //meidän täytyy tarkastaa onko huonenumero olemassa
    if (huonenumero < 1 || huonenumero > huoneet.size()) {
        cout << "Virhe!!! Huonetta " << huonenumero << " Ei ole olemassa" << endl;
        cout << "Tarkista syötitkö numeron oikein" << endl;
        return;
    }
    // Viite (Huone&) mahdollistaa sen, että "valittu_huone" viittaa suoraan vektorin sisältämään huoneeseen.
    // Tämä tarkoittaa, että kun "valittu_huone"-muuttujaa muokataan, muutokset vaikuttavat suoraan
    // alkuperäiseen vektoriin ("huoneet"). Käytämme huonenumeroa viittaamaan oikeaan huoneeseen
    Huone& valittu_huone = huoneet[huonenumero - 1]; //vektori alkaa nollasta joten -1
    //Tarkistetaan onko huone jo varattu
    if (!valittu_huone.varattu) {
        cout << "Huone #" << huonenumero << " ei ole vielä varattu!" << endl;
        cout << "Tarkista syötitkö numeron oikein" << endl;
        cout << "Huoneen täytyy myös olla varattu ennen lisäpalveluiden tilaamista" << endl;
        return;
    }
    //Esitellään lisäpalvelulista
    cout << " Valitse lisäpalvelut huoneeseen#" << huonenumero << " (" << valittu_huone.varaaja << "):" << endl;
    cout << "1. Herkullinen ja ravitseva aamupala (18€/yö) " << endl;
    cout << "2. Urheilukanavapaketti (NHL,F1,Valioliiga...)(10€/yö)" << endl;
    cout << "3. Myöhäinen uloskirjautuminen (20€/varaus)" << endl;
    cout << "4. Pääsy hotellin valtavalle kuntosalille (12€/varaus)" << endl;
    cout << "5. Lopeta valitseminen" << endl;
    //annetaan käyttäjän valita
    int valinta;
    do {
        cout << "Valitse sinulle sopiva lisäpalvelu (1-5): ";
        cin >> valinta;

        // Käytetään switch-rakennetta käsittelemään valinta
        switch (valinta) {
            case 1:
                // Tarkistetaan, onko aamupala jo lisätty
                if (find(valittu_huone.lisapalvelut.begin(), valittu_huone.lisapalvelut.end(), "Aamupala") != valittu_huone.lisapalvelut.end()) {
                    cout << "Aamupala on jo lisätty huoneeseen #" << valittu_huone.numero << endl;
                } else {
                    // Lisätään aamupala ja päivitetään hinta
                    valittu_huone.lisapalvelut.push_back("Aamupala");
                    valittu_huone.hinta += 18;
                    cout << "Aamupala lisätty huoneeseen #" << valittu_huone.numero << endl;
                }
                break; // Lopetetaan tämä case, ettei muut tapaukset suoriteta
            case 2:
                // Tarkistetaan, onko urheilukanavat jo lisätty
                if (find(valittu_huone.lisapalvelut.begin(), valittu_huone.lisapalvelut.end(), "Urheilukanavat") != valittu_huone.lisapalvelut.end()) {
                    cout << "Urheilukanavapaketti on jo lisätty huoneeseen #" << valittu_huone.numero << endl;
                } else {
                    // Lisätään urheilukanavat ja päivitetään hinta
                    valittu_huone.lisapalvelut.push_back("Urheilukanavat");
                    valittu_huone.hinta += 10;
                    cout << "Urheilukanavapaketti lisätty huoneeseen #" << valittu_huone.numero << endl;
                }
                break; // Lopetetaan tämä case
            case 3:
                // Tarkistetaan, onko myöhäinen uloskirjautuminen jo lisätty
                if (find(valittu_huone.lisapalvelut.begin(), valittu_huone.lisapalvelut.end(), "Myöhäinen uloskirjautuminen") != valittu_huone.lisapalvelut.end()) {
                    cout << "Myöhäinen uloskirjautuminen on jo lisätty huoneeseen #" << valittu_huone.numero << endl;
                } else {
                    // Lisätään myöhäinen uloskirjautuminen ja päivitetään hinta
                    valittu_huone.lisapalvelut.push_back("Myöhäinen uloskirjautuminen");
                    valittu_huone.hinta += 20;
                    cout << "Myöhäinen uloskirjautuminen lisätty huoneeseen #" << valittu_huone.numero << endl;
                }
                break; // Lopetetaan tämä case
            case 4:
                // Tarkistetaan, onko kuntosalioikeus jo lisätty
                if (find(valittu_huone.lisapalvelut.begin(), valittu_huone.lisapalvelut.end(), "Kuntosalioikeus") != valittu_huone.lisapalvelut.end()) {
                    cout << "Kuntosalioikeudet on jo lisätty huoneeseen #" << valittu_huone.numero << endl;
                } else {
                    // Lisätään kuntosalioikeus ja päivitetään hinta
                    valittu_huone.lisapalvelut.push_back("Kuntosalioikeus");
                    valittu_huone.hinta += 12;
                    cout << "Kuntosalioikeudet lisätty huoneeseen #" << valittu_huone.numero << endl;
                }
                break; // Lopetetaan tämä case
            case 5:
                // Lopetetaan palveluiden valinta
                cout << "Palveluiden valinta lopetettu " << endl;
                break; // Lopetetaan tämä case ja poistutaan silmukasta
            default:
                // Virheellinen valinta, näytetään virheviesti
                cout << "Virheellinen valinta!" << endl;
                break; // Lopetetaan tämä case
        }
    // silmukka toistuu niin kauan kun käyttäjä ei anna 5    
    } while (valinta != 5);
    //Näytetään tiedot
    cout << "Päivitetyt tiedot huoneesta #" << valittu_huone.numero << ":" << endl;
    cout << "Koko: " << (valittu_huone.koko == 1 ? "1hh" : "2hh") << endl;
    cout << "Varaustilanne: " << (valittu_huone.varattu ? "Varattu" : "Vapaa") << endl;
    cout << "lopullinen hinta: " << valittu_huone.hinta << " €" << endl;
}
void jekkupuhelu(const vector <Huone>& huoneet) {
    int huonenumero;
    cout << "Anna huoneen numero josta soitamme pilapuhelun naapuriin: ";
    cin >> huonenumero;
    //tarkistetaan onko huonetta olemassa
    if (huonenumero < 1 || huonenumero > huoneet.size())    {
        cout << "Huonetta numero #" << huonenumero << " ei ole olemassa!" << endl;
        return;
    }
    //valitaan naapurihuone
    int naapuri_numero;
    if (huonenumero == 1) {
        naapuri_numero = huonenumero + 1; //Ensimmäisellä huoneella on vain yksi naapuri
    } else if (huonenumero == huoneet.size()){
        naapuri_numero =huonenumero - 1; // viimeisellä huoneella yksi naapuri
    } else { // ? : ; lyhyt tapa kirjoittaa if else
        naapuri_numero = (rand() % 2 == 0) ? huonenumero -1 : huonenumero + 1; //randomilla edellinen tai seuraava
    }
    // Naapuri taitaa juuri istua vessanpöntöllä
    cout << "soitetaan huoneesen #" << naapuri_numero << "..." << endl;
    cout << naapuri_numero << ": Lady Gagalla" << endl;
}
int main() {
    vector<Huone> hotellihuoneet;
    alusta_huoneet(hotellihuoneet);
    //muuttuja valinnan tallentamiseen
    int valinta;
    //pääsilmukka, pitää ohjelman käynnissä kunnes käyttäjän valitsee lopettaa
    do {
        valikko();
        cin >> valinta; //käyttäjä valitsee
        // Tarkistetaan syöte:
        // Jos käyttäjä antaa virheellisen arvon, poistetaan virhetila (clear) 
        // ja tyhjennetään puskuri (ignore), jotta voidaan jatkaa.
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Virheellinen syöte. valitse numero välillä 1-6!" << endl;
        }
        //valintaan pohjautuen suoritetaan oikea toiminto
        switch (valinta) {
            case 1:
            tulosta_huoneet(hotellihuoneet);
            break;
            case 2:
            varaus(hotellihuoneet);
            break;
            case 3:
            ihaile_varauksia(hotellihuoneet);
            break;
            case 4:
            lisa_palvelut(hotellihuoneet);
            break;
            case 5:
            jekkupuhelu(hotellihuoneet);
            break;
            case 6:
            cout << "Kiitos, että käytit varauspalvelua" << endl;
            break;
            default:
            cout << "virheellinen valinta!" << endl;

        }

    }while (valinta != 6);
    return 0;
}