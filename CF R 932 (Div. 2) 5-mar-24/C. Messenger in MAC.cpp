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

template<typename T, typename Q> std::ostream& operator<<(std::ostream& os, const std::pair<T,Q>& vec) {
    os << "( " << vec.first << " " << vec.second << " )";
    return os;
}

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

#define INF 1e9+10
double pi = 2*acos(0.0);

int solve() {
    // Input
    int n, L; cin >> n >> L;
    vi a(n), b(n); rep(i, n) cin >> a[i] >> b[i];
    // Dado un conjunto de mensajes a seleccionar, lo mejor es seleccionarlos en orden creciente o decreciente según b[i]
    // Por cada elemento entonces, puedo seleccionarlo o no seleccionarlo.
    // Si selecciono los mensajes p[1], p[2], ..., p[k]. Para calcular costeB = sum(i = 1, k-1, |b[p[i]] - b[p[i+1]]|), podemos hacer b[p[k]] - b[p[1]] si asumimos b[i] <= b[i+1]. Esto sucede si ordenamos los mensajes según b[i]
    // Sabemos entonces que dado un rango [l,r] podemos hayar costeB
    // Lo que nos importa entonces es el valor de costeA = sum(i = 1, k, a[p[i]]), l y r
    // Iteraremos por todas las parejas [l, r] para buscar la máxima cantidad de elementos que podemos almacenar, para esto llevaremos un recuento de los valores de a
    // De esta forma, aplicando la técnica de sliding window podemos hacer un recuento.
    // Al tener ordenado por b, cada vez que seleccione un elemento nuevo voy a poder meter menos elementos

    vector<pii> mensajes(n+1);
    for (int i = 1; i<=n; i++) { mensajes[i].first = b[i-1]; mensajes[i].second = a[i-1]; }
    sort(mensajes.begin(), mensajes.end());
    DBG_COUT(cout << "L: " << L << endl);
    DBG_COUT(cout << "Mensajes: " << mensajes << endl);

    int sol = 0;
    for (int l = 1; l<=n; l++){
        DBG_COUT(cout << "Ranges starting at: " << l << endl);
        priority_queue<int> storedElements;
        int additionA = 0;
        for (int r = l; r<=n; r++){
            DBG_COUT(cout << "\tEnding at " << r << endl);
            storedElements.push(mensajes[r].second);
            additionA += mensajes[r].second;
            while (storedElements.size() && additionA > L + mensajes[l].first - mensajes[r].first){
                additionA-=storedElements.top();
                storedElements.pop();
            }
            DBG_COUT(cout << "\tTop element: " << ((storedElements.size()) ? storedElements.top(): 0) << endl);
            DBG_COUT(cout << "\tValue: " << additionA << endl);
            sol = max(sol, (int)storedElements.size());
        }
    }

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

// https://codeforces.com/contest/1935/problem/C