#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "adminisztracio.h"
#include "jaratok.h"
#include "functions.h"
#include "jegy.h"
#include "memtrace.h"

void Jegy::jegykiadas() {
    int randomCode1, randomCode2, randomCode;
    srand ((unsigned int)time(NULL));
    std::cout << "Tulajdonos adatai:\n" << tulajdonos.getVezetknev() << " " << tulajdonos.getKeresztnev() << std::endl;
    std::cout << tulajdonos.getSzuldatum() << std::endl;
    std::cout << "A vonat azonositoszama: " << jaratom->getAzon() << std::endl;
    std::cout << "Indulas: " << jaratom->getIndulas() << "\t" << jaratom->getM()[0].getNev() << std::endl;
    Kocsik k = helyetAd(vonatom);
    std::cout << "Kocsi: " << k.getAzon() << "(" << k.getKocsitipus() <<") | Hely: " << k.getFoglalthelyek() + 1 << std::endl;
    std::cout << "Ar: " << jaratom->getMegallokszama() * 210 << " Ft" << std::endl;
    randomCode1 = (rand() % 10 + 100) * 37;
    randomCode2 = (rand() % 10 + 100) * 41;
    randomCode = randomCode1 * randomCode2;
    std::cout << "Az on jegyenek azonosito szama: " << randomCode << std::endl;
    std::cout << "Az allomason kihelyezett automataba a fenti kodot begepelve juthat a jegyehez.";
}
