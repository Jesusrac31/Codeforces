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
#define MAX_VAL 200001
double pi = 2*acos(0.0);

static inline long long c2(long long x) {
    return x * (x - 1) / 2;
}

struct SegTree {
    // Para cada posición i mantenemos:
    // - cntActive: si i está activo (o suma en un segmento)
    // - rLeaf(i): R_i = #puntos activos en (i, i+d]
    // - sumRActive: suma de R_i solo para i activos (base para los deltas de respuesta)
    int n;
    vector<int> cntActive;
    vector<long long> sumRActive;
    vector<int> lazy;
    vector<int> rLeaf;

    SegTree(int n): n(n), cntActive(4 * n + 5, 0), sumRActive(4 * n + 5, 0), lazy(4 * n + 5, 0), rLeaf(4 * n + 5, 0) {}

    void apply(int node, int l, int r, int val) {
        // Si a todos los R_i del segmento les sumamos val, la suma sobre activos aumenta val * (#activos).
        sumRActive[node] += 1LL * val * cntActive[node];
        if (l == r) {
            rLeaf[node] += val;
        } else {
            // Marcamos actualización diferida para bajar luego a hijos (lazy propagation).
            lazy[node] += val;
        }
    }

    void push(int node, int l, int r) {
        if (lazy[node] == 0 || l == r) return;
        int m = (l + r) >> 1;
        apply(node << 1, l, m, lazy[node]);
        apply(node << 1 | 1, m + 1, r, lazy[node]);
        lazy[node] = 0;
    }

    void pull(int node) {
        cntActive[node] = cntActive[node << 1] + cntActive[node << 1 | 1];
        sumRActive[node] = sumRActive[node << 1] + sumRActive[node << 1 | 1];
    }

    void rangeAdd(int node, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            apply(node, l, r, val);
            return;
        }
        push(node, l, r);
        int m = (l + r) >> 1;
        rangeAdd(node << 1, l, m, ql, qr, val);
        rangeAdd(node << 1 | 1, m + 1, r, ql, qr, val);
        pull(node);
    }

    long long querySum(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return sumRActive[node];
        push(node, l, r);
        int m = (l + r) >> 1;
        return querySum(node << 1, l, m, ql, qr) + querySum(node << 1 | 1, m + 1, r, ql, qr);
    }

    int queryCnt(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return cntActive[node];
        push(node, l, r);
        int m = (l + r) >> 1;
        return queryCnt(node << 1, l, m, ql, qr) + queryCnt(node << 1 | 1, m + 1, r, ql, qr);
    }

    int getR(int node, int l, int r, int pos) {
        if (l == r) return rLeaf[node];
        push(node, l, r);
        int m = (l + r) >> 1;
        if (pos <= m) return getR(node << 1, l, m, pos);
        return getR(node << 1 | 1, m + 1, r, pos);
    }

    void setActive(int node, int l, int r, int pos, int activeVal) {
        if (l == r) {
            cntActive[node] = activeVal;
            sumRActive[node] = activeVal ? rLeaf[node] : 0;
            return;
        }
        push(node, l, r);
        int m = (l + r) >> 1;
        if (pos <= m) setActive(node << 1, l, m, pos, activeVal);
        else setActive(node << 1 | 1, m + 1, r, pos, activeVal);
        pull(node);
    }
};

int solve() {
    int q, d;
    cin >> q >> d;

    SegTree st(MAX_VAL);
    vector<char> active(MAX_VAL + 1, 0);

    // Invariante global:
    // ans = sum_{i activo} C(R_i, 2), donde R_i = #puntos activos en (i, i+d].
    // Cada triple bonito (i<j<k y k-i<=d) se cuenta exactamente una vez por su mínimo i.
    long long ans = 0;

    for (int qi = 0; qi < q; ++qi) {
        int x;
        cin >> x;

        int L = max(1, x - d);
        int R = x - 1;

        if (!active[x]) {
            long long sumR = 0;
            // Para i en [x-d, x-1], al insertar x se cumple i < x <= i+d, luego R_i += 1.
            if (L <= R) sumR = st.querySum(1, 1, MAX_VAL, L, R);

            // R_x antes de activar x: puntos en (x, x+d].
            int rx = st.getR(1, 1, MAX_VAL, x);

            // Delta por i en [L,R]: C(R_i+1,2)-C(R_i,2)=R_i => suma de R_i.
            ans += sumR;
            // Delta por i=x al activarlo: añade C(R_x,2).
            ans += c2(rx);

            if (L <= R) st.rangeAdd(1, 1, MAX_VAL, L, R, +1);
            st.setActive(1, 1, MAX_VAL, x, 1);
            active[x] = 1;
        } else {
            long long sumR = 0;
            int cnt = 0;
            if (L <= R) {
                sumR = st.querySum(1, 1, MAX_VAL, L, R);
                cnt = st.queryCnt(1, 1, MAX_VAL, L, R);
            }

            int rx = st.getR(1, 1, MAX_VAL, x);

            // Si quitamos x, para i en [L,R]: R_i' = R_i-1
            // C(R_i,2)-C(R_i-1,2)=R_i-1 => restamos sum(R_i-1)=sumR-cnt.
            ans -= (sumR - cnt);
            // Quitamos la contribución de i=x, que deja de estar activo.
            ans -= c2(rx);

            if (L <= R) st.rangeAdd(1, 1, MAX_VAL, L, R, -1);
            st.setActive(1, 1, MAX_VAL, x, 0);
            active[x] = 0;
        }

        cout << ans << endl;
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

// https://codeforces.com/contest/1701/problem/F