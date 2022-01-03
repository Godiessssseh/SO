#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    char name[100] = "Laberinto";
    mkdir(name, 0777); //Crear el directorio principal y definir variables útiles.
    int i;
    int j;
    int k;
    for (i = 1; i <= 3; i++) { //Primer nivel de directorios
        char name[100] = "Laberinto";
        char prueba[100];
        char slatchh[100] = "/";
        sprintf(prueba, "%d", i);   //Guarda el valor de i en prueba (como string)
        strcat(slatchh, prueba);     //Unir / con el i => /1 /2 /3
        strcat(name, slatchh);        //Une laberinto/1,  laberinto/2, laberinto/3
        mkdir(name, 0777);
        char const *a = name;

        for (j = 1; j <= 3; j++) { //Segundo nivel de directorios
            char nombre[100] = "";
            strcpy(nombre, a);
            char prueba[100] = "";
            char slatchh[100] = "/";
            sprintf(prueba, "%d", j);  //Pasamos el valor de j a prueba (como string)
            strcat(slatchh, prueba);        //Le agregamos el / con el j -> /1 /2 / 3
            strcat(nombre, slatchh);
            mkdir(nombre, 0777);
            char const *b = nombre;

            for (k = 1; k <= 3; k++) { //Tercer nivel de directorios
                char fabodios[100] = "";
                strcpy(fabodios, b);
                char prueba[100] = "";
                char slatchh[100] = "/";
                sprintf(prueba, "%d", k);  //Pasamos el valor de k a prueba (como string)
                strcat(slatchh, prueba);        //Le agregamos el / con el k -> /1 /2 / 3
                strcat(fabodios, slatchh);
                mkdir(fabodios, 0777);

            }
        }
    }
    char const slach[100] = "/";
    char frase[20] = "/frase.txt";
    srand(time(NULL));  //Inicializar la seed para que sea random (Sin esto, tira errores y no son numeros al azar)
    char** nandona = (char**)malloc(sizeof(char*)*3);
    for (int x = 0; x < 3; x++) 
    {
        nandona[x] = (char*)malloc(sizeof(char)*256);
        strcpy(nandona[x]," ");
    }

    for (int i = 1; i <= 3; i++)    //Cada valor de i será util para escribir cada frase
    {
        FILE* arch;                 //Definir variables + archivos.
        int direct1;
        int direct2;
        int direct3;
        char lab[100] = "./Laberinto";
        //int flag =2;

        char funcionar[100]="";
        char ayayay[100] ="";

        int uniquePath = 0;
        while(uniquePath == 0)
        {
            uniquePath = 1;
            strcpy(ayayay,slach);   //Copiar permanentemente el / definidio como constante
            direct1 = rand() %3 +1;     //Numeros random entre 1 a 3
            direct2 = rand() %3 +1;
            direct3 = rand() %3 +1;

            //Primer nivel  Laberinto/1
            sprintf(funcionar,"%d",direct1); //Numero random a string
            strcat(ayayay,funcionar); //Concatenar el / con el numero random
            strcat(lab,ayayay); //Unir el /random con Laberinto
            strcpy(ayayay,slach); //Copiar permanentemente el /

            //Segundo Nivel  Laberinto/1/2
            sprintf(funcionar,"%d",direct2);
            strcat(ayayay,funcionar);
            strcat(lab,ayayay);
            strcpy(ayayay,slach); //Copiar permanentemente el /

            //Tercer Nivel  Laberinto/1/2/3
            sprintf(funcionar,"%d",direct3);
            strcat(ayayay,funcionar);
            strcat(lab,ayayay);
            
            for(int j=0;j<3;j++)
                if(strcmp(lab,nandona[j]) == 0)
                {
                    uniquePath = 0;
                }
            strcpy(nandona[i-1], lab);
            strcat(lab,frase);
        }
        //Ver cual archivo se ingresa
        if(i==1)
        {
            arch = fopen(lab, "w+");
            fputs("1, Los hurones del", arch);
            fclose(arch);
        }
        else if(i==2)
        {
            arch = fopen(lab, "w+");
            fputs("2, profesor de sistemas operativos son", arch);
            fclose(arch);
        }
        else
        {
            arch = fopen(lab, "w+");
            fputs("3, los que me carrean jugando lol", arch);
            fclose(arch);
        }
        strcpy(nandona[i-1],lab);

    }
    for (int i = 0; i < 3; ++i) 
    {
        free(nandona[i]);
    }
    free(nandona);
}