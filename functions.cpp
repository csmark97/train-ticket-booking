#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "adminisztracio.h"
#include "jaratok.h"
#include "functions.h"
#include "jegy.h"
#include "memtrace.h"

Kocsik kocsiletrehoz(int azon) {
    int kt;
    Kocsitipus kocsit;
    azon++;
    std::cout << "A(z) " << azon <<  ". kocsi tipusa:\n\t0: TERMES\n\t1: KABINOS";
    std::cin >> kt;
    if (kt == 0)
        kocsit = TERMES;
    else
        kocsit = KABINOS;
    Kocsik k(azon, kocsit);
    return k;
}

int vonatletrehoz() {
    //system("CLS");
    int azon;
    std::cout << "Vonat azonosito szama: ";
    std::cin >> azon;
    int db;
    std::cout << "Kocsik darabszama: ";
    std::cin >> db;
    Kocsik *k = new Kocsik[db];
    for (int i = 0; i < db; i++) {
        k[i] = kocsiletrehoz(i);
    }
    Vonat v(azon, db, k);
    //std::cout << v;
    vonattofile(v);
    delete[] k;
    return azon;

}

Megallok& Jarat::operator[](size_t i) {
    return m[i];
}

const Megallok& Jarat::operator[](size_t i) const {
    return m[i];
}

void vonattofile(const Vonat &v){
    std::ofstream vonatok;
    vonatok.open ("vonatok.txt", std::ofstream::out | std::ofstream::app);
    vonatok << v.getAzon() << "\t" << v.getKocsikszama();
    for (int i = 0; i < v.getKocsikszama(); i++) {
        vonatok << "\t" << v.getK()[i].getAzon() << "\t" << v.getK()[i].getKocsitipus() << "\t" << v.getK()[i].getFoglalthelyek();
    }
    vonatok << std::endl;
    vonatok.close();
}

void jarattofile(Jarat& j) {
    std::ofstream jaratok;
    jaratok.open ("jaratok.txt", std::ofstream::out | std::ofstream::app);
    jaratok << std::endl;
    jaratok << j.getAzon() << "\t" << j.getJt() << "\t" << j.getIndulas() << "\t" << j.getMegallokszama();
    for (int i = 0; i < j.getMegallokszama(); i++) {
        jaratok << "\t" << j.getM()[i].getNev() << "\t" << j.getM()[i].getIdo();
    }
    jaratok.close();
}

Megallok megalloletrehoz(int i){
    std::cout << "\n" << i+1 << ". megallo neve: ";
    std::string m;
    std::cin >> m;
    std::cout << "\nMenetido (percben) a kovetkezo megalloig: ";
    int perc;
    std::cin >> perc;
    Megallok me(m, perc);
    return me;
}

Megallok utolsomegalloletrehoz(){
    std::cout << "\nVegallomas: ";
    std::string m;
    std::cin >> m;
    Megallok me(m,0);
    return me;
}

void jaratletrehoz(int azon) {
    //system("CLS");
    int jt;
    std::cout << "Jarat tipusa:\n\t1: IC\n\t2: SEBES\n\t3: SZEMELY";
    std::cin >> jt;
    Jarattipus jaratt;
    if (jt == 1)
        jaratt = IC;
    else if (jt == 2)
        jaratt = SEBES;
    else if (jt == 3)
        jaratt = SZEMELY;

    int o, p;
    std::cout << "Indulasi idopont (ora): ";
    std::cin >> o;
    std::cout << "Indulasi idopont (perc): ";
    std::cin >> p;
    Idopont ip(o, p);
    std::cout << "Megallok szama: ";
    int db;
    std::cin >> db;
    Megallok *m = new Megallok [db];
    for (int i = 0; i < db - 1; i++) {
        m[i] = megalloletrehoz(i);
    }
    m[db-1] = utolsomegalloletrehoz();
    Jarat j(azon, db, m, ip, jaratt);
    jarattofile(j);
    delete[] m;
}

void adminfelulet(){
    int i = vonatletrehoz();
    jaratletrehoz(i);
}

Jarat* jaratkereses(int azon) {
    std::ifstream jaratok;
    jaratok.open ("jaratok.txt", std::ifstream::in);

    int id;
    std::string jt;
    int megallokszama;
    Idopont indulasiido;
    std::string megallo;
    int menetido;
    Jarattipus jtipus;

    do {
        jaratok >> id >> jt >> indulasiido >> megallokszama;
        Megallok* megallotomb = new Megallok[megallokszama];
        for (int i = 0; i < megallokszama; i++) {
            jaratok >> megallo >> menetido;
            megallotomb[i].set(megallo, menetido);
        }
        if (jt == "IC")
            jtipus = IC;
        else {
            if (jt == "SEBES")
                jtipus = SEBES;
            else
                jtipus = SZEMELY;
        }

        if (id == azon) {
            jaratok.close();
            Jarat* ja = new Jarat(id, megallokszama, megallotomb, indulasiido, jtipus);
            delete[] megallotomb;
            return ja;
        }
        delete [] megallotomb;
    } while (jaratok.good());
    jaratok.close();
    Jarat *hibas = new Jarat(-1,-1);
    return hibas;
}

Vonat* vonatkereses(int azon) {
    std::ifstream vonatok;
    vonatok.open ("vonatok.txt", std::ifstream::in);

    int id;
    int kocsikSzama;
    std::string kTipusString;
    Kocsitipus kocsiTipus;
    int foglalthelyek;
    int kocsiszam;

    do {
        vonatok >> id >> kocsikSzama;
        Kocsik* kocsiTomb = new Kocsik[kocsikSzama];
        for (int i = 0; i < kocsikSzama; i++) {
            vonatok >> kocsiszam >> kTipusString >> foglalthelyek;
            if (kTipusString == "Termes")
                kocsiTipus = TERMES;
            else
                kocsiTipus= KABINOS;
            kocsiTomb[i].set(kocsiszam, kocsiTipus, foglalthelyek);
        }

        if (id == azon) {
            vonatok.close();
            Vonat* vo = new Vonat(id, kocsikSzama, kocsiTomb);
            delete[] kocsiTomb;
            return vo;
        }
        delete [] kocsiTomb;
    } while (vonatok.good());
    vonatok.close();
    Vonat *hibas = new Vonat(-1,-1);
    return hibas;
}

Kocsik helyetAd(Vonat* vonatunk) {
    for (int i = 0; i < vonatunk->getKocsikszama(); i++) {
        if (vonatunk->getK()[i].getFoglalthelyek() < vonatunk->getK()[i].maxotmeghataroz())
            return Kocsik(vonatunk->getK()[i].getAzon(), vonatunk->getK()[i].getKocsitipus(), vonatunk->getK()[i].getFoglalthelyek());
    }
    Kocsik ittnincshely(-1, TERMES, 1);
    return ittnincshely;
}

void jaratkereses(std::string honnan, std::string hova) {
    std::ifstream ifs("jaratok.txt", std::ifstream::in);

    int id;
    std::string tipusStr;
    Idopont indulasiIdo;
    int megallokSzama;
    std::string megallo;
    int menetido;
    Jarattipus tipus;

    while (ifs.good()) {
        ifs >> id >> tipusStr >> indulasiIdo >> megallokSzama;
        if (tipusStr == "IC")
            tipus = IC;
        else if (tipusStr == "SEBES")
            tipus = SEBES;
        else if (tipusStr == "SZEMELY")
            tipus = SZEMELY;

        bool hasKiindulas = false;

        int osszido = 0;
        for (int i = 0; i < megallokSzama; ++i) {
            ifs >> megallo >> menetido;
            osszido += menetido;
            if (hasKiindulas) {
                // Már szerepel a megállók közt a kiindulási hely
                if (megallo == hova) {
                    osszido -=menetido;
                    std::cout << std::endl << id << "\t" << indulasiIdo << "\t" << honnan << "\t" << megallo << "\t" << tipus
                                            << "\t" << osszido << " perc\t" << megallokSzama * 210 << " Ft";
                }

            } else {
                // Ellenõrzés
                hasKiindulas = megallo == honnan;
            }
        }
    }
}

void felhasznaloifelulet(Account a) {
    std::string innen, ide;
    //system("CLS");
    std::cout << "Udvozlom " << a.getKeresztnev() << "!" << std::endl;
    std::cout << "Irja be, honnan, hova szeretne utazni!" << std::endl;
    std::cout << "Innen: ";
    std::cin >> innen;
    std::cout << "Ide: ";
    std::cin >> ide;
    jaratkereses(innen, ide);
    int szam;
    std::cout << std::endl << "Valassza ki az onnek megfelelo jaratot!" << std::endl;
    std::cout << "Azonosito: ";
    std::cin >> szam;
    Jarat* j;
    j = jaratkereses(szam);
    Vonat* v;
    v = vonatkereses(szam);
    Jegy jegy(a, v, j);
    if (j->getAzon() == -1 || v->getAzon() == -1) {
        std::cout << "Rossz azonositot adott meg.";
        delete j;
        delete v;
    } else {
    //system("CLS");
        jegy.jegykiadas();
        delete j;
        delete v;
    }
}
