package Tarea;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

/*
Clase-Hebra que resuelve el problema de la traduccion desde Morse.
Atributos: fooo -> Clase con atributo Long donde guardaremos el tiempo.
Metodo: run() -> Correr el problema.
*/

public class Morse extends Thread
{
    private Foo fooo;
    public Morse(Foo foo)
    {
        fooo = foo;
    }

    @Override
    public void run()   
    { 

        //Alfabeto es un arraylist con todas las letras del alfabeto, Morse es lo mismo pero en Morse. ESTÁN EN ORDEN.

        String Alfabeto[] = {"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"};

        String Morse[] = {".-","-...","-.-.","-..",".","..-.","--.", "....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",
                ".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

        String end = "";  //String que se printeará al final.

        //Abrir y leer el archivo.
        Scanner sc2 = null;
        //Catch si el archivo no existe.
        try
        {
            sc2 = new Scanner(new FileInputStream("./morse.txt"));  //El source del archivo puede variar!
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found.");
        }

        while(sc2.hasNext()) //Mientras tenga una linea/informacion
        {
            String[] tokens = sc2.nextLine().split(" ");  //Obtenemos la linea y la separamos. Si tiene " ", se mete a un arraylist
            //Se recorre según el largo de la token, quizás puede optimizarse.
            for (int n=0;n < tokens.length;n++)
            {
                int fabo = Arrays.asList(Morse).indexOf(tokens[n]);  //Guardar el index, buscarlo en alfabeto y unir strings.
                end = end + Alfabeto[fabo];  //Se agrega la traducción al string final.
            }
            end = end+" ";  //Un espacio de separación para que se vea ordenado.
        }
        sc2.close();  //Cerrar el archivo
        System.out.println(end);
        fooo.run();
    }
}

