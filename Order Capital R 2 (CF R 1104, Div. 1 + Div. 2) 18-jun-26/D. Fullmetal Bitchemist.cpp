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
#define int lli
double pi = 2*acos(0.0);

int solve() {
    // Code aquí
    int n; cin >> n;
    string s; cin >> s;

    // En primer lugar, necesitamos una condición para que un array sea válido
    // Si el array no puede tener todos los bits igual al mismo número, entonces no es válido
    // Para obtener todos los bits al mismo valor (ej. 0) Primero compacta todas las parejas que tengan dos 1s como 0s
    // Ahora, tengo varias posiciones donde aparecen un 1 rodeado de dos 0s, tenemos varios casos:
    // - En alguno de los lados tiene dos 0s seguidos: Entonces compacta los dos 0s en un 1 y los dos 1s en un 0
    // - Ninguno de los lados tiene dos 0s seguidos: Entonces tienes una estructura del estilo ...10101..., si algún 1 del borde puedes transformarlos en 0, también podrás el del medio y el del otro lado
    // De esta forma, deducimos que existe una familia de secuencias que no son válidas,
    // estas son las que alternan en cada posición un 1 y un 0 (...01010101010...). Digamos que toda secuencia de esta familia y con tamaño mayor o igual a 2 son secuencias malas
    // Ahora, buscamos el segundo caso, ya que no siempre que tenemos todos los bits con mismo valor
    // Si tengo la secuencia 0000, esta se puede ver reducida a 0, por lo que con la secuencia con todos los bits al mismo valor,
    // buscamos que la longitud mod 3 sea 1 o -1, ya que si fuera -1, puedo aplicar lo mismo pero el resultado final sería 1.
    // Esto aplica tambien a la inversa naturalmente, por lo que una secuencia tambien es mala si el la longitud final mod 3 es 0
    // Resulta que esto es equivalente a interpretar el balance mod 3. Define el balance como = Cantidad de 1s - Cantidad de 0s
    // - Cuando todos los bits tengan el mismo valor, la longitud de la secuencia es el balance el valor absoluto, por lo que en lo que nos incumbe no afecta
    // - Cuando transformo 11 en 0, el balance cambia en -3, por lo que su valor mod 3 no cambia
    // - Cuando transformo 00 en 1, el balance cambia en 3, por lo que su valor mod 3 no cambia
    // De esta forma, cualquier subsecuencia cuyo balance sea 0 mod 3 es mala

    // Para contar cuantas subsecuencias son buenas, calcularemos las que son malas y se la restaremos a las totales que son n*(n + 1) / 2.
    
    // En primer lugar, definimos las secuencias como (l, r). Esto representa el substring que empieza en el bit en la posición l y termina en el bit de la posición r (incluyendo l y r)
    // Si (l, r) es mala, (l+x, r-y) tambien es mala para 0 <= l+x < r-y <= n ya que si te das cuenta, pertenecen a la misma familia
    // Entonces, si existe una subsecuencia mala (l, r) pero (l-1, r) y (l, r+1) no son malas, entonces llamamos a esta secuencia un bloque malo con tamaño r-l+1
    // Un bloque malo contiene entonces (r-l+1)(r-l)/2 subsecuencias malas
    // Como el balance de este tipo de secuencias es la longitud de la secuencia mod 2, solo queremos contar las impares,
    // Así que un bloque malo realmente contiene: floor((r-l)/2) * (floor((r-l)/2)+1) - floor((r-l)/2) * ((r-l+1) mod 2)

    // El problema ahora se reduce a contar cuantos bloques malos hay, esto se puede hacer rápidamente con un sliding window de O(n)

    // Si quisieramos calcular la el balance de la subsecuencia (l, r), basta con hacer el balance de r menos el balance de l-1
    // De esta forma, sabemos que todos los rangos donde el balance de l y de r sean iguales.

    int l = 0, r = 1;
    char lastBit = s[0];
    vector<pii> ranges;
    for (; r<n; r++){
        if (lastBit == s[r]){
            // La secuencia deja de ser mala
            if (r - l > 1) ranges.PB(pii(l, r-1));
            l = r;
        }
        lastBit = s[r];
    }
    if (r - l > 1) ranges.PB(pii(l, r-1));

    DBG_COUT(cout << "Bloques malos: " << endl; for (auto x:ranges) cout << "( " << x.first << ", " << x.second << ") " << endl);
    int sol = n*(n+1)/2;
    // Secuencias malas por ...101010...
    for (auto x:ranges) sol -= (int)((x.second-x.first)/2) * ((int)((x.second-x.first)/2)+1) - (int)((x.second-x.first)/2) * ((x.second-x.first+1) % 2);

    // Balance
    vi b(n+1);
    for (int i = 1; i<=n; i++){
        if (s[i-1] == '0') b[i] = (b[i-1] - 1 + 3) % 3;
        else  b[i] = (b[i-1] + 1) % 3;
    }

    // Secuencias malas por balance 0
    int balance0 = 0, balance1 = 0, balance2 = 0;
    for (int i = 0; i<=n; i++){
        if (b[i] == 0) balance0++;
        else if (b[i] == 1) balance1++;
        else balance2++;
    }
    DBG_COUT(cout << "Posibles balances 0: " << balance0 << endl);
    DBG_COUT(cout << "Posibles balances 1: " << balance1 << endl);
    DBG_COUT(cout << "Posibles balances 2: " << balance2 << endl);

    sol -= balance0*(balance0-1)/2;
    sol -= balance1*(balance1-1)/2;
    sol -= balance2*(balance2-1)/2;

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
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2237/problem/D