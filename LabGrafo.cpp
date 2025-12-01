#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <windows.h>
#include <algorithm>
#include <tuple>


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
    vector<vector<pair<int,int>>> &g;
    vector<int> dist;
    vector<int> parent;

    Dijkstra(int n, vector<vector<pair<int,int>>> &g) : n(n), g(g) {
        dist.assign(n, 1e9);
        parent.assign(n, -1);
    }

    void ejecutar(int origen) {
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

        if (dist[destino] == 1e9) 
            return camino; // vacio, no hay camino

        for (int v = destino; v != -1; v = parent[v])
            camino.push_back(v);

        reverse(camino.begin(), camino.end());
        return camino;
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
//      DSU "Reconstruccion del arbol"
// ======================================================


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
        if (a == b) return false;

        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
        return true;
    }
};

// =======================================================
//      Algoritmo Kruskal
// ======================================================

class Kruskal {
public:
    int n;
    vector<tuple<int,int,int>> edges;

    Kruskal(int n) : n(n) {}

    void agregarArista(int u, int v, int w) {
        edges.emplace_back(w, u - 1, v - 1); // FIX: ajustar índice
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

// =======================================================
//      Matching Maximal
// ======================================================

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


// =======================================================
//      Matching Grafo General
// ======================================================

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
        cout << "4. Arbol de expansion\n";
        cout << "5. Matching\n";
        cout << "6. Matching avanzado\n";
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
		    cout << "1. Dijkstra (un solo origen, con reconstrucción)\n";
		    cout << "2. Floyd-Warshall (todos contra todos)\n";
		    cin >> algoritmo;
		
		    // =============================
		    //            DIJKSTRA
		    // =============================
		    if (algoritmo == 1) {
		        int origen, destino;
		        cout << "Nodo origen: ";
		        cin >> origen;
		
		        Dijkstra dij(n, grafoP);
		        dij.ejecutar(origen);
		
		        cout << "Nodo destino: ";
		        cin >> destino;
		
		        cout << "\nDistancia mínima de " << origen << " a " << destino << ": ";
		
		        if (dij.dist[destino] == 1e9) {
		            cout << "No existe camino.\n";
		        } else {
		            cout << dij.dist[destino] << "\n\n";
		
		            vector<int> camino = dij.reconstruirCamino(destino);
		
		            cout << "Camino: ";
		            for (int v : camino) cout << v << " ";
		            cout << "\n";
		        }
		    }
		
		    // =============================
		    //      FLOYD-WARSHALL
		    // =============================
		    else if (algoritmo == 2) {
		        FloydWarshall fw(n, grafoP);
		        fw.imprimir();
		    }
		
		    system("pause");
		    break;
		}
		case 4: {
		    if (grafoP.empty()) {
		        cout << "Primero cargue un grafo ponderado.\n";
		        break;
		    }
		
		    Kruskal k(n);
		
		    // Convertir grafo ponderado (lista de adyacencia) en lista de aristas
		    for (int u = 0; u < n; u++) {
		        for (auto &par : grafoP[u]) {
		            int v = par.first;
		            int w = par.second;
		            if (u < v) { 
		                k.agregarArista(u + 1, v + 1, w); // enviar en 1-based
		            }
		        }
		    }
		
		    cout << "\n--- ARBOL DE EXPANSION MINIMO (KRUSKAL) ---\n";
		    auto [costoMin, arbolMin] = k.mst_min();
		
		    cout << "Costo total = " << costoMin << "\n";
		    cout << "Aristas del árbol:\n";
		    for (auto &[w, u, v] : arbolMin) {
		        cout << "(" << u + 1 << ", " << v + 1 << ") peso = " << w << "\n";
		    }
		    system("pause");
		
		    cout << "\n--- ARBOL DE EXPANSION MAXIMO (KRUSKAL) ---\n";
		    auto [costoMax, arbolMax] = k.mst_max();
		
		    cout << "Costo total = " << costoMax << "\n";
		    cout << "Aristas del árbol:\n";
		    for (auto &[w, u, v] : arbolMax) {
		        cout << "(" << u + 1 << ", " << v + 1 << ") peso = " << w << "\n";
		    }
		    system("pause");
		
		    break;
		}
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



        } // switch

    } while (op != 0);

    return 0;
}








