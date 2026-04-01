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
    os << " ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "\n";
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
#define int lli
#define vi vll

void printEquivalent(vector<vi>& matrix){
    for (int i = 0; i<matrix.size(); i++){
        for (int j = 0; j<matrix.size(); j++){
            if (matrix[i][j] < matrix[j][i]) cout << 0 << " ";
            else cout << 1 << " ";
        }
        cout << "\n";
    }
}

struct DSU {
    vector<int> parent;
    int numSets;
    explicit DSU(int n) : parent(n, -1), numSets(n) {}
    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }
    int size(int x) {
        return -parent[find(x)];
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (parent[a] > parent[b]) swap(a, b);
        parent[a] += parent[b];
        parent[b] = a;
        numSets--;
    }
    bool related(int a, int b) {
        return find(a) == find(b);
    }
};

int solve() {
    // Code aquí
    int n; cin >> n;
    vector<vi> A(n, vi(n));
    rep(i, n) rep(j, n) cin >> A[i][j];
    DBG_COUT(cout << "Test: " << endl; printEquivalent(A));
    
    // El DSU tiene dos nodos por operación. El nodo i dice que SI se ejecuta. El nodo i+n dice que NO se ejecuta
    // El nodo i y el nodo i+n no pueden estar en mismos grupos
    // Si queremos que tanto la operación i como la operación j se ejecuten o no (hagan lo mismo), debemos meterlas en el mismo set
    // Esto aplica tambien a los nodos i+n y j+n
    // En caso contrario meteriamos i+n con j y j+n con i
    DSU dsu(2 * n); 
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            
            if (A[i][j] < A[j][i]) { // Busco cambiar
                // Debemos tener en cuenta siempre que si j+n está con i, no puedo unir con j y viceversa
                if (dsu.find(i) != dsu.find(j + n)) { // Si i y j+n no pertenecen al mismo set
                    dsu.unite(i, j);             // 0 con 0
                    dsu.unite(i + n, j + n);     // 1 con 1
                }
            } 
            else if (A[i][j] > A[j][i]) { // Busco no cambiar
                // Debemos tener en cuenta siempre que si j+n está con i, no puedo unir con j y viceversa
                if (dsu.find(i) != dsu.find(j)) { // Si i y j no pertenecen al mismo set
                    dsu.unite(i, j + n);         // 0 con 1
                    dsu.unite(i + n, j);         // 1 con 0
                }
            }
            // Si A[i][j] == A[j][i], nos da igual, no añadimos ninguna regla al DSU.
        }
    }


    // Reconstrucción final de la matriz
    // Si i y j quedaron obligados a ser diferentes, sabemos que se intercambiarán
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dsu.find(i) == dsu.find(j + n)) {
                swap(A[i][j], A[j][i]);
            }
        }
    }

    // Imprimir el resultado
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << A[i][j] << " ";
        }
        cout << "\n";
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

// https://codeforces.com/contest/1713/problem/E