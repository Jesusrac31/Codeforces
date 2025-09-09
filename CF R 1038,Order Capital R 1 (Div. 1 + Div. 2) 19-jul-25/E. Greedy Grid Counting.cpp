#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#include<unordered_set>
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
    bool operator<(const Mint& o) const {return v < o.v;}
    bool operator>(const Mint& o) const {return v > o.v;}
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
istream& operator>>(std::istream& input, Mint& p) {
    input >> p.v;
    return input;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const Mint& m) {
    os << m.v << " ";
    return os;
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

int relu(int a){
    if (a<0){
        return 0;
    }
    return a;
}

#define INF INT_MAX
#define up first
#define down second

int solve() {
    // Input
    int n, k;
    cin >> n >> k;
    vector<pii> a(n);
    rep(i, n) cin >> a[i].up;
    rep(i, n) cin >> a[i].down;
    vector<unordered_map<int, Mint>> c(n-1);
    for (int i = 0; i<n-1; i++){
        if (a[i+1].up == -1 && a[i].down == -1){
            for (int j1 = 1; j1<=k; j1++){
                for (int j2 = 1; j2<=k; j2++){
                    c[i][j1-j2]+=1;
                }
            }
        } else if (a[i+1].up != -1 && a[i].down == -1){
            for (int j1 = 1; j1<=k; j1++){
                c[i][a[i+1].up-j1]+=1;
            }
        } else if (a[i+1].up == -1 && a[i].down != -1){
            for (int j1 = 1; j1<=k; j1++){
                c[i][j1-a[i].down]+=1;
            }
        } else {
            c[i][a[i+1].up-a[i].down]+=1;
        }
    }
    
    vector<unordered_map<int, Mint>> dp(n);
    dp[0][0] = 1;
    bool first = true;
    for (int i = 1; i<n; i++){
        for (auto it:c[i-1]){
            if (it.first >= 0){
                for (auto j:dp[i-1]){
                    if (j.first+it.first <= 0){
                        dp[i][j.first+it.first+first] += j.second*it.second;
                    } else {
                        if (j.first > 0 || first){
                            dp[i][1] += j.second*it.second;
                        }
                    }
                }
            } else {
                for (auto j:dp[i-1]){
                    dp[i][it.first] += j.second*it.second;
                }
            }
        }
        first = false;
    }

    Mint sol = 0;
    for (auto i:dp.back()){
        sol += i.second;
    }
    if (a.back().down == -1){
        sol *= k;
    }
    if (a[0].up == -1){
        sol *= k;
    }
    cout << sol << endl;
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

