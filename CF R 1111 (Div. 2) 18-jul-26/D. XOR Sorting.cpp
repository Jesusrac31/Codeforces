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
#define MAXDEPTH 30

int bad[MAXDEPTH];

struct Node { 
    int minimo, maximo; 
    Node* left;
    Node* right;
    Node(int m = INF, int M = -1, Node* l = nullptr, Node* r = nullptr){
        minimo = m; maximo = M; left = l; right = r;
    } 
    bool isBadLeft(){
        if (left == nullptr) return false;
        return minimo < left->maximo;
    }
    bool isBadRight(){
        if (right == nullptr) return false;
        return maximo > right->minimo;
    }
    int getChange(){
        return (int)isBadLeft() + (int)isBadRight();
    }
};

class SegmentTree {
public:
    vector<Node> st; int n;
    SegmentTree(const vector<int>& data) {
        n = (int)data.size();
        st.assign(n * 4, Node());
        build(data, 1, 0, n - 1, 0);
    }
    Node convert(int x, int idx, int depth){ 
        Node* l = &st[idx-1]; if ((1<<depth) == idx) l = nullptr;
        Node* r = &st[idx+1]; if ((1<<(depth+1))-1 == idx) r = nullptr;
        return Node(x, x, l, r); 
    }
    Node combine(const Node& a, const Node& b, int idx, int depth){ 
        Node* l = &st[idx-1]; if ((1<<depth) == idx) l = nullptr;
        Node* r = &st[idx+1]; if ((1<<(depth+1))-1 == idx) r = nullptr;
        return Node(min(a.minimo, b.minimo), max(a.maximo, b.maximo), l, r); 
    }
    void build(const vector<int>& data, int p, int l, int r, int d){
        if(l==r){ 
            st[p]=convert(data[l], p, d); 
            bad[d] += st[p].isBadLeft();
            DBG_COUT(cout << "Bad with " << p << " " << st[p].minimo << " " << st[p].maximo << " " << st[p].isBadLeft() << " " << d << ": ";for (int i = 1; i<MAXDEPTH; i++) cout << bad[i] << " "; cout << endl; );
            return;
        }
        int m=(l+r)>>1; 
        build(data,p<<1,l,m, d+1); 
        build(data,p<<1|1,m+1,r, d+1);
        st[p]=combine(st[p<<1], st[p<<1|1], p, d);
        bad[d] += st[p].isBadLeft();
        DBG_COUT(cout << "Bad with " << p << " " << st[p].minimo << " " << st[p].maximo << " " << st[p].isBadLeft() << " " << d << ": ";for (int i = 1; i<MAXDEPTH; i++) cout << bad[i] << " "; cout << endl; );
    }
    void update(int idx, int val, int p, int l, int r, int d){
        if(l==r){ 
            bad[d] -= st[p].getChange();
            st[p]=convert(val, p, d); 
            bad[d] += st[p].getChange();
            return; 
        }
        int m=(l+r)>>1; 

        if(idx<=m) update(idx,val,p<<1,l,m, d+1); 
        else update(idx,val,p<<1|1,m+1,r, d+1);

        bad[d] -= st[p].getChange();
        st[p]=combine(st[p<<1], st[p<<1|1], p, d);
        bad[d] += st[p].getChange();
    }
    void update(int idx, int val){ update(idx,val,1,0,n-1, 0); }
    Node query(int ql, int qr, int p, int l, int r, int d){
        if(qr<l||r<ql) return Node();
        if(ql<=l&&r<=qr) return st[p];
        int m=(l+r)>>1;
        return combine(query(ql,qr,p<<1,l,m, d+1), query(ql,qr,p<<1|1,m+1,r, d+1), p, d);
    }
    Node query(int ql, int qr){ return query(ql,qr,1,0,n-1,0); }
};

int getSol(){
    int idx = MAXDEPTH-1;    
    while (idx >= 0 && !bad[idx]) idx--;
    int sol = 0;
    while (idx >= 0 && bad[idx]) {idx--; sol++;}
    DBG_COUT(cout << "Exponente: " << sol-1 << endl);
    DBG_COUT(cout << "Solucion: ");
    return pow(2, sol)/2;
}

int solve() {
    // Code aquí
    memset(bad, 0, sizeof(bad));
    int n, q; cin >> n >> q;
    vi a(n); rep(i, n) cin >> a[i];
    DBG_COUT(cout << "Test: " << a << endl);

    // Vamos a buscar que n sea una potencia de 2
    int potencia = 1;
    while(potencia < n) potencia<<=1;
    while(n < potencia){
        n++;
        a.PB(INF);
    }

    DBG_COUT(cout << "Test power of 2: " << a << endl);

    // Tenemos que buscar si reordenando intervalos de k, donde k es 2^x, sale el array ordenado
    // Para cada posible x, buscamos si el mínimo y el máximo de cada intervalo coinciden
    SegmentTree tree(a);

    DBG_COUT(cout << "Bad: ";for (int i = 1; i<MAXDEPTH; i++) cout << bad[i] << " "; cout << endl; );

    cout << getSol() << endl;

    while(q--){
        int idx, val; cin >> idx >> val;
        tree.update(idx, val);
        cout << getSol() << endl;
    }
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

// https://codeforces.com/contest/2247/problem/D1
// https://codeforces.com/contest/2247/problem/D2