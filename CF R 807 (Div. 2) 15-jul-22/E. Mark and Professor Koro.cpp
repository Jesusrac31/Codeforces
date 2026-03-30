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
#define MAX_EL 400000
#define EXTRA_BITS 60
double pi = 2*acos(0.0);

struct Node {
    int value;
    Node (int n = 0) { value = n; }
};

class LazySegTree {
    vector<Node> st;
    vector<int> lz;
    int n;

public:
    LazySegTree(const vector<int>& data) {
        n = (int)data.size();
        st.assign(4 * n, Node());
        lz.assign(4 * n, -1);
        build(data, 1, 0, n - 1);
    }
    void range_assign(int l, int r, int val) {
        if (l > r) return;
        range_assign(1, 0, n - 1, l, r, val);
    }
    int find_first(int l, int val) {
        return find_first(1, 0, n - 1, l, val);
    }
    int max_one() {
        if (st[1].value == 0) return -1;
        return find_last_one(1, 0, n - 1);
    }

private:
    Node convert(int x) {
        // Custom: construir Node desde un valor
        return Node(x);
    }

    Node combine(const Node& a, const Node& b) {
        // Custom: combinar dos nodos (por ejemplo, suma de unos)
        return Node(a.value + b.value);
    }

    void apply(int p, int l, int r, int val) {
        // Custom: aplicar asignacion de rango a este nodo
        st[p].value = val ? (r - l + 1) : 0;
        lz[p] = val;
    }

    void push(int p, int l, int r) {
        if (lz[p] == -1 || l == r) return;
        int m = (l + r) >> 1;
        apply(p << 1, l, m, lz[p]);
        apply(p << 1 | 1, m + 1, r, lz[p]);
        lz[p] = -1;
    }

    void pull(int p) {
        st[p] = combine(st[p << 1], st[p << 1 | 1]);
    }

    void build(const vector<int>& data, int p, int l, int r) {
        if (l == r) {
            st[p] = convert(data[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(data, p << 1, l, m);
        build(data, p << 1 | 1, m + 1, r);
        pull(p);
    }

    void range_assign(int p, int l, int r, int ql, int qr, int val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, val);
            return;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        range_assign(p << 1, l, m, ql, qr, val);
        range_assign(p << 1 | 1, m + 1, r, ql, qr, val);
        pull(p);
    }

    int find_first(int p, int l, int r, int ql, int val) {
        if (r < ql) return -1;
        int zeros = (r - l + 1) - st[p].value;
        if (val == 1 && st[p].value == 0) return -1;
        if (val == 0 && zeros == 0) return -1;
        if (l == r) return l;
        push(p, l, r);
        int m = (l + r) >> 1;
        int left = find_first(p << 1, l, m, ql, val);
        if (left != -1) return left;
        return find_first(p << 1 | 1, m + 1, r, ql, val);
    }

    int find_last_one(int p, int l, int r) {
        if (st[p].value == 0) return -1;
        if (l == r) return l;
        push(p, l, r);
        int m = (l + r) >> 1;
        if (st[p << 1 | 1].value > 0) return find_last_one(p << 1 | 1, m + 1, r);
        return find_last_one(p << 1, l, m);
    }
};

int solve() {
    // Code aquí
    int n, q; cin >> n >> q;
    vi a(n); for (int i = 0; i<n; i++) cin >> a[i];

    const int MAXN = MAX_EL + EXTRA_BITS;
    vi cnt(MAXN, 0);
    for (int i = 0; i < n; i++) cnt[a[i]]++;
    for (int i = 0; i + 1 < MAXN; i++) {
        if (cnt[i] >= 2) {
            cnt[i + 1] += cnt[i] / 2;
            cnt[i] &= 1;
        }
    }
    vi bits(MAXN, 0);
    for (int i = 0; i < MAXN; i++) bits[i] = cnt[i] & 1;

    LazySegTree seg(bits);
    int k, l;
    while(q--){
        cin >> k >> l; 
        k--;
        int add_pos = seg.find_first(l, 0);
        if (add_pos != -1) {
            if (add_pos > l) seg.range_assign(l, add_pos - 1, 0);
            seg.range_assign(add_pos, add_pos, 1);
        }

        int rem_pos = seg.find_first(a[k], 1);
        if (rem_pos != -1) {
            if (rem_pos > a[k]) seg.range_assign(a[k], rem_pos - 1, 1);
            seg.range_assign(rem_pos, rem_pos, 0);
        }

        cout << seg.max_one() << endl;
        a[k] = l;
    }

    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int T;
    solve();
    return 0;
}

// https://codeforces.com/contest/1705/problem/E