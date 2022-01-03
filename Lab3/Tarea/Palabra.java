package Tarea;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

/*
Clase-Hebra que resuelve el problema Palabra que busca la palabra eiffel en un archivo .txt.
Atributos: fooo -> Clase con atributo Long donde guardaremos el tiempo.
Metodo: run() -> Correr el problema.
*/

public class Palabra extends Thread
{
    private Foo fooo;
    public Palabra(Foo foo)
    {
        fooo = foo;
    }

    @Override
    public void run() 
    {
        int cont = 1;  //Un contador simplemente para el print.
        String word = "eiffel";
        //Abrir y leer el archivo.
        Scanner sc2 = null;
        //Catch si el archivo no existe.
        try
        {
            sc2 = new Scanner(new FileInputStream("./palabras.txt")); 

        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found.");
        }
        while(sc2.hasNextLine())  //Se revisa que haya info en la siguiente linea, si hay True, sino False
        {
            String line = sc2.nextLine();  //Le damos la linea siguiente a Line
            if(line.indexOf(word)!=-1)  //Revisamos si existe la palabra en esa linea, si existe nos dará un index dif de -1. sino, F
            {
                System.out.println(word);  //Imprimimos la palabra.
                cont = 0;  //Se cambia el contador, para que no imprima abajo
                break;  //Primera ocurrencia, se corta de raíz.
            }
        }sc2.close();
        //Lo siguiente ocurre solamente si no existe/no se encuentra la palabra.
        if (cont!=0)
        {
            System.out.println("Word not found :c");
        }
        fooo.run();
    }
}

