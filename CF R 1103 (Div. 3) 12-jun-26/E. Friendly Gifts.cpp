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

struct rango {
    int l;
    int r;
    int minimo;
    int maximo;
    rango(int a, int b, int c, int d){
        l = a; r = b; minimo = c; maximo = d;
    }
    int size() {
        return r-l;
    }
    bool isGood() {
        return (r-l == maximo-minimo+1);
    }
};

int solve() {
    // Code aquí
    int n; cin >> n;
    vi a(n); rep(i, n) cin >> a[i];

    // Un array b es bueno si al ordenarlo se cumble que b[i] = b[i-1] + 1
    // Si un array tiene varias veces un elemento, ese array no es bueno
    // Para comprobar que el array sea bueno, si se cumple que no repite ningún elemento, tan solo hace falta comprobar que la diferencia entre el elemento más grande y el más chico es exactamente la longitud del array - 1

    // De esta forma un array bueno viene definido por su elemento más chico y el más grande y solo se pueden concatenar si el más chico de uno de ellos es igual al más grande del otro + 1
    
    // Para encontrar los rangos [l, r], lo primero será por cada l, buscar cual es el r más grande. Esto se puede hacer en O(n) con sliding windows
    
    vi topR(n, n);
    int l = 0, r = 0;
    set<int> selected;
    while(r < n){
        if (l < r){
            while (selected.find(a[r]) != selected.end()){
                topR[l] = r;
                selected.erase(selected.find(a[l]));
                l++;
            }
        }
        selected.insert(a[r]); 
        r++;
    }

    DBG_COUT(cout << "Max r for each l: " << topR << endl);

    vector<vi> dp(n+1 ,vi(n+1, 0)); // dp[i][j] = 1 si existe un array bueno cuyo elemento minimo sea i y el máximo sea j
    // Buscamos una pareja dp[i][i+k], dp[i+k+1][i+2*k+1]

    for (int l = 0; l < n; l++){
        int minimo = INF;
        int maximo = -1;
        for (int r = l+1; r <= topR[l]; r++){
            minimo = min(minimo, a[r-1]);
            maximo = max(maximo, a[r-1]);
            rango el = rango(l, r, minimo, maximo);
            if (el.isGood()) dp[minimo][maximo] = 1;
        }
    }

    DBG_COUT(cout << "Ranges selected: " << dp << endl);
    
    int sol = 0;
    for (int i = 1; i<=n; i++){
        for (int k = 0; i+2*k+1<=n; k++){
            if (dp[i][i+k] && dp[i+k+1][i+2*k+1]) sol = max(sol, k+1);
        }
    }
    DBG_COUT(cout << "Solucion: ");
    cout << sol << endl;


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
        DBG_COUT(cout << "===============================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2236/problem/E