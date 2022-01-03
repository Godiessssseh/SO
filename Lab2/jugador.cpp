#include "jugador.h"

#include <sstream>

//estas funciones estan definidas en el archivo jugador.h

void Jugador::modDinero(int valor)
{
    dinero += valor;
}

int Jugador::fabopoly()
{
    return dinero;
}

int Jugador::getId()
{ 
    return id;
}

//Metodo para devolver el valor de proxTurn
int Jugador::valorTurno()
{
    return proxTurn;
}

//Metodo para cambiar el valor de proxTurn
void Jugador::cambiarTurno()
{
    if(proxTurn == 0)
        proxTurn = 1;
    else
    {
        proxTurn = 0;
    }
}