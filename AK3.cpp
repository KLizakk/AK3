// LiczenieBinarne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include "stdlib.h"
#include <string>
string PrzeliczNa2(int x)
{
    if (x == 0) {
        cout << "nie wprowadzaj 0";
    }
    string L2 = "";
    while (x > 0) {
        int r = x % 2;
        L2 = to_string(r) + L2;
        x /= 2;
    }
    return L2;
}

string PrzeliczNa8(int x)
{
    if (x == 0) {
        cout << "Nie wprowadzaj 0";
    }
    string L8 = "";
    while (x > 0) {
        int r = x % 8;
        L8 = to_string(r) + L8;
        x /= 8;
    }
    return L8;
}
string PrzeliczNa16(int x)
{
    if (x == 0) {
        cout << "Nie wprowadzaj 0";
    }
    string L16 = "";
    while (x > 0) {
        int r = x % 16;
        L16 = to_string(r) + L16;
        x /= 16;
    }
    return L16;
}

int Na10(string x)
{
    int Liczba10 = 0;
    int PotegaDwa = 1;
    for (int i = x.length() - 1; i >= 0; --i)
    {
        if (x[i] == '1') {
            Liczba10 += PotegaDwa;
        }
        PotegaDwa *= 2;
    }
    return Liczba10;
}
//Niepoprawne dodawanie
string Dodawanie(string a, string b)
{
    int A = Na10(a);
    int B = Na10(b);

    int suma = A + B;

    return PrzeliczNa2(suma);

}
//Poprawne dodawania
string DodawanieP(string a, string b)
{
    string wynik;
    char carry = '0';

    // DoprowadŸ obie liczby do tej samej d³ugoœci poprzez dodanie zer na pocz¹tku
    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    for (int i = a.length() - 1; i >= 0; i--)
    {
        char bitA = a[i];
        char bitB = b[i];

        // Dodawanie bitowe
        char suma = (bitA - '0') + (bitB - '0') + (carry - '0') + '0';

        // Ustaw carry na 1, jeœli suma wynosi 2 lub 3
        carry = (suma >= '2') ? '1' : '0';

        // Jeœli suma wynosi 1 lub 3, ustaw wynik na 1
        wynik = (suma == '1' || suma == '3') ? '1' + wynik : '0' + wynik;
    }

    // Jeœli carry pozosta³o, dodaj je do wyniku
    if (carry == '1') wynik = carry + wynik;

    return wynik;
}
//Odejmowanie : 
string OdejmowanieP(string a, string b)
{
    string wynik;
    int dlugoscA = a.length();
    int dlugoscB = b.length();
    int dlugoscMax = max(dlugoscA, dlugoscB);
    int carry = 0;

    // DoprowadŸ obie liczby do tej samej d³ugoœci poprzez dodanie zer na pocz¹tku
    while (a.length() < dlugoscMax) a = '0' + a;
    while (b.length() < dlugoscMax) b = '0' + b;

    for (int i = dlugoscMax - 1; i >= 0; i--)
    {
        int bitA = a[i] - '0';
        int bitB = b[i] - '0';

        // Odejmowanie bitowe
        int roznica = bitA - bitB - carry;

        // Ustaw carry na 0 lub 1 w zale¿noœci od wyniku odejmowania
        carry = (roznica < 0) ? 1 : 0;

        // Jeœli wynik jest ujemny, dodaj 2 do wyniku
        roznica = (roznica < 0) ? roznica + 2 : roznica;

        // Konwertuj wynik na znak ('0' lub '1') i dodaj do wyniku
        wynik = char(roznica + '0') + wynik;
    }

    // Usuñ wiod¹ce zera z wyniku
    while (wynik.length() > 1 && wynik[0] == '0') wynik = wynik.substr(1);

    return wynik;
}
// Funkcja do mno¿enia dwóch liczb binarnych
string MnozenieP(string a, string b)
{
    string wynik = "0";

    // DoprowadŸ obie liczby do tej samej d³ugoœci poprzez dodanie zer na pocz¹tku
    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    // Przechodzimy przez ka¿dy bit liczby b
    for (int i = b.length() - 1; i >= 0; i--)
    {
        string aktualneMnozenie = "";

        // Dodaj odpowiedni¹ liczbê zer na koñcu, zale¿nie od pozycji bitu
        for (int j = 0; j < b.length() - 1 - i; j++)
        {
            aktualneMnozenie += "0";
        }

        // Pomnó¿ ka¿dy bit liczby a przez bit liczby b
        for (int j = a.length() - 1; j >= 0; j--)
        {
            int mnozenie = (a[j] - '0') * (b[i] - '0');
            aktualneMnozenie = char(mnozenie % 2 + '0') + aktualneMnozenie;
        }

        // Dodaj obliczon¹ wartoœæ do wyniku
        wynik = DodawanieP(wynik, aktualneMnozenie);
    }

    return wynik;
}
// Funkcja do porównywania dwóch liczb binarnych
int PorownanieP(string a, string b)
{
    // DoprowadŸ obie liczby do tej samej d³ugoœci poprzez dodanie zer na pocz¹tku
    while (a.length() < b.length()) a = '0' + a;
    while (b.length() < a.length()) b = '0' + b;

    // Porównuj bity od lewej do prawej
    for (int i = 0; i < a.length(); i++)
    {
        if (a[i] < b[i]) return -1; // a < b
        else if (a[i] > b[i]) return 1; // a > b
    }

    return 0; // a == b
}
string DzielenieP(string a, string b)
{
    string wynik = "0";
    string reszta = a;

    while (reszta.length() >= b.length())
    {
        // ZnajdŸ najwiêksz¹ potêgê 2, która mieœci siê w reszcie
        int potega = reszta.length() - b.length();
        string dzielnik = b + string(potega, '0');

        // Jeœli dzielnik jest mniejszy lub równy reszcie, odejmij go od reszty
        if (PorownanieP(reszta, dzielnik) != -1)
        {
            reszta = OdejmowanieP(reszta, dzielnik);
            wynik = DodawanieP(wynik, "1" + string(potega, '0'));
        }
        else
        {
            wynik = wynik + string(potega, '0');
        }
    }

    return wynik;
}
int OsemkowaNaDziesietna(string liczbaOsemkowa) {
    int wynik = 0;
    int dlugosc = liczbaOsemkowa.length();

    for (int i = 0; i < dlugosc; ++i) {
        int cyfra = liczbaOsemkowa[i] - '0';
        wynik += cyfra * pow(8, dlugosc - i - 1);
    }

    return wynik;
}



int main()
{
    cout << "Menu : " << endl;
    //2.1
    cout << "1 - Przelicz liczbê na system 2" << endl;
    cout << "2 - Przelicz na 8" << endl;
    cout << "3 - przelicz na 16" << endl;
    //2.2
    cout << "4 - Dodaj dwie liczby binarnie" << endl;
    cout << "5 - Odejmij dwie liczby binarnie" << endl;
    cout << "6 - Mnozenie dwoch liczb binarnych" << endl;
    cout << "7 - Dzielenie dwoch liczb binarnych" << endl;
    cout << "8 - Wczytanie liczby w systemie 8 , przeliczenie na 10, wyswietlenie binarnie" << endl;
    int p;
    int x;
  
    string l1, l2;
    cin >> p;
    string Rezultat;
    switch (p)
    {
    case 1:
        cout << "Podaj liczbe :";
        cin >> x;
        Rezultat = PrzeliczNa2(x);
        cout << "Liczba : " << x << endl << " W przeliczeniu na system 2 to : " << Rezultat;
        break;
    case 2:
        cout << "Podaj liczbe :";
        cin >> x;
        Rezultat = PrzeliczNa8(x);
        cout << endl << "Liczba w systemie 8 : " << Rezultat;
        break;
    case 3:
        cout << "Podaj liczbe :";
        cin >> x;
        Rezultat = PrzeliczNa16(x);
        cout << endl << "Liczba  w systemie 16 : " << Rezultat;
        break;
    case 4:
        cout << "Podaj pierwsza liczbe :";
        cin >> l1;
        cout << endl << "Podaj druga liczbe : ";
        cin >> l2;
        Rezultat = DodawanieP(l1, l2);
        cout << "Wartoœc po dodaniu to : " << Rezultat;
        break;
    case 5:
        cout << "Podaj pierwsza liczbe :";
        cin >> l1;
        cout << endl << "Podaj druga liczbe : ";
        cin >> l2;
        Rezultat = OdejmowanieP(l1, l2);
        cout << "Wartosc po odjeciu :" << Rezultat;
        break;
    case 6:
        cout << "Podaj pierwsza liczbe :";
        cin >> l1;
        cout << endl << "Podaj druga liczbe : ";
        cin >> l2;
        Rezultat = MnozenieP(l1, l2);
        cout << "Wartosc po mnozeniu : " << Rezultat;
        break;
    case 7:
        cout << "Podaj pierwsza liczbe :";
        cin >> l1;
        cout << endl << "Podaj druga liczbe : ";
        cin >> l2;
        Rezultat = DzielenieP(l1, l2);
        cout << "Wartosc po dzieleniu : " << Rezultat;
        break;
    case 8:
        cout << "Podaj liczbe do przeksztalcenia : ";
        cin >> l1;
        x = OsemkowaNaDziesietna(l1);
        Rezultat = PrzeliczNa2(x);

        cout << "Wartosc po przeliczeniu : " << Rezultat;
        break;

    default:
        break;
    }




}


