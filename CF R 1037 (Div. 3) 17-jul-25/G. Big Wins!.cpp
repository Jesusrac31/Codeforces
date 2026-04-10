#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
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
typedef vector<long long int> vll;
typedef long long int lli;
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

// Funciones map
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

void lee(lli n, vll& vect) {
  rep(i, n) cin >> vect[i];
  return ;
}

#define INF LONG_MAX

struct DSU
{
    vll f;
    DSU(){};
    DSU(lli n){
        f.resize(n);
        for(lli i=0;i<n;i++)f[i]=i; // Crea una lista de n elementos con los números de [0, n-1]
    }
    lli find(lli x){ // Esta función find es mucho más óptima, ya que por defecto f[x] = x. La única operación existente es sustituir un valor de la lista por otro existente.
                     // Este proceso lo podemos representar como un arbol donde f tiene el padre del elemento i siendo sí mismo por defecto y la operación merge cambia el padre del elemento y al padre del elemento x
        if(f[x]==x)return x;
        return f[x]=find(f[x]);
    }
    void merge(lli x,lli y){
        x=find(x),y=find(y);
        if(x==y)return;
        f[y]=x;
    }
};

lli solve() {
    // Code aquí
    int n;
    cin>>n;
    vll a(n),p(n); // a es el array original
    for(auto &x:a)cin>>x;

    iota(p.begin(),p.end(),0); // p es una de elementos consecutivos perteneciente a [0, p-1]
    sort(p.begin(),p.end(),[&](int x,int y){ // El array p dice el orden de los índices de los elementos sin ordenar en orden.
        return a[x]>a[y];                    // Si a[x] < a[y], en p y irá antes que x
    });

    lli mi=INF; // Inicializamos min como infinito
    lli ans=0;
    DSU fl(n+1),fr(n+1); // Creamos 2 listas de tamaño n+1
    for(auto i:p){ // Asumiremos que el elemento en la posición a[i] es la mediana (empezariamos asumiendo que la mediana es el elemento más grande)
        for(int _=0;_<2;_++){ // Repetimos 2 veces el siguiente proceso por cada valor de p
            lli x=fl.find(i+1); // Buscamos el elemento x en fl con nuestra función find
            if(x){ // Si el elemento tiene un padre que no sea el nodo imaginario 0
                mi=min(mi,a[x-1]); // Actualizamos el mínimo (x-1 es para adaptar a incio de cuenta 0)
                fl.merge(x-1,x); // Establecemos que el padre de x es x-1
            }

            /// Repetimos lo mismo en fr con el elemento anterior pero solo operamos si x<n (si x pertenece a la lista)
            x=fr.find(i);
            if(x<n){ // Si el elemento no es el elemento imaginario al final de la lista
                mi=min(mi,a[x]);
                fr.merge(x+1,x);
            }
        }
        ans=max(ans,a[i]-mi);
        
    }
    cout<< ans <<endl;
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

// https://codeforces.com/contest/2126/problem/G1
// https://codeforces.com/contest/2126/problem/G2