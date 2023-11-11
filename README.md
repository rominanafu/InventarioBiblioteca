# Inventario Biblioteca
## Contexto
Las bibliotecas son lugares en donde se recopila una cantidad enorme de libros, revistas, publicaciones, entre otros textos. Generalmente, estos recursos son categorizados para así elegir una ubicación estratégica en la biblioteca. Asimismo, suele ser importante llevar un registro de cada uno de los textos disponibles y su historial de préstamos.<br>
Sin embargo, el llevar un registro a papel de todo esto, puede llegar a ser algo poco eficiente, ya que el actualizarlo requiere de mucho esfuerzo, y el encontrar un texto en específico podría llevar mucho tiempo.

## Interés
Las bibliotecas tienen una cantidad inmensa de recursos, y me parece interesante el cómo se suelen clasificar estos para lograr identificar la ubicación y los detalles de cada uno de ellos. Me gusaría poder implementar algo que facilite este registro, así como la búsqueda de los recursos disponibles.

## Propuesta
Para evitar hacer todo a papel, considero que es importante tomar en cuenta la tecnología que tenemos disponible, realizando un inventario digital, para así simplificar el proceso de actualización de cada recurso, y tener una herramienta de búsqueda que encuntre los textos de una manera sencilla y rápida.

## Diagrama UML
![Diagrama](UML\Diagrama.jpg)<br><br>
La función de cada clase es la siguiente:
* **Biblioteca:** Tendrá el registro de cada una de las repisas.
* **Repisa:** Contendrá todos los textos disponibles en la biblioteca.
* **Texto:** Será la clase base para cualquier tipo de recurso que la repisa guarde (como libros y revistas).
* **Libro:** Un Texto de tipo libro, que además de los atributos de Texto, tendrá editorial y edición.
* **Revista:** Un Texto de tipo revista, que además de los atributos de Texto, tendrá un volumen y número de publicación.
* **Usuario:** Una clase que contendrá la información de las personas que pidan algún texto, como sus nombres, y los libros que han pedido, así como la fecha en que los regresarán.
* **Categoria:** Esta clase permitirá que los libros sean categorizados (ejemplos: Matemáticas, Ciencias, Filosofía, Economía, Ciencia Ficción, etc.), para así facilitar la identificación de los textos dentro de cierta área.