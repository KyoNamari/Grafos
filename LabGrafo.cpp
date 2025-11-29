#include <iostream>
#include <vector>
#include <windows.h>
#include <queue>
#include <stack>

using namespace std;

// ------------------- INSERTAR PARA NO PONDERADO -------------------
void insertar(int o, int d, vector<vector<int>>& g, bool dirigido) {
    g[o].push_back(d);
    if (!dirigido)
        g[d].push_back(o);
}

// ------------------- INSERTAR PARA PONDERADO ----------------------
void insertarGP(int o, int d, int p, vector<vector<pair<int,int>>>& g, bool dirigido) {
    g[o].push_back({d, p});
    if (!dirigido)
        g[d].push_back({o, p});
}

// ------------------- BFS NO PONDERADO -----------------------------
void bfs(int start, vector<bool>& v, vector<vector<int>>& g) {
    queue<int> q;
    q.push(start);
    v[start] = true;

    cout << "Componente: ";
    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";

        for (int i : g[u]) {
            if (!v[i]) {
                v[i] = true;
                q.push(i);
            }
        }
    }
    cout << "\n";
}

// ------------------- DFS NO PONDERADO -----------------------------
void dfs(int start, vector<bool>& v, vector<vector<int>>& g) {
    stack<int> st;
    st.push(start);
    v[start] = true;

    cout << "Componente: ";
    while (!st.empty()) {
        int u = st.top(); st.pop();
        cout << u << " ";

        for (int i : g[u]) {
            if (!v[i]) {
                v[i] = true;
                st.push(i);
            }
        }
    }
    cout << "\n";
}

// ======================= MAIN PROGRAM =============================
int main() {

    int op, n, a, ori, des, peso;
    bool dirigido, ponderado;

    do {
        system("cls");
        cout << "_________________________________________________\n";
        cout << "      L A B O R A T O R Y  O F  G R A F O S      \n";
        cout << "_________________________________________________\n";

        cout << "1. Almacenar Grafo\n";
        cout << "2. Caracteristicas\n";
        cout << "3. Camino mas corto\n";
        cout << "4. Expansion\n";
        cout << "5. Matching\n";
        cout << "0. Salir\n";
        cin >> op;

        // --------------------- ALMACENAR GRAFO ---------------------
        if (op == 1) {
            system("cls");

            // Selección dirigido / no dirigido
            cout << "Seleccione el tipo:\n";
            cout << "1. Grafo dirigido\n";
            cout << "2. Grafo no dirigido\n";
            cin >> op;
            dirigido = (op == 1);

            // Selección ponderado / no ponderado
            cout << "\nSeleccione si es ponderado:\n";
            cout << "1. Ponderado\n";
            cout << "2. No Ponderado\n";
            cin >> op;
            ponderado = (op == 1);

            cout << "\nIngrese la cantidad de nodos: ";
            cin >> n;

            cout << "Ingrese la cantidad de aristas: ";
            cin >> a;

            if (!ponderado) {
                // ----------- GRAFO NO PONDERADO ----------------
                vector<vector<int>> grafo(n);
                vector<bool> visited(n, false);

                for (int i = 0; i < a; i++) {
                    cout << "Origen Destino: ";
                    cin >> ori >> des;
                    insertar(ori, des, grafo, dirigido);
                }

                cout << "\nGrafo almacenado:\n";
                for (int i = 0; i < n; i++) {
                    cout << i << " -> ";
                    for (auto x : grafo[i])
                        cout << x << " ";
                    cout << "\n";
                }

                cout << "\nComponentes BFS:\n";
                fill(visited.begin(), visited.end(), false);
                for (int i = 0; i < n; i++)
                    if (!visited[i]) bfs(i, visited, grafo);

                cout << "\nComponentes DFS:\n";
                fill(visited.begin(), visited.end(), false);
                for (int i = 0; i < n; i++)
                    if (!visited[i]) dfs(i, visited, grafo);
            }
            else {
                // ----------- GRAFO PONDERADO -------------------
                vector<vector<pair<int,int>>> grafo(n);

                for (int i = 0; i < a; i++) {
                    cout << "Origen Destino Peso: ";
                    cin >> ori >> des >> peso;
                    insertarGP(ori, des, peso, grafo, dirigido);
                }

                cout << "\nGrafo ponderado almacenado:\n";
                for (int i = 0; i < n; i++) {
                    cout << i << " -> ";
                    for (auto &x : grafo[i])
                        cout << "(" << x.first << ", peso=" << x.second << ") ";
                    cout << "\n";
                }

                cout << "\n(BFS y DFS no aplican directamente a ponderados)\n";
            }

            system("pause");
        }

    } while (op != 0);

    return 0;
}


