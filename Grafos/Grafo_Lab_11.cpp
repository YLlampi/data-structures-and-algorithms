#include <bits/stdc++.h>
using namespace std;

class GraphLista{
private:
	int numNodos; // Numero de Nodos
	vector<vector<int>> lista; // Grafo - Listas de Adyacencia
	vector<bool> v;
	vector<bool> visited;
	bool vis[10000]={false};

public:
	GraphLista(int numNodos){
		this->numNodos = numNodos;
		this->lista.resize(numNodos + 1);
	}

	void insertarNodo(int nodo){
		if(nodo > lista.size()){
			this->numNodos++;
			lista.resize(numNodos);
		}
	}

	void insertarArista(int nodoA, int nodoB){
		lista[nodoA].push_back(nodoB);
		// lista[nodoB].push_back(nodoA);
	}

	void borrarNodo(int nodo){
		if(nodo < lista.size()){
			vector<int>::iterator it;
			for(size_t i = 0; i < numNodos; i++){
				borrarArista(i, nodo);
			}
			lista.erase(lista.begin()+nodo);
			this->numNodos--;	
		}
		
	}

	void borrarArista(int nodoA, int nodoB){
		vector<int>::iterator it;
		it = find(lista[nodoA].begin(), lista[nodoA].end(), nodoB);
		
		if(it != lista[nodoA].end()) lista[nodoA].erase(it);
	}

	bool esVacio() const {
		if(lista.size() == 0) return true;
		else return false;
	}

	bool existeNodo(int nodo) const {
		if(nodo < lista.size()) return true;
		else return false;
	}

	bool sonAdyacentes(int nodoA, int nodoB) const {
		for(int i = 0; i < lista[nodoA].size(); i++){
			if(lista[nodoA][i] == nodoB) return true;
		}
		return false;
	}

	void verAdyacencias() const {
		for(int i = 0; i < lista.size(); i++){
			cout << "vertice " << i << " -> ";
			for(int j = 0; j < lista[i].size(); j++){
				cout << lista[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	void dfs(int i){
        if(vis[i]==false){
            vis[i]=true;
            cout << i << " - ";
            for(int it:lista[i]){
                if(vis[it]==false){
                    dfs(it);
                }
            }
        }
    }

	void bfs(int u){
	    queue<int> q;
        vector<int> visited(numNodos);
        q.push(u);
        visited[u]=1;
        while(not q.empty()){
            int temp=q.front();
            cout << temp << " - ";
            q.pop();
            for(int i=0;i<lista[temp].size();i++){
                if(visited[lista[temp][i]]==0){
                    visited[lista[temp][i]]=1;
                    q.push(lista[temp][i]);
                }
            }
        }
	}

	void graficar(){
	    FILE * file;
	    file = fopen("grafo.dot","w+");
	    fprintf(file,"digraph G {\n");
	    getDot(file);
	    fprintf(file,"}");
	    fclose(file);
	    system("dot grafo.dot -o grafica.jpg -Tjpg -Grankdir=TB && xdg-open grafica.jpg");
	}

	void getDot(FILE * file){

		for(int i = 0; i < lista.size(); i++){
			fprintf(file,"x%d[label=\"%i\"];\n",i,i);
			for(int j = 0; j < lista[i].size(); j++){
				fprintf(file,"x%d->x%d[arrowhead = normal];\n",i,lista[i][j]);
			}
		}
	}

};


int main(){

	// n: numero de vertices
	// m: numero de aristas
	int n,m;
	cin>>n>>m;
	GraphLista grafo(n-1);

	// arista de a -> b
	int a,b;
	while(m--){
		cin>>a>>b;
		grafo.insertarArista(a,b);
	}

	cout << "Grafo Original" << '\n';
	grafo.verAdyacencias();

	cout << '\n';
    
    /*
	cout << "Insertar Arista 3-4" << '\n';
	grafo.insertarArista(3,4);
	grafo.verAdyacencias();

	cout << '\n';

	// cout << "Eliminar nodo 3" << '\n';
	// grafo.borrarNodo(3);
	// grafo.verAdyacencias();

	cout << "Borrar Arista 3-4" << '\n';
	grafo.borrarArista(3,4);
	grafo.verAdyacencias();

	cout << '\n';

	cout << "Es vacio? " << grafo.esVacio() << '\n';
	cout << "Existe nodo 3? " << grafo.existeNodo(3) << '\n';
	cout << "Son Adyacentes? 1-3? " << grafo.sonAdyacentes(1,3) << '\n';

	cout << '\n';
    */
    
	cout << "BFS:" << '\n';
	grafo.bfs(0);
	
	cout << '\n';
	
	cout << "DFS:" << '\n';
	grafo.dfs(0);

	grafo.graficar();

	return 0;
}
