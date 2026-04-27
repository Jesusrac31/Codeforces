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
#define MAXK 15
double pi = 2*acos(0.0);

vector<Mint> factorial = {1};
Mint fact(int n){
    for (int i = factorial.size(); i<=n; i++){
        factorial.PB(factorial.back() * i);
    }
    return factorial[n];
}

Mint comb(int n, int k){
    if (n < k) return 0;
    return (fact(n)*(fact(k)*fact(n-k)).inv());
}

// Si obtienes el valor de la longitud del subarray + 1 en logaritmo 2, el valor de k y el número de bits disponibles que tenemos para modificar,
// Podemos obtener cuantas veces aparecen subarrays de dicha longitud en nuestra secuencia entre [0, 2^bits)
// Ten en cuenta que los subarrays que tenemos en cuenta son aquellos válidos para el valor de k
// Resulta que este sigue un patrón como el del binomio de newton. Ahora obtenemos dicho patrón, para eso utilizamos el factorial
Mint getMulti(int bits, int k, int valueLog2){
    // Para cierto valor k, tienes que mirar los números de la diagonal bits-k-2
    // El número de abajo del binomio será bits-k-2
    cout << bits-valueLog2 << " " << bits-k-1 << endl;
    if (k >= bits){ // Solo hay un subarray completo
        if (valueLog2 != bits+1) return 0;
        else return (Mint(2).pow(valueLog2)-1);
    }
    if (valueLog2 > bits || k < 0 || bits < 0 || valueLog2 < 0) return 0;
    Mint combi = comb(bits-valueLog2, bits-k-1);
    return combi;
}

int solveBrute() {
    // Code aquí
    vi seq;
    cerr << "Objetivo: " << (1LL << MAXK) << endl;
    for (lli i = 0; i< (1LL << MAXK); i++) { 
        bitset<MAXK+1> num = i;
        int b = 0;
        for (int j = 0; j<MAXK+1; j++) if (num[j]) b++;
        seq.PB(b); // Introduce cuantos bits tiene en 1
        cerr << "\rProgreso: " << i << flush;
    }
    cerr << "Looking finished" << endl;

    for (int k = 0; k<MAXK; k++){
        cout << "For k = " << k << endl;
        map<int, lli> ranges;
        vi rangesVect;
        int actRange = 0; // Busca las secuencias del mismo elemento más grande
        for (int i = 0; i<seq.size(); i++){
            if (seq[i] <= k) actRange++;
            else if (actRange){
                if (ranges.find(actRange) == ranges.end()) ranges[actRange] = 1;
                else ranges[actRange]++;
                actRange = 0;
            }
        }
        if (actRange){
            if (ranges.find(actRange) == ranges.end()) ranges[actRange] = 1;
            else ranges[actRange]++;
        }
        for (auto x:ranges) cout << x.first << " -> " << x.second << endl;
        cout << "---------------" << endl;
    }
    return 0;
}

int solve(){
    cout << getMulti(25, 0, 5) << endl;
    return 0;
}

int binary(){
    lli n = 795569939321040850;
    cout << bitset<64>(n) << endl;
    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    binary();
    return 0;
}
