<div align="center">

# **Universidad Autónoma de Aguascalientes**
## **Ingeniería en computación inteligente**
### **Centro de ciencias básicas**

<br><br>

# **Laboratorio de grafos**
## **Implementación de varios algoritmos para grafos**

<br><br><br>

### **Manual Técnico y Documentación del Programa**

<br><br><br>

### **Autor: Jesús Alejandro Luevano Macias**  

### **Profesor: Dr. Miguel Angel Meza de Luna**  

### **Materia: Estructuras computacionales avanzadas**  


### **Semestre: Tercer semestre**  

### **Fecha: 03/12/2025**  

<br><br><br><br>

---

<img src="Pruebas/UAA-LOGO.png" alt="Logo UAA" width="180">

---

</div>

# Introducción

El presente documento contiene la documentación completa del programa de análisis y procesamiento de grafos, desarrollado con fines académicos y formativos. Su propósito principal es servir como una herramienta educativa que permita comprender, de forma estructurada y práctica, los algoritmos fundamentales utilizados en la teoría de grafos, así como su correcta implementación en un entorno de programación real.

A lo largo de este manual, el lector encontrará la descripción detallada de las estructuras de datos, funciones auxiliares, representaciones del grafo, y de todos los algoritmos implementados, entre ellos:

- Verificación de propiedades del grafo (bipartito, árbol, conectividad).

- Cálculo de componentes conexas y fuerte conectividad.

- Algoritmos de caminos mínimos (Dijkstra y Floyd–Warshall).

- Construcción de árboles de expansión mínimos y máximos (Kruskal y Reverse Kruskal).

- Algoritmos de matching en grafos bipartitos y generales (Greedy, Hopcroft–Karp y Edmonds/Blossom).

El programa cuenta con un menú interactivo que guía al usuario a través de cada operación, permitiendo explorar de manera intuitiva las capacidades del sistema. De esta forma, el proyecto no solo implementa algoritmos teóricos, sino que también ofrece un entorno práctico para experimentar con grafos, validar resultados y comprender su funcionamiento interno.

Este documento está organizado de tal manera que el lector pueda avanzar de forma progresiva: comenzando con las estructuras esenciales del sistema, pasando por la explicación de cada algoritmo, y finalizando con un análisis integral del funcionamiento del programa. Cada sección ha sido diseñada para facilitar la comprensión sin comprometer la precisión técnica, integrando ejemplos, fragmentos de código, tablas y explicaciones detalladas.

En conjunto, esta documentación constituye una guía completa tanto para el estudio introductorio de grafos como para el análisis avanzado de sus algoritmos más importantes.

# Estructura del programa 
## Estructuras de datos y tipos de datos

En este apartado se presentan y describen las estructuras de datos, tipos auxiliares y variables clave utilizadas a lo largo del sistema. Estas estructuras constituyen el núcleo operativo del programa, ya que permiten almacenar, manipular y consultar grafos de forma eficiente. Su correcta comprensión es esencial, dado que cada algoritmo implementado **—como Dijkstra, Kruskal, Floyd–Warshall, Hopcroft–Karp o Blossom—** depende directamente de la representación del grafo y de la organización interna de los datos.

El diseño de estas estructuras no es arbitrario: ha sido cuidadosamente seleccionado para equilibrar claridad, eficiencia y facilidad de uso dentro de un entorno educativo. La elección entre lista de adyacencia, matriz de adyacencia o matriz de incidencia, así como el uso de contenedores estándar como **vector, pair, tuple o queue,** responde a la necesidad de cubrir los distintos algoritmos clásicos en teoría de grafos, cada uno con requisitos específicos para su funcionamiento óptimo.

A lo largo de esta sección:

- Se explicará el propósito de cada estructura elemental utilizada en el programa.

- Se detalla cómo estas estructuras facilitan la representación de grafos ponderados y no ponderados, tanto dirigidos como no dirigidos.

- Se presentan los tipos auxiliares creados para simplificar la lectura y manipulación del código.

- Se establecen las bases sobre las cuales el resto del sistema opera, permitiendo que el lector comprenda de manera integral el flujo de información entre los distintos módulos.

Esta introducción sienta las bases para el estudio posterior de los algoritmos implementados, brindando un punto de partida claro y sólido para comprender la lógica interna del programa. En las siguientes secciones se profundizará en cada estructura, su utilidad, beneficios y relación directa con los algoritmos que se encuentran distribuidos en el menú principal.

| Tipo / Variable | Definición                | Propósito |
|-----------------|---------------------------|-----------|
| **pii**         | `pair<int, int>`          | Pareja de enteros, usada para `{destino, peso}` en grafos ponderados. |
| **tiii**        | `tuple<int, int, int>`    | Tupla de tres enteros usada principalmente como `{peso, u, v}` para aristas en Kruskal. |
| **INF_INT**     | `1e9` (1,000,000,000)     | Representa el valor infinito para distancias inalcanzables en Dijkstra y Floyd-Warshall. |
| **grafoNP**     | `vector<vector<int>>`     | Lista de adyacencia para grafos no ponderados (solo almacena vecinos). |
| **grafoP**      | `vector<vector<pii>>`     | Lista de adyacencia para grafos ponderados (almacena `{destino, peso}`). |


## Funciones de utilidad y auxiliares

### Validación de nodo ingresado

```cpp
bool inRange(int x, int n) {
    return (x >= 0 && x < n);
}

int pedirEnteroRango(const string &prompt, int n) {
    int x;
    cout << prompt;
    cin >> x;
    if (!inRange(x, n)) {
        cout << "El nodo " << x << " no está en el grafo ingresado (debe estar entre 0 y " << n-1 << ").\n";
        return -1;
    }
    return x;
}
```
Ayuda validar si el nodo ingresado para el uso de algoritmos como Dijsktra esta realmente dentro del grafo. Primero la funcion `**bool inRange**` verifica si el nodo ingresado por el usuario está dentro del grafo dado, después esta misma función es llamada en `**int pedirEnteroRango**` para que evalúe y muestre el mensaje de error (de ser el caso) si el nodo no se encuentra dentro del grafo devolviendo un mensaje de error y -1 como sinónimo de nodo invalido.

### Insertar nodos al grafo

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

La función `**void insertarNP**` es donde insertamos las aristas en **grafos no ponderados**, el apartado donde evaluamos en if llama la función que nombramos anteriormente para verificar si el nodo ingresado realmente pertenece al grafo descrito si es el caso, ingresamos la arista, desde el nodo origen hasta el nodo destino `**g[o].push_back(d);**`. Observe que hay otra condicional y esta es para evaluar si el grafo es dirigido o no, `**!dirigido**` nos ayuda a identificar si el grafo es o no, si no es, automáticamente añadiremos la arista que conecte con el nodo destino al nodo origen `**g[d].push_back(o)**`. Enlazamos dos veces en **grafos no dirirgidos** y una sola vez en **grafos dirigidos**.

La función `**void insertarP**`hace exactamente lo mismo que su hermana, solamente que en este caso va aplicado para **grafos ponderados** utilizando el vector de pares; `**vector<vector<pair<int,int>>>& g**`.

## Algoritmos de recorrido y conectividad

### BFS

```cpp
void bfs_component(int start, vector<bool>& visited, vector<vector<int>>& g) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "Componente: ";

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";

        for (int v : g[u]) {
            if (!inRange(v, (int)g.size())) continue;
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}
```

El algoritmo **BFS** recorre el grafo por niveles (todos los vecinos directos, luego los vecinos de los vecinos, etc.), utilizando una cola `(queue)`.

Nos ayuda encontrar los diferentes componentes de un grafo si es que tiene este, validando cada nodo no visitando esto asegurando que todos los nodos hayan sido visitados correctamente. Utilizando un vector booleano `**vector<bool>& visited**` donde nos ayudara a distinguir que nodos ya fueron visitados y cuáles son los que no lo hemos hecho aun. De igual forma al utilizar una cola también vamos a utilizar sus diferentes funciones como son `**front()**` y  `**pop()**` para tomar y eliminar nodos esto para asegurar el recorrido y gracias a `**!q.empty()**` siempre va evaluar los nodos vecinos hasta que la cola quede vacía.

### DFS 

```cpp
void dfs(int inicio, vector<bool>& visited, vector<vector<int>>& g) {
    int n = g.size();
    stack<int> st;
    st.push(inicio);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (!visited[u]) {
            visited[u] = true;

            // Empujar los vecinos
            for (int v : g[u]) {
                if (!visited[v]) {
                    st.push(v);
                }
            }
        }
    }
}
```

Con su contraparte al **BFS**, el algoritmo **DFS**explora tan lejos como sea posible a lo largo de cada rama antes de retroceder

Es una función auxiliar fundamental utilizada por `**fuertementeConexo**` para verificar el alcance de los nodos. Utiliza una lógica parecida a su hermano **BFS** pero adaptándolo al utilizar pila en vez de cola, sigue siguiendo el mismo orden de funcionamiento pero esta vez utilizando sus propias funciones. en vez de `**front()**`utiliza `**top()**` para tomar el nodo inicial.

### Fuertemente Conexa

```cpp
bool fuertementeConexo(vector<vector<int>>& g, int n) {
    vector<bool> visited(n, false);

    // proteger llamada si 0 no existe
    if (!inRange(0, n)) return false;
    dfs(0, visited, g);
    for (bool x : visited) if (!x) return false;

    vector<vector<int>> trans(n);
    for (int u = 0; u < n; u++)
        for (int v : g[u])

    fill(visited.begin(), visited.end(), false);

    dfs(0, visited, trans);
    for (bool x : visited) if (!x) return false;

    return true;
}
```

La función verifica si un grafo dirigido, representado por una lista de adyacencia g con n nodos (índices 0..n-1), es fuertemente conexo. Un grafo dirigido es fuertemente conexo si desde cualquier nodo se puede llegar a cualquier otro nodo por caminos orientados.

Este algoritmo implementa la comprobación clásica basada en dos búsquedas en profundidad (DFS): una sobre el grafo original y otra sobre el grafo transpuesto (con aristas invertidas). Si desde un nodo de partida (aquí el nodo 0) se visitan todos los nodos en ambos grafos, el grafo es fuertemente conexo. 

| Segmento de Código | Explicación |
|--------------------|-------------|
| `bool fuertementeConexo(vector<vector<int>>& g, int n)` | Declara la función que determina si un grafo dirigido representado por una lista de adyacencia `g` y con `n` nodos es **fuertemente conexo**. Devuelve `true` o `false`. |
| `vector<bool> visited(n, false);` | Crea un vector `visited` de tamaño `n` inicializado en `false`. Se usa para marcar qué nodos se visitan durante DFS. |
| `dfs(0, visited, g);` | Realiza una DFS desde el nodo 0 en el grafo original. Marca como `true` todos los nodos alcanzables desde 0. |
| `for (bool x : visited) if (!x) return false;` | Verifica si existe algún nodo no alcanzado desde 0. Si lo hay, el grafo **no puede ser** fuertemente conexo. Retorna `false`. |
| `vector<vector<int>> trans(n);` | Declara la lista de adyacencia del **grafo transpuesto**, inicialmente vacía pero con `n` listas internas. |
| `for (int u = 0; u < n; u++)` | Itera sobre cada nodo `u` del grafo original. |
| `for (int v : g[u])` | Recorre los vecinos `v` de `u`, es decir, todas las aristas dirigidas `u → v`. |
| *Construcción del transpuesto* | Cada arista `u → v` se convierte en `v → u` y se agrega a `trans[v]`. |
| `fill(visited.begin(), visited.end(), false);` | Reinicia el vector `visited` a `false` para la segunda DFS, reutilizando la estructura. |
| `dfs(0, visited, trans);` | Ejecuta una nueva DFS desde el nodo 0, pero ahora sobre el **grafo transpuesto**. Esto verifica si todos los nodos pueden llegar al nodo 0. |
| `for (bool x : visited) if (!x) return false;` | Si algún nodo no puede alcanzar a 0 (en el grafo original), entonces no es fuertemente conexo. Retorna `false`. |
| `return true;` | Si todos los nodos fueron alcanzados en ambas DFS, entonces el grafo es **fuertemente conexo**. |


### Verificar si es Bipartito

```cpp
bool esBipartito(vector<vector<int>>& g, int n) {
    vector<int> color(n, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] != -1) continue;

        queue<int> q;
        q.push(i);
        color[i] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    return true;
}
```

La logica implemntada para detectar si es bipárttio es solamente utilizar el recorrido **BFS** pero modificado, convirtiendolo en el algoritmo de coloreo;

- Asigna un color (0 o 1) a un nodo inicial.
- Asigna el color opuesto al de sus vecinos.
- Si en algún momento, dos nodos adyacentes tienen el mismo color, el grafo no es bipartito y la función devuelve false.

`**vector<int> color(n, -1)**`
Creamos el vector de coloreo que nos ayudara a distuinguir los dos conjuntos creados. El vector inicia con -1 indicando que ningun nodo esta coloreado.

`**if (color[i] != -1) continue;**`
Es similar al vector de visitados, nos ayuda saber si un nodo ya fue coloreado

Lo demas es similara un recorrido **BFS** solamente coloreando cada nodo de un color, en este caso los colores es 1 y 0.

```cpp
for (int v : g[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                else if (color[v] == color[u]) {
                    return false;
                }
            }
```
Este segmento nos ayuda a cambiar de color y a verificar si el nodo que tiene como vecino, tienen diferentes colores ya que si un nodo y su vecino tienen el mismo color significa que estan en el mismo conjunto y por lo tanto el grafo deja de ser bipartito.

### Verificar si es Arbol

```cpp
bool esArbol(vector<vector<int>>& g, int n, int aristas) {
    vector<bool> visited(n, false);

    bfs_component(0, visited, g);

    for (bool x : visited)
        if (!x) return false;

    if (aristas != n - 1) return false;

    return true;
}
```

Para identificar si un grafo es un árbol solo es necesario identificar dos condiciones esenciales, la tercera que es identificar que no tenga ciclos se cumple con la primera condición donde **aristas = nodos - 1** con esto comprobamos que el grafo no tenga ciclos. La segunda condición es que sea conexo, que todos los nodos sean alcanzados por cualquier nodo.

Utilizamos el recorrido **BFS** para identificar su conectividad esto mediante un ciclo donde vamos a comprobar con el vector de visitados si todos sus nodos fueron visitados, esto asegurando su conectividad. 

De ahí usamos una condición para evaluar **aristas = nodos - 1**. Si las dos condiciones se cumplen entonces el grafo es un árbol, arrogando `**return true**`, pero si sola una condición no  se cumple, automáticamente no será un árbol y nos marcara `**return true**`.

## Algoritmos de caminos

### Algoritmo de Dijkstra

```cpp
class Dijkstra {
public:
    int n;
    vector<vector<pair<int,int>>> &g;
    vector<int> dist;
    vector<int> parent;

    Dijkstra(int n, vector<vector<pair<int,int>>> &g) : n(n), g(g) {
        dist.assign(n, 1e9);
        parent.assign(n, -1);
    }

    void ejecutar(int origen) {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist.assign(n, 1e9);
        parent.assign(n, -1);

        dist[origen] = 0;
        pq.push({0, origen});

        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();
            int d = top.first, u = top.second;

            if (d != dist[u]) continue;

            for (auto &par : g[u]) {
                int v = par.first;
                int peso = par.second;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // ===============================
    //    RECONSTRUIR CAMINO
    // ===============================
    vector<int> reconstruirCamino(int destino) {
        vector<int> camino;

        if (dist[destino] == (int)1e9)
            return camino; // vacio, no hay camino

        for (int v = destino; v != -1; v = parent[v])
            camino.push_back(v);

        reverse(camino.begin(), camino.end());
        return camino;
    }
};
```

El algoritmo de Dijkstra resuelve el problema del camino más corto desde un único origen (Single-Source Shortest Path) en grafos donde las aristas tienen pesos no negativos.

Se basa en el principio "Greedy" (Voraz): en cada paso, siempre selecciona el nodo que actualmente tiene la distancia más corta conocida desde el origen, garantizando que esa distancia es la distancia final más corta para ese nodo.

El algoritmo sigue estos pasos en la función ejecutar(int origen):

**Paso 1: Inicialización**

- Se inicializa la distancia a todos los nodos a INF (Infinito).
- La distancia al nodo origen (dist[origen]) se establece en 0.
- El par {0, origen} se inserta en la cola de prioridad.

**Paso 2: El Ciclo Principal (Extracción Greedy)**

- Mientras la cola de prioridad no esté vacía:Se extrae el nodo (u) con la menor distancia (d) de la cola (pq.top()).
- Optimización (Manejo de entradas obsoletas): Como la cola de prioridad puede contener varias entradas para el mismo nodo (si se encuentra un camino más corto a ese nodo), esta línea asegura que solo procesemos la entrada con la distancia más baja y evitemos procesar caminos obsoletos.

**Paso 3: Relajación (El Corazón del Algoritmo)**

Una vez que se extrae el nodo u y su distancia dist[u] se considera final, se examinan sus vecinos (v):Cálculo de la nueva distancia: Se calcula la distancia al vecino v si se pasa por u: NuevaDistancia = dist[u] + peso(u, v).

- Comparación (Relajación): Se comprueba si la NuevaDistancia es menor que la distancia actual conocida a v dist[v].Si dist[u] + peso(u, v) < dist[v]: 
    - Actualizar Distancia: Se actualiza dist[v] = NuevaDistancia.
    - Actualizar Padre: Se establece parent[v] = u.
    - Insertar en PQ: Se inserta el par {NuevaDistancia, v} en la cola de prioridad para su posterior procesamiento.
    
Este proceso continúa hasta que todos los nodos alcanzables han sido visitados o la cola de prioridad se vacía.

**Reconstrucción del Camino**

Una vez que el algoritmo ejecutar() finaliza, el array dist contiene las distancias mínimas. El método reconstruirCamino(int destino) utiliza el array parent para obtener la ruta:
- Comienza en el nodo destino.
- Retrocede recursivamente (o en un bucle) usando v = parent[v] hasta llegar al nodo que tiene parent[v] == -1 (el origen).
- Como la ruta se construye al revés, se usa reverse para obtener el camino de origen a destino en el orden correcto.

| **Segmento de Código**                                           | **Propósito**                          | **Explicación Detallada**                                                                                                                                           |
| ---------------------------------------------------------------- | -------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `vector<int> dist; vector<int> parent;`                          | Estructuras principales                | `dist[v]` almacena la distancia mínima conocida desde el origen hasta el nodo `v`. `parent[v]` permite reconstruir el camino mínimo encontrado.                     |
| `dist.assign(n, 1e9);`                                           | Inicializar distancias                 | Se inicializa cada distancia a un valor muy grande (∞ aproximado). Significa que inicialmente todos los nodos son inalcanzables.                                    |
| `parent.assign(n, -1);`                                          | Inicializar padres                     | Ningún nodo tiene un predecesor todavía, por lo que se marca con −1.                                                                                                |
| `priority_queue<pair<int,int>, ..., greater<pair<int,int>>> pq;` | Cola de prioridad (min-heap)           | Se utiliza una cola que siempre extrae el nodo con **menor distancia actual**. `pair<distancia, nodo>`. El comparador `greater<>` convierte la cola en un min-heap. |
| `dist[origen] = 0;`                                              | Configurar nodo inicial                | La distancia desde el origen hacia sí mismo es 0. Dijkstra parte desde aquí.                                                                                        |
| `pq.push({0, origen});`                                          | Insertar nodo inicial en la cola       | Se agrega el origen a la cola para iniciar el proceso de expansión.                                                                                                 |
| `while (!pq.empty()) { ... }`                                    | Bucle principal del algoritmo          | Se ejecuta mientras haya nodos pendientes de procesar.                                                                                                              |
| `auto top = pq.top(); pq.pop();`                                 | Tomar el nodo más cercano no procesado | Extrae el par `(distancia, nodo)` más pequeño. Esto asegura procesar primero los nodos con menor distancia.                                                         |
| `if (d != dist[u]) continue;`                                    | Descartar entradas desactualizadas     | Si hay entradas antiguas en la cola (distancias viejas), se ignoran. Esto ocurre por la naturaleza del min-heap.                                                    |
| `for (auto &par : g[u]) { ... }`                                 | Recorrer vecinos de `u`                | Se evalúan todas las aristas salientes desde el nodo actual.                                                                                                        |
| `int v = par.first; int peso = par.second;`                      | Obtener destino y peso de la arista    | Cada arista tiene `(nodo destino, peso)`.                                                                                                                           |
| `if (dist[u] + peso < dist[v])`                                  | Relajación (condición principal)       | Si encontramos un camino más barato hacia `v`, actualizamos su distancia. Esta es la operación clave de Dijkstra.                                                   |
| `dist[v] = dist[u] + peso;`                                      | Actualizar distancia                   | Se mantiene la distancia más corta conocida hacia `v`.                                                                                                              |
| `parent[v] = u;`                                                 | Registrar predecesor                   | Permite reconstruir luego el camino mínimo hacia `v`.                                                                                                               |
| `pq.push({dist[v], v});`                                         | Añadir actualización a la cola         | El nuevo valor de distancia se agrega a la cola para continuar exploración.                                                                                         |
| **Función: `reconstruirCamino(int destino)`**                    | Devolver ruta mínima                   | Reconstruye el camino desde el origen hasta un nodo destino utilizando el vector `parent`.                                                                          |
| `if (dist[destino] == 1e9)`                                      | Verificar si existe camino             | Si la distancia sigue siendo infinita, el nodo es inalcanzable y se retorna un vector vacío.                                                                        |
| `for (int v = destino; v != -1; v = parent[v])`                  | Construcción hacia atrás               | El camino se arma en sentido inverso (desde destino hasta origen).                                                                                                  |
| `reverse(camino.begin(), camino.end());`                         | Corregir el orden                      | Se invierte para mostrar el camino desde origen → destino.                                                                                                          |


### Algoritmo Floyd Warshall

```cpp
class FloydWarshall {
public:
    int n;
    vector<vector<int>> dist;

    FloydWarshall(int n, vector<vector<pair<int,int>>> &g) : n(n) {
        const int INF = 1e9;
        dist.assign(n, vector<int>(n, INF));

        // Inicializamos la matriz
        for (int i = 0; i < n; i++)
            dist[i][i] = 0;

        for (int u = 0; u < n; u++)
            for (auto &par : g[u]) {
                int v = par.first;
                int peso = par.second;
                dist[u][v] = min(dist[u][v], peso);
            }

        // Ejecutar algoritmo
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    }

    void imprimir() {
        const int INF = 1e9;
        cout << "\nMATRIZ DE CAMINOS MINIMOS (Floyd-Warshall)\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF) cout << "INF ";
                else cout << dist[i][j] << " ";
            }
            cout << "\n";
        }
    }
};
```

El algoritmo de Floyd-Warshall utiliza el principio de Programación Dinámica para encontrar las distancias mínimas entre cada par de nodos en un grafo ponderado.

El corazón del algoritmo radica en la idea de ir permitiendo el uso de nodos intermedios de forma incremental. Para calcular la distancia más corta de un nodo i a un nodo j, el algoritmo comprueba si es más corto pasar por un nodo intermedio k.

*dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])*

Donde:
*dist[i][j]* es el camino más corto conocido actualmente de i a j.

*dist[i][k] + dist[k][j]* es el camino que va de i a k, y luego de k a j.

Este proceso se repite para todos los posibles nodos intermedios k.

El primer paso es crear e inicializar la matriz de distancias (dist) que almacenará los caminos más cortos conocidos.

**Explicación del código**

| Segmento de Código                                                                 | Propósito                                | Explicación |
|------------------------------------------------------------------------------------|-------------------------------------------|-------------|
| `dist.assign(n, vector<int>(n, INF));`                                             | Inicialización de matriz de distancias.   | Crea una matriz `dist` de `n×n`, asignando a cada celda el valor `INF` (1e9), indicando inicialmente que todos los nodos están inalcanzables entre sí. |
| `for (int i = 0; i < n; i++) dist[i][i] = 0;`                                      | Distancia de un nodo hacia sí mismo.      | Un nodo siempre tiene distancia 0 a sí mismo. Esto asegura que no existan auto-ciclos con peso incorrecto. |
| **Bucle de aristas directas**<br>`for (int u = 0; u < n; u++)`<br>` for (auto &p : g[u])` | Carga de aristas desde el grafo original. | Para cada arista `(u → v)` con peso `p.second`, se establece `dist[u][v] = min(dist[u][v], peso)`. Esto permite soportar múltiples aristas entre los mismos nodos conservando el menor peso. |
| **Inicio del algoritmo**<br>`for (int k = 0; k < n; k++)`                          | Nodo intermediario `k`.                   | En este ciclo se elige un nodo `k` que funcionará como posible punto intermedio para mejorar distancias entre pares de nodos. |
| **Segundo ciclo**<br>`for (int i = 0; i < n; i++)`                                | Nodo de inicio `i`.                       | Se evalúa si la ruta `i → k` es viable para actualizar distancias. Si `dist[i][k]` es INF, no tiene sentido evaluar caminos vía `k`. |
| **Tercer ciclo**<br>`for (int j = 0; j < n; j++)`                                  | Nodo de destino `j`.                      | Se comprueba si el camino `i → k → j` mejora la distancia actual `i → j`. |
| `if (dist[i][k] < INF && dist[k][j] < INF)`                                        | Verificación de caminos válidos.          | Evita sumar valores INF, que producirían sobreflujo o resultados irreales. |
| `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);`                           | Relajación principal del algoritmo.       | Si la distancia pasando por `k` es menor que la conocida, se actualiza `dist[i][j]`. Esta es la esencia del algoritmo Floyd-Warshall. |

## Algoritmo Kruskal (Arbol de expansión min - max)

```cpp
class DSU {
public:
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == -1 || b == -1) return false;
        if (a == b) return false;

        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
        return true;
    }
};

// =======================================================
//      Algoritmo Kruskal
// =======================================================

class Kruskal {
public:
    int n;
    vector<tuple<int,int,int>> edges;

    Kruskal(int n) : n(n) {}

    // Nota: esta función espera u,v en 1-based (como se hacía en tu código original)
    void agregarArista(int u, int v, int w) {
        // Convertir a 0-based internamente (pero validamos que estén en rango)
        int uu = u - 1, vv = v - 1;
        if (!inRange(uu, n) || !inRange(vv, n)) return;
        edges.emplace_back(w, uu, vv);
    }

    pair<int, vector<tuple<int,int,int>>> mst_min() {
        DSU dsu(n);
        vector<tuple<int,int,int>> res;

        vector<tuple<int,int,int>> ord = edges;
        sort(ord.begin(), ord.end());

        int costo = 0;
        for (auto &[w, u, v] : ord) {
            if (dsu.unite(u, v)) {
                res.emplace_back(w, u, v);
                costo += w;
            }
        }

        return {costo, res};
    }

    pair<int, vector<tuple<int,int,int>>> mst_max() {
        DSU dsu(n);
        vector<tuple<int,int,int>> res;

        vector<tuple<int,int,int>> ord = edges;
        sort(ord.rbegin(), ord.rend());

        int costo = 0;
        for (auto &[w, u, v] : ord) {
            if (dsu.unite(u, v)) {
                res.emplace_back(w, u, v);
                costo += w;
            }
        }

        return {costo, res};
    }
};
```

**Explicación DSU (Disjoint Set Union)**

| Segmento de Código                                    | Propósito                  | Explicación                                                                                                                          |
| ----------------------------------------------------- | -------------------------- | ------------------------------------------------------------------------------------------------------------------------------------ |
| `vector<int> parent, rank;`                           | Estructuras principales    | `parent[i]` almacena el representante del conjunto de `i`. `rank[i]` ayuda a mantener el árbol equilibrado.                          |
| `void makeSet(int v) { parent[v] = v; rank[v] = 0; }` | Crear conjuntos iniciales  | Cada nodo inicia como su propio representante (conjunto independiente). El `rank` se inicializa en 0 porque aún es un árbol trivial. |
| `int findSet(int v)`                                  | Encontrar representante    | Busca la raíz del conjunto de `v`. Incluye **path compression**, lo que hace que las futuras búsquedas sean más rápidas.             |
| `if (v == parent[v]) return v;`                       | Caso base                  | Si el nodo es su propio padre, es el representante.                                                                                  |
| `return parent[v] = findSet(parent[v]);`              | Path compression           | Hace que todos los nodos visitados apunten directamente al representante, reduciendo la profundidad del árbol.                       |
| `void unionSet(int a, int b)`                         | Unir dos conjuntos         | Agrupa los conjuntos que contienen a `a` y `b`.                                                                                      |
| `a = findSet(a); b = findSet(b);`                     | Obtener sus representantes | Antes de unir, necesitamos saber quién es la raíz de cada conjunto.                                                                  |
| `if (a != b)`                                         | Evitar uniones redundantes | Solo se unen si pertenecen a conjuntos distintos.                                                                                    |
| `if (rank[a] < rank[b]) swap(a, b);`                  | Union by rank              | El árbol con menor rango cuelga del de mayor rango para evitar que crezca demasiado.                                                 |
| `parent[b] = a;`                                      | Unir conjuntos             | El representante de `b` ahora es `a`.                                                                                                |
| `if (rank[a] == rank[b]) rank[a]++;`                  | Actualizar rango           | Si ambos tenían igual altura, ahora el representante crece una unidad.                                                               |


**Explicación del Algoritmo de Kruskal**

| Segmento de Código                  | Propósito                  | Explicación                                                                  |
| ----------------------------------- | -------------------------- | ---------------------------------------------------------------------------- |
| `vector<tuple<int,int,int>> edges;` | Lista de aristas           | Cada arista contiene `{peso, u, v}`. Esto facilita el ordenamiento por peso. |
| `sort(edges.begin(), edges.end());` | Ordenar aristas por peso   | Kruskal elige siempre la arista más barata disponible que no forme ciclo.    |
| `int total = 0;`                    | Peso total del MST         | Va acumulando el costo del árbol de expansión mínima.                        |
| `for (auto &[w, u, v] : edges)`     | Recorrer aristas en orden  | Se evalúa cada arista de menor a mayor peso.                                 |
| `if (findSet(u) != findSet(v))`     | Verificar si forma ciclo   | Si `u` y `v` están en distintos conjuntos, no forma ciclo y puede añadirse.  |
| `total += w;`                       | Agregar peso al MST        | Se suma el peso de la arista seleccionada.                                   |
| `unionSet(u, v);`                   | Unir componentes           | Se agrupan los conjuntos para reflejar que la arista ya conecta ambos nodos. |
| `MST.push_back({u, v});`            | Registrar arista en el MST | Guarda la arista dentro del árbol final.                                     |


## Matching

```cpp
class MatchingBipartito {
public:
    int n;
    vector<vector<int>> &g;
    vector<int> matchR;   // A qué nodo está emparejado cada nodo del lado derecho
    vector<bool> seen;

    MatchingBipartito(vector<vector<int>> &grafo)
        : g(grafo), n(grafo.size()), matchR(n, -1) {}

    bool dfs(int u) {
        for (int v : g[u]) {
            if (!seen[v]) {
                seen[v] = true;

                if (matchR[v] == -1 || dfs(matchR[v])) {
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }

    int maxMatching() {
        int resultado = 0;

        for (int u = 0; u < n; u++) {
            seen.assign(n, false);
            if (dfs(u)) resultado++;
        }
        return resultado;
    }

    void imprimir() {
        cout << "\nParejas encontradas:\n";
        for (int v = 0; v < n; v++) {
            if (matchR[v] != -1)
                cout << matchR[v] << " - " << v << "\n";
        }
    }
};
```

La clase MatchingBipartito implementa un algoritmo basado en DFS/Flujo Máximo (a menudo conocido como el Algoritmo Húngaro o de Hopcroft-Karp simplificado) para encontrar el Maximum Bipartite Matching.

| Segmento de Código                                              | Propósito                           | Explicación                                                                                                         |                            |                                                                                                                                                      |
| --------------------------------------------------------------- | ----------------------------------- | ------------------------------------------------------------------------------------------------------------------- | -------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------- |
| `vector<int> matchR;`                                           | Algebra emparejada del lado derecho | `matchR[v]` indica con qué nodo izquierdo `u` está emparejado el nodo `v`. -1 significa libre.                      |                            |                                                                                                                                                      |
| `vector<bool> seen;`                                            | Marcar nodos visitados en cada DFS  | Evita explorar un mismo nodo derecho varias veces durante la búsqueda de un camino aumentante.                      |                            |                                                                                                                                                      |
| **Constructor** `MatchingBipartito(vector<vector<int>> &grafo)` | Inicialización                      | Asigna referencia al grafo bipartito y prepara `matchR` como no emparejados.                                        |                            |                                                                                                                                                      |
| `bool dfs(int u)`                                               | Buscar camino aumentante desde `u`  | Intenta emparejar a `u` buscando un nodo derecho libre o desplazando una coincidencia existente mediante recursión. |                            |                                                                                                                                                      |
| `for (int v : g[u])`                                            | Explorar vecinos del lado derecho   | Busca un nodo `v` al que `u` pueda conectarse (posible emparejamiento).                                             |                            |                                                                                                                                                      |
| `if (!seen[v])`                                                 | Evitar ciclos                       | Cada nodo derecho se visita una vez por búsqueda.                                                                   |                            |                                                                                                                                                      |
| `if (matchR[v] == -1                                            |                                     | dfs(matchR[v]))`                                                                                                    | Paso esencial del matching | **Caso 1:** `v` está libre. <br> **Caso 2:** `v` está emparejado, pero el emparejado actual puede encontrar otro match mediante DFS → se libera `v`. |
| `matchR[v] = u;`                                                | Realizar el emparejamiento          | El nodo derecho `v` se empareja con `u`.                                                                            |                            |                                                                                                                                                      |
| `int maxMatching()`                                             | Ejecutar matching máximo            | Lanza DFS desde cada nodo izquierdo para encontrar caminos aumentantes.                                             |                            |                                                                                                                                                      |
| `seen.assign(n, false);`                                        | Reset por cada DFS                  | Cada intención de emparejar un nodo izquierdo debe iniciar desde cero su lista de visitados.                        |                            |                                                                                                                                                      |
| `if (dfs(u)) resultado++;`                                      | Si se encontró aumento → +1         | Solo si la DFS descubre un nuevo emparejamiento se incrementa.                                                      |                            |                                                                                                                                                      |
| `imprimir()`                                                    | Mostrar resultados                  | Recorre `matchR` e imprime cada nodo derecho emparejado con su izquierdo.                                           |                            |                                                                                                                                                      |

```cpp
class MatchingGeneral {
public:
    int n;
    vector<vector<int>> &g;
    vector<int> match;

    MatchingGeneral(vector<vector<int>> &grafo)
        : g(grafo), n(grafo.size()), match(n, -1) {}

    int maxMatching() {
        int contador = 0;

        for (int u = 0; u < n; u++) {
            if (match[u] == -1) { 
                for (int v : g[u]) {
                    if (match[v] == -1) {
                        match[u] = v;
                        match[v] = u;
                        contador++;
                        break;
                    }
                }
            }
        }
        return contador;
    }

    void imprimir() {
        cout << "\nParejas encontradas:\n";
        vector<bool> visto(n, false);

        for (int u = 0; u < n; u++) {
            if (match[u] != -1 && !visto[u]) {
                cout << u << " - " << match[u] << "\n";
                visto[u] = visto[match[u]] = true;
            }
        }
    }
};
```

La clase MatchingGeneral implementa un algoritmo voraz (greedy) simple para encontrar un matching maximal en un grafo general (dirigido o no dirigido, bipartito o no bipartito).

Es importante notar que un matching maximal (maximal matching) no es necesariamente el matching máximo (maximum matching), ya que este algoritmo se detiene ante el primer emparejamiento encontrado para un nodo.

| Segmento de Código                     | Propósito                            | Explicación                                                                                |
| -------------------------------------- | ------------------------------------ | ------------------------------------------------------------------------------------------ |
| `vector<int> match;`                   | Matching del grafo general           | `match[u]` es el nodo emparejado con `u`. -1 significa libre.                              |
| **Constructor** `MatchingGeneral(...)` | Inicializar variables                | Crea el vector de emparejamientos y referencia el grafo.                                   |
| `int maxMatching()`                    | Calcular matching maximal greedy     | Algoritmo rápido que no necesariamente encuentra el matching máximo, pero uno **maximal**. |
| `if (match[u] == -1)`                  | Solo buscar pareja si `u` está libre | Ahorramos trabajo revisando únicamente nodos libres.                                       |
| `for (int v : g[u])`                   | Revisar vecinos del grafo            | Intenta emparejar a `u` con cualquiera de sus vecinos libres.                              |
| `if (match[v] == -1)`                  | Condición para formar pareja         | Si `v` también está libre → se forma pareja inmediatamente.                                |
| `match[u] = v; match[v] = u;`          | Registrar el emparejamiento          | Se marca que ambos están emparejados entre sí.                                             |
| `contador++;`                          | Aumentar número de parejas           | Cada emparejamiento válido incrementa el contador.                                         |
| `break;`                               | Evitar múltiples parejas             | Una vez emparejado `u`, no se sigue buscando más.                                          |
| `imprimir()`                           | Mostrar emparejamientos              | Imprime todas las parejas, evitando repetirlas (`visto`).                                  |
| `if (match[u] != -1 && !visto[u])`     | Imprimir solo una vez                | Evita repetir por ejemplo “3 - 5” y luego “5 - 3”.                                         |


## Matching Avanzado

### Algoritmo para bipartitos Hopcroft Karp

```cpp
class HopcroftKarp {
public:
    int n, m; // tamaño de los conjuntos U y V
    vector<vector<int>> adj; 
    vector<int> pairU, pairV, dist;

    HopcroftKarp(vector<vector<int>>& g, int nLeft)
        : n(nLeft), m((int)g.size() - nLeft), adj(g) 
    {
        // adaptar estructuras para 1-based dentro de la implementación clásica
        pairU.assign(n + 1, 0);
        pairV.assign(max(1,m) + 1, 0);
        dist.assign(n + 1, 0);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (pairU[u] == 0) {
                dist[u] = 0;
                q.push(u);
            }
            else dist[u] = INT_MAX;
        }

        dist[0] = INT_MAX;

        while (!q.empty()) {
            int u = q.front(); q.pop();

            if (dist[u] < dist[0]) {
                // adj is expected to be 1-based rows for this implementation;
                // we must guard against out-of-range access
                if (u < 0 || u >= (int)adj.size()) continue;
                for (int v : adj[u]) {
                    if (v < 0 || v >= (int)pairV.size()) continue;
                    if (dist[pairV[v]] == INT_MAX) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return dist[0] != INT_MAX;
    }

    bool dfs(int u) {
        if (u == 0) return true;

        if (u < 0 || u >= (int)adj.size()) return false;
        for (int v : adj[u]) {
            if (v < 0 || v >= (int)pairV.size()) continue;
            if (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v])) {
                pairV[v] = u;
                pairU[u] = v;
                return true;
            }
        }

        dist[u] = INT_MAX;
        return false;
    }

    int maxMatching() {
        int matching = 0;

        while (bfs()) {
            for (int u = 1; u <= n; u++)
                if (pairU[u] == 0 && dfs(u))
                    matching++;
        }

        return matching;
    }
};
```

El algoritmo de Hopcroft-Karp organiza la búsqueda de caminos aumentantes en fases interactivas. En cada fase, realiza dos pasos principales:

**Fase BFS:** Encuentra el conjunto más grande de caminos aumentantes disjuntos de longitud mínima.

**Fase DFS:** Ejecuta el aumento de matching a lo largo de los caminos encontrados en la fase BFS.

Este enfoque de "capas" garantiza que los caminos se procesen en orden creciente de longitud, lo que lleva a la alta eficiencia del algoritmo.

**`Estructura y Componentes (Clase HopcroftKarp)`**

| Miembro | Tipo | Propósito |
|--------|------|-----------|
| **n** | int | Tamaño del conjunto izquierdo **U**. Los nodos van de 1 a n. |
| **m** | int | Tamaño del conjunto derecho **V**. Los nodos van de 1 a m. |
| **pairU** | vector<int> | Emparejamiento para U. `pairU[u] = v` significa que **u∈U** está emparejado con **v∈V**. Si vale 0 → está libre. |
| **pairV** | vector<int> | Emparejamiento para V. `pairV[v] = u` significa que **v∈V** está emparejado con **u∈U**. Si vale 0 → está libre. |
| **dist** | vector<int> | Distancias usadas en el **BFS**, representan el nivel o capa de cada nodo U desde los nodos libres. Permite construir caminos aumentantes mínimos. |

**`bool bfs() (Construcción de Capas)`**

| Segmento de Código | Lógica y Proceso |
|--------------------|------------------|
| **Inicialización** | Los nodos de **U** que están libres (`pairU[u] == 0`) se colocan en la cola y su distancia se establece en **0**. Los nodos emparejados reciben distancia **∞** (`INT_MAX`). `dist[0]` funciona como nodo artificial que marca el final de las capas. |
| **Ciclo `while`** | El BFS avanza **por capas**. Cuando se extrae un nodo `u ∈ U` y se analizan sus vecinos `v ∈ V`, se evalúa si se puede extender un camino alternante válido. |
| `if (dist[pairV[v]] == INT_MAX)` | **Condición clave:** Verifica si la pareja actual de `v` no ha sido alcanzada antes. Esto garantiza que se mantengan **caminos alternantes** y de **longitud mínima**. Solo se explora `pairV[v]` cuando pertenece a la capa siguiente correcta. |
| **Actualización** | Si la pareja de `v` no ha sido visitada: `dist[pairV[v]] = dist[u] + 1;` y se mete `pairV[v]` (un nodo de **U**) en la cola, expandiendo la siguiente capa. |
| **Fin del BFS** | El BFS termina. Si `dist[0] != INT_MAX`, significa que un nodo libre en **V** fue alcanzado ⇒ **existe al menos un camino aumentante mínimo** para intentar mejorar el matching. |

`bool dfs(int u) (Búsqueda y Aumento)`

Esta función realiza una búsqueda DFS para encontrar los caminos aumentantes a lo largo de las capas construidas por el BFS.

| Segmento de Código | Lógica y Proceso |
|--------------------|------------------|
| `if (u == 0) return true;` | **Caso Base:** Significa que se alcanzó el nodo artificial `0`, que representa un nodo libre en `V`. Esto implica que se completó un **camino aumentante**. |
| **Iteración sobre `v`** | Se recorren todos los vecinos `v` del nodo `u` en el grafo bipartito. |
| `if (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))` | **Condición de Capa:** Solo continúa por la pareja `pairV[v]` si esta se encuentra en la **siguiente capa BFS** (`dist[u] + 1`) y el DFS desde allí puede completar el camino aumentante. Garantiza buscar **solo los caminos más cortos**, tal como definió el BFS. |
| **Aumento de Matching** | Cuando `dfs(pairV[v])` retorna `true`, significa que se pudo completar el camino aumentante ⇒ se **actualiza el matching**: `pairV[v] = u` y `pairU[u] = v`. |
| `dist[u] = INT_MAX;` | **Poda (Optimización):** Si no se pudo encontrar camino aumentante desde `u`, se marca su distancia como `∞`. Esto evita revisitar `u` en el DFS actual y acelera considerablemente la ejecución. |

`int maxMatching() (El Algoritmo Principal)`

```cpp
while (bfs()) {
    for (int u = 1; u <= n; u++)
        if (pairU[u] == 0 && dfs(u))
            matching++;
}
return matching;
```

Este es el ciclo de fases que garantiza la complejidad $O(E\sqrt{V})$:

- **Fase Principal (while (bfs())):** El algoritmo repite la fase (un bfs seguido de múltiples dfs) mientras el BFS pueda encontrar al menos un camino aumentante de longitud mínima.

- **Aumento del Matching:** En cada fase, se itera sobre todos los nodos libres de U (pairU[u] == 0) y se llama a dfs(u). Cada vez que el DFS tiene éxito, se incrementa el contador de matching.

El resultado final es el tamaño del Matching Máximo Bipartito.

### Algoritmo pagra grafos generales Blossom Edmons

```cpp
class Blossom {
public:
    int n;
    vector<vector<int>> g;
    vector<int> match, p, base;
    vector<bool> used, blossom;
    queue<int> q;

    Blossom(vector<vector<int>>& graph) {
        g = graph;
        n = g.size();
        match.assign(n, -1);
        p.assign(n, -1);
        base.resize(n);
        used.assign(n, false);
        blossom.assign(n, false);
    }

    int lca(int a, int b) {
        vector<bool> visited(n, false);
        while (true) {
            a = base[a];
            visited[a] = true;
            if (match[a] == -1) break;
            a = p[match[a]];
        }
        while (true) {
            b = base[b];
            if (visited[b]) return b;
            b = p[match[b]];
        }
    }

    void markPath(int v, int b, int children) {
        while (base[v] != b) {
            blossom[base[v]] = blossom[base[match[v]]] = true;
            p[v] = children;
            children = match[v];
            v = p[match[v]];
        }
    }

    int findPath(int root) {
        fill(used.begin(), used.end(), false);
        fill(p.begin(), p.end(), -1);
        for (int i = 0; i < n; i++) base[i] = i;

        while (!q.empty()) q.pop();
        q.push(root);
        used[root] = true;

        while (!q.empty()) {
            int v = q.front(); q.pop();

            for (int u : g[v]) {
                if (base[v] == base[u] || match[v] == u) continue;

                if (u == root || (match[u] != -1 && p[match[u]] != -1)) {
                    int cur = lca(v, u);

                    fill(blossom.begin(), blossom.end(), false);
                    markPath(v, cur, u);
                    markPath(u, cur, v);

                    for (int i = 0; i < n; i++)
                        if (blossom[base[i]]) {
                            base[i] = cur;
                            if (!used[i]) {
                                used[i] = true;
                                q.push(i);
                            }
                        }
                }
                else if (p[u] == -1) {
                    p[u] = v;
                    if (match[u] == -1) {
                        v = u;
                        while (v != -1) {
                            int pv = p[v], nv = (pv==-1? -1 : match[pv]);
                            match[v] = pv;
                            if (pv != -1) match[pv] = v;
                            v = nv;
                        }
                        return 1;
                    }
                    u = match[u];
                    used[u] = true;
                    q.push(u);
                }
            }
        }
        return 0;
    }

    int maxMatching() {
        int ans = 0;
        for (int i = 0; i < n; i++)
            if (match[i] == -1)
                ans += findPath(i);
        return ans;
    }
};
```

El algoritmo Blossom (Flor), desarrollado por Jack Edmonds en 1965, es el algoritmo más complejo y potente para encontrar el Maximum Matching (Emparejamiento Máximo) en un grafo general (no necesariamente bipartito).

Su complejidad principal reside en la necesidad de manejar los ciclos de longitud impar (llamados Blossoms o Flores), que no existen en los grafos bipartitos.

Al igual que en el Matching Bipartito avanzado, el algoritmo Blossom se basa en la búsqueda de Caminos Aumentantes. Sin embargo, introduce un mecanismo para manejar ciclos impares:

- **Ciclos Impares (Blossoms):** Un ciclo de longitud impar que comienza y termina en un nodo emparejado (alternando aristas in-matching y out-of-matching) impide la extensión de un camino aumentante.

- **Contracción:** La clave del algoritmo es contraer un blossom a un solo nodo (su base). Esto transforma temporalmente el grafo, eliminando el ciclo impar.

- **Búsqueda** Continua: Una vez contraído, la búsqueda del camino aumentante continúa en el grafo modificado. Si se encuentra un camino aumentante, se "descontrae" el blossom y se ajustan las aristas para incorporar el aumento.

El algoritmo se implementa típicamente usando una Búsqueda en Amplitud (BFS) modificada.

| Miembro      | Tipo                          | Propósito y Función |
|--------------|-------------------------------|----------------------|
| `n, g`       | `int`, `vector<vector<int>>`  | `n` es el tamaño del grafo. `g` es la lista de adyacencia que describe las conexiones del grafo general. |
| `match`      | `vector<int>`                 | Emparejamiento actual: `match[i] = j` indica que el nodo `i` está emparejado con `j`. Se inicializa en `-1` porque todos empiezan libres. |
| `p`          | `vector<int>`                 | Parent en el BFS. Permite reconstruir el **camino alternante** cuando se encuentra un camino aumentante. |
| `base`       | `vector<int>`                 | Base del blossom. `base[i]` es el **representante del ciclo contraído (blossom)** al que pertenece el nodo `i`. |
| `used`       | `vector<bool>`                | Marca los nodos usados durante el BFS. Ayuda a controlar niveles y seguimiento de caminos alternantes. |
| `blossom`    | `vector<bool>`                | Indica qué nodos pertenecen al **blossom actualmente detectado y en proceso de contracción**. |
| `q`          | `queue<int>`                  | Cola de BFS para buscar caminos aumentantes y expandir niveles en el grafo. |


**`int lca(int a, int b) (Lowest Common Ancestor - Mínimo Ancestor Común)`**

Esta función es crucial para identificar un blossom. Encuentra el nodo más cercano a a y b que es la base común de un ciclo impar.

Sigue el camino de a hacia su raíz a través de aristas emparejadas y padres (p[match[a]]). Marca todos los nodos base (base[a]) en ese camino como visitados. Sigue el camino de b. El primer nodo base visitado que coincida con uno marcado en el camino de a es el LCA, que será la base del blossom.

**`void markPath(int v, int b, int children)`** 

Esta función marca y actualiza los punteros dentro del blossom que se acaba de identificar. Recorre el camino desde el nodo v hasta la base b del blossom. Marca las bases de los nodos en el camino (base[v], base[match[v]]) como parte del blossom temporal. Actualiza el padre (p) de los nodos en el camino, dirigiendo las aristas del camino hacia el nodo children (que es el nodo que conecta el camino con el LCA). Esto es parte del proceso de "acortar" el camino.

**`int findPath(int root) (Búsqueda de Camino Aumentante)`**

Esta función realiza el BFS modificado para encontrar un camino aumentante a partir de un nodo libre root.

| **Miembro** | **Tipo**                     | **Propósito y Función**                                                                 |
| ----------- | ---------------------------- | --------------------------------------------------------------------------------------- |
| `n, g`      | `int`, `vector<vector<int>>` | Tamaño del grafo y su lista de adyacencia.                                              |
| `match`     | `vector<int>`                | Emparejamiento actual: `match[i] = j` si i está emparejado con j. Se inicializa a `-1`. |
| `p`         | `vector<int>`                | Padre durante el BFS (camino alternante). Sirve para rastrear el camino aumentante.     |
| `base`      | `vector<int>`                | Base del blossom. `base[i]` es el representante del blossom al que pertenece `i`.       |
| `used`      | `vector<bool>`               | Indica qué nodos ya fueron visitados durante el BFS.                                    |
| `blossom`   | `vector<bool>`               | Marca nodos que pertenecen al blossom actualmente siendo contraído.                     |
| `q`         | `queue<int>`                 | Cola utilizada en el BFS para expandir caminos alternantes.                             |

**`int maxMatching() (Ejecución Principal)`**

Este método coordina las fases de búsqueda de camino aumentante. Itera sobre todos los nodos, si un nodo i no está emparejado (match[i] == -1), se llama a findPath(i) para intentar encontrar un camino aumentante que comience en i,dando como resultado la suma los aumentos de matching encontrados (ans += findPath(i)), dándonos el tamaño del Maximum General Matching.

## Menu

```cpp
int main() {
    int op, n = 0, a = 0;
    bool dirigido = false, ponderado = false;

    vector<vector<int>> grafoNP;
    vector<vector<pair<int,int>>> grafoP;

    do {
        system("cls");
        cout << "____________________________\n";
        cout << "     LABORATORY OF GRAPHS   \n";
        cout << "____________________________\n";
        cout << "1. Almacenar Grafo\n";
        cout << "2. Caracteristicas\n";
        cout << "3. Camino mas corto\n";
        cout << "4. Arbol de expansion\n";
        cout << "5. Matching\n";
        cout << "6. Matching avanzado\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        switch(op) {

        // ===========================================================
        //                  OPCION 1: ALMACENAR GRAFO
        // ===========================================================
        case 1: {
            system("cls");
            int t;
			
			cout <<"\tGuardando\n\n";
            cout << "1. Grafo dirigido\n";
            cout << "2. Grafo no dirigido\n";
            cin >> t;
            dirigido = (t == 1);

            cout << "\n1. Ponderado\n";
            cout << "2. No ponderado\n";
            cin >> t;
            ponderado = (t == 1);

            cout << "\nCantidad de nodos: ";
            cin >> n;
            cout << "Cantidad de aristas: ";
            cin >> a;

            grafoNP.assign(n, {});
            grafoP.assign(n, {});

            if (!ponderado) {
                for (int i = 0; i < a; i++) {
                    int u, v;
                    cout << "Origen Destino [0.." << n-1 << "]: ";
                    cin >> u >> v;
                    if (!inRange(u,n) || !inRange(v,n)) {
                        cout << "Error: uno o ambos nodos no estan en el rango 0.." << n-1 << ". Intenta de nuevo.\n";
                        i--; // permitir reintento
                        continue;
                    }
                    insertarNP(u, v, grafoNP, dirigido);
                }

                cout << "\nGrafo almacenado:\n";
                for (int i = 0; i < n; i++) {
                    cout << i << " = ";
                    for (auto v : grafoNP[i]) {
                        if (inRange(v,n)) cout << v << " ";
                    }
                    cout << "\n";
                }
            }
            else {
                for (int i = 0; i < a; i++) {
                    int u, v, p;
                    cout << "Origen Destino Peso [0.." << n-1 << "]: ";
                    cin >> u >> v >> p;
                    if (!inRange(u,n) || !inRange(v,n)) {
                        cout << "Error: uno o ambos nodos no estan en el rango 0.." << n-1 << ". Intenta de nuevo.\n";
                        i--;
                        continue;
                    }
                    insertarP(u, v, p, grafoP, dirigido);
                    insertarNP(u, v, grafoNP, dirigido); // guardamos versión no ponderada para recorridos
                }

                cout << "\nGrafo ponderado almacenado:\n";
                for (int i = 0; i < n; i++) {
                    cout << i << " = ";
                    for (auto& par : grafoP[i]) {
                        if (inRange(par.first,n)) cout << "[" << par.first << ", peso=" << par.second << "] ";
                    }
                    cout << "\n";
                }
            }

            system("pause");
            break;
        }

        // ===========================================================
        //                OPCION 2: CARACTERISTICAS
        // ===========================================================
        case 2: {
            if (n == 0) {
                cout << "No hay grafo cargado.\n";
                system("pause");
                break;
            }

            system("cls");

            // ------------------ Lista de adyacencia -----------------
            cout << "\nLISTA DE ADYACENCIA\n";
            for (int i = 0; i < n; i++) {
                cout << i << " = ";
                for (int v : grafoNP[i]) if (inRange(v,n)) cout << v << " ";
                cout << "\n";
            }

            // ------------------ Matriz de adyacencia ----------------
            cout << "\nMATRIZ DE ADYACENCIA\n";
            vector<vector<int>> matA(n, vector<int>(n, 0));

            if (!ponderado) {
                // --- No ponderado: solo marcamos 1 ---
                for (int u = 0; u < n; u++)
                    for (int v : grafoNP[u])
                        if (inRange(v,n)) matA[u][v] = 1;
            }
            else {
                // --- Ponderado: usamos pesos reales ---
                for (int u = 0; u < n; u++)
                    for (auto& par : grafoP[u]) {
                        int v = par.first;
                        int peso = par.second;
                        if (!inRange(v,n)) continue;
                        matA[u][v] = peso;
                    }
            }

            // Imprimir matriz
            for (auto& fila : matA) {
                for (int x : fila) cout << x << " ";
                cout << "\n";
            }

            // ------------------ Matriz de incidencia ----------------
            cout << "\nMATRIZ DE INCIDENCIA\n";

            int edgeCount = a;
            if (edgeCount <= 0) edgeCount = 0;
            vector<vector<int>> matI(n, vector<int>(edgeCount, 0));

            vector<vector<bool>> usado(n, vector<bool>(n, false));
            int id = 0;

            for (int u = 0; u < n; u++) {
                for (int v : grafoNP[u]) {
                    if (!inRange(v,n)) continue;

                    if (!dirigido) {
                        if (usado[u][v] || usado[v][u]) continue;
                        usado[u][v] = usado[v][u] = true;
                    }

                    if (id >= edgeCount) break;

                    matI[u][id] = dirigido ? -1 : 1;
                    matI[v][id] = dirigido ?  1 : 1;
                    id++;
                }
            }

            for (auto& fila : matI) {
                for (int x : fila) cout << x << " ";
                cout << "\n";
            }

            // ------------------ Componentes conexas ------------------
            cout << "\nCOMPONENTES CONEXAS (BFS)\n";
            {
                vector<bool> visited(n, false);
                for (int i = 0; i < n; i++)
                    if (!visited[i])
                        bfs_component(i, visited, grafoNP);
            }

            // ------------------ Si es árbol -------------------------
            cout << "\nES ARBOL?\n";
            cout << (esArbol(grafoNP, n, a) ? "SI\n" : "NO\n");

            // ------------------ Bipartito ---------------------------
            cout << "\nES BIPARTITO?\n";
            cout << (esBipartito(grafoNP, n) ? "SI\n" : "NO\n");

            // ------------------ Fuertemente conexo ------------------
            if (dirigido) {
                cout << "\nES FUERTEMENTE CONEXO?\n";
                cout << (fuertementeConexo(grafoNP, n) ? "SI\n" : "NO\n");
            }

            system("pause");
            break;
        }

        // ===========================================================
        //                OPCION 3: CAMINOS MAS CORTOS
        // ===========================================================
        case 3: {
            if (!ponderado) {
                cout << "El grafo no es ponderado. Se requieren pesos para caminos minimos.\n";
                system("pause");
                break;
            }

            int algoritmo;
            system("cls");
            cout << "CAMINOS MAS CORTOS\n";
            cout << "1. Dijkstra\n";
            cout << "2. Floyd-Warshall\n";
            cout << "Elige: ";
            cin >> algoritmo;

            // =============================
            //            DIJKSTRA
            // =============================
            if (algoritmo == 1) {
                int origen, destino;
                cout << "Nodo origen [0.." << n-1 << "]: ";
                cin >> origen;
                if (!inRange(origen,n)) {
                    cout << "El nodo origen " << origen << " no esta en el grafo ingresado.\n";
                    system("pause");
                    break;
                }

                Dijkstra dij(n, grafoP);
                dij.ejecutar(origen);

                cout << "Nodo destino [0.." << n-1 << "]: ";
                cin >> destino;
                if (!inRange(destino,n)) {
                    cout << "El nodo destino " << destino << " no esta en el grafo ingresado.\n";
                    system("pause");
                    break;
                }

                cout << "\nDistancia minima de " << origen << " a " << destino << ": ";

                if (dij.dist[destino] == 1e9) {
                    cout << "No existe camino.\n";
                } else {
                    cout << dij.dist[destino] << "\n\n";

                    vector<int> camino = dij.reconstruirCamino(destino);

                    if (camino.empty()) cout << "No hay camino para reconstruir.\n";
                    else {
                        cout << "Camino: ";
                        for (int v : camino) cout << v << " ";
                        cout << "\n";
                    }
                }
            }

            // =============================
            //      FLOYD-WARSHALL
            // =============================
            else if (algoritmo == 2) {
                FloydWarshall fw(n, grafoP);
                fw.imprimir();
            } else {
                cout << "Opcion no valida.\n";
            }

            system("pause");
            break;
        }

        // ===========================================================
        //                OPCION 4: ARBOL DE EXPANSION
        // ===========================================================
        case 4: {
            if (grafoP.empty()) {
                cout << "Primero cargue un grafo ponderado.\n";
                system("pause");
                break;
            }

            Kruskal k(n);

            // Convertir grafo ponderado (lista de adyacencia) en lista de aristas
            for (int u = 0; u < n; u++) {
                for (auto &par : grafoP[u]) {
                    int v = par.first;
                    int w = par.second;
                    if (!inRange(v,n)) continue;
                    if (u < v) {
                        // agregarArista espera 1-based (como en tu código original)
                        k.agregarArista(u + 1, v + 1, w);
                    }
                }
            }

            cout << "\n--- ARBOL DE EXPANSION MINIMO (KRUSKAL) ---\n";
            auto [costoMin, arbolMin] = k.mst_min();

            cout << "Costo total = " << costoMin << "\n";
            cout << "Aristas del árbol:\n";
            for (auto &[w, u, v] : arbolMin) {
                cout << "[" << u + 1 << ", " << v + 1 << "] peso = " << w << "\n";
            }

            cout << "\n--- ARBOL DE EXPANSION MAXIMO (KRUSKAL) ---\n";
            auto [costoMax, arbolMax] = k.mst_max();

            cout << "Costo total = " << costoMax << "\n";
            cout << "Aristas del árbol:\n";
            for (auto &[w, u, v] : arbolMax) {
                cout << "[" << u + 1 << ", " << v + 1 << "] peso = " << w << "\n";
            }
            system("pause");

            break;
        }

        // ===========================================================
        //                OPCION 5: MATCHING SIMPLE
        // ===========================================================
        case 5: {
            if (grafoNP.empty()) {
                cout << "Primero ingresa un grafo.\n";
                system("pause");
                break;
            }

            cout << "\n--- MATCHING ---\n";

            // Revisamos si es bipartito
            bool bip = esBipartito(grafoNP, grafoNP.size());

            if (bip) {
                cout << "El grafo es bipartito ... usando Matching Bipartito.\n";

                MatchingBipartito mb(grafoNP);
                int res = mb.maxMatching();
                cout << "Matching encontrado: " << res << "\n";
                mb.imprimir();
            }
            else {
                cout << "El grafo NO es bipartito ... usando Matching General.\n";

                MatchingGeneral mg(grafoNP);
                int res = mg.maxMatching();
                cout << "Matching encontrado: " << res << "\n";
                mg.imprimir();
            }
            system("pause");

            break;
        }

        // ===========================================================
        //                OPCION 6: MATCHING AVANZADO
        // ===========================================================
        case 6: {
            if (grafoNP.empty()) {
                cout << "Primero ingresa un grafo.\n";
                system("pause");
                break;
            }

            cout << "\n===== MATCHING AVANZADO =====\n";

            // Revisamos si es bipartito
            bool bip = esBipartito(grafoNP, grafoNP.size());

            if (bip) {
                cout << "El grafo es bipartito usando Hopcroft-Karp.\n";

                // Definimos tamaño del conjunto izquierdo (simple: mitad)
                int mitad = grafoNP.size() / 2;

                HopcroftKarp hk(grafoNP, mitad);
                int res = hk.maxMatching();

                cout << "Matching maximo bipartito = " << res << "\n";
            }
            else {
                cout << "El grafo NO es bipartito usando algoritmo Blossom.\n";

                Blossom bl(grafoNP);
                int res = bl.maxMatching();

                cout << "Matching maximo general = " << res << "\n";
            }

            system("pause");

            break;
        }

        } // switch

    } while (op != 0);

    return 0;
}
```

El menú se encuentra implementado dentro de la función main(), ya que desde este punto central se invocan todos los algoritmos desarrollados en el proyecto. Su finalidad es permitir que el usuario interactúe con cada módulo sin necesidad de modificar el código, proporcionando una interfaz estructurada y fácil de navegar.

El menú está dividido en 7 opciones, las cuales conducen a 6 apartados funcionales donde es posible ejecutar los diferentes algoritmos de análisis y procesamiento de grafos. Para acceder a cualquiera de ellos, el usuario debe ingresar un número que va desde 0 hasta 6, según la operación que desee realizar. Cada opción activa un conjunto de instrucciones y algoritmos específicos que permiten manipular grafo, calcular propiedades o resolver problemas clásicos como caminos mínimos, árboles de expansión o matchings.

A continuación se presenta la estructura general del menú:

| Opción | Nombre                       | Qué hace (resumen) |
|--------|------------------------------|---------------------|
| 0      | Salir                        | Cierra el programa. |
| 1      | Almacenar grafo              | Permite ingresar y guardar el grafo (varias representaciones admitidas). |
| 2      | Características del grafo    | Muestra propiedades: bipartito, árbol, fuertemente conexo; componentes conexas; y las 3 representaciones (lista de adyacencia, matriz de adyacencia, matriz de incidencia). |
| 3      | Caminos cortos               | Submenú de algoritmos de caminos: (1) Dijkstra — ruta mínima entre dos nodos (reconstruye camino). (2) Floyd–Warshall — todas las parejas de distancias mínimas (tabla de distancias). |
| 4      | Árbol de expansión (Min / Max) | Calcula árbol generador mínimo y máximo usando Kruskal (mínimo) y Kruskal invertido (máximo); muestra aristas y costo. |
| 5      | Matching general (greedy)    | Busca un matching maximal en grafo general (algoritmo greedy, rápido, no garantiza máximo). |
| 6      | Matching avanzado            | Matching más potente: opciones para (a) grafos bipartitos — Hopcroft–Karp (matching máximo); (b) grafos generales — Edmonds (Blossom) para matching máximo. |

Cada selección guía al usuario hacia uno de los apartados de análisis o resolución, solicitando información adicional solo cuando es necesaria (por ejemplo, nodos origen/destino en Dijkstra o pesos en el almacenamiento del grafo). El programa también realiza validaciones para asegurar que el grafo cargado sea compatible con el algoritmo solicitado, y en caso contrario muestra mensajes claros y comprensibles.

El menú principal constituye el núcleo de interacción del proyecto, permitiendo acceder de manera ordenada y modular a todos los algoritmos implementados. Gracias a este diseño, el usuario puede analizar un grafo desde distintos enfoques: estructura, conectividad, rutas óptimas, árboles generadores y matchings, empleando algoritmos eficientes y reconocidos en la teoría de grafos.

La integración de estas funciones dentro de una misma interfaz hace que el programa sea versátil, completo y útil tanto para fines educativos como prácticos. Este menú garantiza una navegación intuitiva, facilitando el uso secuencial o independiente de cada apartado según las necesidades del usuario.

# Conclusiones

El desarrollo de este programa permitió integrar en una sola herramienta múltiples algoritmos fundamentales del estudio de grafos, ofreciendo una plataforma práctica, educativa y funcional para analizar estructuras complejas. A lo largo del proyecto se implementaron métodos clásicos como DFS, BFS, Dijkstra, Floyd–Warshall y Kruskal, además de algoritmos avanzados como Hopcroft–Karp y Matching General, logrando así una cobertura amplia de temas esenciales en teoría de grafos y optimización combinatoria.

Durante el proceso se comprobó que una adecuada representación del grafo, ya sea mediante lista de adyacencia, matriz de adyacencia o matriz de incidencia, influye directamente en el rendimiento de los algoritmos, resaltando la importancia de seleccionar la estructura ideal dependiendo del tipo y tamaño del grafo tratado.

Asimismo, la inclusión del menú interactivo facilitó la navegación del usuario, permitiendo evaluar propiedades como bipartición, conectividad, existencia de árboles de expansión y obtención de caminos mínimos. Esto convierte al programa no solo en una herramienta técnica, sino también en un espacio didáctico para comprender el funcionamiento interno de cada algoritmo mediante ejemplos y resultados visibles.

Se verificó además la correcta interacción entre algoritmos, como la comparación entre Dijkstra y Floyd–Warshall, y la validación de que un grafo sea fuertemente conexo mediante DFS en el grafo original y en su transpuesto. Todas estas pruebas permitieron asegurar la fiabilidad del programa.

En conjunto, este trabajo consolida conocimientos teóricos de estructuras de datos, análisis algorítmico y programación, aplicándolos de manera integrada en un proyecto funcional. El sistema final es capaz de procesar grafos de distintos tipos, resolver problemas clásicos y mostrar información útil y ordenada al usuario, cumpliendo los objetivos planteados.
