### Actividad 1:  

En esta primera actividad pudimos evidenciar como el background se modifica para utlizar un color negro, y en la funcion draw se dibuja un circulo color blanco, y obtiene la posición del mouse para seguirla.

### Actividad 2:  

__1)__     private:

        vector<ofVec2f> particles;
        ofColor particleColor;

__2-7)__ La funcion setup da inicio al programa, luego la update se encarga de ejecutarse constantemente para actualizar el programa y mostrarlo en el renderizado (draw), en caso de ser necesario.  

Se crean un vector y una variable para determinar el recorrido del mouse y el color de las particulas (el movimiento y presion del mouse tambien fueron declaradas)  

En el ofapp :: draw, se pone el color al fondo y se setea el color de las particulas inicialmente, en la función draw, se dibuja un circulo yse hace el seguimiento de las particulas.  

En mousemoved, se declara el tamaño de las particulas y se da inicio a las particulas (cuando se mueve el mouse)  

En mousePressed,  se cambia el color a uno random entre 0 y 255.  
