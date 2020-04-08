#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "adminisztracio.h"
#include "jaratok.h"
#include "jegy.h"
#include "memtrace.h"

void Kocsik::set(int id, Kocsitipus k, int fh) {
    azon = id;
    kt = k;
    foglalthelyek = fh;
}

int Kocsik::maxotmeghataroz() {
    if (kt == TERMES)
        return 100;
    else
        return 90;
}

Kocsik& Vonat::operator[](size_t i) {
    return k[i];
}

const Kocsik& Vonat::operator[](size_t i) const {
    return k[i];
}


std::ostream& operator<<(std::ostream& os, Kocsitipus kt) {
    if (kt == TERMES)
        os << "Termes";
    else
        os << "Kabinos";
    return os;
}

std::ostream& operator<<(std::ostream& os, Kocsik &k) {
    os << "\tKocsiszam: " << k.getAzon() << "\tTipusa: " << k.getKocsitipus() << "Eddig foglalt: " << k.getFoglalthelyek() << std::endl;
    return os;
}
