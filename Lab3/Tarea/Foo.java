package Tarea;

/*Esta clase devolverá el tiempo que se demora en trabajar cada Hebra. (EN NANOSEGUNDOS!)
Atributos: Value -> Valor a guardar
Metodo: getValue() -> Devuelve el valor de Value.
*/

public class Foo implements Runnable {
     private volatile Long value;

     @Override
     public void run() { 
        value = System.nanoTime();
     }

     public long getValue() {
         return value;
     }
 }