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

int getIndex(char c){
    return c-'A';
}

int solve() {
    // Code aquí
    int n, c, k; cin >> n >> c >> k;
    string s; cin >> s;

    // Cada grupo de k caracteres consecutivos, al menos uno de ellos tiene que ser un case, en caso contrario, no sería solución
    // Crea mascaras de 18 bits a partir de los substrings de longitud k indicando que al menos uno de esos caracteres aparece, 
    // llamalas m[i] siendo i el carácter donde empieza el substring para crear la máscara
    // Necesitas una mascara que al hacer la operación y con todos los m[i], ninguno sea 0. Llamemos a esa máscara sol, ¿qué posibles valores puede tomar?
    // Tiene como mucho 2^c posibles valores, identifiquemos cuales de esas combinaciones NO son válidas
    // Una combinación no es válida si al hacer la operación y con algún m[i] da 0
    // Esto es lo mismo a decir que sol es submáscara de ~m[i]
    // Ten en cuenta tambien que el último caracter de s SIEMPRE es un case
    // Ahora, dado un m[i], es fácil saber cuales son las máscaras que no son válidas

    unordered_set<int> masks;
    int mask = 0;
    vi presente(c, 0);
    for (int i = 0; i<n; i++){
        if (i >= k){
            masks.insert(mask);
            presente[getIndex(s[i])]++;
            mask |= (1 << getIndex(s[i]));
            presente[getIndex(s[i-k])]--;
            if (!presente[getIndex(s[i-k])]){
                mask &= ~(1 << getIndex(s[i-k]));
            }
        } else {
            presente[getIndex(s[i])]++;
            mask |= (1 << getIndex(s[i]));
        }
    }
    masks.insert(mask);
    masks.insert((1 << getIndex(s[n-1])));
    DBG_COUT(
        for (auto x:masks){
            cout << bitset<18>(x) << endl;
        }
    );
    int full = (1 << c) - 1;
    vector<int> exists(1 << c, 0);
    for (int current : masks) {
        exists[current] = 1;
    }

    // hasSubmask[mask] = 1 si existe alguna máscara de `masks` que sea submáscara de `mask`.
    // La DP propaga esa información desde cada estado hacia los superconjuntos que lo incluyen.
    // Basicamente si a es submascara de b y b es submascara de c, a es submascara de c, por lo que como solo buscamos que exista, no comprobamos b
    vector<int> hasSubmask = exists;
    for (int bit = 0; bit < c; ++bit) {
        for (int candidate = 0; candidate < (1 << c); ++candidate) {
            if (candidate & (1 << bit)) {
                hasSubmask[candidate] |= hasSubmask[candidate ^ (1 << bit)];
            }
        }
    }
    DBG_COUT(cout << hasSubmask << endl);

    int bestMask = 0;
    int bestBits = c + 1;
    for (int candidate = 0; candidate <= full; ++candidate) {
        // Si el complemento del candidato contiene alguna máscara original, entonces
        // existe una máscara de `masks` disjunta con él y no sirve.
        if (hasSubmask[full ^ candidate]) continue;
        int bits = __builtin_popcount((unsigned)candidate);
        if (bits < bestBits) {
            bestBits = bits;
            bestMask = candidate;
        }
    }
    DBG_COUT(cout << "Sol: " << bitset<18>(bestMask) << " -> ");
    cout << bestBits << endl;

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

// https://codeforces.com/contest/1995/problem/D