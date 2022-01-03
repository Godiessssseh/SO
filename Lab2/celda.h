#ifndef _CELDA_H_
#define _CELDA_H_

#include "jugador.h"

#include <string>
#include <vector>


//Estructura para las celdas
//Atributos
//valor: es de tipo TipoCelda y guarda el valor al que corresponde la celda
//Jugadores: vector de jugadores que estan en la casilla
//Tipos definidos dentro de la clase
//TipoCelda: Tipos de valores que puede tomar la casilla
//JugadorEnCelda: Tipos de valores que indica que jugadores estan en la casilla 
struct Celda
{
public:
    //"lista" de valores que pueden tomar las celdas como accion
    enum class TipoCelda
    {
        start, m75, m50, l75, l50, l25, b2, b4, b3, f3, f5, free, jail, empty 
    };

    // Constructor Vacio, crea celdas start
    Celda();

    //Constructor para celdas diferentes
    Celda(TipoCelda tipo);

    // Destructor por defecto
    ~Celda() = default;

    //Metodo para agregar un jugador a jugadores
    //void setJugador(JugadorEnCelda player);
    void setJugador(Jugador player);

    //Metodo para quitar un jugador de jugadores
    void removeJugador(Jugador player);

    //Metodo que imprime la celda vacia
    std::string celdaVacia();

    //Metodo que imprime la celda 
    std::string toString();

    //Metodo que retorna el valor de la celda
    TipoCelda valorCelda();
    
private:
    /* data */
    TipoCelda valor;
    // Template
    std::vector<Jugador> jugadores;
};

//Así podemos exportarlo para que no la use solo este struct
std::string tipoCeldaToString(Celda::TipoCelda tipo);


#endif // _Celda_H_