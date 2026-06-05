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


struct Node {
    int id;
    int v;
    Node(int nId = -1, int Nv = 0){
        v = Nv;
    }
};
istream& operator>>(std::istream& input, Node& m) {
    input >> m.v;
    return input;
}

vll a; // Valor de cada nodo (número de nueces)
vector<vi> g; // Grafo, estructura del árbol con lista de adyascencia
vll sub; // Cuantas nueces hay en el subarbol dado por enraizar el árbol en 1 y seleccionar el subárbol de i
vi parent; // Cual es el padre de cada nodo si enraizamos el árbol en 1
vi dead; // Guarda los nodos que están muertos

lli total_nuts;

/*
Recorre todo el árbol con dfs, si un nodo tiene valor 0 y no tiene ramas con nodos vivos, este se considera muerto
*/
int dfs_dead(int u, int p) {
    int ramas = (a[u] > 0);

    for (int v : g[u]) {
        if (v == p) continue;
        ramas += dfs_dead(v, u);
    }

    if (a[u] == 0 && ramas <= 1) {
        dead[u] = 1;
    }

    return ramas > 0;
}

// Calcula los padres de cada nodo y la suma de cada subárbol si enraizamos el árbol en 1
void dfs_sum(int u, int p) {
    parent[u] = p;
    sub[u] = a[u];

    for (int v : g[u]) {
        if (v == p) continue;
        dfs_sum(v, u);
        sub[u] += sub[v];
    }
}

// Devuelve la suma de frutos en la componente que contiene a u 
// al quitar la arista (u, v).
lli component_sum(int u, int v) {
    if (parent[u] == v) { // Si v era el padre de u en el arbol enraizado en 1, sub[u] contiene el resultado
        return sub[u];
    } else { // En caso contrario, son todas las nueces menos las que están en el subarbol de v (sub[v])
        return total_nuts - sub[v];
    }
}

int solve() {
    int n;
    lli p, q;
    cin >> n >> p >> q;

    // Limpia las listas globales
    a.assign(n + 1, 0);
    g.assign(n + 1, vi());
    sub.assign(n + 1, 0);
    parent.assign(n + 1, 0);
    dead.assign(n + 1, 0);

    total_nuts = 0;

    int root = -1; // Sirve para calcular los nodos muertos, no tiene más uso en el problema, solo hace falta que sea un nodo con valor != 0
    int initial_alive = 0; // Los nodos que no empiezan con a[i] = 0

    // Guarda el número de nueves de cada nodo
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        total_nuts += a[i]; // Calcula cuantas nueves hay en total

        if (a[i] > 0) { // Si el nodo tiene elementos se almacena como vivo
            root = i;
            initial_alive++;
        }
    }

    // Estructura el árbol
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    // Si no hay nueces, el coste es 0
    if (total_nuts == 0) {
        cout << 0 << '\n';
        return 0;
    }

    // 1. Marcamos vértices muertos.
    dfs_dead(root, 0);

    // 2. Calculamos sumas de componentes. 
    // Podemos enraizar en cualquier nodo, por ejemplo 1.
    dfs_sum(1, 0);

    // 3. cost[u] = mínimo número de operaciones para dejar u vacío.
    vll cost;

    for (int u = 1; u <= n; u++) {
        if (dead[u]) { // Si el vertice ya está muerto, cuesta 0 dejarlo vacío
            cost.push_back(0);
            continue;
        }
        // Si no está muerto, buscamos la forma en la que antes se elimina
        lli best = LLONG_MAX;
        for (int v : g[u]) {
            // Por cada arista u, v, digamos que haces una operación en un nodo x que pasa por dicha arista,
            // ¿Cuánto tardas en matar el nodo u? La respuesta es las nueces del subarbol de u si enraizamos el árbol en v.
            best = min(best, component_sum(u, v));
        }
        // Almacena el mejor valor
        cost.push_back(best);
    }

    sort(cost.begin(), cost.end());

    // Solución por defecto, no hacer operaciones
    lli ans = 1LL * initial_alive * q;

    // Si dejamos vacíos x vértices, quedan n - x vértices que comer.
    // Necesitamos cost[x - 1] operaciones.
    for (int x = 1; x < n; x++) {
        lli operations = cost[x - 1];
        lli candidate = operations * p + 1LL * (n - x) * q;
        ans = min(ans, candidate);
    }

    cout << ans << '\n';

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

// https://codeforces.com/contest/2189/problem/F