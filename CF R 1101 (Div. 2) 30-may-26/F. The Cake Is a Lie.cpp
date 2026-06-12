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
#define SAMPLE 999999
double pi = 2*acos(0.0);
#define int lli

mt19937 rd(clock());

int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

int solve() {
    // Code aquí
    int n, a, b, k; cin >> n >> a >> b >> k;
    DBG_COUT(cout << "Test: " << n << " " << a << " " << b << " " << k << endl);
    
    // Tenemos que resolver el sistema de ecuaciones:
    // a * x[0] = k
    // a * x[1] + b * x[0] = k
    // a * x[2] + b * x[1] = k
    // etc.
    // a * x[i+1] + b * x[i] = k
    // etc.
    // a * x[n-1] + b * x[n-2] = k
    // Donde x[i] son enteros no negativos
    
    // En primer lugar, si k no es divisible por d = gcd(a, b), la respuesta es 0.
    // Por otro lado, para a = 1 y b = 1, la solución es n
    // El primer paso de nuestro algoritmo es tratar de satisfacer las primeras ecuaciones. Entonces, si decimos que vamos a cumplir las primeras m ecuaciones:
    // x[0] = k/a
    // x[1] = (k - b * x[0])/a
    // etc.
    // x[i+1] = (k - b * x[i])/a
    // etc.
    // x[m-1] = (k - b * x[m-2])/a
    
    // Una vez hecho eso, sabemos que la ecuación a * x[m] + b * x[m-1] = k no se cumple, por lo que las siguientes son independientes
    // Ahora tenemos en cuenta índices i >= m
    // La evolución de la secuencia podemos ver que es lineal ya que x[i+1] = k/a - b/a * x[i]
    // Generalizando, digamos que r = -b/a y c = k/a. Entonces x[i+1] = r * x[i] + c
    // r es negativo ya que tanto a como b son positivos. Entoces hay un punto donde la sucesión converge:
    // L = r * L + c -> L = c/(1 - r) = (k/a)/(1+b/a) = k/(a+b)
    // Luego, definimos e[i] como el error entre x[i] y L. Entonces e[i+1] = x[i+1]-L -> e[i+1] = (r * x[i] + c) - (r * L + c) -> e[i+1] = r*(x[i] - L) -> e[i+1] = r*e[i]
    // Entonces e[i] sigue una sucesión geométrica, por lo que x[i]-L = r^(i-m) (x[m]-L) [Recuerda que nuestro x[0] sería x[m]]
    // Si sustituimos: x[i] = (-b/a)^(i-m) * (x[m] - k/(a+b)) + k/(a+b) <-> x[i] = (-b/a)^(i-m) * x[m] + (1 - (-b/a)^(i-m)) * k/(a+b)
    // Ahora se trata de buscar el valor de i más grande tal que x[i] sea un entero no negativoy x[m] tampoco.
    
    // Para cumplir, volviendo a la definición recursiva, necesitamos que:
    // 1. k - b * x[i] >= 0 -> x[i] <= k/b
    // 2. b * x[i] = k mod a
    // Así que ahora hay múltiples casos que contemplar:
    // 1. i es infinito: Sucede si x[m] = L o si a = b. Esto es fácil de ver ya que r = -b/a, por lo que la pendiente sería -1 y entraría en bucle
    // 2. i es finito
    // E


    
    DBG_COUT(cout << "=========================================" << endl);

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

//Eliminar comentario si el proyecto está terminado (Dinámica empezó el 21/06/2024)