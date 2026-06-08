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
#define MAXN 100005
double pi = 2*acos(0.0);

int solve(int T) {
    // Code aquí
    int n, k; cin >> n >> k;
    int size = (1<<k)+1;
    pair<bitset<MAXN>, bitset<MAXN>> nums;
    string s;
    cin >> s; nums.first = bitset<MAXN>(s);
    cin >> s; nums.second = bitset<MAXN>(s);
    DBG_COUT(cout << "Test: " << n << " " << k << endl << nums.first << endl << nums.second << endl);

    // Por cada bit, según su combinación podemos deducir los siguiente. (Vamos a tratar los números como bits)
    // 1. Si la combinación es 0 0:
    //      No hay 1s
    // 2. Si la combinación es 1 0 y k es impar:
    //      Los 1s son aquellos números cuya posición i cumplan que i != 0 mod 3
    // 3. Si la combinación es 1 0 y k es par:
    //      Los 1s son aquellos números cuya posición i cumplan que i != 2 mod 3
    // 4. Si la combinación es 0 1:
    //      Los 1s son aquellos números cuya posición i cumplan que i != 1 mod 3
    // 5. Si la combinación es 1 1 y k es impar:
    //      Los 1s son aquellos números cuya posición i cumplan que i != 2 mod 3
    // 6. Si la combinación es 1 1 y k es par:
    //      Los 1s son aquellos números cuya posición i cumplan que i != 0 mod 3

    vector<lli> number1s(3, 0);
    vector<lli> number0s(3, 0);

    for (int i = 0; i<n; i++){
        bool bitInit = nums.first[i];
        bool bitEnd = nums.second[i];
        if (!bitInit && !bitEnd){ // 1
            number0s[0]++;
            number0s[1]++;
            number0s[2]++;
        } else if (bitInit && !bitEnd){
            if (k & 1){ // 2
                number0s[0]++;
                number1s[1]++;
                number1s[2]++;
            } else { // 3
                number1s[0]++;
                number1s[1]++;
                number0s[2]++;
            }
        } else if (!bitInit && bitEnd){ // 4
            number1s[0]++;
            number0s[1]++;
            number1s[2]++;
        } else {
            if (k & 1){ // 5
                number1s[0]++;
                number1s[1]++;
                number0s[2]++;
            } else { // 6
                number0s[0]++;
                number1s[1]++;
                number1s[2]++;
            }
        }
    }
    DBG_COUT(cout << "Counts of 1s: " << number1s << endl);
    DBG_COUT(cout << "Counts of 0s: " << number0s << endl);

    // Los números tienen que ser multiplicados según el número de veces que cumplan
    cout << number0s[0]*number1s[0]*((size)/3) + number0s[1]*number1s[1]*((size+2)/3) + number0s[2]*number1s[2]*((size+1)/3) << endl;


    DBG_COUT(cout << "======================================" << endl);
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
        solve(T);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2234/problem/D