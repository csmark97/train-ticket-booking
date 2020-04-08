#ifndef JEGY_H_INCLUDED
#define JEGY_H_INCLUDED
#include "adminisztracio.h"
#include "jaratok.h"
#include "vonatok.h"
#include "memtrace.h"

class Account;
class Vonat;
class Jarat;

class Jegy {
    Account tulajdonos;
    Vonat* vonatom;
    Jarat* jaratom;

 public:
    Jegy() {}
    Jegy(Account t, Vonat* v, Jarat* j) : tulajdonos(t), vonatom(v), jaratom(j) {}
    Account getTulajdonos() const { return tulajdonos; }
    Vonat* getVonatom() const { return vonatom; }
    Jarat* getJaratom() const { return jaratom; }
    void jegykiadas();
};

#endif // JEGY_H_INCLUDED
