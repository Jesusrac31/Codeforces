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

const lli NEG = LLONG_MIN / 4;

/*
    Lazy Segment Tree adaptado a esta DP.

    Cambios respecto a tu estructura original:
    1. Node.value guarda el máximo del intervalo.
    2. lz guarda suma pendiente, no asignación.
    3. range_assign se sustituye por range_add.
    4. Se añade point_chmax.
    5. find_first no se usa en este problema.
*/

struct Node { 
    lli value; 
    Node(lli n = NEG): value(n) {} 
};

class LazySegTree {
    vector<Node> st;
    vector<lli> lz;
    int n;
public:
    LazySegTree(const vector<lli>& a) {
        n = (int)a.size();
        st.assign(4 * n, Node());
        lz.assign(4 * n, 0);
        build(a, 1, 0, n - 1);
    }
    void range_add(int l, int r, lli val) { 
        if (l <= r) range_add(1, 0, n - 1, l, r, val); 
    }
    void point_chmax(int pos, lli val) { // Modifica la posición pos al maximo entre val y su valor actual
        point_chmax(1, 0, n - 1, pos, val);
    }
    Node query(int l, int r) {
        if (l > r) return Node(NEG);
        return query(1, 0, n - 1, l, r);
    }
private:
    Node convert(lli x) { 
        return Node(x); 
    }
    Node combine(const Node& a, const Node& b) { 
        return Node(max(a.value, b.value)); 
    }
    void apply(int p, int l, int r, lli val) { 
        st[p].value += val; 
        lz[p] += val; 
    }
    void push(int p, int l, int r) { 
        if (lz[p] == 0 || l == r) return; 
        int m = (l + r) >> 1; 
        apply(p << 1, l, m, lz[p]); 
        apply(p << 1 | 1, m + 1, r, lz[p]); 
        lz[p] = 0; 
    }
    void pull(int p) { 
        st[p] = combine(st[p << 1], st[p << 1 | 1]); 
    }
    void build(const vector<lli>& a, int p, int l, int r) {
        if (l == r) { 
            st[p] = convert(a[l]); 
            return; 
        }
        int m = (l + r) >> 1; 
        build(a, p << 1, l, m); 
        build(a, p << 1 | 1, m + 1, r); 
        pull(p);
    }
    void range_add(int p, int l, int r, int ql, int qr, lli val) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { 
            apply(p, l, r, val); 
            return; 
        }
        push(p, l, r); 
        int m = (l + r) >> 1;
        range_add(p << 1, l, m, ql, qr, val); 
        range_add(p << 1 | 1, m + 1, r, ql, qr, val);
        pull(p);
    }

    void point_chmax(int p, int l, int r, int pos, lli val) {
        if (l == r) {
            st[p].value = max(st[p].value, val);
            return;
        }
        push(p, l, r);
        int m = (l + r) >> 1;
        if (pos <= m) point_chmax(p << 1, l, m, pos, val);
        else point_chmax(p << 1 | 1, m + 1, r, pos, val);
        pull(p);
    }
    Node query(int p, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return Node(NEG);
        if (ql <= l && r <= qr) return st[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        return combine(
            query(p << 1, l, m, ql, qr),
            query(p << 1 | 1, m + 1, r, ql, qr)
        );
    }
};

int solve() {
    int n;
    cin >> n;

    vll v(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    vi a(n), b(n);
    rep(i, n) cin >> a[i];
    rep(i, n) cin >> b[i];

    vi posB(n + 1);

    rep(i, n) {
        posB[b[i]] = i;
    }

    /*
        dp[m] = mejor valor procesando cierto prefijo de A.

        m representa:
        - 0: no he descartado todavía ningún objeto por B.
        - k + 1: el máximo posB descartado es k.

        Inicialmente:
        dp[0] = 0
        dp[1..n] = -infinito
    */

    vll dp(n + 1, NEG);
    dp[0] = 0;

    LazySegTree state(dp);

    DBG_COUT(
        cout << "Values: " << v << endl;
        cout << "Stack A: " << a << endl;
        cout << "Stack B: " << b << endl;
        cout << "Position in B: " << posB << endl;
    );

    for (int i = 0; i < n; i++) {
        int x = a[i];
        int q = posB[x];

        /*
            Antes de tocar nada, calculamos el mejor estado que puede descartar x.

            Si m <= q, podemos decidir no coger x en A, es decir, eliminarlo por B.
            Eso lleva el estado a q + 1.
        */
        lli best = state.query(0, q).value;

        /*
            Coger x desde A:
            Solo es compatible con estados m <= q.
            En todos esos estados sumamos v[x].
        */
        state.range_add(0, q, v[x]);

        /*
            No coger x desde A:
            Entonces x se extraerá por B.
            El nuevo máximo descartado pasa a ser q.
            En nuestra codificación eso es q + 1.
        */
        state.point_chmax(q + 1, best);

        DBG_COUT(
            cout << "Procesando objeto " << x << endl;
            cout << "posB = " << q << ", value = " << v[x] << ", best = " << best << endl;
            cout << "DP actual: ";
            for (int j = 0; j <= n; j++) {
                lli cur = state.query(j, j).value;
                if (cur <= NEG / 2) cout << "-INF ";
                else cout << cur << " ";
            }
            cout << endl;
        );
    }

    DBG_COUT(cout << "Solucion: ");
    cout << state.query(0, n).value << '\n';
    DBG_COUT(cout << "========================" << endl);

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
        solve();
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2150/problem/C