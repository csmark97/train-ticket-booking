#ifndef ADMINISZTRACIO_H_INCLUDED
#define ADMINISZTRACIO_H_INCLUDED
#include <string>
#include "memtrace.h"

class Datum {
    int ev;
    int ho;
    int nap;

 public:
    Datum() {}
    Datum(int e, int h, int n) :ev(e),  ho(h), nap(n) {}
    int getEv() const { return ev; }
    int getHo() const { return ho; }
    int getNap() const { return nap; }
    friend std::istream& operator>>(std::istream&, Datum&);
};

class Idopont {
    int ora;
    int perc;

 public:
    Idopont() {}
    Idopont(int o, int p) :ora(o), perc(p) {}
    int getOra() const { return ora; }
    int getPerc() const { return perc; }
    friend std::istream& operator>>(std::istream&, Idopont&);
};

class Account {
    std::string felhaszn;
    std::string jelszo;
    std::string vezeteknev;
    std::string keresztnev;
    Datum szuldatum;

 public:
    Account() {}
    Account(std::string fn, std::string jlsz, std::string vezn, std::string knev, Datum szd)
                        :felhaszn(fn), jelszo(jlsz), vezeteknev(vezn), keresztnev(knev), szuldatum(szd) {}
    std::string getFelhaszn() const { return felhaszn; }
    std::string getJelszo() const { return jelszo; }
    std::string getVezetknev() const { return vezeteknev; }
    std::string getKeresztnev() const { return keresztnev; }
    Datum getSzuldatum() const { return szuldatum; }
    void set(std::string, std::string, std::string, std::string, Datum);
    friend std::istream& operator>>(std::istream&, Account);
    friend void acccheck(std::string, std::string, Account&);
};

void acctofile(Account);
void bejelentkezes();
void regisztracio();

std::ostream& operator<<(std::ostream&, Datum);
std::ostream& operator<<(std::ostream&, Account);
std::ostream& operator<<(std::ostream&, Idopont);

#endif // ADMINISZTRACIO_H_INCLUDED
