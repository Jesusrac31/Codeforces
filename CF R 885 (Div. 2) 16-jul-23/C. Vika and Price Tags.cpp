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

int getT(int a, int b){
    if (a == 0) return 0;
    if (b == 0) return 1;
    int ops = 0;
    int r = a%b;
    int c = a/b;
    int extra; // Actualiza el número de operaciones en este caso
    int newA;
    int newB;
    if (r == 0) { 
        DBG_COUT(cout << "Returing last: " << (2+((c+1)&1) + (((c+1)/2)*3)-3) << endl);
        extra = 2+((c+1)&1);
        return (((c+1)/2)*3)-3+extra;
    } else if (c == 0) {
        DBG_COUT(cout << "Ops, bigger\n");
        newA = b-a;
        newB = a;
        extra = 2;
    } else {
        extra = 2*((c+1)&1)+1;
        extra += ((c/2)*3);
        if (c&1){
            newA = b;
            newB = r;
        } else {
            newA = r;
            newB = b;
        }
    }
    DBG_COUT(cout << "Op with " << a << " " << b << " Extra: " << extra << " newA and newB: " << newA << " " << newB << endl);
    ops = extra + getT(newA, newB); // Haz la siguiente etapa
    return ops;
}

int solve() {
    // Code aquí
    int n; cin >> n;
    vi a(n), b(n); rep(i, n) cin >> a[i]; rep(i, n) cin >> b[i];
    DBG_COUT(cout << "Test: " << n << "\n" << a << endl << b << endl);
    int sol = -1;
    int tAct;
    rep(i,n){
        DBG_COUT(cout << "Cycle " << i << " Values: " << a[i] << " " << b[i] << endl);
    
        if (a[i] == 0 && b[i] == 0) continue;
        else if (a[i] == 0 && b[i] != 0) tAct = 0;
        else if (a[i] != 0 && b[i] == 0) tAct = 1;
        else {DBG_COUT(cout << "Starting Calculations:\n"); tAct = getT(a[i], b[i]) % 3;}
        DBG_COUT(cout << "Result :" << tAct << endl);
        if (sol == -1 || sol == tAct) sol = tAct;
        else {cout << "NO" << endl; return 0;}
    }
    cout << "YES" << endl;

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

// https://codeforces.com/contest/1848/problem/C