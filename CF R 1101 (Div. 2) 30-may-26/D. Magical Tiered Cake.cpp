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

struct operacion {
    int layerId;
    int from;
    int to;
    operacion(int a, int b, int c){
        layerId = a;
        from = b;
        to = c;
    }
};

struct state{
    int n;
    vi stacks[3];
    vi a;
    vector<operacion> ops;
    state(int x, vi& b){
        a = b;
        n = x;
        for (int i = 0; i<n; i++) stacks[0].PB(n-i);
    }
    vi getStack(int i){
        return stacks[i-1];
    }
    int getWeight(int index){
        return a[index-1];
    }
    int get(int st, int pos){ // Los stacks son 1, 2 y 3. Las posiciones son 1-indexed siendo el 1 el más alto aunque se almacenen al reves
        return stacks[st-1][stacks[st-1].size()-pos];
    }
    bool checkMove(int from, int to, int index){
        return getWeight(get(from, index)) == index-1 && (getStack(to).empty() || get(to, 1) > get(from, index));
    }
    bool moveLayer(int from, int to, int index){
        if (checkMove(from, to, index)){
            stacks[to-1].push_back(get(from, index));
            stacks[from-1].erase(stacks[from-1].end()-index);
            ops.PB(operacion(get(to, 1), from ,to));
            DBG_COUT(cout << "Movement of " << get(to, 1) << " defined by: " << from << " -> " << to << ": " << endl);
            DBG_COUT(cout << "Stack 1: " << getStack(1) << endl);
            DBG_COUT(cout << "Stack 2: " << getStack(2) << endl);
            DBG_COUT(cout << "Stack 3: " << getStack(3) << endl);
            return true;
        } else {
            DBG_COUT(cout << "Oops, you cannot move that layer..." << endl);
            return false;
        }
    }
};

int moveSubStack(int from, int to, int aux, int amount, state& s){
    if (amount <= 0 || from == to) return 0;
    DBG_COUT(cout << "Moving " << amount << " layers from: " << from << " to: " << to << endl);
    // Queremos mover la capa s.stacks.get(from, amount) a to
    // Así que antes movemos el substack de los primeros 
    if (s.getWeight(s.get(from, amount)) == 0){
        DBG_COUT(cout << "Case a[i] = 0" << endl);
        moveSubStack(from, aux, to, amount-1, s); // Movemos todos los elementos por encima al stack auxiliar
        s.moveLayer(from, to, 1); // Movemos la capa al stack objetivo
        moveSubStack(aux, to, from, amount-1, s); // Movemos todos los elementos del stack auxiliar al stack objetivo
    } else {
        DBG_COUT(cout << "Case a[i] != 0" << endl);
        int pos = s.getWeight(s.get(from, amount))+1; // Posición del elemento que estamos moviendo, será distinta al mover todo lo de encima
        moveSubStack(from, aux, to, amount-1-s.getWeight(s.get(from, amount)), s); // Movemos los a[i] elementos más por encima al stack auxiliar
        s.moveLayer(from, to, pos); // Movemos la capa al stack objetivo
        moveSubStack(aux, from, to, amount-1-s.getWeight(s.get(to, 1)), s); // Los elementos que movimos antes los devolvemos al stack principal
        moveSubStack(from, to, aux, amount-1, s); // Movemos el stack inicial al stack objetivos
    }
    return 1;
}

state solveHanoi(vi& a, int n){
    // Para mover una capa necesito:
    // 1. Mueve las n-1 capas superiores al stack 2 (auxiliar)
    // 2. Mueve la capa inferior al stack 3 (objetivo)
    // 3. Mueve todo el stack 2 (auxiliar) al stack 3 (objetivo)
    // Este problema puede mover una capa solo si por encima tiene cierto número de capas, no ninguna
    // Esto añade un caso extra, ya que ahora el proceso se divide en si a[i] = 0 o no.
    // Si a[i] = 0 hacemos la secuencia anterior
    // Si a[i] > 0, hacemos lo siguiente:
    // 1. Mueve la torre de las primeras n-a[i]-1 capas al stack 2 (auxiliar)
    // 2. Mueve la capa inferior al stack 3 (objetivo)
    // 3. Mueve de nuevo la torre de las primeras n-a[i]-1 capas al stack 1 (inicial)
    // 4. Mueve todo el stack 1 (inicial) al stack 3 (objetivo)
    // Los roles de los stacks pueden cambiar, ten eso en cuenta
    state s = state(n, a);
    moveSubStack(1, 3, 2, n, s);
    return s;
}

int solve() {
    // Code aquí
    int n; cin >> n;
    vi a(n); rep(i, n) cin >> a[i];
    DBG_COUT(cout << "Test: " << a << endl);
    
    bool sol = true; rep(i, n) if (a[i] > i) {sol = false; break;}
    if(sol){
        state s = solveHanoi(a, n);
        DBG_COUT(cout << "Solucion: ");
        cout << "YES" << endl;
        cout << s.ops.size() << endl;
        for (auto x:s.ops) cout << x.layerId << " " << x.from << " " << x.to << endl;
    } else {
        DBG_COUT(cout << "Solucion: ");
        cout << "NO" << endl;
    }
    DBG_COUT(cout << "========================================" << endl);    
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

// https://codeforces.com/contest/2232/problem/D