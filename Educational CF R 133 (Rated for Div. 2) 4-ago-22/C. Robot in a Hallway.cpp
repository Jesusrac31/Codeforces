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
    os << "]" << endl;
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

#define INF 1111100000
double pi = 2*acos(0.0);

int solve() {
    // Code aquí
    int n; cin >> n;
    vector<vi> mapa(2, vi(n));
    for (int i = 0; i<2; i++) for(int j = 0; j<n; j++) cin >> mapa[i][j];

    DBG_COUT(cout << "----------------------\n" <<  "Test: " << n << endl << mapa);

    // En cada posición hay dos posibilidades:
    // 1. Cambia de fila y ve una hacia la derecha: El problema se reduce al mismo con las filas cambiadas y una columna
    // 2. Ve hacia la derecha: Entonces tienes que llegar al final del todo, bajar y volver de nuevo.

    // El caso 2 es determinado, es decir, una vez que entras en el caso 2 el resto de movimientos es forzado, 
    // por lo que podemos buscar el número de pasos necesarios desde cada una de las casillas
    // Para esto simplemente debemos saber:
    // 1. Cuanto tardas en acceder a la siguiente casilla
    // 2. Cuanto tardas desde la casilla de la derecha
    // 3. Cuanto tardarías desde la casilla de la derecha si todos los valores fueran 0

    // El punto 3 es fácilmente obtenible como 2*x-1 siendo x el número de columnas a partir de la casilla derecha
    // El punto 1 viene dado por el valor por a[0,1] siendo este el valor de la casilla de la derecha
    // El punto 2 se puede obtener de forma recursiva con complejidad O(2*n)

    // Por último, podemos calcular cuanto tardamos en llegar a cada casilla siguiendo el caso 1, introduciendo INF en los casos donde el siguiente movimiento es forzado.
    // Buscamos la suma de ambas tamblas que sea mínima

    vector<vi> caso2(2, vi(n));
    caso2[0].back() = mapa[1].back()+1;// Cuanto tardas en terminar desde arriba en la subtabla 2x1
    caso2[1].back() = mapa[0].back()+1;// Cuanto tardas en terminar desde abajo en la subtabla 2x1
    for (int i = n-2; i>=0; i--){
        // Caso 2 desde arriba
        int start = mapa[0][i+1]+1;
        int duracion = caso2[0][i+1];
        int duracionEsperada = 2*(n-i)-3;
        int duracionFinal = max(duracionEsperada+start, duracion);
        if (duracionFinal < mapa[1][i]) duracionFinal = mapa[1][i]+1;
        else duracionFinal++;
        caso2[0][i] = duracionFinal;

        // Caso 2 desde abajo
        start = mapa[1][i+1]+1;
        duracion = caso2[1][i+1];
        duracionEsperada = 2*(n-i)-3;
        duracionFinal = max(duracionEsperada+start, duracion);
        if (duracionFinal < mapa[0][i]) duracionFinal = mapa[0][i]+1;
        else duracionFinal++;
        caso2[1][i] = duracionFinal;
    }
    DBG_COUT(cout << "Caso 2: \n" << caso2);

    // Generamos el caso 1:
    vector<vi> caso1(2, vi(n));
    caso1[0][0] = 0;
    caso1[1][0] = INF;
    for (int i = 1; i<n; i++){
        if (i&1){
            caso1[0][i] = INF;
            int newValue = caso1[0][i-1];
            newValue = max(newValue, mapa[1][i-1])+1;
            newValue = max(newValue, mapa[1][i])+1;
            caso1[1][i] = newValue; // mapa[0][i-1] -> mapa[1][i-1] -> mapa[1][i]
        } else {
            int newValue = caso1[1][i-1];
            newValue = max(newValue, mapa[0][i-1])+1;
            newValue = max(newValue, mapa[0][i])+1;
            caso1[0][i] = newValue;
            caso1[1][i] = INF;
        }
    }
    DBG_COUT(cout << "Caso 1: \n" << caso1);

    int sol = INF;
    for (int i = 0; i<2; i++){
        for (int j = 0; j<n; j++){
            int duracionEsperada = 2*(n-j)-1;
            sol = min(sol, max(caso1[i][j]+duracionEsperada, caso2[i][j]));
            DBG_COUT(cout << "Inspect with: " << caso1[i][j]+duracionEsperada << " and " << caso2[i][j] << endl);
        }
    }
    DBG_COUT(cout << "Solución: ");
    cout << sol << endl;

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

// https://codeforces.com/contest/1716/problem/C