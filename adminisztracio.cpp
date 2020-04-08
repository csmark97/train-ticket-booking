#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "adminisztracio.h"
#include "jaratok.h"
#include "functions.h"
#include "jegy.h"
#include "memtrace.h"

std::ostream& operator<<(std::ostream& os, Datum d) {
    os << d.getEv() << "." << d.getHo() << "." << d.getNap() << "." << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Datum& d) {
    char temp;
    is >> d.ev >> temp >> d.ho>> temp >> d.nap>>temp;
    return is;
}

std::ostream& operator<<(std::ostream& os, Idopont ip) {
    os << ip.getOra() << ":" << ip.getPerc();
    return os;
}

std::istream& operator>>(std::istream& is, Idopont& ip) {
    char tmp;
    is >> ip.ora >> tmp >> ip.perc;
    return is;
}

void acctofile(Account a){      //Jelszavak fájlba kiírása
    std::ofstream adatok;
    adatok.open ("adatok.txt", std::ofstream::out | std::ofstream::app);
    adatok << a.getFelhaszn() << "\t" << a.getJelszo() << "\t" << a.getVezetknev() << "\t" << a.getKeresztnev() << "\t" << a.getSzuldatum();
    adatok.close();
}

bool accheck(std::string flh, std::string jlsz, Account& acc) {
    std::ifstream adatok;
    adatok.open ("adatok.txt", std::ifstream::in);
    while(adatok.good()) {
        std::string f, j, vn, kn; Datum szd;
        adatok >> f >> j >> vn >> kn >> szd;
        if (flh == f && jlsz == j){
            //std::cout << f << j << vn << kn << szd;
            acc.set(f, j, vn, kn, szd);
            return true;
        }
    }
    adatok.close();
    return false;
}

bool acccheck2(std::string flh) {
    std::ifstream adatok;
    adatok.open ("adatok.txt", std::ofstream::in);
    while(adatok.good()) {
        std::string f, j, vn, kn; Datum szd;
        adatok >> f >> j >> vn >> kn >> szd;
        if (flh == f) {
            return true;
        }
    }
    adatok.close();
    return false;
}

std::ostream& operator<<(std::ostream& os, Account b) {
    os << "\nFelhasznaloi nev: "
        << b.getFelhaszn() << "\nJelszo: " << b.getJelszo();
    return os;
}

std::istream& operator>>(std::istream& is, Account b) {
    is >> b.felhaszn >> b.jelszo;
    return is;
}

void Account::set(std::string fn, std::string jlsz, std::string v, std::string k, Datum dat) {
    felhaszn = fn;
    jelszo = jlsz;
    vezeteknev = v;
    keresztnev = k;
    szuldatum = dat;
}

void bejelentkezes() {
    std::string f; std::string j; Account a;
    do {
    //system("CLS");
    std::cout << "Bejelentkezes\n\tFelhasznaloi nev: ";
    std::cin >> f;
    std::cout << "\n\tJelszo: ";
    std::cin >> j;
    if (accheck(f, j, a) == true)
        std::cout << "Sikeres belepes";
    else
        std::cout << "Helytelen felhasznalonev vagy jelszo. Probalja ujra!";
    } while(accheck(f, j, a) == false);
    felhasznaloifelulet(a);
}

void regisztracio () {
    std::string f; std::string j; std::string v; std::string k; int e, h, n;
    do { //Ne legyen felhasznalonev egyezes
        //system("CLS");
        std::cout << "Regisztracio\n\tFelhasznaloi nev: ";
        std::cin >> f;
        if (acccheck2(f)) {
            std::cout << "Foglalt felhasznalonev!";
            getchar();
        }
        getchar();
    } while (acccheck2(f) == true);
    std::cout << "\n\tJelszo: ";
    std::cin >> j;
    std::cout << "\n\tVezetknev: ";
    std::cin >> v;
    std::cout << "\n\tKeresztnev: ";
    std::cin >> k;
    std::cout << "\n\tSzuletesi ev: ";
    std::cin >> e;
    std::cout << "\n\tSzuletesi honap (szammal): ";
    std::cin >> h;
    std::cout << "\n\tSzuletesi nap: ";
    std::cin >> n;
    Datum d(e, h, n);
    Account reg(f, j, v, k, d);
    acctofile(reg);
}
