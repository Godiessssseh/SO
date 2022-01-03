package Tarea;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList; // import the ArrayList class

/*
Clase-Hebra que resuelve el problema Numero que consiste en encontrar dos numeros que sumen 65.
Atributos: fooo -> Clase con atributo Long donde guardaremos el tiempo.
Metodo: run() -> Correr el problema.
*/

public class Numero extends Thread
{   
    private Foo fooo;
    public Numero(Foo foo)
    {
        fooo = foo;
    }

    @Override
    public void run() 
    {
        int num;
        boolean diegaso = false;

        List<Integer> numeros = new ArrayList<Integer>();

        //Abrir y leer el archivo.
        Scanner sc2 =  null;
        //Catch si el archivo no existe.
        try
        {
            sc2 = new Scanner(new FileInputStream("./numeros.txt"));    
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File not found.");
        }
        
        while(sc2.hasNextInt()) //Mientras tenga una linea/informacion
        {   
            num = sc2.nextInt(); //Filtramos los valores mayores a 56. Ya que como son numeros de 2 digitos y 56+10 = 66, se eliminan.
            if(num < 56)
            {
                if (numeros.size() == 0)  //El primer caso
                {
                    numeros.add( num ) ;
                }
                else  //Se revisa para cada par de numeros y cuando encuentre la primera suma, se imprimen los valores y se termina.
                {
                    for(int x : numeros) 
                    {
                        if(x+num == 65)
                        {
                            System.out.println(num + " " + x);
                            diegaso = true;
                            break;
                        }
                    }
                    if(diegaso)
                    {
                        break;
                    }
                    numeros.add(num);
                }
            }
        }
        sc2.close();
        //Caso donde no se haya encontrado el par de numeros que sume 65
        if(!diegaso)
        {
            System.out.println("No se encontró un par de numeros que sume 65 u.u");
        }
        fooo.run();
    }
}

