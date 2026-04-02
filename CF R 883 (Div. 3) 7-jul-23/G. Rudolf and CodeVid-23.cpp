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
#define MAX_N 10
double pi = 2*acos(0.0);

struct Pastilla {
    int peso;
    int cura;
    int sintomas;
    Pastilla(int p = 0, int c = 0, int s = 0){
        peso = p;
        cura = c;
        sintomas = s;
    }
};

void getNeighbors(vector<pii>& sol, int node, vector<Pastilla> pastillas){
    assert(sol.size() == pastillas.size());
    for (int i = 0; i<pastillas.size(); i++){
        sol[i].first = (node & ~pastillas[i].cura)|pastillas[i].sintomas;// El nuevo estado
        sol[i].second = pastillas[i].peso;
    }
}

int getGoal(){
    return 0;
}

vector<int> dijkstra(int src, vector<Pastilla>& acciones, int V) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<int> dist(V, INF);
    dist[src] = 0;
    pq.emplace(0, src);

    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int d = top.first;  
        int u = top.second; 
        
        DBG_COUT(cout << "Computing: " << bitset<MAX_N>(u) << endl);

        if (d > dist[u]) continue;
        
        vector<pii> neighbors(acciones.size());
        getNeighbors(neighbors, u, acciones);
        for (auto &p : neighbors) {
            int v = p.first; 
            int w = p.second; 

            if (dist[u] + w < dist[v]) {
                DBG_COUT(cout << "Adding: " << bitset<MAX_N>(v) << " to "<< dist[u]+w << endl);
                dist[v] = dist[u] + w;   
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}

int solve() {
    // Code aquí

    int n, m; cin >> n >> m;
    string r; cin >> r;
    int p = bitset<MAX_N>(r).to_ulong();

    DBG_COUT(cout << "Test: " << bitset<MAX_N>(p) << endl);
    vector<Pastilla> pastillas(m);

    int d;
    string cura, sintomas;
    for (int i = 0; i<m; i++){
        cin >> d >> cura >> sintomas;
        pastillas[i] = Pastilla(d, bitset<MAX_N>(cura).to_ulong(), bitset<MAX_N>(sintomas).to_ulong());
        DBG_COUT(cout << "Pastilla " << i << ":\n\tTiempo: " << pastillas[i].peso << "\n\tCura: " << bitset<MAX_N>(pastillas[i].cura) << "\n\tSintomas: " << bitset<MAX_N>(pastillas[i].sintomas) << endl);
    }

    vector<int> dist = dijkstra(p, pastillas, (1<<MAX_N));
    int sol = dist[getGoal()];
    if (sol == INF) sol = -1;
    cout << sol << endl;

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

// https://codeforces.com/contest/1846/problem/G