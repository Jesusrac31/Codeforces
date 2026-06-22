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

struct Graph {
    vector<int> tin, tout, d;
    vector<vector<pair<int, lli>>> up;
 
    int timer;
 
    void dfs(int v, const vector<vector<int>>& g, const vector<int>& arr, int p = -1) {
        tin[v] = timer++;
        up[0][v] = {p, arr[v]};
        for (int l = 1; l < 20; ++l) {
            if (up[l - 1][v].first == -1) {
                up[l][v] = {-1, 0};
                continue;
            }
            up[l][v].first = up[l - 1][up[l - 1][v].first].first;
            up[l][v].second = up[l - 1][up[l - 1][v].first].second + up[l - 1][v].second;
        }
        for (int u : g[v]) {
            if (u == p) continue;
            d[u] = d[v] + 1;
            dfs(u, g, arr, v);
        }
        tout[v] = timer;
    }
 
    Graph(const vector<vector<int>>& g, const vector<int>& a) : tin(g.size()), tout(g.size()), d(g.size()), up(20, vector<pair<int, lli>>(g.size())) {
        timer = 0;
        dfs(0, g, a);
    }
 
    bool anc(int p, int v) {
        return tin[p] <= tin[v] && tout[p] >= tout[v];
    }
 
    int getLenVertical(int u, int v) {
        if (!anc(u, v)) swap(u, v);
        assert(anc(u, v));
        return d[v] - d[u] - 1;
    }
 
    pair<int, lli> LA(int v, int k) {
        if (k <= 0) return {v, 0};
        lli sum = 0;
        for (int i = 0; i < 20; ++i) {
            if (k >> i & 1) sum += up[i][v].second, v = up[i][v].first;
        }
        return {v, sum};
    }
 
    int LCA(int u, int v) {
        if (anc(u, v)) return u;
        for (int l = 19; l >= 0; --l) {
            if (up[l][u].first == -1 || anc(up[l][u].first, v)) continue;
            u = up[l][u].first;
        }
        return up[0][u].first;
    }
 
    bool lower(int a, int b) {
        return tin[a] < tin[b];
    }
};
 
lli sum(int r) { return r * 1LL * (r + 1) / 2; }
 
lli sumSeg(int l, int r) {
    return sum(r) - sum(l - 1);
}
 
void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    vector<int> parent(n), d(n);
    auto dfs = [&](auto& self, int v, int p = -1) -> void {
        parent[v] = p;
        for (int u : g[v]) {
            if (u == p) continue;
            d[u] = d[v] + 1;
            self(self, u, v);
        }
    };
    dfs(dfs, 0);
 
    vector<int> compressed_parent = parent;
    vector<vector<int>> cG(n);
    for (int v = 0; v < n; ++v) {
        vector<int> path;
        while (compressed_parent[v] > 0 && a[compressed_parent[v]] == 0) {
            path.emplace_back(compressed_parent[v]);
            compressed_parent[v] = compressed_parent[compressed_parent[v]];
        }
        for (auto& x : path) compressed_parent[x] = compressed_parent[v];
        if (a[v] == 0 || !v) continue;
        cG[compressed_parent[v]].emplace_back(v);
    }
 
    vector<int> next_collision(n), sum_collision(n);
    for (int v = 0; v < n; ++v) {
        if (!a[v]) continue;
        next_collision[v] = v;
        int xr = a[v], sm = a[v];
        while (xr == sm && next_collision[v] > -1) {
            next_collision[v] = compressed_parent[next_collision[v]];
            if (next_collision[v] == -1) break;
            xr ^= a[next_collision[v]];
            sm += a[next_collision[v]];
        }
    }
 
    for (int v = 0; v < n; ++v) {
        if (!a[v]) {
            if (!v) next_collision[v] = -1;
            else next_collision[v] = next_collision[compressed_parent[v]];
        }
        sum_collision[v] = d[v];
        if (next_collision[v] > -1) sum_collision[v] -= d[next_collision[v]];
        else sum_collision[v]++;
    }
 
    Graph def(g, sum_collision);
    Graph compressed(cG, sum_collision);
 
    while (q--) {
        int u, v; cin >> u >> v;
        --u, --v;
        if (def.lower(v, u)) swap(u, v);
        int z = def.LCA(u, v);
 
        int cv = (a[v] || !v ? v : compressed_parent[v]), cu = (a[u] || !u ? u : compressed_parent[u]), cz = (a[z] || !z ? z : compressed_parent[z]);
 
        lli ans = 0;
 
        vector<int> L, R, Lspaces = {0}, Rspaces = {0};
 
        if (compressed.d[cv] > compressed.d[cz] + 23) {
            int unt = compressed.LA(cv, compressed.d[cv] - (compressed.d[cz] + 23)).first;
            auto [to, sm] = def.LA(v, d[v] - d[unt]);
            ans += sm, v = to;
        }
 
        if (compressed.d[cu] > compressed.d[cz] + 23) {
            int unt = compressed.LA(cu, compressed.d[cu] - (compressed.d[cz] + 23)).first;
            auto [to, sm] = def.LA(u, d[u] - d[unt]);
            ans += sm, u = to;
        }
 
        while (u != z) {
            int to = compressed_parent[u];
            if (def.anc(to, z)) to = z;
            L.emplace_back(u);
            Lspaces.emplace_back(def.getLenVertical(u, to));
            u = to;
        }
        while (v != z) {
            int to = compressed_parent[v];
            if (def.anc(to, z)) to = z;
            R.emplace_back(v);
            Rspaces.emplace_back(def.getLenVertical(v, to));
            v = to;
        }
        L.emplace_back(z);
        std::reverse(R.begin(), R.end());
        std::reverse(Rspaces.begin(), Rspaces.end());
        for (auto& x : R) L.emplace_back(x);
        for (auto& x : Rspaces) Lspaces.emplace_back(x);
        int j = 0, xr = 0, sum = 0;
        lli cnt = 0;
        for (int i = 0; i < L.size(); ++i) {
            while (j < L.size() && xr == sum) {
                xr ^= a[L[j]], sum += a[L[j]];
                cnt += Lspaces[j] + 1;
                j++;
            }
            if (xr != sum) cnt--;
            ans += sumSeg(cnt - Lspaces[i], cnt);
            if (xr != sum) cnt++;
            xr ^= a[L[i]], sum -= a[L[i]];
            cnt -= Lspaces[i] + 1;
        }
        cout << ans << '\n';
    }
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

// https://codeforces.com/contest/2236/problem/G