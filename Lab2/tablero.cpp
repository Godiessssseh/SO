#include "tablero.h"
#include "tablero_utils.h"

#include <iostream>
#include <sstream>


//Constructor para la creación del tablero 
Tablero::Tablero()
{
    // 8x8
    // 1ra linea
    // primeraLinea es un vector constante 
     std::vector<Celda::TipoCelda> const primeraLinea = { Celda::TipoCelda::start,
                                                         Celda::TipoCelda::l75,
                                                         Celda::TipoCelda::l25,
                                                         Celda::TipoCelda::b4,
                                                         Celda::TipoCelda::m75,
                                                         Celda::TipoCelda::f5,
                                                         Celda::TipoCelda::m75,
                                                         Celda::TipoCelda::jail
                                                        };
    tabl.emplace_back(armarLineasExtremos(primeraLinea)); // el retorno del vector se agrega al tablero

    // 2da linea
   
    std::pair<Celda::TipoCelda, Celda::TipoCelda> segundaLinea = {Celda::TipoCelda::m50, Celda::TipoCelda::l25};
    tabl.emplace_back(armarLineasIntermedias(segundaLinea)); // el retorno del vector se agrega al tablero

    // 3ra linea
    
    std::pair<Celda::TipoCelda, Celda::TipoCelda> terceraLinea = {Celda::TipoCelda::m50, Celda::TipoCelda::l50};
    tabl.emplace_back(armarLineasIntermedias(terceraLinea)); // el retorno del vector se agrega al tablero

    // 4taa linea
   
    std::pair<Celda::TipoCelda, Celda::TipoCelda> cuartaLinea = {Celda::TipoCelda::l25, Celda::TipoCelda::m50};
    tabl.emplace_back(armarLineasIntermedias(cuartaLinea)); // el retorno del vector se agrega al tablero
 
    // 5ta linea
    
    std::pair<Celda::TipoCelda, Celda::TipoCelda> quintaLinea = {Celda::TipoCelda::b2, Celda::TipoCelda::b4};
    tabl.emplace_back(armarLineasIntermedias(quintaLinea)); // el retorno del vector se agrega al tablero

    // 6ta linea
   
    std::pair<Celda::TipoCelda, Celda::TipoCelda> sextaLinea = {Celda::TipoCelda::m50, Celda::TipoCelda::m50};
    tabl.emplace_back(armarLineasIntermedias(sextaLinea)); // el retorno del vector se agrega al tablero

    // 7ma linea
    
    std::pair<Celda::TipoCelda, Celda::TipoCelda> septimaLinea = {Celda::TipoCelda::l25, Celda::TipoCelda::f3};
    tabl.emplace_back(armarLineasIntermedias(septimaLinea)); // el retorno del vector se agrega al tablero

    // 8va linea
   
    std::vector<Celda::TipoCelda> const ultimaLinea = { Celda::TipoCelda::jail,
                                                         Celda::TipoCelda::m75,
                                                         Celda::TipoCelda::l50,
                                                         Celda::TipoCelda::l50,
                                                         Celda::TipoCelda::m75,
                                                         Celda::TipoCelda::m75,
                                                         Celda::TipoCelda::b3,
                                                         Celda::TipoCelda::free
                                                        };
    tabl.emplace_back(armarLineasExtremos(ultimaLinea)); // el retorno del vector se agrega al tablero
}

Tablero::Tablero(std::vector<Jugador>& jugadores):Tablero()
{
    //Tablero();
    this->showTablero();
    for(auto & jugador : jugadores)
    {
        tabl[0][0].setJugador(jugador); 
        jugador.setUltimaPos(0,0); 
    }
}

//Funcion que entrega el estado actual del tablero en forma de string
//retorna el string del tablero
std::string Tablero::showTablero()
{
    std::stringstream tablero;

    // Recorrer las lineas en orden inverso (de abajo hacia arriba por rbegin)
    //it es un vector de casillas (una fila)
    bool verbose = false;
    if(verbose)
    {
        std::cout << "[0,0]: " << tabl[0][0].toString() << std::endl;
        std::cout << "[0,1]: " << tabl[0][1].toString() << std::endl;
        std::cout << "[1,0]: " << tabl[1][0].toString() << std::endl;
        std::cout << "[0,7]: " << tabl[0][7].toString() << std::endl;
        std::cout << "[7,7]: " << tabl[7][7].toString() << std::endl;
        std::cout << "[7,0]: " << tabl[7][0].toString() << std::endl;
    }

    for(auto it = tabl.rbegin(); it != tabl.rend(); ++it)
    {
        //para cada casilla de la fila
        for(auto casilla : *it)
        {
            tablero << casilla.toString();
        }
        tablero << "\n";
    }

    return tablero.str();
}


//Funcion para mover al jugador de posicion en el tablero
//Recibe
//mov: cantidad de espacios que se mueve el jugador
//jugador: jugador que va a moverse por el tablero
void Tablero::play(int mov, Jugador& jugador)
{
    // celda actual del jugador
    auto pos = jugador.getPos();

    if(mov>0)
    {
        // [0,0][0,7] => y+
        //Si el jugador esta dentro de las primeras 7 casillas se mueve de esta manera (de la 0 a la 7)
        if(pos.second == 0 and pos.first < 7)
        {
            auto newPos = pos.first + mov;
            if (newPos > 7)
            {
                auto extra = newPos%7;
                pos.second+= extra;
                pos.first = 7;
            }
            else
                pos.first += mov;
        }
        // [0,7][7,7] => x+
        //Si el jugador esta entre las casillas 8 y la 13 se mueve de esta manera 
        else if(pos.second < 7 and pos.first == 7)
        {
            auto newPos = pos.second + mov;
            if (newPos > 7)
            {
                auto extra = newPos%7;
                pos.first -= extra;
                pos.second = 7;
            }
            else
                pos.second += mov;
        }
        //[7,7][7,0] => y-
        //Si el jugador esta entre las casillas 14 y la 20 se mueve de esta manera
        else if(pos.second == 7 and pos.first > 0 )
        {
            auto newPos = pos.first - mov;
            if (newPos < 0)
            {
                //auto extra = newPos*-1;
                pos.second+= newPos;
                pos.first = 0;
            }
            else
                pos.first -= mov;   
        }
        //[7,0][0,0] => x-
        //Si el jugador esta entre las casillas 21 y la 27 se mueve de esta manera
        else
        {
            auto newPos = pos.second - mov;
            if(newPos < 0)
            {
                pos.first += newPos*-1;
                pos.second = 0;
                jugador.modDinero(100);
                std::cout << " Pasaste por Start, se añaden 100 Fabochones a tu dinero\n";
                std::cout << std::endl;
            }
            else
            {
                pos.second -= mov;
                if (pos.second == 0)
                    jugador.modDinero(100);
            }
            
        }
    }
    else
    {
        if(mov == -2)
        {
            pos.first = 2;
            pos.second = 0;
        }
        else if(mov == -3)
        {
            pos.first = 7;
            pos.second = 3;
        }
        else
        {
            if(pos.second == 7)
            {
                pos.first = 7;
                pos.second = 6;
            }
            else
            {
                pos.first = 0;
                pos.second = 7;
            }
        }
    }
    
    //Coloca en el tablero al jugador en la posición correspondiente obtenida
    tabl[pos.first][pos.second].setJugador(jugador);
    //Quita del tablaro la posición anterior de ese jugador
    tabl[jugador.getPos().first][jugador.getPos().second].removeJugador(jugador);
    //Cambias dentro del jugador la posición a la actual
    jugador.setUltimaPos(pos.first,pos.second);

    Celda::TipoCelda dieguito = tabl[pos.first][pos.second].valorCelda();

    std::cout << "El jugador ha caido en la casilla" << tipoCeldaToString(dieguito) << "\n";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << showTablero(); // mostramos el tablero por pantalla
    std::cout << std::endl;
    std::cout << std::endl;

    efectoCelda(dieguito, jugador);

}


//
void Tablero::efectoCelda(Celda::TipoCelda valorCelda, Jugador& player)
{
    switch(valorCelda)
    {
        case Celda::TipoCelda::m75:
            player.modDinero(75);
            std::cout << "Por lo tanto el jugador gana 75 Fabochones" << "\n";
            std::cout << std::endl;
            std::cout << "Dinero actualizado del jugador: " << player.fabopoly() << "\n";
            std::cout << std::endl;
            break;
        case Celda::TipoCelda::m50:
            player.modDinero(50);
            std::cout << "Por lo tanto el jugador gana 50 Fabochones" << "\n";
            std::cout << std::endl;
            std::cout << "Dinero actualizado del jugador: " << player.fabopoly() << "\n";
            std::cout << std::endl;
            break;
        case Celda::TipoCelda::l75:
            player.modDinero(-75);
            std::cout << "Por lo tanto el jugador pierde 75 Fabochones" << "\n";
            std::cout << std::endl;
            std::cout << "Dinero actualizado del jugador: " << player.fabopoly() << "\n";
            std::cout << std::endl;
            break;
        case Celda::TipoCelda::l50:
            player.modDinero(-50);
            std::cout << "Por lo tanto el jugador pierde 50 Fabochones" << "\n";
            std::cout << std::endl;
            std::cout << "Dinero actualizado del jugador: " << player.fabopoly() << "\n";
            std::cout << std::endl;
            break;
        case Celda::TipoCelda::l25:
            player.modDinero(-25);
            std::cout << "Por lo tanto el jugador pierde 25 Fabochones" << "\n";
            std::cout << std::endl;
            std::cout << "Dinero actualizado del jugador: " << player.fabopoly() << "\n";
            std::cout << std::endl;
            break;
        case Celda::TipoCelda::b2:
            std::cout << "Por lo tanto el jugador retrocede 2 espacios" << "\n";
            std::cout << std::endl;
            play(-2,player);
            break;
        case Celda::TipoCelda::b4:
            std::cout << "Por lo tanto el jugador retrocede 4 espacios" << "\n";
            std::cout << std::endl;
            play(-4,player);
            break;
        case Celda::TipoCelda::b3:
            std::cout << "Por lo tanto el jugador retrocede 3 espacios" << "\n";
            std::cout << std::endl;
            play(-3,player);
            break;
        case Celda::TipoCelda::f3:
            std::cout << "Por lo tanto el jugador avanza 3 espacios" << "\n";
            std::cout << std::endl;
            play(3,player);
            break;
        case Celda::TipoCelda::f5:
            std::cout << "Por lo tanto el jugador avanza 5 espacios" << "\n";
            std::cout << std::endl;
            play(5,player);
            break;
        case Celda::TipoCelda::free:
            std::cout << "Estas en Free , relajate mientras puedas... \n";
            std::cout << std::endl;
            break;
        case Celda::TipoCelda::jail:
            player.cambiarTurno();
            std::cout << "Estas en la carcel, pierdes un turno, F\n";
            std::cout << std::endl;
            break;
        case Celda::TipoCelda::start:
            std::cout << "Es peligroso ir solo, toma este dinerillo (ganas 100 Fabochones)\n";
            std::cout << std::endl;
            std::cout << "Dinero actualizado del jugador: " << player.fabopoly() << "\n";
            std::cout << std::endl;
            break;
        default:
            std::cout << "\n";
            break;
    }
}