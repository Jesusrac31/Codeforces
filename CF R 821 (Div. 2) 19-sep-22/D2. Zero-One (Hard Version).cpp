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

#define INF LLONG_MAX
double pi = 2*acos(0.0);

lli backTracking(vi& posiciones, lli x, lli y, int n){
    vll dp(n+1, INF);
    dp[0] = 0;
    x*=2; // Multiplicamos por 2 para evitar problemas con decimales
    for (int i = 1; i<=n; i++){
        if (i != 1){ // Solo en este caso se puede usar la operación x
            dp[i] = dp[i-2] + x*(posiciones[i-1] - posiciones[i-2]);
            DBG_COUT(cout << "Valor 1: " << dp[i-2] + x*(posiciones[i-1] - posiciones[i-2]) << endl );
        }
        DBG_COUT(cout << "Valor 2: " << dp[i-1] + y << endl );
        if (dp[i] > dp[i-1] + y){
            dp[i] = dp[i-1] + y;
        }
        DBG_COUT(cout << "Indice: " << i << " Estado: " << dp[i] << endl);
    }
    DBG_COUT(cout << "Final: " << dp << endl);
    return dp[n]/2;
}

int solve(int T) {
    // Code aquí
    lli n, x, y; cin >> n >> x >> y;
    string a; cin >> a;
    string b; cin >> b;

    DBG_COUT(cout << "Test: " << x << " " << y << endl << a << endl << b << endl);
    vi posicionesFlips;
    int m = 0; // Número de flips
    for (int i = 0; i<n; i++) if (a[i] != b[i]) {m++; posicionesFlips.PB(i);}
    if (m&1) {cout << -1 << endl; return 0;}

    int p = 0; // Oportunidades para usar x
    for (int i = 1; i<n; i++){
        if (a[i] != b[i] && a[i-1] != b[i-1]){
            p++;
            i++;
        }
    }

    if (m == 0) cout << 0 << endl;
    else if (m == 2 && p == 1) cout << min(2*y, x) << endl;
    else { // Este es el único caso cuando la cosa puede parecer dificil, debemos comprobar según la diferencia entre x e y que renta más
        // Por cada bit diferente podemos hacer dos cosas:
        // 1. Eliminarlo con el siguiente a base de operaciones x
        // 2. Eliminarlo usando una operación y
        // Fijate que eliminarlo con una operación x solo rentaría si es con el que es justo el siguiente
        // Por cada elemento que elimine usando operación y, suma y/2. Por cada par de elementos que elimine usando operación x, suma x*d donde d es la distancia entre ellos

        // Podemos hacer esto por backtracking sin embargo siguiendo este esquema el resultado viene definido por dos valores: Cuantos elementos hemos eliminado y cuánto peso llevamos
        // Crearé la función recursiva de backtracking a partir de la lista de los bits a cambiar. 
        // Puede parecer que hay un inconveniente cuando dos haces operación x en todas las parejas menos en dos elementos consecutivos, pero al ser x<y, siempre hará la operación x
        
        // Vamos a ir calculando para cada posición el máximo
        cout << backTracking(posicionesFlips, x, y, m) << endl;
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
        solve(T);
    }
    return 0;
}

// https://codeforces.com/contest/1733/problem/D2