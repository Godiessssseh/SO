package Tarea;

public class Main {
    
    public static void main(String[] args) {
        //Creacion de las variables para guardar el tiempo final de cada hebra.
        Foo val1 = new Foo();  
        Foo val2 = new Foo();
        Foo val3 = new Foo();

        //Creación de las hebras
        Numero hebra1 = new Numero(val1);
        Palabra hebra2 = new Palabra(val2);
        Morse hebra3 = new Morse(val3);

        //Tiempo inicial
        Long valor = System.nanoTime();

        //Inicializacion de las hebras.
        hebra1.start();
        hebra2.start();
        hebra3.start();
        
        //Espera que todas las hebras terminen e ignore el error si terminaron.
        try
        {
            hebra1.join();
            hebra2.join();
            hebra3.join();
        }
        catch (Exception e){}

        //Recoleccion de los tiempos de cada hebra.
        Long h1 = val1.getValue();
        Long h2 = val2.getValue();
        Long h3 = val3.getValue();

        //Calculo del tiempo de ejecucion de cada hebra.
        Long r1 = h1-valor;
        Long r2 = h2-valor;
        Long r3 = h3-valor;

        //print
        System.out.println("Hebra 1 para el ejercicio de numeros se demoro: "+r1+" nanosegundos");
        System.out.println("Hebra 2 para el ejercicio de palabras se demoro: "+r2+" nanosegundos");
        System.out.println("Hebra 3 para el ejercicio de morse se demoro: "+r3+" nanosegundos");
        }
}