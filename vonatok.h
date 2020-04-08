#ifndef VONATOK_H_INCLUDED
#define VONATOK_H_INCLUDED
#include "adminisztracio.h"
#include "jaratok.h"
#include "memtrace.h"

enum Kocsitipus {
    TERMES, KABINOS
};

class Kocsik {
    int azon;
    Kocsitipus kt;
    int foglalthelyek;

 public:
    Kocsik() :azon(0), kt(TERMES), foglalthelyek(0) {}
    Kocsik(int a, Kocsitipus k, int foglalt = 0) :azon(a), kt(k), foglalthelyek(foglalt) {}
    int getAzon() const { return azon; }
    Kocsitipus getKocsitipus() const { return kt; }
    int getFoglalthelyek() { return foglalthelyek; }
    int maxotmeghataroz();
    void set(int, Kocsitipus, int);
    ~Kocsik() {}
};

class Vonat {
    int azon;
    int kocsikszama;
    Kocsik *k;

 public:
    Vonat(): k(NULL) {}
    Vonat(int a, int kdb) :azon(a), kocsikszama(kdb), k(NULL) {}
    Vonat(int a, int kdb, Kocsik *kparam) {
        azon = a;
        kocsikszama = kdb;
        k = new Kocsik[kocsikszama];
        for (int i = 0; i < kocsikszama; i++) {
            k[i] = kparam[i];
        }
    }
    Vonat& operator=(const Vonat& v) {
        azon = v.azon;
        kocsikszama = v.kocsikszama;
        if(this != &v) {
            delete[] k;
            k = new Kocsik[v.kocsikszama];
            for (int i = 0; i < kocsikszama; i++) {
            k[i] = v.k[i];
            }
        }
        return *this;
    }
    Kocsik* getK() const { return k; }
    int getAzon() const { return azon; }
    int getKocsikszama() const { return kocsikszama; }
    Kocsik& operator[](size_t i);
    const Kocsik& operator[](size_t i) const;
    ~Vonat() {
        delete[] k;
    }
};

std::ostream& operator<<(std::ostream&, Kocsitipus);
std::ostream& operator<<(std::ostream&, Kocsik&);

#endif // VONATOK_H_INCLUDED
