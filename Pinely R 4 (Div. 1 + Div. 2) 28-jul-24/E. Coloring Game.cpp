#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
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

unordered_set<int> isColor0;
unordered_set<int> isColor1;

bool coloring2(vector<vi>& grafo, int node, int color, vector<bool>& recorrido){
    if (recorrido[node]){ // Si ya lo has recorrido
        // Comprueba que el color sea consistente
        if (color==0) return (isColor0.find(node) != isColor0.end());
        else return (isColor1.find(node) != isColor1.end());
    }
    // Sino, establece el color y marca como recorrido
    recorrido[node] = true;
    if (color==0) isColor0.insert(node);
    else isColor1.insert(node);

    // Comprueba tambien sus hijos
    bool sol = true;
    for (auto v:grafo[node]){
        sol &= coloring2(grafo, v, (color+1)&1, recorrido);
    }
    return sol;
}

bool coloring2(vector<vi>& grafo, int n){
    vector<bool> recorrido(n+1, false);
    return coloring2(grafo, 1, 1, recorrido);
}

void SequenceBob(int n){
    int a, b;
    auto color1It = isColor0.begin();
    auto color2It = isColor1.begin();
    for (int i = 0; i<n; i++){
        cin >> a >> b;
        if (a == -1) exit; // Bad answer
        if (a == 1){
            if (color1It==isColor0.end()){ // Si ya he coloreado todos los 1
                cout << (*color2It) << " " << b << endl;
                color2It++;
            } else {
                cout << (*color1It) << " " << 1 << endl;
                color1It++;
            }
        } else if (b == 1){
            if (color1It==isColor0.end()){ // Si ya he coloreado todos los 1
                cout << (*color2It) << " " << a << endl;
                color2It++;
            } else {
                cout << (*color1It) << " " << 1 << endl;
                color1It++;
            }
        } else {
            if (color2It==isColor1.end()){ // Si ya he coloreado todos los 2
                cout << (*color1It) << " " << 3 << endl;
                color1It++;
            } else {
                cout << (*color2It) << " " << 2 << endl;
                color2It++;
            }
        }
    }
}

void SequenceAlice(int n){
    int node, c;
    for (int i = 0; i<n; i++){
        cout << "1 2" << endl;
        cin >> node >> c;
        if (node == -1) exit; // Bad answer
    }
}

int solve() {
    // Input
    int n, m; cin >> n >> m;
    if (n == -1) exit; // Bad answer

    vector<vi> grafo(n+1);
    int u, v;
    for (int i = 0; i<m; i++){ cin >> u >> v; grafo[u].PB(v); grafo[v].PB(u); }

    // Bob gana si solo si puede colorear el grafo con dos colores solo. Prueba:
    // Si necesitara tres colores, Alice podría siempre seleccionar dos colores y llegaría un momento en el que Bob no puede hacer nada.
    // Si puede colorear el grafo con dos colores, sigue el siguiente proceso:
    // 1. Selecciona los vertices que debe pintar de color 1
    // 2. Selecciona los vertices que debe pintar de color 2
    // 3. Si Alice selecciona el color 1, pinta uno de los vertices que debes pintar de color 1
    // 4. En caso de que no lo seleccione, habrá seleccionado el color 2, por lo que debes pintar uno de los vertices del otro grupo
    // 5. Si en algún momento pintas todos los vertices de uno de los grupos, los vertices restantes no serán adyascentes entre ellos, por lo que puedes usar tambien el color 3 en ellos sin problema

    // Ahora el problema se reduce a si el grafo puede ser coloreado con tan solo dos colores lo cual es fácil de comprobar, ya que si un vertice es de color 1, todos los vecinos serán color 2, y los vecinos de estos color 1, y así sucesivamente
    // Si en algún momento hay alguna contradicción, sería imposible.
    // Esto funciona principalmente al ser un grafo conectado, no dirigido y simple.
    isColor0.clear();
    isColor1.clear();
    bool winBob = coloring2(grafo, n);

    cout << (winBob ? "Bob":"Alice") << endl;

    if (winBob){
        SequenceBob(n);
    } else {
        SequenceAlice(n);
    }

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

// https://codeforces.com/contest/1991/problem/E