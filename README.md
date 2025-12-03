# Proyecto Laboratorio de Grafo (Laboratory Graph!)
---
Este proyecto tiene como finalidad implementar diferentes representaciones de grafos y desarrollar algoritmos fundamentales para su análisis.

El programa permite construir un grafo, analizar sus propiedades, generar matrices, obtener caminos mínimos, árboles de expansión y evaluar emparejamientos (matching).

Todo esto mediante un menú interactivo desarrollado en C++.

Con la finalidad de aplicar los conocimientos obtenidos mediante la  impartición del curso, por lo que se espera cumplir con las expectativas deseadas que se obtuvieron a la finalización de este mismo. De igual forma se explicará a detalle cada algoritmo implementado en este proyecto desde su:
- Tiempo de ejecución
- Espacio
- Lógica
- Implementación
---
# Objetivos

- Implementar correctamente un grafo dirigido y ponderado.

- Construir sus distintas representaciones:

    - Lista de adyacencia

    - Matriz de adyacencia

    - Matriz de incidencia

- Evaluar características importantes del grafo:

    - Conectividad

    - Si es árbol

    - Si es fuertemente conexo

    - Si es bipartito

- Ejecutar algoritmos clásicos:

    - BFS, DFS

    - Dijkstra

    - Floyd–Warshall

    - Kruskal

    - Prim

    - Matching

    - Mostrar e interpretar resultados obtenidos.
---
## Representaciones de un Grafo

### 1. Lista de Adyacencia

Representa cada nodo mediante un vector que contiene todas sus aristas salientes. Si el grafo es ponderado, se guarda un par (destino, peso).

**Complejidad**

| Operación       | Complejidad           |
| --------------- | --------------------- |
| Espacio         | **O(V + E)**          |
| Insertar arista | **O(1)**              |
| Obtener vecinos | **O(grado del nodo)** |

La  implementación del codigo es la siguiente: 

```cpp
void insertarNP(int o, int d, vector<vector<int>>& g, bool dirigido) {
    if (!inRange(o, (int)g.size()) || !inRange(d, (int)g.size())) return;
    g[o].push_back(d);
    if (!dirigido)
        g[d].push_back(o);
}

void insertarP(int o, int d, int p, vector<vector<pair<int,int>>>& g, bool dirigido) {
    if (!inRange(o, (int)g.size()) || !inRange(d, (int)g.size())) return;
    g[o].push_back({d, p});
    if (!dirigido)
        g[d].push_back({o, p});
}
```

Donde insertarNP seria para el apartado de grafosno No Ponderados (NP), con su contraparte de insertarP que acepta grafos ponderados. De igual forma se explica mejor el codigo en el apartado de la **"Documentación"** que esta subido aqui mismo.

---

### 2. Matriz de Adyacencia

Crea una matriz V × V donde cada posición indica si existe o no una arista.

mat[u][v] = peso si existe arista. Se agrega 1 en grafos no ponderados si existe conexión.
∞ o 0 si no existe.

| Operación            | Complejidad |
| -------------------- | ----------- |
| Espacio              | **O(V²)**   |
| Insertar arista      | **O(1)**    |
| Consultar existencia | **O(1)**    |


### 3. Matriz de Incidencia

Genera una matriz V x E donde cada columna corresponde a una arista, indicando qué nodos participan en ella. Se coloca -1 dando entender el nodo origen y 1 al nodo destino. 

| Operación    | Complejidad |
| ------------ | ----------- |
| Espacio      | **O(V·E)**  |
| Construcción | **O(V·E)**  |

## Caracteristicas del grafo

### Recorrido BFS (Breadth-First Search)

 Explora el grafo nivel por nivel desde un nodo de origen. Comienza visitando al nodo inicial, luego todos sus vecinos directos, después los vecinos de esos vecinos, y así sucesivamente. Se utiliza comúnmente para encontrar el camino más corto en un grafo no ponderado, detectar ciclos o encontrar componentes conectados. 

 **¿Qué hace?**

- Recorre el grafo por niveles.

- Determina conectividad.

- Apoya la detección de grafo bipartito.

- Calcula distancias mínimas en grafos no ponderados.

 **Complejidad**

- `Tiempo: O(V + E)`

- `Espacio: O(V)`

### Recorrido DFS (Depth-First Search)

Explora una rama hasta el límite antes de retroceder y probar otra. Funciona comenzando en un nodo inicial, explorando lo más lejos posible a lo largo de cada ruta y, cuando llega a un punto muerto o nodo visitado, retrocede para explorar una rama no visitada desde el último punto. Se puede implementar mediante recursión o una pila.

**¿Qué hace?**

-Detecta ciclos

-Encuentra componentes conexas

-Funciona para verificar fuertemente conexidad (parte del algoritmo)

**Complejidad**

- `Tiempo: O(V + E)`

- `Espacio: O(V)`

### Determinación de Bipartito

Usa BFS para colorear nodos y comprobar si puede dividirse en dos conjuntos sin conflictos.

**Complejidad**

- `Tiempo: O(V + E)`

- `Espacio: O(V)`

### Comprobar si es fuertemente Conexo

Comprobamos utilizando el algoritmo de Kosaraju pero mas simplificado donde invertimos el grafo para comprobarlo si es fuertementye conexo utilisando bfs para buscan conexion ya sea en grafo normal e invertido. 

Ya que para considerar que un grafo sea fuertemente se debe tener accesibilidad mutua; Debe existir un camino dirigido desde cualquier vértice u hacia cualquier otro vértice v dentro de la gráfica, y también debe existir un camino dirigido de regreso desde v hacia u. 

En otras palabras, no debe haber ningún par de vértices en la gráfica donde uno no pueda ser alcanzado desde el otro siguiendo la dirección de las aristas.

**Complejidad**

- `Tiempo: O(V + E)`

- `Espacio: O(V + E) (para grafo y su transpuesto)`

## Algoritmos de Caminos Mínimos

### Algoritmo Dijsktra 

Encuentra el camino mas corto de un nodo inicial a todos los demas. Lo hace seleccionando repetidamente el vértice no visitado más cercano y calculando la distancia a todos los vértices vecinos no visitados.

**Complejidad**

- `Tiempo: O(E log V)`

- `Espacio: O(V)`

### Floyd–Warshall

Es un algoritmo de análisis de grafos que encuentra el camino más corto entre todos los pares de vértices en un grafo ponderado dirigido. Funciona de manera iterativa, mejorando gradualmente la estimación de las distancias más cortas, y es útil para grafos densos o cuando se requiere conocer todas las rutas más cortas. Admite pesos de arista negativos, siempre que no existan ciclos de peso negativo. 

**Complejidad**

- `Tiempo: O(n³)`

- `Espacio: O(n²)`

## Arbol de expansión (Minima - Maxima)

### Algoritmo de Kruskal

Es un algoritmo de la teoría de grafos que encuentra el árbol de expansión mínima (AEM) en un grafo conexo y no dirigido, es decir, un subconjunto de aristas que conecta todos los vértices sin formar ciclos y con el peso total mínimo. Para ello, se ordenan las aristas por peso de menor a mayor (para encontrar el maximo se hace lo contrario de mayor a menor) y se van añadiendo al árbol siempre que no se forme un ciclo.

**Complejidad**

- `Tiempo: O(E log E)`

- `Espacio: O(V)`

## Matching (Emparejamiento)

### Algoritmo Hopcroft–Karp

Es un algoritmo eficiente para encontrar una coincidencia de cardinalidad máxima en un **grafo bipartito**. Funciona encontrando iterativamente conjuntos de los caminos de aumento más cortos en paralelo hasta que no se puedan encontrar más caminos de aumento.

***Complejidad***

- `Tiempo: O(√V · E)`

- `Espacio: O(V + E)`

### Algoritmo Edmonds Blossom

El algoritmo de Edmonds Blossom es una forma inteligente de encontrar las mayores coincidencias posibles en grafos generales. Es una extensión del algoritmo de Blossom , creado originalmente para trabajar con grafos bipartitos.

Al basarse en el algoritmo Blossom , el algoritmo Blossom de Edmonds también puede trabajar con grafos más complicados, lo que lo hace más versátil y eficiente a la hora de encontrar el máximo de coincidencias con menos pasos.

 **Complejidad** 
  - `Tiempo: O(V³)` 
  - `Espacio: O(V + E)` 
---

Con este ultimo algoritmo terminamos de explicar todos los metodos que utilizamos para el desarrollo de este programa.  Sin mas que agregar lo invito a leer los demas documentos que se encuentran en este apartado y de ante mano le invito probar el programa. 

*`Jesús Alejandro Luevano Macias`*