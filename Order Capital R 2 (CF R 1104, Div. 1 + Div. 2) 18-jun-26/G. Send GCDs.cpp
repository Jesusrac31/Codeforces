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
#define MAXNUMBER 1e6
#define WORDSIZE 20
#define COMPRESSEDSIZE 18

// Lista precomputada de los primeros 110 primos
vi primerosPrimos = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601};

unordered_map<int, int> fromCandidateToIndex;
vi fromIndexToCandidate;

void addValidCandidate(int n){
    fromCandidateToIndex[n] = fromIndexToCandidate.size();
    fromIndexToCandidate.PB(n);
}

void getList(int index = 0, int acc = 1){
    if (fromIndexToCandidate.size() >= (1 << 18)) return ;
    if (index >= primerosPrimos.size()) {
        addValidCandidate(acc);
        return ;
    }
    while (acc < MAXNUMBER && !(fromIndexToCandidate.size() >= (1 << 18))){
        getList(index+1, acc);
        acc*= primerosPrimos[index];
    }
}

int solve1() {
    // Code aquí
    int n; cin >> n;
    vi a(n); rep(i, n) cin >> a[i];

    // Para este problema tenemos una clave:
    // gcd(p^k, x) = p^t donde p es un número primo, k es el número más alto tal que p^k <= 10^6, x es el número que tenemos que obtener y t es el exponente que tiene el primo p en la factorización de x
    // De esta forma, podemos obtener la factorización de los números cuyos primos aparezcan en la lista b que devolvemos.
    // Resulta que hay más de 2^18 números menores o iguales que 10^6 y que su factorización solo contiene primos de entre los 110 primeros. Lo que haremos será:
    // Mandar una lista con los primeros 110 primos y luego añadir números cuya factorización esté formada por estos.
    // Para desencriptarlo es simple:
    // 1. Cada número en a contiene 20 bits
    // 2. Concatena todos los números de 20 bits en a, llamemos al resultado de esto s
    // 3. Divide s en trozos de 18 bits.
    // 4. Cada uno de esos trozos tiene asociado un número cuya factorización se forma con los primeros 110 primos
    // 5. Sustituye los trozos por sus números asociados y envia la lista resultante

    string longSeq;
    for (auto x:a) longSeq += bitset<WORDSIZE>(x).to_string();
    while(longSeq.size() % COMPRESSEDSIZE) longSeq += "0";

    DBG_COUT(cout << "Long seq: " << longSeq << endl);

    vi newSeq;
    for (int i = 0; i<longSeq.size(); i+=COMPRESSEDSIZE)
        newSeq.PB(bitset<COMPRESSEDSIZE>(longSeq.substr(i, COMPRESSEDSIZE)).to_ulong());

    DBG_COUT(cout << "New seq: " << newSeq << endl);
    
    vi b;
    for (auto x:primerosPrimos)
        b.PB(pow(x, (int)(log10(MAXNUMBER)/log10(x))));
    for (auto x:newSeq)
        b.PB(fromIndexToCandidate[x]);

    cout << b.size() << endl;
    for (auto x:b)
        cout << x << " ";
    cout << endl;

    return 0;
}

int solve2() {
    // Code aquí
    int n, k; cin >> n >> k;

    // Para formar esta, tenemos que obtener cada valor de nuestra secuencia b
    // Los primeros 110 elementos son conocidos
    // Los siguientes se obtienen haciendoles el GCD con cada uno de los 110 primeros elementos y multiplicando
    // Invertimos el proceso de conversión creado antes para obtener el resultado final

    vi candidateSeq;
    for (int i = primerosPrimos.size()+1; i<=k; i++){ 
        candidateSeq.PB(1);
        for (int j = 1; j <= primerosPrimos.size(); j++){
            cout << "? " << j << " " << i << endl;
            int el; cin >> el;
            candidateSeq.back() *= el;
        }
    }

    vi translatedSeq;
    for (auto x:candidateSeq)
        translatedSeq.PB(fromCandidateToIndex[x]);
    
    string longSeq = "";
    for (auto x:translatedSeq)
        longSeq += bitset<COMPRESSEDSIZE>(x).to_string();
    
    vi a;
    for (int i = 0; i<n; i++)
        a.PB(bitset<WORDSIZE>(longSeq.substr(i*WORDSIZE, WORDSIZE)).to_ulong());

    cout << "! ";
    for (auto x:a)
        cout << x << " ";
    cout << endl;

    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    auto start = chrono::high_resolution_clock::now();

    getList();
    string caso;
    cin >> caso; // Número de casos
    int T; cin >> T;
    if (caso == "first"){
        while (T--) solve1();
    } else {
        while (T--) solve2();
    }
    
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2237/problem/G