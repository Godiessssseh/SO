#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>

//Path es el directorio donde inicia la búsqueda y dirContents es una lista de strings
//Obtiene el path y un array con los contenidos del directorio.
//Devuelve nada porque es void

void getDirContents(char* path, char** dirContents) //Funcion recursiva para obtener el contenido del directorio
{
    DIR *d;     //Abrir un directorio
    struct dirent *dir;  //Strut para directorios
    d = opendir(path);  //Abrir el directorio en el path ingresado
    if (d)
    {
        int i = 0;
        while ((dir = readdir(d)) != NULL)      //Leer el directorio y ver si es distinto de null
        {
            //printf("%s\n", dir->d_name);    //Revisa que valor tiene la dirección de memoria
            if(i>1)
            {
                strcpy(dirContents[i-2], dir->d_name);  //Obtener el contenido del directorio.
            }
            i++;
        }
        closedir(d);
    }
}

//Files una lista con las direcciones de donde están los archivos .txt
//Obtiene el path, un array con los archivos, la profundidad (de la raiz), y los archivos restantes.
//No retorna nada porque es un void.

void LookForFiles(char* const path, char** files, int depth, int* remainingFiles)  //Buscar los archivos
{
    if(*remainingFiles < 0)  //Archivos restantes es igual a 0, se termina.
        return;

    //printf("Current Path: %s\n", path);       //Saber en cual Path estamos
    

    char** dirContents = (char**)malloc(sizeof(char*)*depth);  //El contenido del directorio con su memoria correspondiente
    for (int i = 0; i < depth; i++)
    {
        dirContents[i] = (char*)malloc(sizeof(char)*256);   //Pedir memoria para cada parte del arreglo
        strcpy(dirContents[i], ""); 
    }
    //GetDirContents retorna una lista de todos los archivos de los directorios que no son "." o ".."
    getDirContents(path, dirContents);

    //Dir no está vacío, asi que o es la raíz o un nodo intermedio del árbol
    if( dirContents[0][0] != '\0')    //dirContents tiene lo que está en la carpeta y con el \0 revisa si es que está vacío o no.
    {
        //Si la carpeta NO está vacía, entramos fiuuuuuum
        for( int i = 0; i < depth; i++ )
        {
            if( strstr(dirContents[i], ".txt") != NULL )    //Busca un sub-string dentro del elemento actual
            {
                //printf("File %s found in %s !\n", dirContents[i], path);  //Saber en que dirección está el file.
                char* auxPath = (char*)malloc(sizeof(char)*256);
                strcpy(auxPath,path);    //Creamos un path auxiliar para utilizar
                strcat(auxPath,"/");    //Concatenar el /
                strcat(auxPath, dirContents[i]);   //Concatenar el path con el nombre de la carpeta
                strcpy(files[*remainingFiles-1], auxPath);    //Se copia a Files, y se encuentra un directorio
                (*remainingFiles)--;    //Encontramos un archivo! :D nos faltan más (?)
                free(auxPath);
                if(*remainingFiles == 0)
                {
                    char** finalMessage = (char**)malloc(sizeof(char*)*depth);
                    for (int i = 0; i < depth; i++)
                    {
                        finalMessage[i] = (char*)malloc(sizeof(char)*256);
                    }

                    for (int i = 0; i < depth; i++)
                    {
                        FILE* f = fopen(files[i], "r");
                        
                        size_t len = 256;
                        char* text = (char*)malloc(sizeof(char)*len);
                        ssize_t read;
                        if((read = getline(&text, &len, f)) != -1)
                        {
                            //printf("Text %s\n",text);  //Imprime el texto correspondiente, si es el 1, 2 o 3.
                            char* tokens;
                            tokens = strtok(text, ",");
                            int index = atoi(tokens);
                            tokens = strtok(NULL, ",");
                            strcpy(finalMessage[index-1], tokens+1);
                        }
                        free(text);
                        fclose(f);
                    }

                    for (int i = 0; i < depth; i++)
                        printf("%s ", finalMessage[i]);
                    printf("\n");

                    (*remainingFiles)--;

                    for (int i = 0; i < depth; i++)
                    {
                        free(finalMessage[i]);
                    }
                    free(finalMessage);

                    for (int i = 0; i < depth; i++)
                    {
                        free(dirContents[i]);
                    }
                    free(dirContents);
                    return;
                }
                break;

            }
            //Estamos en un nodo intermedio. Se corre nuevamente con el path nuevo para trabajar con los nodos (recursión)
            char* auxStr = (char*)malloc(sizeof(char)*256);
            strcpy(auxStr, path);
            strcat(auxStr, "/");
            strcat(auxStr,dirContents[i]);
            LookForFiles(auxStr, files, depth, remainingFiles);
            free(auxStr);
            //free(currNode);
        }

    }
    for (int i = 0; i < depth; i++)
    {
        free(dirContents[i]);
    }
    free(dirContents);
}
int main(void){
    int depth = 3;
    int remainingFiles = 3;
    char** files = (char**)malloc(sizeof(char*)*depth);
    for (int i = 0; i < depth; i++)
    {
        files[i] = (char*)malloc(sizeof(char)*256);    //Lista de los archivos
        strcpy(files[i],"");    //Copia al espacio un ""
    }
    LookForFiles("./Laberinto", files, depth, &remainingFiles);
    for (int i = 0; i < depth; ++i)
    {
        free(files[i]);
    }
    free(files);
}
