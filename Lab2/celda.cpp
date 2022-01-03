#include "celda.h"

#include <sstream>


//Función que ayuda a convertir el tipo de celda a un string con el formato correcto para mostrar para el tablero
//Recive el valor del tipo de celda
//Retorna el string final 
std::string tipoCeldaToString(Celda::TipoCelda tipo)
{
    //pasa el valor a string según sea el caso
    switch(tipo)
    {
        case Celda::TipoCelda::start:
            return "  Start  ";
        case Celda::TipoCelda::m75:
            return "   +75   ";
        case Celda::TipoCelda::m50:
            return "   +50   ";
        case Celda::TipoCelda::l75:
            return "   -75   ";
        case Celda::TipoCelda::l50:
            return "   -50   ";
        case Celda::TipoCelda::l25:
            return "   -25   ";
        case Celda::TipoCelda::b2:
            return " Back 2  ";
        case Celda::TipoCelda::b4:
            return " Back 4  ";
        case Celda::TipoCelda::b3:
            return " Back 3  ";
        case Celda::TipoCelda::f3:
            return " Fwd 3   ";
        case Celda::TipoCelda::f5:
            return " Fwd 5   ";
        case Celda::TipoCelda::free:
            return "  Free   ";
        case Celda::TipoCelda::jail:
            return "  Jail   ";
        default:
            return "";
    }
}

//Constructor para la celda Start
Celda::Celda()
{
    valor = TipoCelda::start;
    //jugadores.emplace_back(JugadorEnCelda::none);
}

//Constructor para las celdas
Celda::Celda(TipoCelda tipo)
{
    valor = tipo;
    //jugadores.emplace_back(JugadorEnCelda::none);
}

//Función para agregar a un jugador a la lista de jugadores de la celda
//recibe el jugador que se quiere agregar
void Celda::setJugador(Jugador player)
{
    // inserta al final
    jugadores.emplace_back(player);
}

//Función para quitar a un jugador de la lista de jugadores de la celda
//recibe el jugador que se quiere quitar
void Celda::removeJugador(Jugador player)
{
    // Si no existe el jugador en la casilla no se entra en el for
    for(auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        //Lo que esté dentro de it se ve si es igual al jugador que se quiere quitar
        if((*it).getId() == player.getId())
        {
            jugadores.erase(it);
            break;
        }
            
    }
}

//Función que retorna un string que indica el valor (de accion) de la celda si no tiene jugadores en ella o los jugadores que estan en ellas en el caso contrario
//retorna el string final correspondiente al valor en la celda
std::string Celda::toString()
{
    if(valor == TipoCelda::empty)
        return Celda::celdaVacia();
        
    std::stringstream salida;
    salida  << "| ";
    
    //si la celda esta sin jugadores printea el valor de accion de la celda
    if( jugadores.size() == 0)
        salida << tipoCeldaToString(valor);

    // Equivalente en C++ a foreach
    //recorre toda la lista de jugadores y va concatenando en el string de salida los jugadores que hay
    for(auto & jg : jugadores)
    {
        switch(jg.getId())
        {
            case 1:
                salida << "p1 ";
                break;
            case 2:
                salida << "p2 ";
                break;
            case 3:
                salida << "p3 ";
                break;
            default:
                salida << tipoCeldaToString(valor);
                break;
        }
    }
    // mantiene el tamaño de la celda en un tamaño fijo
    if(jugadores.size()!=0 and jugadores.size()<3)
    {
        for(std::size_t i=0; i < (3-jugadores.size());i++)
            salida << "   ";
    }

    salida << "|";

    return salida.str();
}

//Retorna un string predeterminado para las celdas vacias
std::string Celda::celdaVacia()
{
    return "            ";
}

//Metodo que retorna el valor de la celda
Celda::TipoCelda Celda::valorCelda()
{
    return valor;
}