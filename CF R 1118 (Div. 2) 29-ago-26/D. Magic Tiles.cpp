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
template<typename T, size_t X> std::ostream& operator<<(std::ostream& os, const std::array<T, X>& vec) {
    os << "{ ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "}";
    return os;
}

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

void add(vector<lli>& v, lli x) {
    v.emplace_back(x);
    for (int i = int(v.size()) - 1; i >= 1; --i) {
        if (v[i] > v[i - 1]) {
            swap(v[i - 1], v[i]);
        } else {
            break;
        }
    }
}
 
void solve() {
    int n, m;
    cin >> n >> m;
 
    // Get input
    vector<array<lli, 2>> columnaIzquierda(n), columnaDerecha(m);
    for (int i = 0; i < n; ++i) {
        cin >> columnaIzquierda[i][0] >> columnaIzquierda[i][1];
        columnaIzquierda[i][1]++;
    }
    for (int i = 0; i < m; ++i) {
        cin >> columnaDerecha[i][0] >> columnaDerecha[i][1];
        columnaDerecha[i][1]++;
    }

    DBG_COUT(cout << "TEST: " << endl << "Columna izquierda: " << columnaIzquierda << endl << "Columna derecha: " << columnaDerecha << endl);
 
    // Marca los intervalos que esten contenidos en otro comprobando cada par de intervalos n, m <= 3000
    vector<int> vis1(n, true), vis2(m, true);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // Si el intervalo de la derecha está contenido en el de la izquierda
            if (vis1[i] && columnaIzquierda[i][0] <= columnaDerecha[j][0] && columnaDerecha[j][1] <= columnaIzquierda[i][1])  {
                vis2[j] = false;
            }
            // Si el intervalo de la izquierda está contenido en el de la derecha
            if (vis2[j] && columnaDerecha[j][0] <= columnaIzquierda[i][0] && columnaIzquierda[i][1] <= columnaDerecha[j][1]) {
                vis1[i] = false;
            }
        }
    }
 
    DBG_COUT(cout << "Intervalos independientes columna izquierda: " << vis1 << endl << "Intervalos independientes columna derecha: " << vis2 << endl);

    vector<array<lli, 2>> a, b;
    for (int i = 0; i < n; ++i) {
        if (vis1[i]) {
            a.push_back(columnaIzquierda[i]);
        }
    }
    for (int i = 0; i < m; ++i) {
        if (vis2[i]) {
            b.push_back(columnaDerecha[i]);
        }
    }
 
    columnaIzquierda = move(a);
    columnaDerecha = move(b);
    n = int(columnaIzquierda.size());
    m = int(columnaDerecha.size());

    DBG_COUT(cout << "Nuevo input: " << endl << n << " " << m << endl << columnaIzquierda << " " << columnaDerecha << endl);
 
    vector<lli> points;
    for (int i = 0; i < n; ++i) {
        points.emplace_back(columnaIzquierda[i][0]);
        points.emplace_back(columnaIzquierda[i][1]);
    }
    for (int i = 0; i < m; ++i) {
        points.emplace_back(columnaDerecha[i][0]);
        points.emplace_back(columnaDerecha[i][1]);
    }
 
    sort(points.begin(), points.end());
    points.erase(unique(points.begin(), points.end()), points.end());
    int k = int(points.size());

    DBG_COUT(cout << "Puntos de inflexion: " << points << endl);
 
    vector<lli> prv(k);
    for (int i = 0; i < k; ++i) {
        prv[i] = points[i];
    }
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(points.begin(), points.end(), columnaIzquierda[i][0]);
        while (it != points.end() && *it <= columnaIzquierda[i][1]) {
            prv[it - points.begin()] = min(prv[it - points.begin()], columnaIzquierda[i][0]);
            it++;
        }
    }
    for (int i = 0; i < m; ++i) {
        auto it = lower_bound(points.begin(), points.end(), columnaDerecha[i][0]);
        while (it != points.end() && *it <= columnaDerecha[i][1]) {
            prv[it - points.begin()] = min(prv[it - points.begin()], columnaDerecha[i][0]);
            it++;
        }
    }

    DBG_COUT(cout << "Punto más lejano en el rango al que pertenece points[i]: " << prv << endl);
 
    vector<vector<lli>> f(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < i; ++j) {
            if (points[j] >= prv[i]) {
                auto vec = f[j];
                add(vec, points[i] - points[j]);
                f[i] = max(f[i], vec);
            }
        }
        if (i + 1 != k) {
            f[i + 1] = max(f[i + 1], f[i]);
        }
    }
    DBG_COUT(cout << "DP obtained: " << endl;for (auto x:f) cout << x << endl);
    vector<lli> ans = f[k - 1];

    DBG_COUT(cout << "Solucion: " << endl);
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
    
    return;
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
        DBG_COUT(cout << "==================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2258/problem/D