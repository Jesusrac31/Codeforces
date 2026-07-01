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
    int n, d; cin >> n >> d;
    vll a(n); rep(i, n) cin >> a[i];

    // Para resolver este problema lo primero que observamos es como interactua seleccionar un vértice
    // Trabajaremos con índices mod n
    // En ese caso, seleccionar el vértice i añade al resultado sum(a[i] - a[j], j in i-d..i+d)
    // Podemos observar entonces que si a[i] es el valor más grande, sum(a[i] - a[j], j in i-d..i+d) >= 0, por lo que siempre es positivo
    // Al seleccionar un segundo elemento a[k], tenemos dos casos:
    // - abs(k-i) <= d -> Nos damos cuenta que tenemos que tener en cuenta que uno de los elementos con el que interactuaríamos es i
    // pero eso nos conviene, ya que ahora el vértice i recibe a[i]-a[k] menos de alegría, o lo que es lo mismo, estamos sumando a[k]-a[i]
    // - abs(k-i) > d -> En este caso, estos dos no interactuan y puedes añadir directamente sum(a[k] - a[j], j in k-d..k+d)
    // De esta forma, definimos S como el conjunto de vértices al que daremos regalo
    // Ahora buscamos maximizar sum(sum(a[i]-a[j], j in i-d..i+d), i in S) pudiendo cambiar los valores de S
    // Podemos simplificar un poco la función como sum((2*d+1) * a[i] - sum(a[j], j in i-d..i+d), i in S)
    // Podemos precalcular para cada valor de i sum(a[j], j in i-d..i+d), llamemosle add[i]:
    // sum(a[i] * (2*d+1) - add[i], i in S). Este valor lo podemos precomputar tambien por cada vértice. 
    // Finalmente, selecciona solo aquellas i tal que a[i] * (2*d+1) - add[i] sea positivo

    vll sumRange(n);
    for (int i = -d; i <= d; i++) sumRange[0] += a[(i+n)%n];
    
    for (int i = 1; i<n; i++)
        sumRange[i] = sumRange[i-1] + a[(i+d)%n] - a[(i-d-1+n)%n]; 
    
    DBG_COUT(cout << "Suma de cada rango: " << sumRange << endl);
    
    vll changeVersion(n);
    for (int i = 0; i<n; i++)
        changeVersion[i] = a[i] * (2*d+1) - sumRange[i];

    lli sol = 0;
    for (auto x:changeVersion) if (x >= 0) sol += x;

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
        DBG_COUT(cout << "=====================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2239/problem/B