#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#include<unordered_set>
#pragma GCC optimize("O3")
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
template<typename T> std::ostream& operator<<(std::ostream& os, const Mint& m) {
    os << m.v << " ";
    return os;
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
#define F first;
#define S second;

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

int solve() {
    // Code aquí
    int r, g, b; cin >> r >> g >> b;
    string sol = "";

    set<pair<int, char>> Reorder1 = {
        {r,'R'},
        {g,'G'},
        {b,'B'}
    }; // .begin gives the smallest
    
    auto init = Reorder1.begin();
    pair<int, char> valSmallest = (*init);
    auto middle = Reorder1.begin();
    middle++;
    pair<int, char> valMiddle= (*middle);
    auto ending = Reorder1.begin();
    ending++;
    ending++;
    pair<int, char> valGreatest = (*ending);

    // Primero haz una secuencia con el grande y el chico hasta quedarte sin chico o que el grande sea igual al mediano.
    if (valGreatest.first != valMiddle.first){
        valGreatest.first--;
        sol+=valGreatest.second;
    }
    //cout << sol << endl;
    while (valSmallest.first && valGreatest.first != valMiddle.first){
        valSmallest.first--;
        sol+=valSmallest.second;
        valGreatest.first--;
        sol+=valGreatest.second;
    }
    //cout << sol << endl;
    // Ahora mezclamos el mediano con el grande hasta que el mediano llegue al chico y empiece su turno (empiezas por el mediano)
    while (valMiddle.first != valSmallest.first){
        valMiddle.first--;
        sol+=valMiddle.second;
        valGreatest.first--;
        sol+=valGreatest.second;
    }
    //cout << sol << endl;
    // Final, si hemos llegado a este punto pueden pasar X cosas
    // El primer while paró ya que el valor Smallest llegó a 0, en ese caso no hacemos nada ya que el segundo habrá reducido el valor middle a 0 y termina en el valor Greatest
    // El primer while paró ya que el valor Greatest llegó a Middle, entonces el segundo bucle se ejecutará con normalidad y falta reducir todos los valores a 0
    // Para reducir los valores a 0 hay una secuencia que reduce todos los valores en uno, repetimos dicha secuencia hasta que no nos queden más
    // Al terminar siempre nuestros whiles con el valor Greatest, sabemos que no podemos empezar con este
    // Debemos decidir si empezar con Middle o con Smallest, para este punto o ambos estan en 0 o tienen todos los números el mismo valor
    // Resulta que esto no es tanto un problema ya que la secuencia habrá quedado como GXGXG donde G es el valor de greatest
    // Eso significa que el final queda algo como GXGXGY
    // La secuencia que hablabamos antes con números es:
    // 1 2 3 2 3 1 3 1 2
    // Así que la secuencia realmente sería X G Y G Y X Y X G
    // Ahora sí, cual es X y cual es Y
    // Si la longitud de sol al llegar es menor que 2, es irrelevante. En caso contrario, X es el mismo que el penultimo caracter
    
    string secuencia = "XGYGYXYXG";
    char elF = 'S', elS = 'M';
    if (sol.size()>=2){
        if (valMiddle.second == sol[sol.size()-2]){
            elF = 'M';
            elS = 'S';
        }
    }
    for (int i = 0; i<secuencia.size(); i++){
        if (secuencia[i] == 'X'){
            secuencia[i] = elF;
        } else if (secuencia[i] == 'G'){
            secuencia[i] = 'G';
        } else {
            secuencia[i] = elS;
        }
    }
    for (int i = 0; true; i = (i+1)%9){
        if (secuencia[i] == 'S'){
            if (!valSmallest.first) break;
            sol+=valSmallest.second;
            valSmallest.first--;
        } else if (secuencia[i] == 'M'){
            if (!valMiddle.first) break;
            sol+=valMiddle.second;
            valMiddle.first--;
        } else {
            if (!valGreatest.first) break;
            sol+=valGreatest.second;
            valGreatest.first--;
        }
    }

    cout << sol << endl;
    //cout << "-------------" << endl;
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

// https://codeforces.com/contest/2209/problem/D