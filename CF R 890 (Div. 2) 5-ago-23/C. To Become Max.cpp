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

#define INF -1
double pi = 2*acos(0.0);
#define int lli
#define vi vll

// Persistent segment tree over prefix b[i] = a[i] + i
// Stores count and sum of b values to query cost in a subarray.
struct PST {
    struct Node {
        int l;
        int r;
        long long sum;
        long long cnt;
        Node() : l(0), r(0), sum(0), cnt(0) {}
    };

    int n;
    vector<Node> st;
    vector<int> root;

    // Create an empty tree with coordinate size n.
    explicit PST(int n_) : n(n_) {
        st.reserve(n_ * 20);
        st.push_back(Node());
        root.clear();
    }

    // Insert one value (val) at position pos, returning new version root.
    int update(int prev, int l, int r, int pos, long long val) {
        int cur = (int)st.size();
        st.push_back(st[prev]);
        st[cur].sum += val;
        st[cur].cnt += 1;
        if (l != r) {
            int m = (l + r) >> 1;
            if (pos <= m) st[cur].l = update(st[prev].l, l, m, pos, val);
            else st[cur].r = update(st[prev].r, m + 1, r, pos, val);
        }
        return cur;
    }

    // Query count and sum of elements with index <= q in a prefix range.
    pair<long long, long long> query(int nodeR, int nodeL, int l, int r, int q) {
        if (q <= 0  || nodeR == nodeL) return {0, 0};
        if (r <= q) {
            return {st[nodeR].sum - st[nodeL].sum, st[nodeR].cnt - st[nodeL].cnt};
        }
        int m = (l + r) >> 1;
        auto left = query(st[nodeR].l, st[nodeL].l, l, m, q);
        if (q <= m) return left;
        auto right = query(st[nodeR].r, st[nodeL].r, m + 1, r, q);
        return {left.first + right.first, left.second + right.second};
    }
};

int solve(){
    int n; long long k; cin >> n >> k;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Transform to b[i] = a[i] + i to model rightward constraint.
    vector<long long> b(n + 1);
    vector<long long> vals;
    vals.reserve(n);
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] + i;
        vals.push_back(b[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    // Build persistent segment trees for prefix ranges of b.
    PST pst((int)vals.size());
    pst.root.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        int pos = (int)(lower_bound(vals.begin(), vals.end(), b[i]) - vals.begin()) + 1;
        pst.root[i] = pst.update(pst.root[i - 1], 1, (int)vals.size(), pos, b[i]);
    }

    // Sparse table for range maximum of b to find first support index.
    vector<int> lg(n + 1, 0);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    int K = lg[n] + 1;
    vector<vector<long long>> stMax(K, vector<long long>(n + 1, LLONG_MIN));
    for (int i = 1; i <= n; i++) stMax[0][i] = b[i];
    for (int k2 = 1; k2 < K; k2++) {
        int len = 1 << k2;
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= n; i++) {
            stMax[k2][i] = max(stMax[k2 - 1][i], stMax[k2 - 1][i + half]);
        }
    }
    auto rangeMax = [&](int l, int r) {
        if (l > r) return LLONG_MIN;
        int k2 = lg[r - l + 1];
        return max(stMax[k2][l], stMax[k2][r - (1 << k2) + 1]);
    };

    long long maxA = *max_element(a.begin() + 1, a.end());

    // Feasibility check for a target x.
    auto can = [&](long long x) {
        for (int i = 1; i <= n; i++) {
            // Need to raise a[i..r-1] to reach x with slope -1.
            long long T = x + i;
            if (b[i] >= T) return true;
            if (rangeMax(i, n) < T) continue;

            // Find first r where b[r] >= T (support point).
            int lo = i, hi = n, r = n;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (rangeMax(i, mid) >= T) {
                    r = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }

            int rCost = r - 1;
            if (rCost < i) return true;

            // Cost = sum of (T - b[j]) for all b[j] < T in [i, r-1].
            int idx = (int)(lower_bound(vals.begin(), vals.end(), T) - vals.begin());
            if (idx <= 0) return true;
            auto res = pst.query(pst.root[rCost], pst.root[i - 1], 1, (int)vals.size(), idx);
            long long sum = res.first;
            long long cnt = res.second;
            long long cost = T * cnt - sum;
            if (cost <= k) return true;
        }
        return false;
    };

    // Binary search for the maximum achievable value.
    long long lo = maxA, hi = maxA + k + 1, ans = maxA;
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        if (can(mid)) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    cout << ans << endl;
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

// https://codeforces.com/contest/1856/problem/C