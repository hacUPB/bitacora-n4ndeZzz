Actividad 1:
¿Qué es un computador digital moderno?
Es una máquina electrónica que procesa datos y ejecuta instrucciones almacenadas en memoria, realizando operaciones lógicas y aritméticas para resolver problemas.

¿Cuáles son sus partes?
Unidad Central de Procesamiento (CPU): Ejecuta instrucciones.
Memoria: Almacena datos e instrucciones.
Dispositivos de entrada/salida: Permiten comunicarse con el exterior.
Bus de datos: Canal que conecta las partes para transferir información.


Actividad 2
¿Qué es un programa?
Una serie de instrucciones que le dicen a la computadora qué hacer.
¿Qué es un lenguaje ensamblador?
Un lenguaje de bajo nivel que usa instrucciones simbólicas que se traducen directamente a lenguaje máquina.
¿Qué es lenguaje de máquina?
El código binario que entiende directamente el procesador para ejecutar instrucciones.


Actividad 3
¿Qué son PC, D y A?
PC (Program Counter): Registro que indica la dirección de la siguiente instrucción a ejecutar.
D: Registro donde se almacenan datos temporales para operaciones.
A: Registro que puede contener una dirección de memoria o un valor inmediato.


¿Para qué los usa la CPU?
Para controlar el flujo de ejecución y manipular datos durante la operación del programa.

8)
1. ¿Qué hace este programa?
Primero, carga en D el contenido de la dirección var1.

Luego, suma al valor en D el contenido de la dirección var2.

Finalmente, guarda el resultado de esa suma en la dirección var3.

2. ¿En qué posición de la memoria están var1, var2 y var3? ¿Por qué en esas posiciones?

var1 estará en RAM[16]
var2 en RAM[17]
var3 en RAM[18]

Las direcciones son asignadas automáticamente porque el programa detecta que son variables y las posiciona a partir de la 16

9)
1. ¿Qué hace este programa?

Inicializa la variable i con 1

Inicializa la variable sum con 0

Suma el valor de i a sum (sum = sum + i)

Incrementa i en 1 (i = i + 1)

Basicamente un contador


2. ¿En qué parte de la memoria RAM están las variables i y sum? ¿Por qué en esas posiciones?

En el programa, las variables i y sum se asignan automáticamente a partir de la dirección RAM 16 en adelante.
Esto es porque las direcciones RAM 0-15 están reservadas R0 a R15 y 

i estará en RAM[16]
sum estará en RAM[17]

OPTIMIZACIÓN: 
@i
M=M+1

11)
1. ¿Qué hace este programa?

Inicializa la variable i con 1000.

Entra en un bucle y en cada iteración:

Si i es igual a 0, salta a la etiqueta CONT y termina el bucle.
Si no, decrementa i en 1.
Vuelve a saltar a LOOP.

O sea cuenta hacia atrás desde 1000 hasta 0.


2. ¿En qué memoria está almacenada la variable i? ¿En qué dirección de esa memoria?
i es una variable simbólica, por lo que si no hay mas variables asignadas debería ser en la 16.


3. ¿En qué memoria y en qué dirección de memoria está almacenado el comentario // i = 1000?
Los comentarios no se almacenan en memoria, son ignorados por el assembler.

Solo sirven para el programador, no afectan al programa ejecutable ni al almacenamiento en memoria.


4. ¿Cuál es la primera instrucción del programa anterior? ¿En qué memoria y en qué dirección de memoria está almacenada esa instrucción?
La primera instrucción ejecutable es @1000, Esta instrucción se almacena en la memoria ROM, en la dirección 0.


5. ¿Qué son CONT y LOOP?
Son etiquetas las cuales marcan direcciones de memoria de instrucciones dentro de la ROM.

LOOP indica el inicio del bucle.
CONT indica el punto donde se continúa la ejecución después de que i llegue a 0.


6. ¿Cuál es la diferencia entre los símbolos i y CONT?
i es una variable simbólica, está en RAM y es un espacio para guardar datos.
CONT es una etiqueta, está en ROM




16)
1. ¿Qué hace este programa?
Suma los 10 elementos de un arreglo (de tamaño 10) que está en memoria y guarda el resultado en la variable sum. Es decir, calcula la suma total de todos los valores almacenados en el arrego.

2. ¿Cuál es la dirección base de arr en la memoria RAM?
La dirección base del arreglo está almacenada en R0. o sea que R0 contiene la posición inicial en la RAM donde comienza el arreglo.

3. ¿Cuál es la dirección base de sum en la memoria RAM y por qué?
La variable sum está almacenada en R1. Se usa R1 porque en el código asignamos que el acumulador sum se guarde en esa dirección, aprovechando los registros simbólicos R0 a R15 que se usan para variables predeterminadas.

4. ¿Cuál es la dirección base de j en la memoria RAM y por qué?
El índice j se guarda en R2. Se eligió R2 porque es otro registro simbólico disponible para variables temporales, esto porque podemos controlar el contador del ciclo sin interferir con arr ni sum.
