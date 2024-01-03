#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <iterator>

using namespace std;

class Sekwencja {
public:
    string nazwa;
    vector<char> nukleotyd;
    vector<int> jakosc;
    vector<int> pozycja;

    Sekwencja(string s1) {
        nazwa = s1;
    }

    void Snukleotyd(vector<char> s2) {
        for (int i = 0; i < s2.size(); i++) {
            nukleotyd.push_back(s2[i]);
        }
    }

    void Sjakosc(vector<int> s3) {
        for (int i2 = 0; i2 < s3.size(); i2++) {
            jakosc.push_back(s3[i2]);
        }
        //wpisanie wartosci
    }

    void Spozycja(vector<int> s4) {
        for (int i3 = 0; i3 < s4.size(); i3++) {
            pozycja.push_back(s4[i3]);
        }

    }
};

vector<Sekwencja> sekwencje;

class Wierzcholek {
public:
    Wierzcholek() {}

    vector<char> odcinektab;
    vector<int> sasiedzi;

    string odcinek;
    int sekwencja;
    int lokalizacja;
    int id;

    void Wodcinektab(vector<char> w1) {

        for (int i1 = 0; i1 < w1.size(); i1++) {
            odcinektab.push_back(w1[i1]);
        }

    }

    void Wsekwnecja(int w2) {
        sekwencja = w2;
    }

    void Wlokalizacja(int w3) {
        lokalizacja = w3;
    }

    void Wsasiedzi(int w4) {
        sasiedzi.push_back(w4);
    }

    void Wid(int w5) {
        id = w5;
    }

    void Wodcinek(string w6) {
        odcinek = w6;
    }

};

vector<Wierzcholek> wierzcholki;

void czyszczenie(int threshold, vector<int> jakosci, string nazwa, string seq) {
    vector<int> numery;
    vector<char> zasady;
    int tmp;
    for (tmp = 0; tmp < jakosci.size(); tmp++) {
        numery.push_back(tmp + 1);

        zasady.push_back(seq[tmp]);


    }
    for (tmp = 0; tmp < jakosci.size(); tmp++) {
        if (jakosci[tmp] < threshold) {
            zasady.erase(zasady.begin() + tmp);
            numery.erase(numery.begin() + tmp);
            jakosci.erase(jakosci.begin() + tmp);
            tmp = 0;
        }
    }
    Sekwencja *nowa = new Sekwencja(nazwa);

    nowa->Spozycja(numery);
    nowa->Snukleotyd(zasady);
    nowa->Sjakosc(jakosci);
    sekwencje.push_back(*nowa);


    return;
}

void stworzwierzcholki(int lenf) {
    vector<char> znaki;

    int id = 0;
    int numer;
    int origin;

    for (int i = 0; i < sekwencje.size(); i++) {
        for (int i1 = 0; i1 < sekwencje[i].nukleotyd.size() - lenf; i1++) {

            for (int i2 = 0; i2 < lenf; i2++) {
                znaki.push_back(sekwencje[i].nukleotyd[i1 + i2]);
            }
            string ciag(znaki.begin(), znaki.end());
            numer = sekwencje[i].pozycja[i1];
            // origin = sekwencje[i].id[];
            Wierzcholek *nowy = new Wierzcholek;
            nowy->Wodcinektab(znaki);
            nowy->Wsekwnecja(i);
            nowy->Wodcinek(ciag);
            nowy->Wlokalizacja(numer);
            nowy->Wid(id);
            wierzcholki.push_back(*nowy);
            znaki.clear();

            id++;
        }

    }


    return;
};

void krawedzie(int lenf) {
    int bledy = 0;
    int odleglosc = 0;
    for (int x = 0; x < wierzcholki.size(); x++) {
        for (int x2 = 0; x2 < wierzcholki.size(); x2++) {


            if (wierzcholki[x].sekwencja != wierzcholki[x2].sekwencja) {
                for (int y = 0; y < lenf; y++) {
                    if (wierzcholki[x].odcinektab[y] != wierzcholki[x2].odcinektab[y]) {
                        bledy++;

                    }
                }
                if (wierzcholki[x].lokalizacja >= wierzcholki[x2].lokalizacja) {
                    odleglosc = wierzcholki[x].lokalizacja - wierzcholki[x2].lokalizacja;
                } else {
                    odleglosc = wierzcholki[x2].lokalizacja - wierzcholki[x].lokalizacja;
                }
                if (odleglosc < (lenf * 10)) {


                    if (bledy < 2) {
                        wierzcholki[x].Wsasiedzi(wierzcholki[x2].id);

                    }
                }
                bledy = 0;
                odleglosc = 0;

            }

        }

    }
    return;
};

void szukaj(int rozmiar) {
    vector<int>::iterator it;
    int heur = 0;
    int heur2 = 0;

    vector<int> warunek;
    vector<int> oo;
    vector<vector<int>> zbiormozliwosci;
    vector<int> uzyte;

    for (int w = 0; w < rozmiar; w++) {
        warunek.push_back(w);
    }


    for (int petla = 0; petla < rozmiar; petla++) {


        for (int i = heur2; i < wierzcholki.size(); i++) {
            if (wierzcholki[i].sekwencja == petla) {
                heur++;
            }
            if (wierzcholki[i].sekwencja > petla) {
                break;
            }

        }


        for (int x = heur2; x < heur2 + heur; x++) {
            for (int x2 = 0; x2 < wierzcholki[x].sasiedzi.size(); x2++) {
                int t = (wierzcholki[x].sasiedzi[x2]);
                oo.push_back(wierzcholki[t].sekwencja);
            }
            it = unique(oo.begin(), oo.end());
            oo.resize(distance(oo.begin(), it));
            oo.push_back(petla);
            sort(oo.begin(), oo.end());
            if (warunek == oo) {
                uzyte.push_back(x);

            }
            oo.clear();
        }
        zbiormozliwosci.push_back(uzyte);
        uzyte.clear();
        heur2 += heur;
        heur = 0;
    }


    vector<int> mozliwosci;
    for (int i = 0; i < zbiormozliwosci.size(); i++) {
        for (int j = 0; j < zbiormozliwosci[i].size(); j++) {
            mozliwosci.push_back(zbiormozliwosci[i][j]);
            // cout << zbiormozliwosci[i][j] << "  ";}
            // cout << zbiormozliwosci[i][j] << "   "<<wierzcholki[zbiormozliwosci[i][j]].odcinek<<"   "<<wierzcholki[zbiormozliwosci[i][j]].lokalizacja;
            // cout << endl;
        }
    }
    for (int clean = 0; clean < zbiormozliwosci[0].size(); clean++) {
        for (int clean2 = 0; clean2 < wierzcholki[zbiormozliwosci[0][clean]].sasiedzi.size(); clean2++) {
            if (count(mozliwosci.begin(), mozliwosci.end(), wierzcholki[zbiormozliwosci[0][clean]].sasiedzi[clean2])) {
            } else {
                wierzcholki[zbiormozliwosci[0][clean]].sasiedzi.erase(
                        wierzcholki[zbiormozliwosci[0][clean]].sasiedzi.begin() + clean2);
                clean2 = 0;
            }

        }
    }
    vector<int>::iterator zbieznosc;
    vector<int> rozne;
    bool brak = true;
    for (int motyw = 0; motyw < zbiormozliwosci[0].size(); motyw++) {
        if (wierzcholki[zbiormozliwosci[0][motyw]].sasiedzi.size() >= (rozmiar - 1)) {
            for (int lupa = 0; lupa < wierzcholki[zbiormozliwosci[0][motyw]].sasiedzi.size(); lupa++) {
                int zz = (wierzcholki[zbiormozliwosci[0][motyw]].sasiedzi[lupa]);
                rozne.push_back(wierzcholki[zz].sekwencja);
            }
            zbieznosc = unique(rozne.begin(), rozne.end());
            rozne.resize(distance(rozne.begin(), zbieznosc));
            if (rozne.size() >= rozmiar - 1) {

                int wyswietl = zbiormozliwosci[0][motyw];
                cout << wierzcholki[wyswietl].odcinek << " :motyw " << wierzcholki[wyswietl].lokalizacja
                     << ": lokalizacja w sekwencji" << endl;
                for (int motyw2 = 0; motyw2 < wierzcholki[zbiormozliwosci[0][motyw]].sasiedzi.size(); motyw2++) {
                    int skladowe = wierzcholki[wyswietl].sasiedzi[motyw2];
                    cout << wierzcholki[skladowe].odcinek << " " << wierzcholki[skladowe].sekwencja << " :sekwencja "
                         << wierzcholki[skladowe].lokalizacja << " :lokalizacja" << endl;
                    brak = false;
                }
            }
            rozne.clear();
        }
    }


    if (brak) {
        cout << "nie znaleziono motywu" << endl;
    }


    return;
};

int main() {
    vector<int> jakosc;
    string seq;
    string nazwa;
    ifstream plik_z_zasadami;
    ifstream plik_z_jakoscia;
    int wartosc;
    string line;
    int q;
    plik_z_zasadami.open("fasta2.txt");
    plik_z_jakoscia.open("quality2.txt");
    cout << "podaj wymagana jakosc odczytu" << endl;
    cin >> q;
    int liczbasekwencji = 7;
    for (int rekordy = 0; rekordy < liczbasekwencji; rekordy++) {
        while (!plik_z_zasadami.eof()) {
            plik_z_zasadami >> nazwa;
            plik_z_zasadami >> seq;
            break;
        }
        while (!plik_z_jakoscia.eof()) {
            getline(plik_z_jakoscia, line);
            for (int l = 0; l < seq.length(); l++) {
                plik_z_jakoscia >> wartosc;
                jakosc.push_back(wartosc);
            }
            getline(plik_z_jakoscia, line);
            break;
        }
        czyszczenie(q, jakosc, nazwa, seq);

        jakosc.clear();

    }
    int x;
    cout << "podaj dlugosc szukanego motywu" << endl;
    cin >> x;
    stworzwierzcholki(x);
    krawedzie(x);
    szukaj(liczbasekwencji);
    getch();


    return 0;
}
