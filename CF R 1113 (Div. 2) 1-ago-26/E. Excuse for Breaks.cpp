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

typedef __int128_t i128;

int solve() {
    // Code aquí
    lli n, m, d; cin >> n >> m >> d;

    vector<lli> p(m), r(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i] >> r[i];
    }

    /*
    Tengo infinitos objetos de m tipos, cada uno con un valor y un peso, a medida que aumenta el valor aumenta el peso. En nuestro caso, el objeto de tipo i tendría un valor de pref_r[i] y un peso de p[i]+1

    Debemos saber si puedo seleccionar un conjunto de objetos tal que la suma de sus valores sea mayor a W(suma de los pesos + número de objetos - 1) + (número de objetos - 1) * d
    */

    // Precalculamos las sumas acumuladas de r
    vector<lli> pref_r(m + 1, 0);
    for (int i = 0; i < m; i++) {
        pref_r[i + 1] = pref_r[i] + r[i];
    }

    // Función O(log m) para obtener W(k)
    // Definimos W(k) como la puntuación que da una racha de k 1s
    auto get_W = [&](lli k) -> lli {
        if (k <= 0) return 0; // Seguro de la función
        if (k >= n) return n * d + pref_r[m]; // Si pides el de un número muy grande, al estar capado en n, devolvemos el resultado como si k = n
        int idx = upper_bound(p.begin(), p.end(), k) - p.begin();
        return k * d + pref_r[idx]; // La suma del prefijo más el número de tiempos utilizados
    };

    lli W_n = get_W(n);

    // 1. Construimos el conjunto reducido de PUNTOS CRÍTICOS K (|K| <= 4002)
    // Los puntos críticos son aquellos donde hay un cambio de puntuación y justo antes
    vector<lli> K;
    K.push_back(0);
    if (n - 1 > 0) K.push_back(n - 1);
    for (int i = 0; i < m; i++) {
        if (p[i] < n) K.push_back(p[i]);
        if (p[i] - 1 >= 0 && p[i] - 1 < n) K.push_back(p[i] - 1);
    }

    sort(K.begin(), K.end());
    K.erase(unique(K.begin(), K.end()), K.end()); // En caso que se repitan puntos, los borramos

    // 2. Comprobación 1: Rendimiento asintótico de un bloque individual
    for (lli k : K) {
        if (k < n) {
            lli W_k = get_W(k);
            if ((i128)W_k * n > (i128)W_n * (k + 1)) {
                cout << "YES\n";
                return 0;
            }
        }
    }

    // 3. Comprobación 2: Evaluamos todas las parejas de bloques (k1, k2)
    for (lli k1 : K) {
        lli W_k1 = get_W(k1);
        for (lli k2 : K) {
            lli W_k2 = get_W(k2);
            lli L = k1 + 1 + k2; // Longitud total del arreglo a
            
            lli f_a = W_k1 + W_k2;
            lli q = L / n;
            lli rem = L % n;
            lli f_I = q * W_n + get_W(rem);

            if (f_a > f_I) {
                cout << "YES" << endl;
                return 0;
            }
        }
    }

    cout << "NO" << endl;

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

// https://codeforces.com/contest/2248/problem/E