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

const int MOD = 1000000007; // Módulo del problema, cambiar en caso de no ser ese. NO TIENE PORQUÉ SER CONSTANTE, SOLO GLOBAL

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

template<typename A, typename Q> std::ostream& operator<<(std::ostream& os, const std::pair<A, Q>& p) {
    os << "{ " << p.first << ", " << p.second << " }";
    return os;
}

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

bool getBit(lli n, int k){
    return (n & (1L << (k-1)));
}

bool isPowerOfTwo(lli x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int floorLog2ll(lli x) {
    int lg = 0;
    while (x > 1) {
        x >>= 1;
        lg++;
    }
    return lg;
}

vector<Mint> factorial = {1};
Mint fact(int n){
    for (int i = factorial.size(); i<=n; i++){
        factorial.PB(factorial.back() * i);
    }
    return factorial[n];
}

Mint comb(lli n, lli k){
    if (n < k || k < 0 || n < 0) return 0;
    return (fact(n)*(fact(k)*fact(n-k)).inv());
}

lli pow(lli a, lli p) {
    lli res = 1;
    while (p > 0) {
        if (p & 1) res *= a;
        a *= a;
        p >>= 1;
    }
    return res;
}

// Obtiene cuantos subarrays existen en un array de tamaño n
Mint getAllSubArrays(lli n){
    return (((Mint(n+1)-1) * Mint(n+1))*(Mint(2).inv()));
}

struct Info {
    lli len;   // Longitud del bloque
    lli pref;  // Prefijo bueno más largo
    lli suff;  // Sufijo bueno más largo
    Mint ans;  // Subarrays k-good dentro del bloque
};

Info joinInfo(const Info& a, const Info& b) {
    Info c;
    c.len = a.len + b.len;
    c.pref = (a.pref == a.len ? a.len + b.pref : a.pref);
    c.suff = (b.suff == b.len ? b.len + a.suff : b.suff);
    c.ans = a.ans + b.ans + Mint(a.suff) * Mint(b.pref);
    return c;
}

// fullBlock(m, k): información para el bloque [0, 2^m - 1].
Info memo[61][62];
bool seen[61][62];

Info fullBlock(int m, int k) {
    if (k < 0) return { (1LL << m), 0, 0, 0 };
    if (k >= 60) {
        lli L = (1LL << m);
        return { L, L, L, getAllSubArrays(L) };
    }
    if (seen[m][k + 1]) return memo[m][k + 1];

    Info ret;
    if (m == 0) {
        ret = { 1, 1, 1, 1 }; // Solo el número 0
    } else {
        // [0..2^{m-1}-1]  +  [2^{m-1}..2^m-1]
        // segunda mitad equivale a popcount <= k-1 sobre m-1 bits.
        Info left = fullBlock(m - 1, k);
        Info right = fullBlock(m - 1, k - 1);
        ret = joinInfo(left, right);
    }

    seen[m][k + 1] = true;
    memo[m][k + 1] = ret;
    return ret;
}

// solvePrefix(n, k): información para el bloque [0, n-1].
Info solvePrefix(lli n, int k) {
    if (n == 0) return { 0, 0, 0, 0 };
    if (k < 0) return { n, 0, 0, 0 };
    if (k >= 60) return { n, n, n, getAllSubArrays(n) };

    int m = floorLog2ll(n);
    lli p = (1LL << m);
    if (n == p) return fullBlock(m, k);

    Info left = fullBlock(m, k);
    Info right = solvePrefix(n - p, k - 1);
    return joinInfo(left, right);
}

int solve() {
    // Code aquí
    lli n;
    int k;
    cin >> n >> k;
    DBG_COUT(cout << "Test: " << n << " " << k << endl);

    Info sol = solvePrefix(n, k);
    DBG_COUT(cout << "Solucion: ");
    cout << sol.ans << endl;

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

// https://codeforces.com/contest/1982/problem/E