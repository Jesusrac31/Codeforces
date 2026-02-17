#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#include<unordered_set>
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

void get_depth(vector<vi>& tree, vector<vi>& depth, vi& padre, int node = 1, int p = 0){
    if (depth.size()<=p){
        depth.PB({});
    }
    depth[p].PB(node);
    for (auto v:tree[node]){
        if (padre[node] != v){
            padre[v] = node;
            get_depth(tree, depth, padre, v, p+1);
        }
    }
}

int solve() {
    // Code aquí
    int n;
    cin >> n;
    vector<vi> tree(n+1);
    int u, v;
    for (int i = 0; i<n-1; i++){
        cin >> u >> v;
        tree[u].PB(v);
        tree[v].PB(u);
    }
    vector<vi> depth; 
    vi padre(n+1, 0);
    get_depth(tree, depth, padre);

    int colors = 0;
    vi color_node (n+1, 0);

    for (int i = 0; i<depth.size(); i++){
        int colored = 1;
        int reservaColors = 0;
        bool singleParent = true;
        int parent = padre[depth[i][0]];
        for (int j = 0; j<depth[i].size(); j++){
            if (parent != padre[depth[i][j]]){
                singleParent = false;
            }
            if (reservaColors && color_node[padre[depth[i][j]]] != reservaColors){
                color_node[depth[i][j]] = reservaColors;
                reservaColors = 0;
            } else {
                if (colored == color_node[padre[depth[i][j]]]){
                    reservaColors = colored;
                    colored++;
                }
                color_node[depth[i][j]] = colored;
                colored++;
            }
        }
        if (i>0 && reservaColors && !singleParent){
            color_node[depth[i].back()] = color_node[depth[i][0]];
            color_node[depth[i][0]] = reservaColors;
            colored--;
        }
        colors = max(colors, colored-1);
    }
    // Easy version
    cout << colors << endl;

    //Hard version
    vector<vi> removals(colors+1);
    for (int i = 1; i<color_node.size(); i++){
        removals[color_node[i]].PB(i);
    }
    for (int i = 1; i<removals.size(); i++){
        cout << removals[i].size() << " ";
        for (auto v:removals[i]){
            cout << v << " ";
        }
        cout << endl;
    }

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

// https://codeforces.com/contest/2183/problem/D1
// https://codeforces.com/contest/2183/problem/D2