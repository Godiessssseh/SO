#ifndef _TABLERO_H_
#define _TABLERO_H_

#include "celda.h"
#include "jugador.h"


//Estructura para el tablero
//Atributos
//tabl: corresponde a un vector de vectores de celdas
struct Tablero
{
public:

    //metodo para convertir el estado del tablero a string
    std::string showTablero();


    //metodo para realizar los efecto de la celda en el juego
    void efectoCelda(Celda::TipoCelda valorCelda, Jugador& player);

    //Funcion para mover al jugador de posicion en el tablero
    void play(int mov, Jugador& jugador);

    // Constructor del tablero base
    Tablero();

    //Constructor con parametros para poner a los jugadores en el inicio
    Tablero(std::vector<Jugador>& jugadores);

    // Destructor
    ~Tablero() = default;

private:
    /* data */
    //Vector de Vectores de celdas
    std::vector<std::vector<Celda>> tabl;
};

#endif // _TABLERO_H_