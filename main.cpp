#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "adminisztracio.h"
#include "jaratok.h"
#include "functions.h"
#include "vonatok.h"
#include "jegy.h"
#include "memtrace.h"

int main() {
    unsigned int valasztas;
    do {
    std::cout << "Udvozlom a programban!" << std::endl;
    std::cout << "\nJelentkezzen be vagy regisztraljon uj fiokot!\n\t1: Bejelentkezes\n\t2: Regisztracio\n\t3: Kilepes\n\t0: Vonatok felvetele(admin)";
        std::cin >> valasztas;
        switch(valasztas) {
        case 0: adminfelulet();  break;
        case 1: bejelentkezes(); break;
        case 2: regisztracio(); break;
        case 3: break;
        }
    } while(valasztas != 3);
	return 0;
}
