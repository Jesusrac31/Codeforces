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
double pi = 2*acos(0.0);

int solve() {
    // Code aquí
    int n, d12, d23, d13; cin >> n >> d12 >> d23 >> d13;

    // La rama principal debe ser la que tiene la distancia más pequeña

    int refNode; // Nodo 1 en esquema
    int endMainNode; // Nodo 2 en esquema
    int extraNode; // Nodo 3 en esquema
    int distPrincipal; // d12 en esquema
    int distEndingExtra; // d23 en esquema
    int distReferenciaExtra; // d13 en esquema

    if (d12 < d23){
        if (d12 < d13){
            refNode = 1;
            endMainNode = 2;
            extraNode = 3;
            distPrincipal = d12;
            distEndingExtra = d23;
            distReferenciaExtra = d13;
        } else {
            refNode = 1;
            endMainNode = 3;
            extraNode = 2;
            distPrincipal = d13;
            distEndingExtra = d23;
            distReferenciaExtra = d12;
        }
    } else {
        if (d23 < d13){
            refNode = 2;
            endMainNode = 3;
            extraNode = 1;
            distPrincipal = d23;
            distEndingExtra = d13;
            distReferenciaExtra = d12;
        } else {
            refNode = 1;
            endMainNode = 3;
            extraNode = 2;
            distPrincipal = d13;
            distEndingExtra = d23;
            distReferenciaExtra = d12;
        }
    }
    
    int p = (distReferenciaExtra+distEndingExtra-distPrincipal);
    DBG_COUT(cout << "P before dividing: " << p << endl);
    if (p&1){
        cout << "NO" << endl;
        return 0;
    }
    p/=2; // Longitud de la rama del 3 a partir de la rama entre 1 y 2
    DBG_COUT(cout << "Branch 3 size: " << p << endl);
    
    int i = distPrincipal+p+1-distEndingExtra; // Nodo del camino entre 1 y 2 que conecta el camino del 3

    DBG_COUT(cout << "Start of branch 3: " << i << endl);
    if (i<=0 || i>distPrincipal+1 || i+p+distPrincipal <= 0 || 1+p+distPrincipal > n){
        cout << "NO" << endl;
        return 0;
    }

    int node = 4; // Id del nodo extra siguiente a colocar
    vector<pii> aristas;
    // Construimos camino entre 1 y 2
    int prev = refNode;
    for (int i = 1; i<distPrincipal; i++){
        aristas.PB(pii(prev, node)); prev = node; node++;
    }
    aristas.PB(pii(prev, endMainNode));

    // Rama del nodo 3
    int codo; // Indice desde donde empieza la rama
    if (i == 1) codo = refNode;
    else if (i == distPrincipal+1) codo = endMainNode;
    else codo = i+2;

    prev = codo;
    for (int i = 1; i<p; i++){
        aristas.PB(pii(prev, node)); prev = node; node++;
    }
    aristas.PB(pii(prev, extraNode));

    // Añade los nodos faltantes
    while(node <= n){
        aristas.PB(pii(prev, node)) prev = node; node++;
    }

    cout << "YES" << endl;
    for (int i = 0; i<aristas.size(); i++){
        cout << aristas[i].first << " " << aristas[i].second << endl;
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

// https://codeforces.com/contest/1714/problem/F