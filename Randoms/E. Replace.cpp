#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
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

#define div 100001L
struct Index {
    int l, r;
    Index(int l=0, int r=0) : l(l), r(r) {}
    Index(lli num) : l((int)(num / div)), r((int)(num % div)) {}
    lli get() const {
        return 1LL * l * div + r;
    }
};

template <typename T>
struct SparseTable {
    vector<int> lg;
    vector<vector<T>> st;
    function<bool(const T&, const T&)> better;

    SparseTable() = default;
    SparseTable(const vector<T>& a,
                function<bool(const T&, const T&)> f = [](const T& x, const T& y) {
                    return x < y; // Criterio por defecto
                }): better(f) { build(a); }

    T pick(const T& x, const T& y) const { return better(x, y) ? y : x; }

    void build(const vector<T>& a) {
        int n = (int)a.size();
        if (!n) return;
        int K = __lg(n) + 1;
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        st.assign(K, vector<T>(n));
        st[0] = a;
        for (int k = 1; k < K; k++) for (int i = 0; i + (1 << k) <= n; i++)
            st[k][i] = pick(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
    }

    T query(int l, int r) const {
        int k = lg[r - l + 1];
        return pick(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
// -------------------------------------------

struct GraphReachability {
    int n, K;
    vector<SparseTable<int>> stL, stR;

    GraphReachability(int _n, const vi& initL, const vi& initR) : n(_n), K(18), stL(K), stR(K) {
        auto min_cmp = [](const int& x, const int& y) { return x > y; };
        auto max_cmp = [](const int& x, const int& y) { return x < y; };
        vi curL = initL, curR = initR;
        stL[0] = SparseTable<int>(curL, min_cmp);
        stR[0] = SparseTable<int>(curR, max_cmp);
        for (int j = 1; j < K; j++) {
            vi nextL(n), nextR(n);
            for (int i = 0; i < n; i++) {
                if (curL[i] > curR[i]) nextL[i] = n, nextR[i] = -1;
                else nextL[i] = stL[j - 1].query(curL[i], curR[i]), nextR[i] = stR[j - 1].query(curL[i], curR[i]);
            }
            stL[j] = SparseTable<int>(nextL, min_cmp);
            stR[j] = SparseTable<int>(nextR, max_cmp);
            curL.swap(nextL); curR.swap(nextR);
        }
    }

    pii jump(int j, int l, int r) const {
        if (l > r) return {n, -1};
        return {stL[j].query(l, r), stR[j].query(l, r)};
    }

    int query(int l, int r) const {
        if (l == 0 && r == n - 1) return 0;
        int steps = 0;
        for (int j = K - 1; j >= 0; j--) {
            auto [nl, nr] = jump(j, l, r);
            if (nl > 0 || nr < n - 1) l = nl, r = nr, steps += (1 << j);
        }
        auto [fl, fr] = jump(0, l, r);
        return (fl == 0 && fr == n - 1) ? steps + 1 : -1;
    }
};

int solve() {
    // Code aquí
    int n, q;
    cin >> n >> q;
    vi a(n); for (int i = 0; i<n; i++) cin >> a[i];
    
    vector<int> initL(n-1);
    vector<int> initR(n-1);
    for (int i = 1; i<n; i++){
        initL[i-1] = min(a[i], a[i-1])-1;
        initR[i-1] = max(a[i], a[i-1])-2;
    }
    GraphReachability solver(n-1, initL, initR);

    int l, r;
    while(q--){
        cin >> l >> r;
        if (n == 1) cout << 0 << '\n';
        else if (l == r) cout << -1 << '\n';
        else cout << solver.query(l-1, r-2) << '\n';
    }
    
    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    solve();
    return 0;
}

// https://codeforces.com/contest/1707/problem/E