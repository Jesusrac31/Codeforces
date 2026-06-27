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
    int n, m; cin >> n >> m;
    vi a(n); rep(i, n) cin >> a[i];
    DBG_COUT(cout << "Test: " << m << endl << a << endl);

    // Para este problema, empecemos planteando un algoritmo O(n^2) utilizando dp
    // Definimos dp[i][j] como el coste minimo en el cual podemos llegar a pintar el elemento i de color j
    // Tenemos dos casos:
    // 1. Si queremos pintarlo de color 1, podemos pintar todo lo de antes y luego pintar el intervalo que empezaría desde i.
    // En este caso, decimos que dp[i][1] = min(dp[i-1][j], j in 1..m) + (1 != a[i])
    // 2. Si queremos que el elemento i este pintado de color j > 1, el elemento i-1 debe estar pintado de color j-1.
    // Tambien aplica si el elemento i-1 está de color m, en ese caso la combinación sería pintar primero el intervalo con el elemento i, y luego el intervalo que termina en i-1
    // Esto significa que dp[i][j] = min(dp[i-1][j-1], dp[i-1][m]) + (j != a[i]) si j != 1
    
    // El resultado de esta solución sería dp[n][m] ya que debe terminar en el color m
    
    // Ahora, para optimizar el algoritmo, redefinimos un poco nuestra solución
    // Definimos dp[i][j] como el máximo de elementos que pueden mantener su valor para llegar a pintar el elemento i de color j
    // De esta forma:
    // dp[0][j] = 0
    // dp[i][1] = max(dp[i-1][j], j in 1..m) + (1 == a[i])
    // dp[i][j] = max(dp[i-1][j-1], dp[i-1][m]) + (j == a[i]) si j != 1

    // Con esta definición solo tenemos que sumar 1 a un valor en vez de sumarselos a todos
    // Sin embargo, aún no es suficiente. Este acercamiento nos permite observar que muchos valores se reciclan

    // Sabemos tambien que si dp[i][j] < dp[i][m], dp[i][j] no aporta nada, deberemos usar tan solo dp[i][m]
    
    // La idea de optimización completa sería la siguiente:
    // Manten los valores de dp[1][j] al principio.
    // dp[i][m] siempre será almacenado en una varible a parte
    // En cada paso, añade al principio de la lista el máximo entre todos los elementos (incluyendo dp[i][m])
    // Luego, elimina el último elemento
    // Al elemento dp[i+1][a[i+1]] = max(dp[i][m], dp[i][a[i+1]-1]) + 1
    // Con esto es suficiente actualización, el resto se actualizarán cuando sea necesario.

    // Último problema, no podemos añadir elementos al principio de una lista, borrarlos del final y modificar otros en O(1). 
    // Usando una lista, en vez de borrando estableciendo un corte e invirtiendo la lógica añadiendo así al final de la lista,
    // podemos hacer estas operaciones en O(1). La solución será el último elemento de la lista que corresponderá a dp[n+1][1]

    int start = 0;
    int lastEl = -INF;
    vi historial (m-1, -INF);
    int maximo = 0;

    for (int i = 0; i<n; i++){
        // Paso 1: Añade el máximo de la secuencia anterior:
        historial.PB(maximo);

        // Paso 2: Guarda lastEl para el paso 4
        int prevLastEl = lastEl;

        // Paso 3: Computa el nuevo lastEl incluyendo suma de 1 en caso de que a[i] == m
        lastEl = max(lastEl, historial[historial.size()-m]) + (a[i] == m);

        // Paso 4: Actualiza el elemento a[i] al máximo entre a[i] y lastEl. En caso de que a[i] == m, actualizaremos lastEl más adelante
        if (a[i] != m) historial[historial.size()-a[i]] = max(historial[historial.size()-a[i]], prevLastEl)+1;

        // Paso 5: Obten el nuevo maximo, tan solo comprueba el elemento a[i]
        if (a[i] == m) maximo = max(lastEl, maximo);
        else maximo = max(historial[historial.size()-a[i]], maximo);

        // Paso 6: Mueve el inicio un paso a la derecha
        start++;
        DBG_COUT(cout << "Historial: "; for (int i = historial.size()-1; i>=start; i--) cout << historial[i] << " "; cout << lastEl << endl;);
    }
    DBG_COUT(cout << "Last Element: " << lastEl << endl << "Solucion: ");
    cout << n-lastEl << endl;

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
        DBG_COUT(cout << "===========================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2237/problem/F