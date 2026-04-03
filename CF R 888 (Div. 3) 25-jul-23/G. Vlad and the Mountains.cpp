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

bool sort_func(const array<int,4>& a, const array<int,4>& b) {
    if (a[2] < b[2]) {
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
    os << "]\n";
    return os;
}
template<typename T, typename Q> std::ostream& operator<<(std::ostream& os, const std::pair<T, Q>& vec) {
    os << "( " << vec.first << ", " << vec.second << " )";
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

// Formato de la lista como {peso, nodo}
void kruskal(int n, const vector<vector<pii>>& g, vector<vector<pii>>& mst){
    DSU ufds(n);
    using arista = tuple<int,int,int>;
    vector<arista> A;
    A.reserve(n * 4);
    for (int u = 0; u < n; u++) {
        for (const auto& edge : g[u]) {
            int w = edge.first;
            int v = edge.second;
            if (u < v) A.emplace_back(w, u, v);
        }
    }
    sort(A.begin(), A.end());
    mst.assign(n, {});
    for (const auto& e : A) {
        int w = get<0>(e);
        int u = get<1>(e);
        int v = get<2>(e);
        if (!ufds.related(u, v)) {
            ufds.unite(u, v);
            mst[u].push_back({w, v});
            mst[v].push_back({w, u});
            if (ufds.numSets == 1) break;
        }
    }
}

int solve() {
    // Code aquí
    int n, m; cin >> n >> m;
    vector<pii> nodes(n+1); for (int i = 1; i<=n; i++) {cin >> nodes[i].first; nodes[i].second = i;}
    vector<vector<pii>> grafo(n+1);
    int u, v;
    rep(i, m){ 
        cin >> u >> v;
        grafo[u].PB(pii(max(nodes[u].first, nodes[v].first), v));
        grafo[v].PB(pii(max(nodes[u].first, nodes[v].first), u));
    }
    DBG_COUT (cout << "Test:\n" << grafo << endl);
    DBG_COUT (cout << "Heights: " << nodes);

    /*vector<vector<pii>> kruskalTree; 
    kruskal(n+1, grafo, kruskalTree);
    DBG_COUT(cout << kruskalTree << endl);*/

    // Vamos a obtener todas las queries y a computar siguiendo cierto orden. De esta forma será mucho más sencillo
    int q; cin >> q;
    vector<array<int,4>> queries(q);
    rep(i, q) {cin >> queries[i][0] >> queries[i][1] >> queries[i][2]; queries[i][3] = i; queries[i][2] += nodes[queries[i][0]].first;}
    ord(queries);
    sort(nodes.begin(), nodes.end());

    vector<bool> solutions(q);
    DSU estado(n+1);
    int index = 0;
    for (int i = 0; i<q; i++){
        int a=queries[i][0], b=queries[i][1], e=queries[i][2], query=queries[i][3];
        DBG_COUT(cout << "Query: " << a << " " << b << " " << e << " " << query << endl);
        while(index < nodes.size() && nodes[index].first <= e){
            for (int i = 0; i<grafo[nodes[index].second].size(); i++){
                pii added = nodes[index];
                pii conect = grafo[nodes[index].second][i];
                if (grafo[nodes[index].second][i].first<=e && !estado.related(added.second, conect.second)){
                    estado.unite(added.second, conect.second);
                }
            }
            index++;
        }
        solutions[query] = estado.related(a, b);
    }

    for (auto x:solutions) cout << (x ? "YES":"NO") << endl;

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

// https://codeforces.com/contest/1851/problem/G