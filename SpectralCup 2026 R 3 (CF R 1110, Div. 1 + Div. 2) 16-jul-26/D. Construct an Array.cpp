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

// Estructura para representar una restricción en el grafo
struct Restriccion {
    int v;     // El otro elemento involucrado
    int tipo;  // 1 para >= 0, 2 para < 0
    int id;    // Identificador único de la restricción para evitar doble procesamiento
};

void solve() {

    // Asume que todos los elementos de nuestra solución serán distintos
    // Sabemos que existe una solución donde todos los elementos son distintos en valor absoluto ya que tenemos tres casos:
    // 1. a[i] > 0 && a[j] > 0 -> Realmente no importan sus valores, el signo de la suma será el mismo
    // 2. a[i] < 0 && a[j] < 0 -> Realmente no importan sus valores, el signo de la suma será el mismo
    // 3. a[i] > 0 && a[j] < 0 -> Si fueran iguales en valor absoluto, su resultado sería 0, por lo que basta
    // con sumar 1 a a[i] y sumar 1 al valor absoluto de todo a[k] que sea mayor que a[i] en valor absoluto
    // De esta forma, sabemos que si existe solución, existe una solución con elementos de diferente valor absoluto
    // De forma parecida, puedes saber que si existe solución con elementos cuya diferencia en valor absoluto es mayor a 1, existe
    // una solución donde la diferencia sea igual a 1. Por lo que buscamos es una permutación
    
    // En ese caso, a[i] + a[j] < 0 si el más grande en valor absoluto entre esos 2 es negativo
    // Haciendo eso, sabes que hay al menos uno que tiene que ser más grande que todos o más pequeño que todos.
    // Una vez establecido este elemento, damos todas sus restricciones como resueltas y continuamos con el siguiente
    // Una vez terminadas todas las restricciones ya tenemos los valores, y a medida que fuimos progresando vimos el signo de cada elemento
    // Ya solo queda imprimir los resultados

    int n, m;
    if (!(cin >> n >> m)) return;

    vector<vector<Restriccion>> adj(n + 1);
    vector<int> cnt1(n + 1, 0); // Cantidad de restricciones activas de Tipo 1 para cada nodo
    vector<int> cnt2(n + 1, 0); // Cantidad de restricciones activas de Tipo 2 para cada nodo
    vector<bool> procesada(m, false);

    for (int i = 0; i < m; ++i) {
        int o, u, v;
        cin >> o >> u >> v;
        if (u != v) {
            adj[u].push_back({v, o, i});
            adj[v].push_back({u, o, i});
            if (o == 1) {
                cnt1[u]++;
                cnt1[v]++;
            } else {
                cnt2[u]++;
                cnt2[v]++;
            }
        } else {
            // Restricción sobre sí mismo (u == v)
            // Estas no generan aristas, solo obligan a que ese elemento sea positivo o negativo
            // Añadiendo 1 a alguno de los cnt nos aseguramos de que estos no caigan a 0 y por consecuente se interprete un signo erroneo
            if (o == 1) cnt1[u]++;
            else cnt2[u]++;
        }
    }

    // Cola para procesar los elementos que no tienen restricciones conflictivas
    queue<int> Q;
    vector<bool> en_cola(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (cnt1[i] == 0 || cnt2[i] == 0) {
            Q.push(i);
            en_cola[i] = true;
        }
    }

    vector<int> permutationValues(n + 1, 0);     // Almacenará el valor absoluto
    vector<int> signo(n + 1, 0);  // Almacenará el signo (-1 o 1)
    vector<bool> activo(n + 1, true);
    int rango_actual = n;

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();

        activo[u] = false;

        // Asignamos el valor más grande que todavia no se ha puesto al nodo procesado
        // El recuento baja en 1
        permutationValues[u] = rango_actual--;
        
        // Si no tiene restricciones de Tipo 2 activas, su signo debe ser positivo
        // En caso contrario, al estar en la cola, no tiene restricciones de Tipo 1 y su signo es negativo
        signo[u] = (cnt2[u] == 0) ? 1 : -1;

        for (auto& arista : adj[u]) {
            int v = arista.v;
            int tipo = arista.tipo;
            int id = arista.id;

            if (!procesada[id]) {
                procesada[id] = true;
                
                // Reducimos los contadores de restricciones activas
                if (tipo == 1) {
                    cnt1[v]--;
                    cnt1[u]--;
                } else {
                    cnt2[v]--;
                    cnt2[u]--;
                }

                // Si el vecino se vuelve candidato viable, lo añadimos a la cola
                if (activo[v]) {
                    if ((cnt1[v] == 0 || cnt2[v] == 0) && !en_cola[v]) {
                        Q.push(v);
                        en_cola[v] = true;
                    }
                }
            }
        }
    }

    // Si pudimos colocar todos los elementos, la solución es válida
    // Nota que hemos dado valor a todos los nodos cuando el valor más grande que podemos poner es el 0
    if (rango_actual == 0) {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) {
            cout << signo[i] * permutationValues[i] << (i == n ? "" : " ");
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
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

// https://codeforces.com/contest/2245/problem/D1
// https://codeforces.com/contest/2245/problem/D2