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

template<typename T> std::ostream& operator<<(std::ostream& os, const std::set<T>& s) {
    os << "{ ";
    copy(s.begin(), s.end(), ostream_iterator<T>(os, " "));
    os << "}";
    return os;
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

template <typename T>
class SegmentTree {
    vector<T> st; int n;
public:
    SegmentTree(const vector<T>& data) {
        n = (int)data.size();
        st.assign(n * 4, T());
        build(data, 1, 0, n - 1);
    }
    T convert(T x){ return x; }
    T combine(const T& a, const T& b){ return T(a+b); }
    void build(const vector<T>& data, int p, int l, int r){
        if(l==r){ st[p]=convert(data[l]); return; }
        int m=(l+r)>>1; build(data,p<<1,l,m); build(data,p<<1|1,m+1,r);
        st[p]=combine(st[p<<1], st[p<<1|1]);
    }
    void update(int idx, T val, int p, int l, int r){
        if(l==r){ st[p]=convert(val); return; }
        int m=(l+r)>>1; if(idx<=m) update(idx,val,p<<1,l,m); 
        else update(idx,val,p<<1|1,m+1,r);
        st[p]=combine(st[p<<1], st[p<<1|1]);
    }
    void update(int idx, T val){ update(idx,val,1,0,n-1); }
    T query(int ql, int qr, int p, int l, int r){
        if(qr<l||r<ql) return T();
        if(ql<=l&&r<=qr) return st[p];
        int m=(l+r)>>1;
        return combine(query(ql,qr,p<<1,l,m), query(ql,qr,p<<1|1,m+1,r));
    }
    T query(int ql, int qr){ return query(ql,qr,1,0,n-1); }
};

int solve() {
    // Code aquí
    lli n; cin >> n;
    vll a(n+1); for (int i = 1; i<=n; i++) cin >> a[i];
    vi p(n); rep(i, n) cin >> p[i];
    DBG_COUT(cout << "TEST: " << endl << a << endl << p << endl);

    vll sol(n, 0);
    vll init(n+1, 0); SegmentTree<lli> st(init);
    set<int> forfeats;
    for (int i = n-1; i >= 0; i--){
        DBG_COUT(cout << "Computing i = " << i << "..." << endl);
        // Añade el elemento p[i]
        st.update(p[i], a[p[i]]);
        if (forfeats.empty() || *forfeats.begin() > p[i])
            forfeats.insert(p[i]);
        DBG_COUT(cout << "Added element: " << forfeats << endl);
        DBG_COUT(cout << "Tree actual: { "; for (int i = 1; i<=n; i++) cout << st.query(i, i) << " "; cout << "}" << endl);
        
        // Busca el indice en forfeats menor que p[i] pero más grande posible
        auto startMod = forfeats.lower_bound(p[i]); 

        // Comprueba si hay un nuevo forfeat
        if (startMod != forfeats.begin()){
            startMod--;
            if (st.query(*startMod, p[i]-1) < a[p[i]]) forfeats.insert(p[i]);
        }
        DBG_COUT(cout << "First element to inspect: " << *startMod << endl);
        DBG_COUT(cout << "Forfeats updating left: " << forfeats << endl);

        // Actualiza el resto
        auto indexRight = forfeats.upper_bound(p[i]);  
        auto indexLeft = indexRight; indexLeft--;
        DBG_COUT(
            cout << "Initial pair: " << *indexLeft << " "; 
            if (indexRight != forfeats.end()) cout << *indexRight; 
            else cout << "None"; 
            cout << endl;
        );

        while (indexRight != forfeats.end()){
            if (st.query(*indexLeft, (*indexRight)-1) < a[*indexRight]) break;
            auto toErase = indexRight++;
            forfeats.erase(toErase);
        }
        DBG_COUT(cout << forfeats << endl);
        sol[i] = forfeats.size() - 1;
    }
    DBG_COUT(cout << "Solucion: ");
    for (auto x: sol) 
        cout << x << " ";
    cout << endl;

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
        DBG_COUT(cout << "====================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2263/problem/D