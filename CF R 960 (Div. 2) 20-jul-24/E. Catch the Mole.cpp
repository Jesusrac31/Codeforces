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

const int MAXN = 5005;

int n;
vector<int> adj[MAXN];
int paret[MAXN];
int tin[MAXN], tout[MAXN];
vector<int> order;
int timer;

bool posible[MAXN];
int child_cand[MAXN];
int cnt[MAXN];
int parents_in_subtree[MAXN];
bool proximo_turno[MAXN];

// DFS inicial en O(N) para linealizar el árbol
void dfs_init(int u, int p) {
    paret[u] = p;
    tin[u] = ++timer;
    order.push_back(u);
    for (int v : adj[u]) {
        if (v != p) {
            dfs_init(v, u);
        }
    }
    tout[u] = timer;
}

void solve() {
    if (!(cin >> n)) return;

    // 1. Limpieza rápida de las estructuras globales
    timer = 0;
    order.clear();
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_init(1, 0);
    paret[1] = 1; // La raíz es su propio padre para el movimiento del topo

    // Lista activa de sospechosos
    vector<int> suspects;
    suspects.reserve(n);
    for (int i = 1; i <= n; ++i) {
        posible[i] = true;
        suspects.push_back(i);
    }

    while (true) {
        // Si solo queda uno, ¡hemos ganado!
        if (suspects.size() == 1) {
            cout << "! " << suspects[0] << endl;
            break;
        }

        // 2. Limpieza de vectores de estado en O(N)
        memset(child_cand, 0, sizeof(int) * (n + 1));
        memset(cnt, 0, sizeof(int) * (n + 1));
        memset(parents_in_subtree, 0, sizeof(int) * (n + 1));
        memset(proximo_turno, 0, sizeof(bool) * (n + 1));

        // Inicializar hojas de la DP solo con los sospechosos activos
        int total_parents = 0;
        for (int v : suspects) {
            cnt[v] = 1;
            int p = paret[v];
            if (child_cand[p] == 0) total_parents++;
            child_cand[p]++;
        }

        for (int i = 1; i <= n; ++i) {
            if (child_cand[i] > 0) parents_in_subtree[i] = 1;
        }

        // 3. DP Bottom-Up iterativa perfecta
        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            if (v != 1) { // Evitamos que la raíz se propague a sí misma infinitamente
                int p = paret[v];
                cnt[p] += cnt[v];
                parents_in_subtree[p] += parents_in_subtree[v];
            }
        }

        // 4. Buscar la query óptima mediante Minimax
        int mejor_u = 1;
        int min_peor_caso = 1e9;

        for (int u = 1; u <= n; ++u) {
            if (cnt[u] == 0 && parents_in_subtree[u] == 0) continue;

            int q_si_es_1 = cnt[u];
            int q_si_es_0 = total_parents - parents_in_subtree[u];
            
            if (u != 1) {
                int p = paret[u];
                if (child_cand[p] > 0) q_si_es_0--;
                if (child_cand[p] - (posible[u] ? 1 : 0) > 0) q_si_es_0++;
            }

            int peor_escenario = max(q_si_es_1, q_si_es_0);
            if (peor_escenario < min_peor_caso) {
                min_peor_caso = peor_escenario;
                mejor_u = u;
            }
        }

        // 5. Interacción interactiva (usa endl para vaciar el búfer/flush)
        cout << "? " << mejor_u << endl;
        int ans; cin >> ans;

        // 6. Actualización del estado real de sospechosos
        vector<int> next_suspects;
        next_suspects.reserve(suspects.size());

        if (ans == 1) {
            for (int v : suspects) {
                if (tin[mejor_u] <= tin[v] && tin[v] <= tout[mejor_u]) {
                    next_suspects.push_back(v);
                } else {
                    posible[v] = false;
                }
            }
        } else {
            for (int v : suspects) {
                if (!(tin[mejor_u] <= tin[v] && tin[v] <= tout[mejor_u])) {
                    int p = paret[v];
                    if (!proximo_turno[p]) {
                        proximo_turno[p] = true;
                        next_suspects.push_back(p);
                    }
                }
                posible[v] = false;
            }
            for (int v : next_suspects) {
                posible[v] = true;
            }
        }
        suspects = move(next_suspects);
    }
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

// https://codeforces.com/contest/1990/problem/E1
// https://codeforces.com/contest/1990/problem/E2