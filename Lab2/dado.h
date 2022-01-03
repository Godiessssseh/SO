#ifndef _DADO_H_
#define _DADO_H_

#include <random>
#include <iostream>     /* cout (print) */
using namespace std;

inline int tirarDado() {
    int dadito;
    random_device rd;   // Generador no deterministico
    mt19937 gen(rd());  // to seed mersenne twister. (Es un nombre genérico el mt no c cuanto) 
    uniform_int_distribution<> dist(1,6); // Distribución entre 1 a 6 (Dado)
    dadito = dist(gen);  //Le damos el valor a dadito
    return dadito;  //Se retorna 
}

#endif