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

const int MOD = 1000000007; // Módulo del problema, cambiar en caso de no ser ese. NO TIENE PORQUÉ SER CONSTANTE, SOLO GLOBAL

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

struct range {
    int v;
    int init;
    int ending;

    range(int vN, int initN, int endingN){
        v = vN;
        init = initN;
        ending = endingN;
    }
};

int solve(int T) {
    // Code aquí
    int n; cin >> n;
    vi a(n+1); for (int i = 1; i<=n; i++) cin >> a[i];
    a[0] = n;

    vector<range> ranges = {{n, 0, 1}};
    vector<bool> Appear(n+1, false);
    Appear[n] = true;
    bool posible = true;
    for (int i = 1; i<=n; i++){
        if (a[i] > a[i-1]){
            posible = false;
            break;
        } else if (a[i] == a[i-1]){
            Appear[a[i]] = true;
            ranges.back().ending++;
        } else {
            if (n-a[i] > i){
                posible = false;
                break;
            }
            Appear[a[i]] = true;
            ranges.PB(range(a[i], i, i+1));
        }
    }
    ranges.PB(range(0, n+1, n+2));
    if (!posible){
        cout << "0" << endl;
        return 0;
    }
    // Chequea las posibilidades de cada numero.
    // Ejemplo de 6 6 6 4 3 3
    // n = 6
    // Añade n al principio de la lista: 6 6 6 6 4 3 3
    // Para todo valor de x que NO pertenezca en la lista, se cumple lo siguiente:
    // 1. Aparece EXACTAMENTE una vez
    // 2. Si y es un numero que aparece en la lista siendo lo más grande posible y a su vez menor a x, e i es la posición donde aparece dicho numero, 
    // nuestro número x aparece antes de la posición i.
    // Con estas propiedades puedes obtener los posibles valores de todos los valores que no aparezcan en la lista
    // en las posiciones j donde el elemento en j-1 sea igual al elemento en j
    // En dichas posiciones, no pueden aparecer otros numeros, por lo que las posibilidades en dichas posiciones son faciles de calcular
    // En el ejemplo, los valores serían el 5, 2, 1, 0. El 5 puede aparecer en 3 posiciones (1, 2, 3)
    // El 2 puede aparecer en 4 posiciones (1, 2, 3, 6), el 1 y el 0 tienen las mismas posiciones que el 2
    // Para computarlo facilmente, sería 3*3*2*1, ya que una vez que coloques el 5, todos los demás numeros menores tendrán una posibilidad menos
    // Esto se hace con todos y queda que el resultado parcial es 3*3*2*1
    vector<Mint> posibilidades = {0};
    int index = 0;
    for (int i = n; i>=0; i--){
        if (Appear[i]) continue;
        posibilidades.PB(posibilidades.back());
        while (index < ranges.size() && ranges[index].v > i){
            posibilidades.back() += ranges[index].ending - ranges[index].init - 1;
            index++;
        }
    }
    Mint sol = 1;
    for (int i = 1; i<posibilidades.size(); i++){
        sol *= posibilidades[i]-i+1;
    }

    // La segunda parte son las posiciones donde el elemento en i es menor que el elemento en i-1.
    // En esta posicion puede ir cualquier numero mayor a a[i] o que haya aparecido anteriormente en la lista.
    // En el cao de antes, para 6 6 6 6 4 3 3, en la posicion 4, habría aparecido el 5, y dos numeros mas los cuales son menores a 4,
    // Por lo que en dicha posicion puede haber 4 numeros, el 6, el 5 y los dos que aparecieron anteriormente.
    // Para computar esto, tenemos que tener en cuenta que dicho numero mayor a 4 aparece SIEMPRE anteriormente si no está en la lista original
    // Debemos filtrar dicho elemento, para ello tan solo debes modificar una de las condiciones
    // En vez de decir numeros mayores a 4, di que dichos numeros deben aparecer en la lista. De esa forma, necesitas 2 valores:
    // 1. Cuantas posiciones hay antes de esta posicion i tal que el elemento j sea igual a j-1
    // 2. Cuantos numeros son mayores que el valor en esta posición y ADEMÁS aparezcan en la lista
    // Sumando esos dos numeros, obtenemos el resultado final.

    // En primer lugar, saber las posiciones que buscamos es sencillo, la lista range nos la da con el elemento .init
    // Además, saber cuantas posiciones hay tal que el elemento j sea igual al elemento j-1 te lo dice tambien range, ya que por cada rango, se da la situacion contraria
    for (int i = 1; i<ranges.size()-1; i++){
        Mint Mult = 0;
        Mult += ranges[i].init;
        if (Mult == 0) Mult = 1;
        sol *= Mult;
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
        solve(T);
    }
    return 0;
}

// https://codeforces.com/contest/2207/problem/E2