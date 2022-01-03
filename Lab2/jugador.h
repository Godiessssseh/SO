#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include <string>

//Estructura para los jugadores
//Atributos
//dinero: corresponde a un entero que es el dinero actual que tiene el jugador y siempre parate con un valor de 100
//posicion: casilla en que esta el jugador, siendo 0 Start y 27 el -75 que esta a la derecha de Start
//proxTurn: entero que dice si el jugador perdio el proximo turno (0) o no (1)
struct Jugador
{
public:

    //metodo para modificar el dinero del jugador
    //recive el valor a sumar o restar al jugador
    void modDinero(int valor);

    //metodo para mostrar el dinero del jugador
    int fabopoly();

    //metodo para retornar el numero del jugador
    int getId();

    //metodo que cambia la posicion del jugador 
    //Recibe
    //x: posición en x (en que vector se encuentra)
    //y: posicion en y (en que espacio de ese vector se encuentra)
    void setUltimaPos(int x, int y)
    {
        posicion = {x,y};
    };

    //Metodo para devolver la posicion del jugador como una tupla de enteros
    std::pair<int,int> getPos(){ return posicion;};

    //Metodo para devolver el valor de proxTurn
    int valorTurno();

    //Metodo para cambiar el valor de proxTurn
    void cambiarTurno();

    // Constructor
    //Recive un numero (num) que indica que jugador es
    Jugador(int num)
    {
        id = num;
        posicion = {0,0};
        dinero = 100;
        proxTurn = 0;
    };

    // Destructor
    ~Jugador() = default;

private:
    //obliga a construir un jugador entregandole parametros
    Jugador() = delete;

    /* data */

    int id;
    int dinero;
    bool proxTurn;

    //par que indica en que vector y en que parte de ese vector de las celdas del tablero esta el jugador
    std::pair<int, int> posicion;
};

#endif // _JUGADOR_H_