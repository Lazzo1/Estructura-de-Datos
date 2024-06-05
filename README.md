# Grafo Interactivo

Este proyecto implementa un programa interactivo en C++ para trabajar con grafos. El usuario puede realizar varias operaciones, como agregar vértices, agregar aristas, mostrar el grafo, trabajar con matrices de adyacencia, ejecutar algoritmos para encontrar el camino más corto y el árbol de expansión mínima, entre otras.

## Estructura del Código

El código está estructurado en un bucle do-while que continuará ejecutándose hasta que el usuario seleccione la opción de salida. Cada opción del menú se implementa como un caso dentro de una declaración switch, lo que facilita la navegación y la ejecución de las diferentes funcionalidades.

```cpp
do {
    // Lógica para mostrar el menú y obtener la opción del usuario
    switch (opcion) {
        case 1:
            // Lógica para agregar vértices
            break;
        case 2:
            // Lógica para agregar aristas
            break;
        case 3:
            // Lógica para mostrar el grafo
            break;
        // Otros casos para las diferentes funcionalidades
    }
} while (opcion != 9);



## Funcionalidades Principales

1. **Agregar Vértices**
   - Solicita al usuario ingresar el número de vértices y los valores para cada vértice.
   - Inserta los vértices en la estructura del grafo.
   - Guarda la representación del grafo en el archivo "vertice.txt".

2. **Agregar Aristas**
   - Solicita al usuario ingresar el número de aristas y los nodos de origen y destino para cada una.
   - Opcionalmente, el usuario puede ingresar el peso de la arista.
   - Verifica la existencia de los nodos de origen y destino en el grafo.
   - Inserta las aristas en la estructura del grafo.
   - Guarda la representación del grafo en el archivo "grafo.txt".

3. **Mostrar Grafo**
   - Muestra en la consola la representación actual del grafo.

4. **Trabajar con Matrices**
   - Permite al usuario ingresar y visualizar matrices relacionadas con el grafo.
   - Muestra las matrices ingresadas por el usuario.
   - Carga matrices desde un archivo y las visualiza.

5. **Algoritmos sobre Grafos**
   - Permite al usuario seleccionar entre los algoritmos de Dijkstra y Floyd-Warshall para encontrar el camino más corto en el grafo.
   - Permite al usuario seleccionar entre los algoritmos de Kruskal y Prim para encontrar el árbol de expansión mínima en el grafo.

6. **Salir del Programa**
   - Permite al usuario salir del programa.

## Consideraciones

- El código hace uso de archivos de texto para guardar la representación del grafo y las matrices asociadas.
- Utiliza funciones auxiliares para realizar operaciones específicas, como insertar vértices y aristas, y ejecutar algoritmos sobre el grafo.
