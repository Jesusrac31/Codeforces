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

int solve() {
    // Code aquí
    int n;
    cin >> n;
    vi resp(n);
    for (int i = 1; i<n; i++){
        cout << "? " << i << " " << i+1 << endl;
        cin >> resp[i];
    }
    vi sol(n);
    bool exist = false;
    iota(sol.begin(), sol.end(), 1);
    for (int i = n-1; i>1; i--){
        if (resp[i] < resp[i-1]){ //Buscamos el ultimo pico apuntando hacia arriba de la grafica
            exist = true;
            // Ahora tenemos que crear la solución. Para eso tenemos en cuenta que resp[i] es 1 si el elemento i es menor que i+1
            // Primero definimos a como sol[i-1] y b como sol[i]
            // Buscamos el punto más abajo en la permutacion en sol[i..n], llamale sol[x]
            // El punto más bajo es tan facil como buscar x para que resp[x] > resp [x-1], si no existe, x=n
            // Ordenamos dichos puntos usando la misma estrategia que se usa en merge sort:
            // Partes de una lista con sol[x] y las variables l y r iguales a 1
            // Si sol[x-l] < sol[x+r] entonces añades sol[x-l] a la lista y sumas 1 a l
            // En caso contrario haces lo mismo con la r
            // Repite hasta que x+r sea mayor que n (introduce todos los elementos que quedan en orden por la izquierda) o que sol[x+r] > b, si pasa eso habrás llegado a sol[i] < sol[x+r]
            // Así que metes b a la lista y tienes los elementos de esa franja ordenados lexicograficamente.
            // Hasta ahora has gastado en el peor de los casos aproximadamente 2n operaciones, para saber la relación entre cada par de elementos adyascentes y para ordenar este rango
            // Te faltan n operaciones, estas las usaras para introducir a, compara con cada elemento de la listade forma ordenada de menor a mayor, el primero que diga ser mayor que a debe ser intercambiado por este
            // Esta ultima parte la puedes hacer con busqueda binaria pero no es necesario :)
            // Necesitas entonces como muchisimo 3n operaciones (usando busqueda binaria 2n + log(n))
            int down = n;
            for (int j = i; j<n; j++){ // Puede hacerse más optimo con busqueda binaria
                if (resp[j] > resp[j-1]){
                    down = j;
                    break;
                }
            }
            vi reorder = {down};
            int l=1, r=1;
            while (down-l >= i){
                if (down+r <= n){
                    int smaller;
                    cout << "? " << down-l << " " << down+r << endl;
                    cin >> smaller;
                    if (smaller){
                        reorder.PB(down-l);
                        l++;
                    } else {
                        reorder.PB(down+r);
                        r++;
                    }
                } else {
                    reorder.PB(down-l);
                    l++;
                }
            }

            // Apply resolution to all range
            pii range = {i, down+r};
            int index = 0;
            for (int j = range.first; j<range.second; j++){
                sol[j-1] = reorder[index];
                index++;
            }

            // Changing a
            int aFinder;
            for (int j = 0; j<reorder.size(); j++){ // Optimizable con busqueda binaria
                cout << "? " << i-1 << " " << reorder[j] << endl;
                cin >> aFinder;
                if (aFinder){
                    sol[i-2] = reorder[j];
                    sol[range.first+j-1] = i-1;
                    break;
                }
            }


            break;
        }
    }
    if (exist){
        cout << "! ";
        for (auto x:sol){
            cout << x << " ";
        }
        cout << endl;
    } else {
        cout << "! -1" << endl;
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

// https://codeforces.com/contest/2190/problem/C