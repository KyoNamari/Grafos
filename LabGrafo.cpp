#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>

using namespace std;

void insertar(int o, int d, vector<vector<int>>& g){
	g[o].push_back(d);
	g[d].push_back(o);
}

void BFS(){
	
}

void DFS(){
	
}

int main(){
	int n, a, ori, des;
	vector<vector<int>> grafo;
	
	cout << "Ingrese la cantidad de nodos: ";
	cin >> n;
	cout << "\nIngrese la cantidad de aristas: ";
	cin >> a;
	grafo.resize(n);
	
	for (int i=0; i < a; i++){
		cout << "\nIngresa las conecciones (origen - destino)";
		cin >> ori >> des;
		insertar(ori,des,grafo);
	}
	
	cout << "\nEl grafo almacenado es el siguiente: ";
	for (int i=0; i < a; i++){
		cout << i << " = [ ";
		for (auto x : grafo[i]){
			cout << x << " ";
		}
		cout << "]\n";
	}
	
	
	
	
}
