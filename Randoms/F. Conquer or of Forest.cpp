#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#include<unordered_set>
#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
#endif

using namespace std;

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
    bool operator==(const Mint& o) const {return v == o.v;}
    bool operator!=(const Mint& o) const {return v != o.v;}
    Mint pow(long long p) const {
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
template<typename T> std::ostream& operator<<(std::ostream& os, const Mint& m) {
    os << m.v << " ";
    return os;
}

typedef vector<Mint> vi;

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
#define F first;
#define S second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

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
double pi = 2*acos(0.0);

int getSubTreesSizes(vector<vector<int>>& graph, int node, vi& sol, int parent = 0){
    int counting = 0;
    for (auto v:graph[node]){
        if (v != parent){
            counting += getSubTreesSizes(graph, v, sol, node);
        }
    }
    if (counting & 1 || node == 1){ // Si tiene un número impar de hijos, es un nodo blanco
        sol.PB(counting+1);
        counting = 0;
    } else {
        counting++;
    }
    return counting;
}

Mint factorial(Mint x){
    Mint sol = 1;
    for (Mint i = 1; i<x+1; i+=1) sol*=i;
    return sol;
}

// Se salta el último elemento (Tamaño del arbol raíz)
Mint multiplicaVectorCuadrado(vi& v){
    Mint sol = 1;
    for (int i = 0; i<v.size()-1; i++) sol *= v[i]*v[i];
    return sol;
}

// Se salta el último elemento (Tamaño del arbol raíz)
Mint sumaVectorInversas(vi& v){
    Mint sol = 0;
    for (int i = 0; i<v.size()-1; i++) sol += v[i].inv();
    return sol;
}

int solve() {
    // Code aquí
    int n;
    cin >> n;
    vector<vector<int>> tree(n+1);
    int u, v;
    for (int i = 0; i<n-1; i++){
        cin >> u >> v;
        tree[u].PB(v);
        tree[v].PB(u);
    }
    vi subTreesSizes;
    getSubTreesSizes(tree, 1, subTreesSizes); // Tamaño de los árboles
    if (subTreesSizes.back() == 0) subTreesSizes.pop_back();

    Mint k = subTreesSizes.size(); // Número de árboles
    if (k == 1) {cout << 1 << endl; return 0;}
    
    cout << factorial(k-2) * subTreesSizes.back() * multiplicaVectorCuadrado(subTreesSizes) * sumaVectorInversas(subTreesSizes) << endl;
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

// https://codeforces.com/contest/2178