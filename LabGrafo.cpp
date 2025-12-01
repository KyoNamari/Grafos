#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <windows.h>
#include <algorithm>
#include <tuple>

using namespace std;

// --------------------------- UTIL --------------------------------
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;
const int INF_INT = 1e9;

// --------------------------- HELPERS ------------------------------
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

// =======================================================
//       INSERTAR ARISTAS
// =======================================================

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

// =======================================================
//       BFS para componentes y conectividad
// =======================================================

void bfs_component(int start, vector<bool>& visited, vector<vector<int>>& g) {
    if (!inRange(start, (int)g.size())) return;
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

// =======================================================
//       DFS (para componentes y conectividad)
// =======================================================

void dfs_rec(int u, vector<bool>& visited, vector<vector<int>>& g) {
    if (!inRange(u, (int)g.size())) return;
    visited[u] = true;
    for (int v : g[u])
        if (inRange(v, (int)g.size()) && !visited[v])
            dfs_rec(v, visited, g);
}

// =======================================================
//       VERIFICAR SI ES BIPARTITO
// =======================================================

bool esBipartito(vector<vector<int>>& g, int n) {
    if (n == 0) return true;
    vector<int> color(n, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] != -1) continue;

        queue<int> q;
        q.push(i);
        color[i] = 0;

        while (!q.empty()) {
            int u = q.front(); q.pop();

            for (int v : g[u]) {
                if (!inRange(v, n)) continue;
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
    if (n == 0) return true;
    vector<bool> visited(n, false);

    // proteger llamada si 0 no existe
    if (!inRange(0, n)) return false;
    dfs_rec(0, visited, g);
    for (bool x : visited) if (!x) return false;

    vector<vector<int>> trans(n);
    for (int u = 0; u < n; u++)
        for (int v : g[u])
            if (inRange(v,n)) trans[v].push_back(u);

    fill(visited.begin(), visited.end(), false);

    dfs_rec(0, visited, trans);
    for (bool x : visited) if (!x) return false;

    return true;
}

// =======================================================
//       VERIFICAR SI ES ÁRBOL
// =======================================================

bool esArbol(vector<vector<int>>& g, int n, int aristas) {
    if (n == 0) return false;
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
        if (!inRange(origen, n)) return;
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
                if (!inRange(v, n)) continue;

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
        if (!inRange(destino, n)) return camino;

        if (dist[destino] == (int)1e9)
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
                if (!inRange(v, n)) continue;
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

// =======================================================
//      DSU "Reconstruccion del arbol"
// =======================================================

class DSU {
public:
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (!inRange(x, (int)parent.size())) return -1;
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

// =======================================================
//      Matching Maximal
// =======================================================

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
            if (!inRange(v, n)) continue;
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
//      Matching Grafo General (greedy maximal)
// =======================================================

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
                    if (!inRange(v, n)) continue;
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
//      Algoritmo Blossom - Edmons
// =======================================================

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
                if (!inRange(u,n)) continue;
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

// =======================================================
//      Algoritmo Hopcroft Karp
// =======================================================

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









