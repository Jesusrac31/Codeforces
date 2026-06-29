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

#define DIE(x) { cout << x << endl; exit(0); }


bool checkIsValid(vi& l){
    for (int i = 1; i<l.size(); i++)
        if (l[i] != l[i-1]+1) return false;
    return true;
}

void opera(vi& l1, vi& l2){
    l1.push_back(l2.back());
    l2.pop_back();
    l2.push_back(l1[0]);
    l1.erase(l1.begin());
    ord(l1);
    ord(l2);
}

int solve(int T) {
    // Code aquí
    int n; cin >> n;
    vi a(n); rep(i, n) cin >> a[i];
    DBG_COUT(cout << "Test: " << a << endl);

    // Vamos a transformar el problema
    // Obten por cada valor en que posiciones de la lista aparece. Expresa l[i] como la lista de apariciones del valor i
    // Con uno o cero operaciones debes hacer que todas las l[i] estén compuestas de elementos contiguos
    // Una operación intercambia un elemento de l[i] con un elemento de l[j].
    // Realmente, solo es útil intercambiar los elementos del principio y del final de cada l[i].

    // Para la resolución, marcaremos que l[i] son inválidas. Ahora tenemos varios casos:
    // - Si existen tres o más l[i] inválidas, es imposible hacer que sean válidas, por lo que puedes responder NO
    // - Si existen exactamente dos l[i] inválidas, tienes que solucionar ambas a la vez, por lo que solo 4 operaciones son posibles
    // Digamos que l[i] y l[j] son las inválidas. Entonces las operaciones son (l[i][0], l[j].back()), (l[i].back(), l[j][0]). Las otras no ayudan a mejorar las posibiliades
    // Comprobar por fuerza bruta esto es como mucho O(2n), así que no tendrás problema.
    // - Si existe exactamente una l[i] inválida, tenemos que encontrar las operaciones que podrían hacer la lista l[i] válida.
    // Solo son cambiar l[i][0] o l[i].back(). Pero por cuales elementos.
    // Supongamos que queremos operar con l[i][0]. Podemos buscar cual es el elemento que falta en l[i][1..k]
    // En caso de faltar varios, la operación no tiene sentido. En caso de no faltar ninguno, tenemos la posibilidad de ponerlo antes o después
    // Lo mismo podría aplicar para l[i].back()
    // - Si todas son válidas devuelve "YES"

    unordered_map<int, vi> appear;
    for (int i = 0; i<n; i++) appear[a[i]].PB(i);

    DBG_COUT(cout << "Positions of each value:\n"; for(auto x:appear) cout << x.first << " -> " << x.second << endl);

    vi invalidIndex;
    int invalidCounter = 0;
    for (auto x: appear){
        if (!checkIsValid(x.second)){
            invalidIndex.PB(x.first);
            invalidCounter++;
        }
    }

    DBG_COUT(cout << "Amount invalid lists: " << invalidCounter << endl);
    DBG_COUT(cout << "Record of invalids: "; for (auto x:invalidIndex) cout << x << " "; cout << endl);
    
    if (invalidCounter >= 3){
        DBG_COUT(cout << "Too many invalids, Solution: ");
        cout << "NO" << endl;
    } else if (invalidCounter == 2){
        DBG_COUT(cout << "Lists have 2 invalids, checking if any operation makes them valid..." << endl);
        
        vi l1, l2;
        copia(appear[invalidIndex[0]], l1);
        copia(appear[invalidIndex[1]], l2);
        opera(l1, l2);
        DBG_COUT(cout << "New arrays:" << endl << l1 << endl << l2 << endl);
        if (checkIsValid(l1) && checkIsValid(l2)){
            DBG_COUT(cout << "Is valid changing first element of array " << (*invalidIndex.begin()) << endl << "Solucion: ");
            cout << "YES" << endl;
            return 0;
        }
        swap(l1, appear[invalidIndex[1]]);
        swap(l2, appear[invalidIndex[0]]);
        opera(l1, l2);
        DBG_COUT(cout << "New arrays:" << endl << l1 << endl << l2 << endl);
        if (checkIsValid(l1) && checkIsValid(l2)){
            DBG_COUT(cout << "Is valid changing first element of array " << (*invalidIndex.begin()+1) << endl << "Solucion: ");
            cout << "YES" << endl;
            return 0;
        }
        DBG_COUT("None of the operations were valid. Solucion: ");
        cout << "NO" << endl;

    } else if (invalidCounter == 1){
        DBG_COUT(cout << "Lists have 1 invalid, looking if there is any operation that makes it valid..." << endl);
        // Para l[i][0]
        int arrInvalid = invalidIndex[0];
        int hueco = -1;
        bool canOperate = true;
        for (int i = 2; i<appear[arrInvalid].size(); i++){
            if (appear[arrInvalid][i] == appear[arrInvalid][i-1]+1) continue;
            if (appear[arrInvalid][i] == appear[arrInvalid][i-1]+2 && hueco == -1) {
                hueco = appear[arrInvalid][i-1]+1;
                continue;
            }
            canOperate = false;
            break;
        }
        if (canOperate){ 
            vi posibles;
            if (hueco == -1){
                if (appear[arrInvalid][1]-1 >= 0) posibles.PB(appear[arrInvalid][1]-1);
                if (appear[arrInvalid].back()+1 < n) posibles.PB(appear[arrInvalid].back()+1);
            } else posibles = {hueco};
            DBG_COUT(cout << "Candidates of being an operation: " << posibles << endl);
            for (auto x:posibles){
                vi l;
                int newEl = appear[arrInvalid][0];
                bool added = false;
                for (auto y:appear[a[x]]){
                    if (newEl < y && !added) {l.PB(newEl); added = true;}
                    if (y == x) continue;
                    l.PB(y);
                }
                if (!added) l.PB(newEl);
                DBG_COUT(cout << "New list: " << l << endl);
                if (checkIsValid(l)){
                    DBG_COUT(cout << "Is valid with swap " << x << " " << newEl << endl << "Solucion: ");
                    cout << "YES" << endl;
                    return 0;
                }
            }
        }
        DBG_COUT(cout << "It has not been found any valid swap with l[i][0], checking l[i].back()..." << endl);
        // Para l[i].back()
        hueco = -1;
        canOperate = true;
        for (int i = 1; i<appear[arrInvalid].size()-1; i++){
            if (appear[arrInvalid][i] == appear[arrInvalid][i-1]+1) continue;
            if (appear[arrInvalid][i] == appear[arrInvalid][i-1]+2 && hueco == -1) {
                hueco = appear[arrInvalid][i-1]+1;
                continue;
            }
            canOperate = false;
            break;
        }
        if (canOperate){ 
            vi posibles;
            if (hueco == -1){
                if (appear[arrInvalid][0]-1 >= 0) posibles.PB(appear[arrInvalid][0]-1);
                if (appear[arrInvalid][appear[arrInvalid].size()-2]+1 < n) posibles.PB(appear[arrInvalid][appear[arrInvalid].size()-2]+1);
            } else posibles = {hueco};
            DBG_COUT(cout << "Candidates of being an operation: " << posibles << endl);
            for (auto x:posibles){
                vi l;
                int newEl = appear[arrInvalid].back();
                bool added = false;
                for (auto y:appear[a[x]]){
                    if (newEl < y && !added) {l.PB(newEl); added = true;}
                    if (y == x) continue;
                    l.PB(y);
                }
                if (!added) l.PB(newEl);
                DBG_COUT(cout << "New list: " << l << endl);
                if (checkIsValid(l)){
                    DBG_COUT(cout << "Is valid with swap " << x << " " << newEl << endl << "Solucion: ");
                    cout << "YES" << endl;
                    return 0;
                }
            }
        }
        
        DBG_COUT(cout << "None of the operations were valid. Solucion: ");
        cout << "NO" << endl;
    } else {
        DBG_COUT(cout << "Lists are already valids, Solution: ");
        cout << "YES" << endl;
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
        solve(T);
        DBG_COUT(cout << "===========================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2233/problem/D