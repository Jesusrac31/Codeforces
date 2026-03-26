#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
#endif

#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<long long> vll;
typedef long long lli;
typedef pair<int, int> pii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

const int MOD = 998244353; // Módulo del problema, cambiar en caso de no ser ese. NO TIENE PORQUÉ SER CONSTANTE, SOLO GLOBAL

struct Mint { // Es una estructura como el int pero que trabaja en mod MOD
    int v;
    Mint(long long val = 0) {
        v = int(val % MOD);
        if (v < 0) v += MOD;
    }
    Mint operator+(const Mint &o) const { return Mint(v + o.v); }
    Mint operator-(const Mint &o) const { return Mint(v - o.v); }
    Mint operator*(const Mint &o) const { return Mint(1LL * v * o.v); }
    Mint operator/(const Mint &o) const { return *this * o.inv(); }
    Mint& operator+=(const Mint &o) { v += o.v; if (v >= MOD) v -= MOD; return *this; }
    Mint& operator-=(const Mint &o) { v -= o.v; if (v < 0) v += MOD; return *this; }
    Mint& operator*=(const Mint &o) { v = int(1LL * v * o.v % MOD); return *this; }
    bool operator<(const Mint& o) const {return v < o.v;}
    bool operator>(const Mint& o) const {return v > o.v;}
    bool operator<=(const Mint& o) const {return v <= o.v;}
    bool operator>=(const Mint& o) const {return v >= o.v;}
    bool operator==(const Mint& o) const {return v == o.v;}
    bool operator!=(const Mint& o) const {return v != o.v;}
    Mint pow(long long p) const {
        if (p == -1){
            return inv();
        }
        Mint a = *this, res = 1;
        while (p > 0) {
            if (p & 1) res *= a;
            a *= a;
            p >>= 1;
        }
        return res;
    }
    Mint inv() const { return pow(MOD - 2); }
    friend ostream& operator<<(ostream& os, const Mint& m) {
        os << m.v;
        return os;
    }
};
istream& operator>>(std::istream& input, Mint& m) {
    input >> m.v;
    return input;
}

// Funciones vector
#define PB(a) push_back(a);

bool sort_func(int a, int b) {
    if (a < b) {
        return true;
    } else {
        return false;
    }
}
#define ord(vect) sort(vect.begin(), vect.end(), sort_func)
#define rep(x,n) for(int x = 0; x < n; ++x)
#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
#define B begin();
#define E end();
#define copia(v1, v2)                                                                                                                    \
    ;                                                                                                                                                        \
    copy(v1.begin(), v1.end(), back_inserter(v2));

// Funciones pair
#define F first
#define S second

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }


template<typename T> std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& vec) {
    os << "{ ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto elem : vec) {
        os << elem << " ";
    }
    os << "}\n";
    return os;
}

// Imprime cualquier vector 
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}



void Imprime_set(set<int> s) {
    copy(s.begin(), s.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int maximo_comun_divisor(int a, int b) {
    int temporal; // Para no perder b
    while (b != 0) {
        temporal = b;
        b = a % b;
        a = temporal;
    }
    return a;
}

int minimo_comun_multiplo(int a, int b) {
    return (a * b) / maximo_comun_divisor(a, b);
}

bool isNumeric(string const &str) {
    auto it = str.begin();
    while (it != str.end() && isdigit(*it)) {
        it++;
    }
    return !str.empty() && it == str.end();
}

void lee(int n, vi& vect) {
  rep(i, n) cin >> vect[i];
  return ;
}

#define INF INT_MAX

void dfs(int node, unordered_set<int>& tree, vector<vi>& graph, vector<bool>& bloqueados, vi& treePerNode, int k){
    bloqueados[node] = true;
    tree.insert(node);
    treePerNode[node] = k;
    for (auto v:graph[node]){
        if (!bloqueados[v]){
            dfs(v, tree, graph, bloqueados, treePerNode, k);
        }
    }
}

int connectedComponents(vector<vi>& forest, vector<unordered_set<int>>& trees, int n, vi& treePerNode){
    int k = 0;
    vector<bool> bloqueados(n+1, false);
    for (int i = 1; i<=n; i++){
        if (!bloqueados[i]){
            trees.PB({});
            dfs(i, trees[k], forest, bloqueados, treePerNode, k);
            k++;
        }
    }
    return k;
}

bool searchPath(int init, int ending, vector<vi>& graph, vi& path, int parent = 0){
    if (init == ending){
        path.PB(init);
        return true;
    }
    bool sol = false;

    for (auto v:graph[init]){
        if (v != parent){
            sol = searchPath(v, ending, graph, path, init);
            if (sol){
                path.PB(init);
                break;
            }
        }
    }

    return sol;
}

Mint getSizeBranch (int padre, int nodo, vector<vi>& graph){
    Mint sol = 1;
    for (auto v:graph[nodo]){
        if (v != padre){
            sol += getSizeBranch(nodo, v, graph);
        }
    }
    return sol;
}

int solve() {
    // Code aquí
    int n, m;
    cin >> n >> m;
    vector<vi> forest(n+1);
    int u, v;
    for (int i = 0; i<m; i++){
        cin >> u >> v;
        forest[u].PB(v);
        forest[v].PB(u);
    }

    vector<unordered_set<int>> trees; // Conjuntos de componentes conexos
    vi treePerNode(n+1, -1); // A que arbol pertenece cada nodo
    int k = connectedComponents(forest, trees, n, treePerNode);
    vector<Mint> sol(n+1, 0);
    Mint nM = n;
    if (treePerNode[n] == treePerNode[n-1]){ // Caso fácil, todas las posibilidades se las lleva el mismo nodo
        vi path;
        searchPath(n, n-1, forest, path);
        int node = path[path.size()-2];
        sol[node] = 1;
        for (int i = 0; i<k; i++){
            sol[node] = sol[node]*trees[i].size();
        }
        sol[node] = sol[node] * nM.pow(k-2);
    } else { // Caso difícil, el nodo n-1 está en otro árbol, combinaciones
        // Vamos a buscar que porcentaje de los casos desembocan en v=x, siendo x el nodo que buscamos
        // Si v pertenece al mismo arbol que n pero no es adyascente, su porcentaje es 0
        // Si v pertenece al mismo arbol que n y es adyascente, su porcentaje es (b/c) siendo b el numero de nodos en su rama asumiendo q n es la raiz y c el numero de nodos del arbol donde está n
        // Si v pertenece a otro arbol, su porcentaje es (b1/(c+b1)) siendo b1 el tamaño del arbol donde se encuentra nuestro nodo, ten en cuenta que has modificado el arbol, por lo que el total es distinto
        // Se te queda en las posibilidades total/(n*c)
        // Si v pertenece al mismo arbol que n-1, sus posibilidades es total
        // Entonces lo primero que tenemos que hacer es calcular el total y aplicar luego el porcentaje
        Mint mult = 1;
        for (auto s:trees){
            mult *= Mint(s.size());
        }
        Mint total = mult*(nM.pow(k-2));
        Mint inverseNTree = Mint(trees[treePerNode[n]].size()).inv();
        Mint invN = nM.inv();
        Mint solCase;
        for (int i = 0; i<k; i++){ // Por cada arbol
            if (treePerNode[n] == i){ // mismo arbol
                for (auto v:forest[n]){
                    if (v != n) sol[v] = getSizeBranch(n, v, forest)*total*inverseNTree;
                }
                continue; // Siguiente arbol
            } else if (treePerNode[n-1] == i){
                solCase = total*(trees[treePerNode[n]].size()+trees[i].size())*invN*inverseNTree*(Mint(trees[i].size()).inv());
                for (auto v:trees[i]) {
                    sol[v] = solCase;
                }
                continue;
            }
            // En caso de que sea un arbol distinto
            solCase = total*invN*inverseNTree;
            for (auto v:trees[i]) sol[v] = solCase;
        }
    }

    for (int i = 1; i<n; i++) cout << sol[i] << " ";
    cout << endl;

    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int T;
    cin >> T; // Número de casos
    while (T--) {
        solve();
    }
    return 0;
}

// https://codeforces.com/contest/2190/problem/D