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

int solve() {
    // Code aquí
    int n; cin >> n;
    vi a(n-1); rep(i, n-1) cin >> a[i];
    DBG_COUT(cout << "Test: " << a << endl);

    vi p(n, 0);

    // Según la explicación de la operación, v[i] = x si los valores pertenecientes a (x, n] están en el mismo lado y x en el otro
    // Digamos que p[k] = n
    // Entonces, v[i] = max(p[j], j in 0..i) para i<k
    // Y además, v[i] = max(p[j], j in i+1..n) para i>=k

    // Sabemos entonces que v es no decreciente para i<k
    // Además v es no creciente para i>=k

    // Debe haber al menos un punto donde p[t] = n-1
    // Si t < k, v[t] = v[t+1] = ... = v[k-1] = n-1
    // Sino, v[k] = v[k+1] = ... = v[t-1] = n-1
    // Ya tenemos dos posiciones fijas, la de n y n-1 que pueden intercambiarse
    // Además, ambas combinaciones llevan a las mismas posibilidades, lo cual no compensa claramente
    
    // Asumamos que k<t
    // Si v[i-1] != v[i] para i<k, p[i] = v[i], aplica esto a todo este intervalo dando valores fijos e inmoviles a ciertos p[i]
    // El resto de las posiciones entre i y k se pueden llenar con números menores a v[i]
    // Aplica lo mismo para i>=t
    
    int leftRange = -1;
    for (int i = 0; i<n-1; i++) if (a[i] == n-1) {
        leftRange = i;
        break;
    }
    int rightRange = -1;
    for (int i = 0; i<n-1; i++) if (a[i] == n-1) 
        rightRange = i;
    
    if (leftRange == -1){
        DBG_COUT(cout << "No hay ningun valor en a con n-1" << endl);
        cout << 0 << endl;
        return 0;
    }

    for (int i = leftRange; i<=rightRange; i++){
        if (a[i] != n-1){
            DBG_COUT(cout << "Rango de n-1 no valido" << endl);
            cout << 0 << endl;
            return 0;
        }
    }

    p[leftRange] = n-1; p[rightRange+1] = n;
    DBG_COUT(cout << "Permutación base: " << p << endl);

    p[0] = a[0];
    for (int i = 1; i<leftRange; i++){
        if (a[i] < a[i-1]){
            DBG_COUT(cout << "Segmento de la izquierda no es no decreciente" << endl);
            cout << 0 << endl;
            return 0;
        }
        if (a[i] > a[i-1]){
            p[i] = a[i];
        }
    }

    DBG_COUT(cout << "Permutacion con obligatorios a la izquierda: " << p << endl);

    if (rightRange != n-2) p[n-1] = a[n-2];

    for (int i = rightRange+1; i<n-2; i++){
        if (a[i] < a[i+1]){
            DBG_COUT(cout << "Segmento de la derecha no es no creciente" << endl);
            cout << 0 << endl;
            return 0;
        }
        if (a[i] > a[i+1]){
            p[i+1] = a[i];
        }
    }

    DBG_COUT(cout << "Permutacion con obligatorios: " << p << endl);

    vector<bool> appear(n+1);

    for (int i = 0; i<n; i++){
        if (p[i] == 0) continue;
        if (appear[p[i]]){
            DBG_COUT(cout << "No es una permutación" << endl);
            cout << 0 << endl;
            return 0;
        }
        appear[p[i]] = true;
    }

    // Para el conteo, como de costumbre, veremos las posiciones en las que se puede colocar el elemento más grande a la izquierda por un lado y a la derecha
    // Un elemento y tal que y<x puede colocarse en al menos las mismas posiciones que x

    vector<int> posicionesPosibles(n);
    int lastEl = 0;
    for (int i = 0; i<leftRange; i++){
        lastEl = max(p[i], lastEl);
        posicionesPosibles[lastEl]++;
    }

    lastEl = 0;
    for (int i = n-1; i>rightRange+1; i--){
        lastEl = max(p[i], lastEl);
        posicionesPosibles[lastEl]++;
    }
    for (int i = 0; i<n; i++) if (posicionesPosibles[i]) posicionesPosibles[i]--;
    
    posicionesPosibles[n-1] = rightRange - leftRange;

    for (int i = n-2; i>0; i--)
        posicionesPosibles[i] += posicionesPosibles[i+1];
    
    DBG_COUT(cout << "Posiciones posibles: " << posicionesPosibles << endl);

    Mint sol = 2;
    int remove = 0;
    for (int i = n-1; i>0; i--){
        if (!appear[i]){
            sol *= (posicionesPosibles[i]-remove);
            remove++;
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
        DBG_COUT(cout << "===================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2250/problem/D