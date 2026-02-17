#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#include<unordered_set>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
#endif

#include<bits/stdc++.h>

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

int solve(){
    // Este es un problema de la maleta con los atributos balance, numero de objetos y cuantos elementos de la secuencia )(( están presentes. 
    // Haces una programación dinámica sin tener en cuenta nada durante el proceso. Como en el problema de la mochila, por cada objeto (en este caso caracter)
    // Tenemos que decidir si meter el elemento o no. No meterlo implica que la nueva columna sigue igual, meterlo implica sumar los cambios, según el caracter y que elemento de
    // la tabla sea, actuaremos de una forma o de otra
    int n;
    cin >> n;
    string s;
    cin >> s;
    // dp[k][b][l] ->   k = que caracteres aparecen de )((
    //                  b = balance ( ( suma 1 y ) resta 1)
    //                  l = longitud secuencia
    vector<vector<vector<Mint>>> dp(4, vector(n + 1, vector(n + 1, Mint(0)))); // balance, length
    dp[0][0][0] = 1; // Importante empezar con 1. El score de una lista de balance 0 con longitud 0 es 1.
    for(int i = 0; i < n; i++){
        auto ndp = dp; // Simula el siguiente estado, copiamos la columna de antes a ndp (new dp). Optimiza espacio
        // El hecho de copiar la fila original incluye tambien que pasaria con cada caracter si no lo añadimos.
        int add = s[i] == '(' ? 1 : -1; // El cambio de balance
        for(int b = 0; b < n; b++){
            if(b + add < 0) continue; // Si fuera menor que 0 no hay posibilidades de que sea regular
            for(int l = 0; l < n; l++){
                for(int k = 0; k < 4; k++){
                    int ni = k; // Indice k que se modifica
                    if(k == 0 && s[i] == ')') ni++;
                    if((k == 1 || k == 2) && s[i] == '(') ni++;
                    ndp[ni][b + add][l + 1] += dp[k][b][l];
                }
            }
        }
        swap(dp, ndp); // Parte de la mecanica de ahorro de memoria con las columnas de dp y ndp
    }

    Mint ans = 0;
    for(int l = 0; l <= n; l++){
        ans += dp[3][0][l] * (l - 2); // Todas las secuencias de longitud l tienen un score de l-2
    }

    cout << ans << '\n';
    return 0;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int T;
    cin >> T;
    while(T--){
        solve();
    }
}
// https://codeforces.com/contest/2190/problem/B2