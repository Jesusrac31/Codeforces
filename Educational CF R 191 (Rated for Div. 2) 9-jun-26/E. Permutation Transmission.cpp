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

#define DIE(x) { cout << x << endl; exit(0); }

#define INF INT_MAX
double pi = 2*acos(0.0);

int solve() {
    // Code aquí
    int n; cin >> n;
    // El cálculo de log2 de n puede dar problemas al usar double. 
    // Este while simula ceil(log2(n+1)) en O(log2(n+1))
    int bits = 0;
    while ((1 << bits) <= n) bits++;

    vector<string> seq(bits); rep(i, bits) {cin >> seq[i]; seq[i]+="0"; if ((int)seq[i].size() != n+1) {cout << n << "-" << bits << "-" << seq[i] << "-"; DIE("ERR_SEQ_SIZE");}}
    DBG_COUT(cout << "Test: " << endl; for (auto s:seq) cout << s << endl);
    
    // Asumiremos que la respuesta es >= 1. Entonces, si n = 2^k - 1 o n = 2^k - 2, cualquier orden da una respuesta correcta,
    // Esto sucede ya que si partes de una configuración correcta, al hacer un swap entre dos arrays, puede pasar 4 casos:
    // - Cambias 0 por 0, el número permanece igual
    // - Cambias 1 por 1, el número permanece igual
    // - Cambias 1 por 0, cambia el número
    // - Cambias 0 por 1, cambia el número
    // Lo peculiar, es que en estos casos, hay tantas combinaciones 1 0 como 0 1, por lo que pueden emparejarse y tan solo cambias el orden
    // Pero sigue siendo una solución. Así, en estos casos la solución es de k!

    // Para el caso en el que n no cumple la condición anterior, podemos reducir el problema:
    // Si no es ninguno de estos números, no todos los arrays tienen la misma cantidad de 1. De hecho, el array con la menor cantidad de 1s es aquel que 
    // se debe colocar más arriba, siendo el array de más arriba el que contiene el bit más representativo de cada número
    // Lo que haremos será especificar que este array tiene que aparecer en esa posición, y reduciremos el problema:
    // Al colocar ese array, en aquellos sitios donde hubiera 0s no los volveremos a tener en cuenta en ningún paso posterior en ningún array
    // Utilizaremos los otros arrays con solo los bits que seguiremos tomando en cuenta
    // n ahora se deberá de ver reducido a n - 2^k.
    
    // Debemos solucionar un problema, resulta que puede suceder que el número de bits más pequeño que haya sea 0 y haya varios. En ese caso, tenemos que saber que todos esos arrays pueden intercambiarse entre ellos
    // Así que cada vez que pase esto, tenemos que hacer un conteo de cuantas secuencias existen que puedan colocarse.

    // Finalmente, nos queda comprobar si estos calculos que hemos hecho son correctos, para eso tan solo pon un resultado calculado arbitrario y checkea que el resultado sea correcto
    
    set<int> candidatosBits; rep(i, n+1) candidatosBits.insert(i);
    set<int> candidatosArrays; rep(i, bits) candidatosArrays.insert(i);
    int carry = n;
    int index = bits-1;
    vector<int> order;
    vector<lli> multiplicadoresExtra;
    while (index >= 0){
        if (index+1 >= 31) DIE("ERR_SHIFT1");
        DBG_COUT(cout << "Inspecting bit " << index << ":" << endl);
        DBG_COUT(cout << "Arrays candidates: "; for (auto x:candidatosArrays) cout << x << " "; cout << endl);
        DBG_COUT(cout << "Bits candidates: "; for (auto x:candidatosBits) cout << x << " "; cout << endl);
        DBG_COUT(cout << "Multiplicadores en factorial " << multiplicadoresExtra << endl);
        
        DBG_COUT(cout << "Carry: " << carry << endl);

        if (carry == ((1<<(index+1)) - 1) || carry == ((1<<(index+1)) - 2)) { // carry en binario es 1111...
            DBG_COUT(cout << "carry + 1 or + 2 is power of 2" << endl);
            break;
        } else { 
            vector<int> menores = {-1};
            int value = INF;
            for (auto idxArr: candidatosArrays){
                if (idxArr < 0 || idxArr >= bits) DIE("ERR_ARR_IDX");
                int counter = 0;
                for (auto idxBit: candidatosBits){
                    if (idxBit < 0 || idxBit >= (int)seq[idxArr].size())
                        DIE("ERR_SEQ_OOB");
                    counter += (seq[idxArr][idxBit] == '1');
                }

                if (menores.empty()) DIE("ERR_EMPTY_MEN");

                if (counter < value) menores = {idxArr};
                else if (counter == value) menores.PB(idxArr);
                value = min(value, counter);
            }

            DBG_COUT(cout << "Valid arrays found: " << menores << endl);
            DBG_COUT(cout << "Value of these: " << value << endl);

            if (value != 0){
                set<int> newCandidatosBits;
                for (auto idxBit: candidatosBits){
                    if (idxBit < 0 || idxBit >= (int)seq[menores[0]].size())
                        DIE("ERR_FILTER_OOB");
                    if (seq[menores[0]][idxBit] == '1')
                        newCandidatosBits.insert(idxBit);
                }
                swap(candidatosBits, newCandidatosBits);
                if (candidatosBits.empty()) DIE("ERR_EMPTY_BITS");
            }
            order.PB(menores[0]);
            candidatosArrays.erase(menores[0]);
            multiplicadoresExtra.PB(menores.size());
        }

        if (index >= 31) DIE("ERR_SHIFT2");

        if (carry >= (1 << (index))) carry -= (1 << (index));
        index--;
    }
    if ((int)order.size() > bits) DIE("ERR_ORDER_BIG");

    DBG_COUT(cout << "Especificados: " << order << endl);
    lli sol = 1;
    for (auto x:multiplicadoresExtra) sol *= x;
    for (int i = 2; i <= bits-order.size(); i++) sol *= i;
    
    // Test de si es posible
    for (auto x:candidatosArrays) order.PB(x);

    if ((int)order.size() != bits) DIE("ERR_ORDER_SIZE");

    DBG_COUT(cout << "Solucion de ejemplo: " << endl; for (auto x:order) cout << seq[x] << endl);
    
    vector<bool> appear(n+1);
    bool existSol = true;
    for (int i = 0; i<=n; i++){
        int num = 0;
        for(int j = 0; j<bits; j++){
            if (j >= (int)order.size()) DIE("ERR_ORDER_OOB");
 
            if (order[j] < 0 || order[j] >= bits) DIE("ERR_ORDER_IDX");
 
            if (i >= (int)seq[order[j]].size()) DIE("ERR_FINAL_OOB");

            num <<= 1;
            num+=(seq[order[j]][i] == '1');
        }
        if (num > n || appear[num]) {existSol = false; break;}
        appear[num] = true;
    }

    DBG_COUT(cout << "Solucion: "); 
    cout << sol*existSol << endl;
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

// https://codeforces.com/contest/2233/problem/E1
// https://codeforces.com/contest/2233/problem/E2