# Proyecto final 1

Este es el proyecto final de cierta materia en la cual nos pedía crear un "Sistema bancario"
el cual tenia que guardar la información en un archivo y poder recuperarla.

Recomendaban utilizar archivos de texto para guardar la información, pero yo me fui a lo loco y
terminé realizándolo de forma binaria.

Retire los nombres y los cambie por números.

## Características

1. Guarda la información de forma binaria
2. 3 archivos para guardar la información
3. 2 bugs conocidos (¡Encuéntrelos si pueden!)
4. Compilación automatizada por medio de un makefile
5. Biblioteca archivos con codigo que puede volverse una función

## Algo de historia

Este proyecto se realizó el año 2023 por el mes de enero.
Fue un trabajo muy duro…
Todos hicieron lo mejor que podían bajo lo que entendían de C y en la mayoría de los casos no
sabían el como hacerlo, por lo que termine ayudándolos.
A pesar de que se repartieron respectivamente las bibliotecas que cada uno realizaría, falto
más atención de mi parte, aunque en mi defensa yo les preguntaba…
A mi me toco la biblioteca archivos.
La cual fue una aventura completa ya que era la primera vez que hacia algo asi hablando de
archivos y además binarios el cual fue el trabajo mas pesado, lo demas era hacer la interfaz
de como se va a comunicar el usuario y mensajes (los cuales faltan muchos más), operaciones
sobre el interés a cobrar por el préstamo.
Lo otro más complicado era el realizar el main el cual juntaría todo y el cual si o si tenia
que ayudar ya que si no (4) se pegaría un tiro intentando hacer.

En lo que respecta a quien le toco hacer que cosa:

- (1) Y (3) Les toco hacer la interfaz del programa (Supongo que (3) fue quien decidió el nombre del banco).
- (2) Le toco hacer la parte matemática (No le sabe al C muy bien…).
- (4) y PaikLC Unir todo en el main.c
- PaikLC Bibliotecas archivos, entrada (con su buffer overflow el cual puedo explicar).

Puedo explicar por qué no termine utilizando la funcion scanf_s y es porque al parecer el compilador
de (4) no tenía esas funciones seguras y para arreglarlo era hacer otras cosas con memoria dinámica
y eso era modificar mucho del codigo.

Además de que se colocaban cadenas de caracteres con tamaños diferentes por lo que no era tan sencillo
colocar el número máximo de elementos por leer.

## Agradecimientos extra especiales

A (4), realizo un buen trabajo corrigiendo lo que hizo (2) y en la parte de depuración a pesar de que
se nos paso un pequeño bug el cual no logramos resolver a tiempo y además de explicarles a los demas el
cómo funcionaba el main.c, imprimir las hojas para explicarlo mas eficientemente al momento de estar
todos reunidos y en especial para organizar a todos en la parte del documento escrito que tambien se
tenía que entregar.
