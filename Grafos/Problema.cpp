#include <bits/stdc++.h>
using namespace std;

int n,m;

bool solve(vector<vector<char>> &mapa, int a, int b ){
	if(mapa[a][b] == 'X') return false;
	else if(mapa[a][b] == 't') return true;

	mapa[a][b] = 'X';

	if (a+1 < n and solve(mapa, a+1, b)) {
		return true;
	} else if (a-1 >= 0 and solve(mapa, a-1, b)) {
		return true;
	} else if (b+1 < m and solve(mapa, a, b+1)) {
		return true;
	} else if (b-1 >= 0 and solve(mapa, a, b-1)) {
		return true;
	} else {
		return false;
	}

}

int main(){
	cin>>n>>m;

	vector<vector<char>> mapa(n, vector<char>(m));

	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin>>mapa[i][j];

	int a,b; cin>>a>>b;

	if(solve(mapa, a-1, b-1)) cout << "yes" << '\n';
	else cout << "no" << '\n';

	return 0;
}