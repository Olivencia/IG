Práctica 3 - Revolución de un modelo a partir de un perfil
==

En esta práctica se ha procurado crear un personaje de una serie de televisión, Bart Simpson. Para ella se han ido cogiendo las diferentes formas ya creadas (esfera, semiesfera, cilindro, cubo, tetraedro, etc) y con imaginación escalarlas y trasladarlas para componer la figura completa. 

En la siguiente imagen podremos ver el personaje:

<img src="https://github.com/Olivencia/ugr_informatica_grafica/blob/master/Practica3/BartSimpson.png">


En la siguiente imagen podemos ver el grafo jerárquico del personaje:

<img src="https://github.com/Olivencia/ugr_informatica_grafica/blob/master/Practica3/grafo.png">

Se han cargado un ficheros PLY para su lectura de datos en memoria: beethoven.ply (necesaria para la correcta entrega de la práctica)

Se han establecido 4 modos de visualización: puntos, lineas, sólido y ajedrez.

Se han añadido 4 grados de libertad: cuerpo completo, torso, brazos y mano.


#IMPORTANTE

Se ha añadido la función de movimiento de la figura, para ello hay que modificar en el archivo practica3.cc la variable de la linea 7 idle=true.


#Teclas asignadas

V/v -> 1º Grado de libertad - Mover a Bart en skate

Z/z -> 2º Grado de libertad - Mover el torso hacia abajo

X/x -> 3º Grado de libertad - Mover los brazos hacia abajo

C/c -> 4º Grado de libertad - Mover la mano derecha hacia dentro

Si se pulsan las teclas anteriores con SHIFT se realizará el movimiento contrario.



P/p -> Visualizar la figura en modo puntos

L/l -> Visualizar la figura en modo lineas

S/s -> Visualizar la figura en modo sólido

A/a -> Visualizar la figura en modo ajedrez

re pág -> Alejar ventana

av pág -> Acercar ventana

P/p -> Salir
