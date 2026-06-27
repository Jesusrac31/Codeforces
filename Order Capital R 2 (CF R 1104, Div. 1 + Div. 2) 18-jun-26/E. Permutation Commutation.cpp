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

void dfs(vi& record, vector<bool>& recorridos, vi& a, int node, vector<pii>& cicloPerNode, int val, int index = 0){
    if(recorridos[node]) return ;
    record.PB(node);
    recorridos[node] = true;
    cicloPerNode[node] = {val, index};
    dfs(record, recorridos, a, a[node], cicloPerNode, val, index+1);
}

bool addCycle(vi& ciclo, int actualCycle, vi& b, int actualB, vi& a, int initB = -1, int initCycle = -1){
    if (actualB == initB && actualCycle == initCycle) return true; // Termina de colocar
    if (initB == -1) initB = actualB; // Primer elemento, guarda donde empezaste
    if (initCycle == -1) initCycle = actualCycle; // Primer elemento, guarda donde empezaste
    if (b[actualB] == -1) b[actualB] = ciclo[actualCycle]; 
    else if (b[actualB] != ciclo[actualCycle]) return false;
    return addCycle(ciclo, (actualCycle+1) % ciclo.size(), b, a[actualB], a, initB, initCycle);
}

int solve() {
    // Code aquí
    int n; cin >> n;
    vi a(n+1); rep(i, n) cin >> a[i+1];
    vi b(n+1); rep(i, n) cin >> b[i+1];

    DBG_COUT(cout << "Test: " << endl << a << endl << b << endl);

    // Primero, la propiedad de que a conmuta en b. Esta propiedad definida matemáticamente
    // puede ser complicada, así que podemos definirla de forma más simple.
    
    // Digamos que las permutaciones son funciones donde a(x) nos dice el elemento en la posición x.
    // Entonces a(a(x)) tan solo hace una especie de camino pasando de elemento en elemento
    // Esto que estoy explicando podeis visualizarlo como un grafo que tiene varios subgrafos, cada uno de estos ciclicos,
    // donde el arco x->y existe si y solo si a(x) = y
    // Si interpretas así la permutación, ves que al componer la función hace un ciclo, los mismos del grafo.

    // Bien, decimos que a conmuta en b, si al aplicar la permutación de b (mueve el elemento i a b[i]), los ciclos siguen apareciendo (a tiene el mismo grafo)
    // Resulta que sabiendo esto, el problema es mucho más fácil, ya que tan solo hay dos operaciones que podemos hacer,
    // 1. Rota los elementos de un ciclo: Si el ciclo 1 2 3 existe en a, puedes tener tambien el ciclo 3 1 2 sin problema (no acepta invertidos como 3 2 1)
    // 2. Intercambia ciclos del mismo tamaño: Si tengo el ciclo 1 2 3 y el ciclo 4 5 6 [ej 2 3 1 5 6 4], puedo intercambiarlos teniendo el 4 5 6 1 2 3
    // Para mayo sencillez, necesitas un representante por cada ciclo, y ponerlos para que dicho representante quede en la posición correcta

    // Ahora para movilizarlos y rotarlos, cada uno de los representantes debe mapearse a un elemento del ciclo al que vas a hacer swap (o a un elemento de su propio ciclo incluyendose)
    // Entonces tratamos con el ciclo destino y el ciclo origen (el del representante). Deben mantener el mismo orden. Si el ciclo origen tenia un 5 después del representante 7, y el ciclo destino tenía un 2 después de un 1
    // Al mapear el 7 al 1, el 5 debe reemplazar al 2.

    // Para elegir un representante, tenemos un orden de prioridad:
    // 1. Si aparece en b, debe elegirse como representante del ciclo a no ser que el representante del ciclo ya aparezca en b
    // 2. En caso de que ningún elemento del ciclo aparezca en b, selecciona el más pequeño como representante

    // Para formar la cadena, primero pon los ciclos que tengan elementos que aparezcan en b. El resto de ciclos pueden hacer swap con otros de su mismo tamaño introduciendo su representante como primer elemento

    // Paso 1: Obten los ciclos
    vector<vi> ciclos;
    vector<pii> cicloPerNode(n+1);
    vector<bool> recorridos(n+1, false);
    vector<bool> cicloEstablecido;
    for (int i = 1; i<=n; i++){
        if (!recorridos[i]){
            ciclos.PB({}); cicloEstablecido.PB(false);
            dfs(ciclos.back(), recorridos, a, i, cicloPerNode, ciclos.size()-1);
        }
    }
    DBG_COUT(
        cout << "Ciclos generados: " << endl;
        for (int i = 0; i<ciclos.size(); i++) cout << i << " -> " << ciclos[i] << endl;
    );
    DBG_COUT(
        cout << "Ciclo al que pertenece cada nodo:" << endl;
        for (auto x:cicloPerNode) cout << "(" << x.first << " " << x.second << ") ";
        cout << endl;
    );

    // Paso 2: Coloca todo ciclo que tenga elementos en b
    bool existSol = true;
    for (int i = 1; i<=n; i++){
        if (b[i] != -1 && !cicloEstablecido[cicloPerNode[b[i]].first]){
            if (!addCycle(ciclos[cicloPerNode[b[i]].first], cicloPerNode[b[i]].second, b, i, a)) {
                DBG_COUT(cout << "WARNING, CICLO INVALIDO" << endl);
                existSol = false;
                break;
            }
            cicloEstablecido[cicloPerNode[b[i]].first] = true;
        }
    }
    
    DBG_COUT(cout << "b después de colocar forzados: " << endl << b << endl);

    // Paso 3: En caso de que haya repetidos o haya algún ciclo invalido, debes devolver NO
    vector<bool> aparece(n+1, false);
    for (int i = 1; i<=n && existSol; i++){
        if (b[i] != -1){
            if (aparece[b[i]]) {DBG_COUT(cout << "WARNING, repite elementos" << endl); existSol = false;}
            aparece[b[i]] = true;
        }
    }

    if (!existSol) {cout << "NO" << endl; return 0;}

    // Paso 4: Organiza los ciclos
    unordered_map<int, vi> ciclosPorTamano;
    for (int i = 0; i<ciclos.size(); i++)
        ciclosPorTamano[ciclos[i].size()].PB(i);
    
    DBG_COUT(
        cout << "Ciclos por tamano: " << endl;
        for (auto x:ciclosPorTamano) cout << x.first << " -> " << x.second << endl;
    );

    // Paso 5: Los ciclos dentro de la clasificación están ordenados por orden de prioridad
    // El primer ciclo de longitud x debe aparecer en el primer hueco de longitud x
    // Si el ciclo con id 0 empieza por el elemento 1, significa que hay un rango del mismo tamaño empezando en el 1
    for (auto& pareja : ciclosPorTamano){
        int indexPosicion = 0;
        for (int indexCiclo = 0; indexCiclo < pareja.second.size(); indexCiclo++){
            if (cicloEstablecido[pareja.second[indexCiclo]]) continue;
            while (b[ciclos[pareja.second[indexPosicion]][0]] != -1) indexPosicion++;
            DBG_COUT(cout << "Inserting " << ciclos[pareja.second[indexCiclo]] << " at position " << ciclos[pareja.second[indexPosicion]][0] << "..." << endl);
            addCycle(ciclos[pareja.second[indexCiclo]], 0, b, ciclos[pareja.second[indexPosicion]][0], a);
            cicloEstablecido[pareja.second[indexCiclo]] = true;
        }
    }

    DBG_COUT(cout << "Solucion: ");
    cout << "YES" << endl;
    for (int i = 1; i<=n; i++) cout << b[i] << " ";
    cout << endl;

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
        DBG_COUT(cout << "====================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2237/problem/E