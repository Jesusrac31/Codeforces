#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#define DBG_COUT(stmt) do { stmt; } while (0)
#else
#define DBG_COUT(stmt) do {} while (0)
#endif

using namespace std;
typedef long long ll;
int n;
ll a[300005], f[300005][24], smn[30];

vector<int> g[300005]; // Arbol

#define INF 8e18

// Recorre los nodos siguiendo dfs. Recibe el hijo y el padre
void dfs(int x, int fa) {
	for (int i = 1; i <= 22; i++) f[x][i] = i * a[x]; // Si desactivamos el nodo en el turno i, pierdes i*a[x]
	for (int y : g[x]) { // Por cada hijo
		if (y == fa) continue; // si el hijo es el padre, no hacemos nada (ya fue compilado y evita bucles infinitos en dfs)
		dfs(y, x); // Por cada hijo, repite el proceso
		ll tt = INF;
		smn[23] = INF;
        // Por cada ronda, obtienes cual es el peso que te da el hijo si dijeras que este se elimina en dicha ronda
		for (int i = 22; i >= 1; i--) {
			smn[i] = min(smn[i + 1], f[y][i]);
		}
        // Si elimino mi nodo en ronda 1, su hijo puede eliminarse en cualquier ronda menos en la 1
        // tt almacena cual es el valor mínimo de smn de las rondas ya computadas
        // smn[i+1] almacena cual es el valor mínimo si ejecutamos el hijo en una ronda más avanazada
		for (int i = 1; i <= 22; i++) {
			f[x][i] += min(tt, smn[i + 1]);
			tt = min(tt, f[y][i]);
		}
	}
}
void Solve() {
    // Input
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1, x, y; i < n; i++) {
		cin >> x >> y;
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j<25; j++){
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
	cout << *min_element(f[1] + 1, f[1] + 23) << '\n';

    // Reset para el siguiente test
	for (int i = 1; i <= n; i++) {
		g[i].clear();
		memset(f[i], 0, sizeof(f[i]));
	}
}
int main() {
	ios::sync_with_stdio(0), cin.tie(0);
	int t;
	cin >> t;
	while (t--) Solve();
}