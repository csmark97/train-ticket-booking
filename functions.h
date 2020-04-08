#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "adminisztracio.h"
#include "jaratok.h"
#include "vonatok.h"
#include "jegy.h"
#include "memtrace.h"

Kocsik kocsiletrehoz(int);
int vonatletrehoz();
void vonattofile(const Vonat &v);
Megallok megalloletrehoz(int);
void jaratletrehoz(int);
void adminfelulet();
void felhasznaloifelulet(Account a);
void jarattofile(Jarat&);
Jarat* jaratkereses(int);
Vonat* vonatkereses(int);
void jaratkereses(std::string, std::string);
Kocsik helyetAd(Vonat* vonatunk);

#endif // FUNCTIONS_H_INCLUDED
