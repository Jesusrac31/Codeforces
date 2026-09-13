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
typedef pair<lli, lli> pii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

const int MOD = 1e9+7; // Módulo del problema, cambiar en caso de no ser ese. NO TIENE PORQUÉ SER CONSTANTE, SOLO GLOBAL

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

bool sort_func(pii a, pii b) {
    if (a.second < b.second) {
        return true;
    } else if (a.second == b.second){
        return a.first < b.first;
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
#define int lli
double pi = 2*acos(0.0);

class SegmentTree {
    vector<Mint> st; int n;

public:
    SegmentTree(const vector<int>& data) {
        n = (int)data.size();
        st.assign(n * 4, Mint());
        build(data, 1, 0, n - 1);
    }
    Mint convert(int x){ return Mint(x); }
    Mint combine(const Mint& a, const Mint& b){ return a+b; }
    void build(const vector<int>& data, int p, int l, int r){
        if(l==r){ st[p]=convert(data[l]); return; }
        int m=(l+r)>>1; build(data,p<<1,l,m); build(data,p<<1|1,m+1,r);
        st[p]=combine(st[p<<1], st[p<<1|1]);
    }
    void update(int idx, int val, int p, int l, int r){
        if(l==r){ st[p]=convert(val); return; }
        int m=(l+r)>>1; if(idx<=m) update(idx,val,p<<1,l,m); 
        else update(idx,val,p<<1|1,m+1,r);
        st[p]=combine(st[p<<1], st[p<<1|1]);
    }
    void update(int idx, int val){ update(idx,val,1,0,n-1); }
    Mint query(int ql, int qr, int p, int l, int r){
        if(qr<l||r<ql) return Mint();
        if(ql<=l&&r<=qr) return st[p];
        int m=(l+r)>>1;
        return combine(query(ql,qr,p<<1,l,m), query(ql,qr,p<<1|1,m+1,r));
    }
    Mint query(int ql, int qr){ return query(ql,qr,1,0,n-1); }
};

int solve() {
    // Code aquí
    lli n; cin >> n;
    vll a(n+1); rep(i, n) cin >> a[i+1];

    // Calcula cuales son los valores que pueden usarse, el resto estan prohibidos
    vll diff(n+1, 0);
    for (int i = 1; i<=n; i++){
        diff[min(i*a[i], n)]--;
        diff[min(i*(a[i]+1), n)]++;
        DBG_COUT(cout << "After " << i << ": " << diff << endl);
    }
    vector<bool> posible(n, true);
    int acc = 0;
    for (int i = 0; i<n; i++){
        acc += diff[i];
        posible[i] = (acc == 0);
    }
    DBG_COUT(cout << "Posibles: " << posible << endl);

    vector<pii> intervalos;
    for (int i = 1; i<=n; i++)
        for (int j = 0; j<min(i*a[i], n); j += i) 
            intervalos.push_back(pii(j, min(j+i-1, n-1)));
    
    DBG_COUT(cout << "Intervalos: " << endl;for (auto x: intervalos) cout << "{ " << x.first << " " << x.second << " } "; cout << endl);
    
    // Si un intervalo contiene a otro, el intervalo pequeño prevalece
    vll limitRightInterval(n, n);
    for (int i = 0; i<(int)intervalos.size(); i++)
        limitRightInterval[intervalos[i].first] = min(limitRightInterval[intervalos[i].first], intervalos[i].second);
    
    int prevVal = n;
    for (int i = n-1; i>=0; i--){
        if (limitRightInterval[i] >= prevVal){
            limitRightInterval[i] = n;
        } else {
            prevVal = limitRightInterval[i];
        }
    }
    
    DBG_COUT(cout << "limit Right: " << limitRightInterval << endl);

    vector<pii> intervalosFiltered;
    for (int i = 0; i<n; i++) 
        if (limitRightInterval[i] != n)
            intervalosFiltered.push_back(pii(i, limitRightInterval[i]));
    DBG_COUT(cout << "Intervalos filtrados:" << endl; for (auto x: intervalosFiltered) cout << "{ " << x.first << " " << x.second << " } "; cout << endl);

    vll nearestLower(n+1, -1);
    int index = 0;
    for (int i = 0; i<=n; i++){
        while (index < (int)intervalosFiltered.size() && i > intervalosFiltered[index].second) 
            index++;
        if (index) nearestLower[i] = intervalosFiltered[index-1].first;
    }
    DBG_COUT(cout << "Nearest lower: " << nearestLower << endl);

    vll init(n, 0); 
    SegmentTree dp(init);
    // Número de posibilidades de seleccionar elementos seleccionando el elemento i hasta i
    // Para seleccionar i, debe haber antes seleccionado un j que pertenezca a un intervalo de la izquierda
    // dp[i] = sum(dp[j], j in low(i)..i-1)
    // low(i) es para todos los intervalos (Lj, Rj) el maximo valor de Lj tal que Rj sea menor que i
    // Como hemos filtrado los intervalos, es tan solo el valor de L de un intervalo anterior a x
    for (int i = 0; i<n; i++){
        if (posible[i]){
            dp.update(i, (nearestLower[i] == -1) + dp.query(nearestLower[i],i-1).v);
            DBG_COUT(cout << "Query " << i << ": " << dp.query(nearestLower[i],i-1).v << endl);
        }
    }
    DBG_COUT(cout << "DP: "; for (int i = 0; i<n; i++) cout << dp.query(i, i) << " "; cout << endl);

    cout << (nearestLower[n] == -1) + dp.query(nearestLower[n], n).v << endl;

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
        DBG_COUT(cout << "================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2263/problem/C2