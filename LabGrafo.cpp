#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <windows.h>

using namespace std;

// =======================================================
//       INSERTAR ARISTAS
// =======================================================

void insertarNP(int o, int d, vector<vector<int>>& g, bool dirigido) {
    g[o].push_back(d);
    if (!dirigido)
        g[d].push_back(o);
}

void insertarP(int o, int d, int p, vector<vector<pair<int,int>>>& g, bool dirigido) {
    g[o].push_back({d, p});
    if (!dirigido)
        g[d].push_back({o, p});
}

// =======================================================
//       BFS para componentes y conectividad
// =======================================================

void bfs_component(int start, vector<bool>& visited, vector<vector<int>>& g) {
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "Componente: ";

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";

        for (int v : g[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    cout << "\n";
}

// =======================================================
//       DFS (para componentes y conectividad)
// =======================================================

void dfs_rec(int u, vector<bool>& visited, vector<vector<int>>& g) {
    visited[u] = true;
    for (int v : g[u])
        if (!visited[v])
            dfs_rec(v, visited, g);
}

// =======================================================
//       VERIFICAR SI ES BIPARTITO
// =======================================================

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

// =======================================================
//       FUERTEMENTE CONEXO 
// =======================================================

bool fuertementeConexo(vector<vector<int>>& g, int n) {
    vector<bool> visited(n, false);

    dfs_rec(0, visited, g);
    for (bool x : visited) if (!x) return false;

    vector<vector<int>> trans(n);
    for (int u = 0; u < n; u++)
        for (int v : g[u])
            trans[v].push_back(u);

    fill(visited.begin(), visited.end(), false);

    dfs_rec(0, visited, trans);
    for (bool x : visited) if (!x) return false;

    return true;
}

// =======================================================
//       VERIFICAR SI ES ÁRBOL
// =======================================================

bool esArbol(vector<vector<int>>& g, int n, int aristas) {
    vector<bool> visited(n, false);

    bfs_component(0, visited, g);

    for (bool x : visited)
        if (!x) return false;

    if (aristas != n - 1) return false;

    return true;
}

// =======================================================
//       Algoritmo Dijkstra "Clase"
// =======================================================

class Dijkstra {
public:
    int n;
    vector<vector<pair<int,int>>> &g; // Grafo ponderado

    Dijkstra(int n, vector<vector<pair<int,int>>> &g) : n(n), g(g) {}

    vector<int> ejecutar(int origen) {
        const int INF = 1e9;
        vector<int> dist(n, INF);
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

        dist[origen] = 0;
        pq.push({0, origen});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d != dist[u]) continue;

            for (auto &par : g[u]) {
                int v = par.first;
                int peso = par.second;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
};

// =======================================================
//       Algoritmo Floyd Warshall "Clase"
// =======================================================

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



// =======================================================
//                       MAIN
// =======================================================

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
        cout << "0. Salir\n";
        cin >> op;

        switch(op) {

        // ===========================================================
        //                  OPCION 1: ALMACENAR GRAFO
        // ===========================================================
        case 1: {
            system("cls");
            int t;

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
                    cout << "Origen Destino: ";
                    cin >> u >> v;
                    insertarNP(u, v, grafoNP, dirigido);
                }

                cout << "\nGrafo almacenado:\n";
                for (int i = 0; i < n; i++) {
                    cout << i << " -> ";
                    for (auto v : grafoNP[i]) cout << v << " ";
                    cout << "\n";
                }
            }
            else {
                for (int i = 0; i < a; i++) {
                    int u, v, p;
                    cout << "Origen Destino Peso: ";
                    cin >> u >> v >> p;
                    insertarP(u, v, p, grafoP, dirigido);
                    insertarNP(u, v, grafoNP, dirigido);
                }

                cout << "\nGrafo ponderado almacenado:\n";
                for (int i = 0; i < n; i++) {
                    cout << i << " -> ";
                    for (auto& par : grafoP[i])
                        cout << "(" << par.first << ", peso=" << par.second << ") ";
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
                cout << i << " -> ";
                for (int v : grafoNP[i]) cout << v << " ";
                cout << "\n";
            }

            // ------------------ Matriz de adyacencia ----------------
            cout << "\nMATRIZ DE ADYACENCIA\n";
			vector<vector<int>> matA(n, vector<int>(n, 0));
			
			if (!ponderado) {
			    // --- No ponderado: solo marcamos 1 ---
			    for (int u = 0; u < n; u++)
			        for (int v : grafoNP[u])
			            matA[u][v] = 1;
			}
			else {
			    // --- Ponderado: usamos pesos reales ---
			    for (int u = 0; u < n; u++)
			        for (auto& par : grafoP[u]) {
			            int v = par.first;
			            int peso = par.second;
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
            vector<vector<int>> matI(n, vector<int>(edgeCount, 0));

            vector<vector<bool>> usado(n, vector<bool>(n, false));
            int id = 0;

            for (int u = 0; u < n; u++) {
                for (int v : grafoNP[u]) {

                    if (!dirigido) {
                        if (usado[u][v] || usado[v][u]) continue;
                        usado[u][v] = usado[v][u] = true;
                    }

                    if (id >= edgeCount) break;

                    matI[u][id] = -1;
                    matI[v][id] = 1;
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
            cout << "\n¿ES ARBOL?\n";
            cout << (esArbol(grafoNP, n, a) ? "SI\n" : "NO\n");

            // ------------------ Bipartito ---------------------------
            cout << "\n¿ES BIPARTITO?\n";
            cout << (esBipartito(grafoNP, n) ? "SI\n" : "NO\n");

            // ------------------ Fuertemente conexo ------------------
            if (dirigido) {
                cout << "\n¿ES FUERTEMENTE CONEXO?\n";
                cout << (fuertementeConexo(grafoNP, n) ? "SI\n" : "NO\n");
            }

            system("pause");
            break;
        }
        case 3: {
		    if (!ponderado) {
		        cout << "El grafo no es ponderado. Se requieren pesos para caminos mínimos.\n";
		        system("pause");
		        break;
		    }
		
		    int algoritmo;
		    system("cls");
		    cout << "CAMINOS MAS CORTOS\n";
		    cout << "1. Dijkstra (un solo origen)\n";
		    cout << "2. Floyd-Warshall (todos contra todos)\n";
		    cin >> algoritmo;
		
		    if (algoritmo == 1) {
		        int origen;
		        cout << "Nodo origen: ";
		        cin >> origen;
		
		        Dijkstra dij(n, grafoP);
		        vector<int> dist = dij.ejecutar(origen);
		
		        cout << "\nDISTANCIAS MINIMAS DESDE " << origen << "\n";
		        for (int i = 0; i < n; i++) {
		            if (dist[i] >= 1e9) cout << i << ": INF\n";
		            else cout << i << ": " << dist[i] << "\n";
		        }
		    }
		    else if (algoritmo == 2) {
		        FloydWarshall fw(n, grafoP);
		        fw.imprimir();
		    }
		
		    system("pause");
		    break;
		}


        } // switch

    } while (op != 0);

    return 0;
}








