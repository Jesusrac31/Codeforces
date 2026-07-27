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

#define INF 1e18
double pi = 2*acos(0.0);

template<typename T> struct Max {
    T neutral = -INF;
    T operator()(T x, T y) { return max(x, y); }
};
template<typename T> struct Sum {
    T neutral = 0;
    T operator()(T x, T y) { return (x + y); }
};

template <typename T, typename OpUpdate, typename OpQuery>
class LazySegTree {
    OpUpdate op_update; OpQuery op_query;
    vector<T> st;
    vector<T> lz;
    int n;
public:
    LazySegTree(const vector<T>& a){
        n = (int)a.size();
        st.assign(4 * n, op_query.neutral);
        lz.assign(4 * n, op_update.neutral);
        build(a, 1, 0, n - 1);
    }
    void update(int l, int r, lli val) { 
        update(l, r, val, 1, 0, n - 1); 
    }
    T query(int l, int r) {
        return query(l, r, 1, 0, n - 1);
    }
private:
    void push(int p, int l, int r) { 
        if (lz[p] == T(0) || l == r) return; 
        int m = (l + r) >> 1; 
        // Propagamos la actualización lazy a los hijos
        st[p << 1] = op_update(st[p << 1], lz[p]);
        lz[p << 1] = op_update(lz[p << 1], lz[p]);
        st[p << 1 | 1] = op_update(st[p << 1 | 1], lz[p]);
        lz[p << 1 | 1] = op_update(lz[p << 1 | 1], lz[p]);
        lz[p] = T(0); 
    }
    void build(const vector<T>& a, int p, int l, int r) {
        if (l == r) { 
            st[p] = T(a[l]); 
            return; 
        }
        int m = (l + r) >> 1; 
        build(a, p << 1, l, m); 
        build(a, p << 1 | 1, m + 1, r); 
        st[p] = op_query(st[p << 1], st[p << 1 | 1]); 
    }
    void update(int ql, int qr, T val, int p, int l, int r) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { 
            st[p] = op_update(st[p], val);
            lz[p] = op_update(lz[p], val);
            return; 
        }
        push(p, l, r); 
        int m = (l + r) >> 1;
        update(ql, qr, val, p << 1, l, m); 
        update(ql, qr, val, p << 1 | 1, m + 1, r);
        st[p] = op_query(st[p << 1], st[p << 1 | 1]); 
    }
    T query(int ql, int qr, int p, int l, int r) {
        if (qr < l || r < ql) return op_query.neutral;
        if (ql <= l && r <= qr) return st[p];
        push(p, l, r);
        int m = (l + r) >> 1;
        return op_query(
            query(ql, qr, p << 1, l, m),
            query(ql, qr, p << 1 | 1, m + 1, r)
        );
    }
};

int solve() {
    // Code aquí
    int n; cin >> n;

    vector<int> p(n + 1);
    vector<int> pos(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }

    // Usamos ventanas deslizantes buscando prefijos malos. La clave está en recorrer de derecha a izquierda

    // Será el encargado de saber cuantos bloques hay para un prefijo
    LazySegTree<lli, Sum<lli>, Max<lli>> st(vll(2 * n, 0));
    int ans = 0;

    // Procesamos la ventana deslizante de derecha a izquierda
    for (int s = 2 * n; s >= 1; s--) {
        int real_s = (s - 1) % n + 1;
        int val = p[real_s];

        // 1. Añadimos el nuevo elemento a todos los prefijos posibles
        st.update(s, 2 * n, 1);

        // 2. Comprobamos si formamos un enlace con sus números adyacentes
        for (int diff = -1; diff <= 1; diff += 2) {
            int u = val + diff;
            if (u >= 1 && u <= n) {
                int y = pos[u];
                // Si la posición original está detrás de nuestro 's' actual,
                // significa que la encontraremos en la copia duplicada
                while (y <= s) y += n;
                
                // Si el prefijo se estira hasta 'y', el número de bloques disminuye
                if (y <= 2 * n) {
                    st.update(y, 2 * n, -1);
                }
            }
        }

        // 3. Si ya estamos en el array original, consultamos si es "Good Start"
        if (s <= n) {
            if (st.query(s, s + n - 1) <= 2) {
                ans++;
            }
        }
    }

    cout << ans << "\n";

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

// https://codeforces.com/contest/2250/problem/E