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
    os << "]\n";
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

int solve() {
    // El problema lo resolveremos diciendo que de l a r, vamos a tener nuestro intervalo entero de 1s (Es el que consideraremos como intervalo más grande)
    // En caso de haber otro, lo tendremos en cuenta cuando inspeccionemos dicho intervalo
    // En el resto buscaremos cual es el espacio de 0 mas grandes que podemos obtener

    //Input
    int n, k; cin >> n >> k;
    string s; cin >> s;
    DBG_COUT(cout << "Test: k = " << k << "\ns = " << s << endl);

    // Maximo número de 0s que puedo obtener seguidos gastando coste j y terminando en i
    vector<vi> pref(n, vi(k+1, 0));
    
    for (int i = 0; i<n; i++){
        for (int j = 0; j<=k; j++){
            if (s[i] == '0') {
                if (i == 0) pref[i][j] = 1;
                else pref[i][j] = pref[i-1][j] + 1;
            } else if (s[i] == '1' && j != 0) {
                if (i == 0) pref[i][j] = 1;
                else pref[i][j] = pref[i-1][j-1] + 1;
            }
        }
    }
    DBG_COUT(cout << "Secuencia de ceros obtenibles más grande terminando en la posición i y con j operaciones:\n" << pref << endl);

    // Modifica pref, ahora tendrá la secuencia con más 0s obtenible hasta la posición i con j operaciones
    for (int i = 1; i<n; i++){
        for (int j = 0; j<=k; j++){
            pref[i][j] = max(pref[i][j], pref[i-1][j]);
        }
    }
    DBG_COUT(cout << "Secuencia de 0s más larga obtenible que termine en la posición i o antes con j operaciones:\n" << pref << endl);

    // Modifica pref, ahora tendrá la secuencia con más 0s obtenible hasta la posición i con como mucho j operaciones
    for (int i = 0; i<n; i++){
        for (int j = 1; j<=k; j++){
            pref[i][j] = max(pref[i][j], pref[i][j-1]);
        }
    }
    DBG_COUT(cout << "Secuencia de 0s más larga obtenible que termine en la posición i o antes con j operaciones o menos:\n" << pref << endl);

    // Maximo número de 0s que puedo obtener seguidos gastando coste j y empezando en i
    vector<vi> suf(n, vi(k+1, 0));
    
    for (int i = n-1; i>=0; i--){
        for (int j = 0; j<=k; j++){
            if (s[i] == '0') {
                if (i == n-1) suf[i][j] = 1;
                else suf[i][j] = suf[i+1][j] + 1;
            } else if (s[i] == '1' && j != 0) {
                if (i == n-1) suf[i][j] = 1;
                else suf[i][j] = suf[i+1][j-1] + 1;
            }
        }
    }
    DBG_COUT(cout << "Secuencia de ceros obtenibles más grande empezando en la posición i y con j operaciones:\n" << suf << endl);

    // Modifica suf, ahora tendrá la secuencia con más 0s obtenible empezando en la posición i o después con j operaciones
    for (int i = n-2; i>=0; i--){
        for (int j = 0; j<=k; j++){
            suf[i][j] = max(suf[i][j], suf[i+1][j]);
        }
    }
    DBG_COUT(cout << "Secuencia de 0s más larga obtenible que empiece en la posición i o después con j operaciones:\n" << suf << endl);

    // Modifica suf, ahora tendrá la secuencia con más 0s obtenible empezando en la posición i o después con j operaciones o menos
    for (int i = n-1; i>=0; i--){
        for (int j = 1; j<=k; j++){
            suf[i][j] = max(suf[i][j], suf[i][j-1]);
        }
    }
    DBG_COUT(cout << "Secuencia de 0s más larga obtenible que empiece en la posición i o después con j operaciones o menos:\n" << suf << endl);

    // Numero de ceros entre la posición 0 y la posición y
    vi zeros(n);
    zeros[0] = (s[0] == '0');
    for (int i = 1; i<n; i++) zeros[i] = zeros[i-1] + (s[i] == '0');

    DBG_COUT(cout << "Count of zeros " << zeros << endl);

    // Por cada pareja [l,r], el número de ceros que haya entre ella son el número de operaciones que tienes que hacer para obtener todo el intervalo lleno de 1s
    vector<vi> costeIntervalo(n, vi(n, INF));
    for (int l = 0; l<n; l++){
        for (int r = l; r<n; r++){
            costeIntervalo[l][r] = zeros[r]-zeros[l]+(s[l] == '0');
        }
    }

    DBG_COUT(cout << "Operaciones necesarias para transformar el intervalo [l, r] en 1s:\n" << costeIntervalo << endl);

    // Por cada pareja [l, r], debemos buscar el máximo número de ceros que podemos obtener seguidos
    // Cada pareja tiene un coste asociado, por lo que sería el máximo entre el número de ceros que puedes obtener en pref o en suf con menos del coste
    // Este número es max(pref[l-1][k-costeIntervalo[l][r]], suf[r+1][k-costeIntervalo[l][r]])
    // Para cada longitud del intervalo (r-l+1), vamos a buscar el que devuelva el coeficiente max(pref[l-1][k-costeIntervalo[l][r]], suf[r+1][k-costeIntervalo[l][r]]) más grande
    vi coeficiente(n+1, -1); // El índice indica el valor de l_1 y el valor el mejor obtenible para l_0
    // Para la longitud 0:
    coeficiente[0] = pref[n-1][k];
    for (int i = 1; i<=n; i++){
        for (int l = 0; l<=n-i; l++){
            int r = l+i-1;
            if (costeIntervalo[l][r] > k) continue;
            else if (l == 0 && r == n-1) coeficiente[i] = 0;
            else if (l == 0 && r != n-1) coeficiente[i] = max(coeficiente[i], suf[r+1][k-costeIntervalo[l][r]]);
            else if (l != 0 && r == n-1) coeficiente[i] = max(coeficiente[i], pref[l-1][k-costeIntervalo[l][r]]);
            else if (l != 0 && r != n-1) coeficiente[i] = max(coeficiente[i], max(pref[l-1][k-costeIntervalo[l][r]], suf[r+1][k-costeIntervalo[l][r]]));
        }
    } 

    DBG_COUT(cout << "l_0 por cada posible valor de l_1: " << coeficiente << endl);

    // Por cada valor de a, revisamos los coeficientes para ver cual da el mejor resultado
    DBG_COUT(cout << "Solucion final: ");
    for (int a = 1; a<=n; a++){
        int caso = 0;
        for (int i = 0; i<coeficiente.size(); i++){
            if (coeficiente[i] != -1) caso = max(caso, a*coeficiente[i] + i);
        }
        cout << caso << " ";
    }
    cout << endl;

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

// https://codeforces.com/contest/1858/problem/D