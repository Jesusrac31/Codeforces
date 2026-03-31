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

template<typename T, typename Q> std::ostream& operator<<(std::ostream& os, const std::pair<T, Q>& elem) {
    os << "{ ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    os << elem.first << ", " << elem.second;
    os << " }";
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

int solve() {
    // Code aquí
    int n, m; cin >> n >> m;
    vi a(m); rep(i, m) cin >> a[i]; ord(a);
    DBG_COUT(cout << "---------------" << endl);
    DBG_COUT(cout << "Test " << n << " " << m << endl);
    DBG_COUT(cout << a << endl);
    if (m == 1) {cout << 2 << endl; return 0;}
    vi pathsLenght(2*m, 2*m-1); // La longitud máxima de cada camino es 2*m-1 (sin contar el nodo inicial infectado)
    vi shareLast(2*m,-1); // Dice si el último nodo se comparte con otro camino
    for (int i = 0; i<m; i++){
        int diff;
        if (i == 0) diff = a[i]+n-a.back();
        else diff = a[i]-a[i-1]; // Diferencia entre ambos números
        DBG_COUT(cout << "Diferencia entre " << a[i] << " e " << a[(i-1+m)%m] << ": " << diff << endl);
        int longitud = diff/2; // Longitud de cada camino

        pathsLenght[i*2] = min(longitud, pathsLenght[i*2]);
        pathsLenght[(i*2-1+2*m)%(2*m)] = min(longitud, pathsLenght[(i*2-1+2*m)%(2*m)]);
        if (!(diff&1) && longitud <= 2*m-1){
            shareLast[i*2] = (i*2-1+2*m)%(2*m);
            shareLast[(i*2-1+2*m)%(2*m)] = i*2;
        }
    }
    DBG_COUT(cout << "Paths length: " << pathsLenght << endl);
    DBG_COUT(cout << "Sharing node paths: " << shareLast << endl);

    // Ordenamos los caminos manteniendo el índice
    vector<pii> caminos(2*m);
    for (int i = 0; i<2*m; i++){
        caminos[i] = pii(pathsLenght[i], i);
    } 

    auto sortingFunc = [&shareLast, m](pii a, pii b) {
        if (a.first != b.first) return a.first < b.first;
        bool aShared = (shareLast[a.second] != -1);
        bool bShared = (shareLast[b.second] != -1);
        if (aShared != bShared) return aShared > bShared; // no compartidos primero
        return ((a.second-1+2*m)%(2*m)) < ((b.second-1+2*m)%(2*m));
    };

    sort(caminos.begin(), caminos.end(), sortingFunc); // Si hubiera dos caminos con longitudes iguales pero uno de ellos comparte nodo, este tiene una prioridad menor pero mayor a la de los caminos de menor longitud
    DBG_COUT(cout << "Paths: " << caminos << endl );

    // Inicializamos el coste:
    int sharedNodes = 0;
    for (int i = 0; i<2*m; i++){
        if (shareLast[i] != -1){
            sharedNodes++;
        }
    }
    sharedNodes/=2;
    DBG_COUT(cout << "Number of sharde Nodes: " << sharedNodes << endl);

    int coste = -sharedNodes;
    for (int i = 0 ; i<2*m; i++){
        coste += caminos[i].first;
    }
    DBG_COUT(cout << "Maximum cost: " << coste << endl);
    // Recortamos los caminos de menor a mayor eliminando todos
    int pena = 0;
    vector<bool> cut(2*m, false);
    DBG_COUT(cout << "Steps of cutting each path: " << endl);
    for(int i = 2*m-1; i>=0; i--){
        if (caminos[i].first-pena > 0){
            coste-=caminos[i].first-pena;
            if (shareLast[caminos[i].second] != -1 && !cut[shareLast[caminos[i].second]] && (caminos[i].first-pena) != 1){
                coste++;
            }
            cut[caminos[i].second]=true;
        } else break;
        pena++;
        DBG_COUT(cout << "Cut path number " << caminos[i].second << " of lenght " << caminos[i].first << " reducing cost to " << coste << endl);
    }
    DBG_COUT(cout << "Solution: ");
    cout << coste+m << endl;

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

// https://codeforces.com/contest/1704/problem/C