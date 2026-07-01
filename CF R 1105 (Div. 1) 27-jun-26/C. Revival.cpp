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

class BIT {
public:
    int n;
    vi bit;
    BIT(int n): n(n), bit(n + 2, 0) {}
    void add(int i, int x) {
        for (; i <= n; i += i & -i) 
            bit[i] += x;
    }
    int sum(int i) const {
        int res = 0;
        for (; i > 0; i -= i & -i) 
            res += bit[i];
        return res;
    }
    int find_kth(int k) {
        int pos = 0;
        for (int step = 1 << __lg(n); step; step >>= 1) {
            if (pos + step <= n && bit[pos + step] <= k) {
                k -= bit[pos + step];
                pos += step;
            }
        }
        return pos + 1;
    }
};

int solve() {
    int n; cin >> n;

    vll val(n + 1);
    vector<char> type(n + 1);
    vi p(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> type[i] >> val[i];
        if (type[i] == 'p') p[i] = val[i]; // Si sabes el valor, almacenalo en p
        else val[i] = 1LL * i * (i - 1) / 2 - val[i]; // Cambia de la cantidad de inversiones a la cantidad de "no inversiones"
    }
    DBG_COUT(cout << "Actual p: " << p << endl);

    // Precalcular último índice con 's'
    vi lastS(n + 1);
    for (int i = 1; i <= n; i++) {
        if (type[i] == 's') lastS[i] = i;
        else lastS[i] = lastS[i - 1];
    }
    DBG_COUT(cout << "Last index of s: " << lastS << endl);

    // Inicializar BIT con todos los valores disponibles
    BIT fenwick(n);
    for (int i = 1; i <= n; i++) fenwick.add(i, 1);

    // Quitar los ya conocidos del sufijo
    for (int i = lastS[n] + 1; i <= n; i++) fenwick.add(p[i], -1);
    

    // Procesar intervalos de derecha a izquierda
    for (int i = lastS[n]; i > 0; i = lastS[i - 1]) {
        int L = lastS[i - 1];
        lli delta = val[i] - val[L];

        // Procesar bloque (L, i)
        // Quita todos los disponibles en este intervalo y resta a delta 
        // la cantidad de parejas (j, k) tal que p[j] > p[k]
        for (int j = i - 1; j > L; j--) {
            delta -= fenwick.sum(p[j] - 1);
            fenwick.add(p[j], -1);
        }
        // Añade a delta el número de elementos del bloque
        delta += (i - L - 1);

        // Cada elemento del bloque pasa a tener un peso de 2. Esto se hace
        // para eliminar el error que provoca el calculo según p[j] < p[lastS[i]] o p[j] > p[lastS[i]]
        for (int j = i - 1; j > L; j--) fenwick.add(p[j], 2);

        // #[j < i : p[j] ​< p[i]] = delta
        p[i] = fenwick.find_kth(delta);

        // Reinician fenwick
        for (int j = i - 1; j > L; j--) fenwick.add(p[j], -2);
        fenwick.add(p[i], -1);
    }

    // Output
    DBG_COUT(cout << "Solucion: " << endl);
    for (int i = 1; i <= n; i++) cout << p[i] << " ";
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
        DBG_COUT(cout << "=======================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2239/problem/C