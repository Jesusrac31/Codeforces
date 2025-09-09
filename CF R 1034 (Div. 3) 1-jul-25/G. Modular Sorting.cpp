#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
#endif

using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
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

// Funciones vector
#define PB(a) push_back(a);

bool sort_func(int a, int b) {
    if (a > b) {
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

// Funciones map
#define F first;
#define S second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

// Imprime cualquier vector 
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]" << endl;
    return os;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::pair<T, T>& par) {
    os << "{ " << par.first << ", " << par.second << " }";
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
//#define MAXM 500001
#define MAXM 20

/*int counting = 0;

vi primos = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701};

void getFactorsOpt(int m, vi& factores){
    factores.emplace_back(1);
    factores.emplace_back(m);
    for (int i = 0; primos[i] < m; i++){
        for (int j = 1; m%primos[i]==0; j++){
            factores.emplace_back(primos[i]*j);
            m/=primos[i];
        }
    }
    ord(factores);
}*/

void getFactors(int m, vi& factores){
    for (int i = 1; i <= sqrt(m); ++i) {
        if (m % i == 0) {
            factores.emplace_back(i);
            if (i != m / i) { // Evitar duplicados si es un cuadrado perfecto
                factores.emplace_back(m / i);
            }
        }
    }
    ord(factores);
}

int solve() {
    // Code aquí
    int n, m, q;
    cin >> n >> m >> q;
    vi a(n);
    lee(n, a);

    vi factores;
    getFactors(m, factores);
    
    unordered_map<int, vector<int>> sols;
    unordered_map<int, int> turns;
    for (auto i:factores){
        int suma1 = 0, modulo1 = i;
        int ant1=0;
        turns[modulo1] = 0;
        sols[modulo1] = {0};
        for (int j = 0; j<n; j++){
            if ((a[j]%modulo1)+suma1 < ant1){
                suma1+=modulo1;
                turns[modulo1]++;
            }
            ant1 = (a[j]%modulo1)+suma1;
            sols[modulo1].emplace_back(a[j]%modulo1);
        }
        sols[modulo1].emplace_back(modulo1);
    }

    // Queries
    while (q--){
        int op, i, x, k;
        cin >> op;
        if (op == 1) {
            cin >> i >> x;
            for (auto it:factores){
                if (sols[it][i-1] > sols[it][i] && sols[it][i-1] <= (x%it)){
                    turns[it]--;
                } else if (sols[it][i-1] <= sols[it][i] && sols[it][i-1] > (x%it)){
                    turns[it]++;
                }
                if (sols[it][i+1] >= sols[it][i] && sols[it][i+1] < (x%it)){
                    turns[it]++;
                } else if (sols[it][i+1] < sols[it][i] && sols[it][i+1] >= (x%it)){
                    turns[it]--;
                }
                sols[it][i] = (x%it);
            }
        } else {
            cin >> k;
            int it = maximo_comun_divisor(m, k);
            if (turns[it] < m/it){
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }


    return 0;
}

int main() {
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
