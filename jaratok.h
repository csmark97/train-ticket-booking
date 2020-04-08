#ifndef JARATOK_H_INCLUDED
#define JARATOK_H_INCLUDED
#include "adminisztracio.h"
#include "vonatok.h"
#include "memtrace.h"

enum Jarattipus {
    IC, SEBES, SZEMELY
};

class Megallok {
    std::string nev;
    int ido;

 public:
    Megallok() :nev(), ido() {}
    Megallok(std::string n, int i = 0) :nev(n), ido(i) {}
    std::string getNev() const { return nev; }
    int getIdo() const { return ido; }
    void set(std::string, int);
    friend std::istream& operator>>(std::istream&, Megallok&);
    ~Megallok() {}
};

class Jarat {
    int azon; ///FONTOS!!! A járatot és a vonatot az azon köti össze.
    int megallokszama;
    Megallok *m;
    Idopont indulas;
    Jarattipus jt;

 public:
    Jarat(): megallokszama(0), m(NULL) {}
    Jarat(int a, int mdb) :azon(a), megallokszama(mdb), m(NULL) {}
    Jarat(int a, int mdb, Megallok *mparam, Idopont ip, Jarattipus j) {
        azon = a;
        megallokszama = mdb;
        m = new Megallok[megallokszama];
        for (int i = 0; i < megallokszama; i++) {
            m[i] = mparam[i];
        }
        indulas = ip;
        jt = j;
    }
    Jarat(const Jarat& masik){
        m = NULL;
        *this = masik;
    }
    Jarat& operator=(const Jarat& j) {
        azon = j.azon;
        megallokszama = j.megallokszama;
        if(this != &j){
            delete[] m;
            m = new Megallok[megallokszama];
            for (int i = 0; i < megallokszama; i++) {
            m[i] = j.m[i];
            }
        }
        indulas = j.indulas;
        jt = j.jt;
        return *this;
    }
    int getAzon() const { return azon; }
    int getMegallokszama() const { return megallokszama; }
    Megallok* getM() const { return m; }
    Jarattipus getJt() const { return jt; }
    Idopont getIndulas() const { return indulas; }
    Megallok& operator[](size_t i);
    void set(int a, int mdb, Idopont ip, Jarattipus j);
    const Megallok& operator[](size_t i) const;
    ~Jarat() {
		delete[] m;
    }
};

std::ostream& operator<<(std::ostream&, const Vonat&);
std::ostream& operator<<(std::ostream&, Jarattipus);

#endif // JARATOK_H_INCLUDED
