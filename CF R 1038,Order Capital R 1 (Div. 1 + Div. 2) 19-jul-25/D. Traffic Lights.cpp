#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
#endif

using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
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

// Funciones map
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

int dijkstra(vector<vi>& grafo, int n, int nodo, int fin){
    
    int sol = INF;
    vector<bool> bloqueados(n, false);
    priority_queue<pair<int, int>, vector<pair<lli, lli>>, greater<pair<lli, lli>>> q;
    q.push({0, nodo}); // tiempo total, nodo
    
    while(q.size()){
        int t = q.top().first, v = q.top().second;
        if (v == fin){
            sol = t;
            break;
        }
        if (!bloqueados[v]){
            bloqueados[v] = true;
            for (int i = 0; i<grafo[v].size(); i++){
                if (!bloqueados[grafo[v][i]]){
                    int tamano = grafo[v].size();
                    q.push({t+((i-(t%tamano)+tamano)%tamano)+1, grafo[v][i]});
                }
            }
        }
        q.pop();
    }
    return sol;
}

int solve() {
    // Code aquí
    int n, m;
    cin >> n >> m;
    vector<vi> grafo(n+1);
    int u, v;
    for (int i = 0; i<m; i++){
        cin >> u >> v;
        grafo[u].emplace_back(v);
        grafo[v].emplace_back(u);
    }
    int tMax = dijkstra(grafo, n+1, 1, n);
    vector<vi> dp(n+1, vi(tMax+1, tMax+1));
    dp[1][0] = 0;

    for (int j = 0; j<tMax; j++){
        for (int i = 1; i<=n; i++){
            dp[i][j+1] = min(dp[i][j]+1, dp[i][j+1]);
            dp[grafo[i][j%grafo[i].size()]][j+1] = min(dp[i][j], dp[grafo[i][j%grafo[i].size()]][j+1]);
        }
    }

    cout << tMax << " " << dp[n][tMax] << endl;
    
    return 0;
}

int main() {
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
