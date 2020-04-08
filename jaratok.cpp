#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "adminisztracio.h"
#include "jaratok.h"
#include "jegy.h"
#include "vonatok.h"
#include "memtrace.h"


void Megallok::set(std::string neve, int ideje) {
    nev = neve;
    ido = ideje;
}

void Jarat::set(int a, int mdb, Idopont ip, Jarattipus j) {
    azon = a;
    megallokszama = mdb;
    indulas = ip;
    jt = j;
}

std::ostream& operator<<(std::ostream& os, Jarattipus jt) {
    if (jt == IC)
        os << "IC";
    else if(jt == SEBES)
        os << "SEBES";
    else if(jt == SZEMELY)
        os << "SZEMELY";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Vonat &v) {
    os << "Vonatszam: " << v.getAzon() << "\nKocsik darabszama: " << v.getKocsikszama() << "\nKocsik: " << std::endl;
    for (int i = 0; i < v.getKocsikszama(); i++) {
        os << v.getK()[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, Megallok& m) {
    char tmp;
    is >> m.nev >> tmp >> m.ido;
    return is;
}
