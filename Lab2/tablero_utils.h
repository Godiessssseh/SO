#ifndef _TABLERO_UTILS_H_
#define _TABLERO_UTILS_H_

#include "celda.h"
#include "jugador.h"
#include "dado.h"
#include <iostream>
#include <unistd.h>


//Funciones de ayuda para el tablero

// inline deja definir funciones en un archivo .h

//Esta función crea un vector de celdas en base a un vector de tipoceldas para las filas externas
//Le pasamos un vector de tipocelda con los parametros que tendran las celdas del vector final
// retorna un vector con las celdas de una fila del tablero
inline std::vector<Celda> armarLineasExtremos(std::vector<Celda::TipoCelda> const& tipos)
{
    std::vector<Celda> linea;
    for(auto const& tipo : tipos)
    {
            Celda aux(tipo);
            linea.emplace_back(aux);
    }
    return linea;
}

//Esta función crea un vector de celdas en base a un vector de tipoceldas para filas intermedias, aquí las celdas intermedias se rellanan vacias
//Le pasamos un vector de tipocelda con los parametros que tendran las celdas del vector final
// retorna un vector con las celdas de una fila del tablero
inline std::vector<Celda> armarLineasIntermedias(std::pair<Celda::TipoCelda, Celda::TipoCelda> const& tipos)
{
    std::vector<Celda> linea;

    Celda first(tipos.first);
    linea.emplace_back(first);

    for(std::size_t i=0; i < 6; i++)
    {
            Celda aux(Celda::TipoCelda::empty);
            linea.emplace_back(aux);
    }

    Celda last(tipos.second);
    linea.emplace_back(last);

    return linea;
}

//Funcion que printea al ganador y su dienero
inline void ganador(Jugador player)
{

    std::cout << std::endl;
    std::cout << "       ¡¡ Finaliza el juego !!\n";
    std::cout << std::endl;
    std::cout << "El jugador " << player.getId() << " ha conseguido 500 o mas Fabochones!! \n";
    std::cout << std::endl;
    std::cout << "El jugador " << player.getId() << " ha ganado con un total de "<<  player.fabopoly() <<" Fabochones!! \n";
    std::cout << std::endl;
    std::cout << "Felicitaciones, ganaste el juego del Calamar \n";
    std::cout << std::endl;
}

//funcion que lleva a cabo los turnos de un jugador por proceso
inline int hacerTurno(int dadito, int jugador,int algo[3])
{
    sleep(1);
    std::cout << " - - - - - - - - Turno del Jugador "<< jugador <<" - - - - - - - - \n" ;
    std::cout << std::endl;
    dadito = -1;
    if(algo[0] == 0)
    {
        std::string x;
        std::cout << "Dinero actual del jugador "<< jugador <<": " << algo[1] << "\n";
        if(jugador ==1)
        {
            std::cout << "Presione cualquier tecla para arrojar el dado (y luego enter)\n";   
            std::cin >> x;
        }
        dadito = tirarDado();
        std::cout << "El numero  del dado obtenido por el jugador "<< jugador <<" fue: " << dadito << "\n";
    }
    else
    {
        std::cout << "Turno perdido \n";
        std::cout << " \n";
    }
    return dadito;
}

#endif // _TABLERO_UTILS_H_