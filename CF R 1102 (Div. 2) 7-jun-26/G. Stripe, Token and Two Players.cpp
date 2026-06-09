#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#pragma GCC optimize("O3")
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

int solve() {
    // Decimos que un estado del juego viene definido por state[index][value]
    // Donde index es la posición del token y value es el valor del token.
    // state[i][j] es 1 o 0, siendo 1 si gana el jugador 1 y 0 si gana el jugador 2
    // Tenemos que obtener state[1][1]

    // Usamos sprague-grundy, pero al ser un unico problema grande, no necesitamos 
    // los números de grundy, tan solo si la situación es ganadora o no.

    // Sabemos que state[i][j] = 1 <-> existe state[i+x][j+y] = 0 para x perteneciente a [0, j+y] e y perteneciente a [0, a[i]]
    // Usando esta propiedad tenemos una solución O(n^3) como mucho ya que state[n][j] = 0.

    // Además, si a[i] es demasiado grande podemos simplemente reducir su valor.

    // Si decimos que el index son las columnas y las filas son el value:
    // Recorreremos las columnas de derecha a izquierda
    // Cada fila tendrá una tag de si está habilitada o deshabilitada.
    // Cuando la fila i está deshabilitada, significa que existe state[i+x][j] = 0 para x perteneciente a [0, j]
    // Con una sucesion de eventos, cuando deshabilitemos una fila, introduciremos cuando debe volver a habilitarse
    // Luego para computar cuales deshabilitar en cada rango, por columna, almacenaremos los intervalos de filas habilitadas.
    // Aplicaremos la propiedad de que si la fila i+x está deshabilitada para x perteneciente a [1, a[i]], entonces state[index][i] será 1
    // En caso contrario será 0 y habría que deshabilitarla

    int n;
    cin >> n;

    vector<long long> a(n);
    rep(i, n) cin >> a[i];

    /*
        libres = intervalos de potencias que NO están deshabilitadas.

        Si una potencia p NO está libre, significa que existe una posición
        perdedora alcanzable usando potencia p desde el índice actual.
    */
    set<pii> libres;
    libres.insert({1, n});

    vector<vector<int>> eventos(n + 1);

    bool estadoInicialPerdedor = false;

    auto removeSafe = [&](int p) {
        /*
            Quita p del conjunto de intervalos libres.
        */
        auto it = libres.upper_bound({p, INF});

        if (it == libres.begin()) return;
        --it;

        int l = it->first;
        int r = it->second;

        if (p < l || p > r) return;

        libres.erase(it);

        if (l <= p - 1) {
            libres.insert({l, p - 1});
        }

        if (p + 1 <= r) {
            libres.insert({p + 1, r});
        }
    };

    auto addSafe = [&](int p) {
        /*
            Añade p al conjunto de intervalos libres, fusionando con vecinos.
        */

        int l = p;
        int r = p;

        auto itRight = libres.lower_bound({p + 1, -INF});

        if (itRight != libres.end() && itRight->first == p + 1) {
            r = itRight->second;
            libres.erase(itRight);
        }

        auto itLeft = libres.lower_bound({p, -INF});

        if (itLeft != libres.begin()) {
            --itLeft;

            if (itLeft->second + 1 == p) {
                l = itLeft->first;
                libres.erase(itLeft);
            }
        }

        libres.insert({l, r});
    };

    /*
        Procesamos de derecha a izquierda.
        No procesamos index = n, porque la celda final se maneja con
        la condición de ganar directamente.
    */
    for (int index = n - 1; index >= 0; index--) {
        DBG_COUT(cout << "Index " << index << endl);

        /*
            Reactivamos potencias cuyo cooldown ha terminado.
        */
        for (int p : eventos[index]) {
            DBG_COUT(cout << "Reactivando potencia " << p << endl);
            addSafe(p);
        }

        /*
            Si value + a[index] >= n - index, el jugador puede saltar
            directamente al final y gana.

            Solo pueden ser perdedores los value tales que:
                value + a[index] < n - index

            value <= n - index - a[index] - 1
        */
        long long add = min<long long>(a[index], n);
        long long maxValueLL = (long long)n - index - add - 1;

        if (maxValueLL < 1) {
            continue;
        }

        int maxValue = (int)min<long long>(maxValueLL, n);

        vector<int> nuevosPerdedores;

        /*
            Ahora recorremos intervalos libres, NO todos los values.

            Si [L, R] es libre, entonces [value, value+add] está libre
            cuando:
                value >= L
                value + add <= R

            Por tanto:
                value <= R - add
        */
        for (auto it = libres.begin(); it != libres.end(); ++it) {
            int L = it->first;
            int R = it->second;

            if (L > maxValue) break;

            long long hastaLL = min<long long>(maxValue, (long long)R - add);

            if (hastaLL < L) continue;

            int hasta = (int)hastaLL;

            for (int value = L; value <= hasta; value++) {
                nuevosPerdedores.push_back(value);

                if (index == 0 && value == 1) {
                    estadoInicialPerdedor = true;
                }
            }
        }

        /*
            Aplicamos todos los nuevos perdedores después de terminar
            la columna actual.
        */
        for (int value : nuevosPerdedores) {
            removeSafe(value);

            /*
                Si (index, value) es perdedor, será alcanzable desde:
                    index - value, ..., index - 1

                Cuando lleguemos a:
                    index - value - 1
                deja de ser alcanzable.
            */
            int removeAt = index - value - 1;

            if (removeAt >= 0) {
                eventos[removeAt].push_back(value);
            }

            DBG_COUT(
                cout << "Perdedor: index=" << index
                     << " value=" << value
                     << " removeAt=" << removeAt << endl;
            );
        }
    }

    cout << (estadoInicialPerdedor ? 2 : 1) << '\n';

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

// https://codeforces.com/contest/2234/problem/G