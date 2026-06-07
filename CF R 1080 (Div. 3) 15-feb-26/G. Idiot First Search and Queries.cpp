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
#define int lli
#define vi vll

const int LOG = 20; // El máximo del logaritmo en base 2. Si es 20, asumes que los nodos no pueden tener un valor > 2^20
vector<vi> up; // binary lifting
vi parent; // Obtiene el padre de cada nodo
vi accValues; // Pesos de cada nodo, cuantas operaciones necesitas para llegar a 0
vi firstApp; // Si empiezo en el vértice 1, en que momento aparece por primera vez el nodo x
vi resultFromVertex1; // Resultados de las operaciones desde el vértice 1

int getAcc(vi& values, vi& acc, vector<vi>& arbol, int node = 0){
    acc[node] = values[node];
    for(auto x:arbol[node]){
        acc[node] += getAcc(values, acc, arbol, x);
    }
    return acc[node];
}

// construir padres
void build_parent(vector<vi>& arbol, int node, int p){
    parent[node] = p;
    for(auto x: arbol[node]){
        build_parent(arbol, x, node);
    }
}

// tabla binary lifting
// Guarda en cada nodo su ascentro 2^i posiciones más arriba, esto se hace con una complejidad de O(log n) por nodo, osea O(n log n)
void build_lift(int n){
    up.assign(n+1, vi(LOG, -1));
    for(int i = 0; i <= n; i++){
        up[i][0] = parent[i];
    }
    for(int j = 1; j < LOG; j++){
        for(int i = 0; i <= n; i++){
            if(up[i][j-1] != -1)
                up[i][j] = up[ up[i][j-1] ][j-1];
        }
    }
}
int getValues(vector<vi>& arbol, vi& values, int node = 0){
    values[node] = arbol[node].size()+1;
    for(auto x:arbol[node]){
        values[node] += getValues(arbol, values, x);
    }
    return values[node];
}

void initAcc(vector<vi>& arbol, vi& values, int node = 1, int padre = 0){
    accValues[node] = values[node] + accValues[padre];
    for(auto x:arbol[node]){
        initAcc(arbol, values, x, node);
    }
    return ;
}

void initFirstApp(vector<vi>& arbol, vi& values, int node = 1, int cost = 0){
    firstApp[node] = cost;
    for(auto x:arbol[node]){
        initFirstApp(arbol, values, x, 1 + cost);
        cost += values[x] + 1;
    }
    return ;
}

void initResults(vector<vi>& arbol, int node = 1){
    resultFromVertex1.PB(node);
    for(auto x:arbol[node]){
        initResults(arbol, x);
        resultFromVertex1.PB(node);
    }
    return ;
}

// Obtiene el peso del nodo
int getWeight(int v){
    return accValues[v];
}

// query
int query(int v, int x){
    int init = v;
    if(getWeight(init) - getWeight(parent[init]) > x) return v;
    for(int j = LOG-1; j >= 0; j--){
        int u = up[v][j];
        if(u != -1 && getWeight(init) - getWeight(u) <= x){
            v = u;
        }
    }
    return v;
}

int solve() {
    // Code aquí
    int n, q; cin >> n >> q;

    vector<vi> arbol(n+1); 
    arbol[0] = {1};

    int l, r;
    rep(i, n) {
        cin >> l >> r; 
        if (l != 0 || r != 0) {
            arbol[i+1] = {l, r};
        }
    }
    vi values(n+1, 0);
    getValues(arbol, values);
    DBG_COUT(cout << "Values: " << values << endl);
    accValues.assign(n+1, 0);
    initAcc(arbol, values);
    DBG_COUT(cout << "Accumulated values: " << accValues << endl);

    parent.assign(n+1, -1);
    build_parent(arbol, 0, -1);
    DBG_COUT(cout << "Parent: " << parent << endl);
    build_lift(n);
    DBG_COUT(cout << "Up lifting: " << up << endl);

    firstApp.assign(n+1, -1);
    initFirstApp(arbol, values);
    DBG_COUT(cout << "First appearance when root is 1: " << firstApp << endl);

    resultFromVertex1.clear();
    initResults(arbol);
    DBG_COUT(cout << "Results from vertex 1: " << resultFromVertex1 << endl);

    int v, k;
    while (q--){
        cin >> v >> k;
        DBG_COUT(cout << "Pair of " << v << " with value more than " << k << ":\n");
        int vEq = query(v, k);
        int kEq = k - (getWeight(v) - getWeight(vEq));
        DBG_COUT(cout << "Equivalent operation: " << vEq << " " << kEq << endl);
        int valueFrom1 = firstApp[vEq] + kEq;
        DBG_COUT(cout << "Operation from vertex 1: " << valueFrom1 << endl);
        int sol;
        if (valueFrom1 >= resultFromVertex1.size()) sol = 0;
        else if (valueFrom1 < 0) {cout << "WTH!!!" << endl; sol = 0;}
        else sol = resultFromVertex1[valueFrom1];
        DBG_COUT(cout << "Solución: ");
        cout << sol << " ";
        DBG_COUT(cout << endl);
    }
    DBG_COUT(cout << "===================================================");
    cout << endl;

    return 0;
}


signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    auto start = chrono::high_resolution_clock::now();
    int T;
    cin >> T; // Número de casos
    while (T--) {
        solve();
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2195/problem/G