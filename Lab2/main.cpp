#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>  //Para el dado
#include <fstream> // para la escritura
#include "celda.h"
#include "tablero.h"
#include "jugador.h"
#include "tablero_utils.h"

//#include <sys/wait.h>

using namespace std;

int main()
{
    //Se deberían usar varios pipe para pasar la información de los hijos al padre y viceversa.
    int ph01[2];  //Mensaje de Padre a jugador1 o Hijo 1
    int ph10[2];  //Mensaje de Hijo 1 a Padre
    int ph02[2];  //Mensaje de Padre a jug2 o Hijo 2
    int ph20[2];  //Mensaje de Hijo 2 a Padre
    int ph03[2];  //Mensaje de Padre a jug3 o Hijo 3
    int ph30[2];  //Mensaje de Hijo 3 a Padre
    Jugador jugador1(1);   //Creacion del Jugador 1
    Jugador jugador2(2);   //Creacion del Jugador 2
    Jugador jugador3(3);   //Creacion del Jugador 3
    std::vector<Jugador> jugadores = {jugador1, jugador2, jugador3}; // vector de los jugadores para pasarcelo al tablero
    Tablero tablero(jugadores);
    int hijo1,hijo2,hijo3;
    int dadito = -1;

    pid_t p;  // variable para guardar los id de los procesos

    //Revisar que los pipe estén bien hechos y funcionen correctamente.
    if (pipe(ph01) == -1 || pipe(ph10) == -1 || pipe(ph02) == -1 || pipe(ph20) == -1 || pipe(ph03) == -1 || pipe(ph30) == -1)  //Revisar los pipe
    {
        cout << "Se produjo un error en la creacion de los pipes";  //error en los pipes
        return 1;
    }

    //Creación de los procesos hijos
    int familia[]={-1,-2,-3,-4};  
    familia[0] = getpid();  //Proceso padre en la pos 0
    hijo1 = fork(); //Primer proceso hijo
    if (hijo1 != 0)
    {
        //familia[1]= hijo1;  //Proceso Hijo en la pos1
        hijo2 = fork();
        if (hijo2 != 0)
        {
            hijo3 = fork();
            if (hijo3 == 0)
            {
                familia[3]= getpid();  //Proceso Hijo 3 en la pos3
            }
        }
        else
        {
            familia[2] = getpid();  //Proceso hijo 2 en la pos2.
        }
    }
    else
    {
        familia[1]= getpid();  //Proceso Hijo 1 en la pos1
    }

    p = getpid();


    //Bienvenida e inicio del juego ********************
    // "lista" para pasar del padre a los hijos: en la primera posicion el estado del siguiente turno del jugador, en la segunda el dinero del jugador y la tercera la condicion final
    int algo[] = {0,0,0}; 
    if(p == familia[0])
    {   
        cout << "                                     F A B O P O L Y\n";
        cout << endl;
        cout << "                       ¡¡ Bienvenidos a su muerte jugadores !! >:3\n";
        cout << endl;
        cout << "Este sera nuestro tablero \n";
        cout << endl;
        cout << tablero.showTablero(); // mostramos el tablero por pantalla
        cout << endl;
        cout << endl;
        cout << "Usted será el jugador numero 1 (p1) y participara contra otros dos jugadores muy bien entrenados \n";
        cout << endl;
        cout << "Aqui usamos una moneda llamada Fabochon, la cual es más valiosa que los mismos Bitcoins \n";
        cout << endl;
        cout << "Cada vez que pases o caigas en la casilla Start ganaras 100 Fabochones \n";
        cout << endl;
        cout << "El primero en conseguir 500 o mas Fabochones gana el juego \n";
        cout << endl;
        cout << "¡COMENCEMOS! \n";
        cout << endl;
        algo[0] = jugador1.valorTurno();
        algo[1] = jugador1.fabopoly();
        algo[2] = 0; //Condición de termino del juego, cuando tome el valor de un jugador entonces ese jugador habra ganado
        write(ph01[1],&algo,sizeof(algo));
    }

    // Se juega hasta que alguien gane y entonces algo[2] sera igual al numero del jugador ganador
    while(algo[2] == 0)
    {   
        //Turno jugador 1
        if (p == familia[1])
        {  //Jugador 1. Aquí se hace el proceso, el jugador 1 solo apreta el dado. El jug 2 y 3 se DEBE hacer automático.
            while(read(ph01[0],&algo,sizeof(algo)) < 0){}
            if(algo[2] == 0)
            {
                dadito = hacerTurno(dadito, 1,algo);                
                write(ph10[1],&dadito,sizeof(int));
            }
            else{break;}
        }
        if (p == familia [0])
        {
            while(read(ph10[0],&dadito,sizeof(int)) < 0){}
            if(dadito != -1)
            {
                tablero.play(dadito, jugador1);
                if(jugador1.fabopoly() >= 500 && algo[2] == 0)
                {
                    algo[2] = 1;
                    write(ph01[1],&algo,sizeof(algo));
                    write(ph02[1],&algo,sizeof(algo));
                    write(ph03[1],&algo,sizeof(algo));
                    break;
                }
            }
            if (algo[0] ==1)
            {
                jugador1.cambiarTurno();
            }
            algo[0] = jugador2.valorTurno();
            algo[1] = jugador2.fabopoly();
            write(ph02[1],&algo,sizeof(algo));                
        }

        //Turno jugador 2
        if (p == familia[2])
        {
            while(read(ph02[0],&algo,sizeof(algo)) < 0){}
            if(algo[2] == 0)
            {
                dadito = hacerTurno(dadito, 2,algo);            
                write(ph20[1],&dadito,sizeof(int));
            }
            else{break;}
            
        }
        if (p == familia [0])
        {
            while(read(ph20[0],&dadito,sizeof(int)) < 0){}
            if(dadito != -1)
            {
                tablero.play(dadito, jugador2);
                if(jugador2.fabopoly() >= 500 && algo[2] == 0) 
                {
                    algo[2] = 2;
                    write(ph01[1],&algo,sizeof(algo));
                    write(ph02[1],&algo,sizeof(algo));
                    write(ph03[1],&algo,sizeof(algo));
                    break;
                }
            }
            if (algo[0] ==1)
            {
                jugador2.cambiarTurno();
            }
            algo[0] = jugador3.valorTurno();
            algo[1] = jugador3.fabopoly();
            write(ph03[1],&algo,sizeof(algo));                
        }


        //Turno jugador 3
        if (p == familia[3])
        {
            while(read(ph03[0],&algo,sizeof(algo)) < 0){}
            if(algo[2] == 0)
            {
                dadito = hacerTurno(dadito, 3,algo);                
                write(ph30[1],&dadito,sizeof(int));
            }
            else{break;}
            
        }
        if (p == familia [0])
        {
            while(read(ph30[0],&dadito,sizeof(int)) < 0){}
            if(dadito != -1)
            {
                tablero.play(dadito, jugador3);
                if(jugador3.fabopoly() >= 500 && algo[2] == 0)
                {
                    algo[2] = 3;
                    write(ph01[1],&algo,sizeof(algo));
                    write(ph02[1],&algo,sizeof(algo));
                    write(ph03[1],&algo,sizeof(algo));
                    break;
                }
            }
            if (algo[0] ==1)
            {
                jugador3.cambiarTurno();
            }
            algo[0] = jugador1.valorTurno();
            algo[1] = jugador1.fabopoly();
            write(ph01[1],&algo,sizeof(algo));                
        }
        
    }
   
    if(familia[0]== p)
    {
        if(algo[2] == 1  ){
            ganador(jugador1);
        }
        else if(algo[2] == 2 )
        {
            ganador(jugador2);
        }
        else if (algo[2] ==3)
        {
            ganador(jugador3);
        }
    }
    

    pid_t wpid;
    int status =0;
    while((wpid = wait(&status))>0){}

    return 0;   
}