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

lli getBits(lli x){
    int sol = 0;
    while(x){
        sol++;
        x>>=1;
    }
    return sol;
}

lli getCostIndividual(lli x){
    return __builtin_popcount(x) + getBits(x) - 1;
}

lli getCost(vll& a, lli k){
    lli div = pow(2, k);
    lli sol = k;
    for (auto x:a) {
        lli rem = (x + div - 1) % div;
        lli incremento = div - rem - 1;
        lli costIndividual = INF;
        x += incremento;
        for (int i = 0; i<=32; i+=div)
            costIndividual = min(getCostIndividual((x+i)/div)+i, costIndividual);
        sol += incremento + costIndividual;
        DBG_COUT(cout << "Coste individual de " << x << ": " << incremento + costIndividual << endl);
    }
    return sol;
}

int solve() {
    lli n; 
    cin >> n;
    vll a(n); 
    rep(i, n) cin >> a[i];
    DBG_COUT(cout << "Test: " << a << endl);

    // La estrategia que seguirá Bob es la siguiente:
    // - Si todos son pares no puede hacer nada
    // - Si existe algún impar lo pondrá en la segunda posición para que los pares se reduzcan lo menos posible a la vez
    // - Repite hasta el final

    // Entonces, el problema lo podemos reducir a:
    // Tengo un array de n elementos. Yo al principio puedo hacer la operación de coste 1 de sumar 1 a cualquier elemento de la lista. Luego empieza la siguiente simulación:
    // - Si todos los elementos son pares, divide entre 2 todos los elementos por coste 1
    // - Si existen elementos pares y elementos impares, selecciona un elemento par y dividelo entre 2 por coste 1.
    // - Si solo existen números impares, resta 1 a dicho elemento por coste 1
    // - Si en algún momento hay algún 0 en la lista, borralo de esta.
    // ¿Cual es el coste mínimo para llegar a la lista vacia? 

    // En primer lugar, que pasaría si no todos los elementos fueran pares,
    // pues podemos calcular los turnos como sum(popcount(a[i]) + bits(a[i]) - 1) donde popcount son los bits establecidos a 1 y bits el número de bits de nuestro número
    // Ya solo nos queda calcular cuantas veces conviene hacer la primera operación.
    // Digamos que k es el número de veces que lo vamos a hacer. Podemos saber tambien que hay números 
    // Al final, queremos reducir el coste individual de cada elemento trás las operaciones
    // Como a[i] <= 1e6, resulta que el coste individual máximo es 33, por lo que como mucho podemos ahorrarnos 32 de coste.
    // Esto significa que cada elemento de b[i] (el primer múltiplo de 2^k mayor o igual a a[i]) solo tiene sentido incrementarlo como mucho 32 veces y por lo tanto solo estos números deben ser considerados.


    lli solGlobal = INF; // Inicializado con un "infinito" seguro para long long
    for (lli k = 0; k < 18; k++){
        lli sol = getCost(a, k);
        
        DBG_COUT(cout << "Sol para k = " << k << ": " << sol << endl);
        solGlobal = min(solGlobal, sol);
    }
    DBG_COUT(cout << "Solucion: ");
    cout << solGlobal << endl;

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

// https://codeforces.com/contest/2246/problem/D