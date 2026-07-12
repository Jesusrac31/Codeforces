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
    string a, b; cin >> a >> b;

    // Si l es una longitud de a y b tal que a = b, si l puede ser x, tambien puede ser x-1
    // Solo hay solución entonces si ambas sumas mod 10 son iguales
    // Si partimos de la solución l=1, podemos comprobar en O(n^2) todas las posibles soluciones l=2
    // Esto equivale a buscar dos puntos por donde partir cada string
    // Realmente, con confirmar que el primero de los números al partir coinciden, sabemos que el segundo tambien
    // De esta forma, buscamos la mayor cantidad de cortes
    // Vamos a representarlo como un grafo bipartito de |a|+|b| nodos
    // Si hacemos un bipartite matching sería una respuesta aproximada, porque nos falta por tener en cuenta que
    // Si disponemos los nodos en orden las aristas no se entrecruzan

    // Para esto, define dp[i][j] como la máxima cantidad de emparejamientos hasta los nodos i y j de cada grupo
    // dp[0][0] = 0
    // dp[i][j] si la arista i, j existe es dp[i-1][j-1] + 1
    // dp[i][j] si la arista no existe es max(dp[i-1][j], dp[i][j-1])

    vi valuesA(a.size()+1);
    for (int i = 0; i<a.size(); i++)
        valuesA[i+1] = (valuesA[i] + (a[i] - '0')) % 10;
    
    vi valuesB(b.size()+1);
    for (int i = 0; i<b.size(); i++)
        valuesB[i+1] = (valuesB[i] + (b[i] - '0')) % 10;

    if (valuesA.back() != valuesB.back()){
        cout << -1 << endl;
        return 0;
    }

    int n = a.size(), m = b.size();
    vector<vector<bool>> matrixAdj (n+1, vector<bool>(m+1, false));
    for (int i = 1; i<valuesA.size(); i++){
        for (int j = 1; j<valuesB.size(); j++){
            if (valuesA[i] == valuesB[j]){
                matrixAdj[i][j] = true;
            }
        }
    }
    DBG_COUT(cout << valuesA << endl);
    DBG_COUT(cout << valuesB << endl);
    DBG_COUT(cout << matrixAdj << endl);

    vector<vi> dp (n+1, vi(m+1, 0));
    for (int i = 1; i<=n; i++){
        for (int j = 1; j<=m; j++){
            if (matrixAdj[i][j]) dp[i][j] = dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    cout << dp[n][m] << endl;
    

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

// https://codeforces.com/contest/2242/problem/D