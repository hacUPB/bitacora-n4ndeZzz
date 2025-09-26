# [Reto 1](<../Códigos/Reto 1.asm>)  

## ¿Cómo están implementadas las variables `i` y `sum`?  
Como etiquetas simbólicas que el ensamblador traduce automáticamente a direcciones de memoria RAM.  
Por defecto, las primeras variables definidas se colocan desde la posición 16 en adelante.  

## ¿En qué direcciones de memoria están estas variables?  
Cuando no se usan registros predefinidos (como R0, R1, etc.), las primeras variables se asignan así:  

i → dirección 16  
sum → dirección 17  

## ¿Cómo está implementado el ciclo `while`?  
Con la etiqueta END. Si i >= 101, saltar a END (salir del bucle), en caso de que no, salta a la etiqueta LOOP que repite todo el proceso  

## ¿Cómo se implementa la variable `i`?  
inicialmente se declara esa variable y luego con:  
@i  
M=M+1     se suma 1 cada que se repite el bucle  


## ¿En qué parte de la memoria se almacena la variable `i`?  
En la 16 debido a que es la primera variable simbolica asignada  

##  Después de todo lo que has hecho, ¿Qué es entonces una variable?  
Es un nombre simbólico que se asigna a una dirección de memoria. Sirve para guardar datos que pueden cambiar durante la ejecución del programa (como contadores, resultados, etc.)  

## ¿Qué es la dirección de una variable?  
Es la ubicación de esta en la RAM  

## ¿Qué es el contenido de una variable?  
Es el valor que hay almacenado en la ubicación de una variable  

# [Reto 2,3](<../Códigos/Reto 2-3.asm>)

## Conclusiones:  
Este codigo simbolicamente es muy similar a el del while, por lo que al menos para este ejercicio puedo concluir que es mas facil con el ciclo while, esto porque puede ser mas corto debido a que el for necesita un cuerpo y un lugar para la condicion como LOOP.  