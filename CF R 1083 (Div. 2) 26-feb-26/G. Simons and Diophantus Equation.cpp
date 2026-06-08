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

const int MOD = 998244353;

struct Mint {
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
    return a < b;
}

#define ord(vect) sort(vect.begin(), vect.end(), sort_func)
#define rep(x,n) for(int x = 0; x < n; ++x)
#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
#define B begin();
#define E end();
#define copia(v1, v2) copy(v1.begin(), v1.end(), back_inserter(v2));

// Funciones pair
#define F first
#define S second

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

// Imprime cualquier vector
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
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
    int temporal;
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
}

#define INF LONG_LONG_MAX

/*
    Constante suficientemente grande.

    m <= 300000
    2*m <= 600000
    Usamos bits 19..0, es decir, hasta 2^20.
    El trie completo puede tener hasta algo cercano a 2^21 nodos.
*/
const int N = (1 << 21) + 10;

int tot;

// Trie binario
int hijo[N][2];
int cantidadTrie[N];
int tamSubarbol[N];
int padreTrie[N];

// f[T] = número de triples, sin contar casos con XOR 0,
// tales que T divide a (i^j) y a (j^k).
lli f[N];

// Arrays auxiliares del trie
lli suma[N];

// Criba de Möbius
int primos[N];
int visitado[N];
int miu[N];

void limpiar_trie_y_auxiliares() {
    for(int i = 0; i <= tot; i++) {
        hijo[i][0] = hijo[i][1] = 0;
        cantidadTrie[i] = 0;
        tamSubarbol[i] = 0;
        padreTrie[i] = 0;
        suma[i] = 0;
    }
}

void calcular_mobius(int limite) {
    miu[1] = 1;
    tot = 0;

    for(int i = 2; i <= limite; i++) {
        visitado[i] = 0;
        miu[i] = 0;
    }

    for(int i = 2; i <= limite; i++) {
        if(!visitado[i]) {
            primos[++tot] = i;
            miu[i] = -1;
        }

        for(int j = 1; j <= tot && 1LL * primos[j] * i <= limite; j++) {
            int x = primos[j] * i;
            visitado[x] = 1;

            if(i % primos[j] == 0) {
                miu[x] = 0;
                break;
            }

            miu[x] = -miu[i];
        }
    }
}

void insertar_en_trie(int x) {
    int nodo = 1;

    for(int bit = 19; bit >= 0; bit--) {
        int b = (x >> bit) & 1;

        if(!hijo[nodo][b]) {
            hijo[nodo][b] = ++tot;
            padreTrie[tot] = nodo;
        }

        nodo = hijo[nodo][b];
    }

    while(nodo) {
        tamSubarbol[nodo]++;
        nodo = padreTrie[nodo];
    }
}

void construir_trie(int m) {
    tot = 1;

    for(int x = 0; x <= m; x++) {
        insertar_en_trie(x);
    }
}

/*
    Esta función calcula todos los f[T].

    f[T] cuenta pares de XOR positivos:

        a = i ^ j
        b = j ^ k

    tales que:

        T | a
        T | b

    y además i,j,k están en [0,m].

    Los casos a = 0 o b = 0 se añaden después aparte.
*/
void calcular_f(int m) {
    for(int T = 1; T <= 2 * m; T++) {
        f[T] = 0;

        /*
            Primera pasada:
            Marcamos en el trie los conjuntos asociados a cada múltiplo de T.
        */
        for(int d = 1; d <= 2 * m / T; d++) {
            int nodo = 1;
            int bg = 0;
            int valor = (d * T) ^ m;

            for(int bit = 19; bit >= 0; bit--) {
                int x = (valor >> bit) & 1;

                if((m >> bit) & 1) {
                    int u = hijo[nodo][x ^ 1];
                    if(u) {
                        cantidadTrie[u]++;
                        suma[u] += tamSubarbol[u];
                    }
                }

                if(!hijo[nodo][x]) {
                    bg = bit + 1;
                    break;
                }

                nodo = hijo[nodo][x];
            }

            lli num = 0;

            if(!bg) {
                cantidadTrie[nodo]++;
                suma[nodo]++;
                num++;
            }

            for(int bit = bg; bit <= 19; bit++) {
                nodo = padreTrie[nodo];

                int x = (valor >> bit) & 1;

                if((m >> bit) & 1) {
                    int u = hijo[nodo][x ^ 1];
                    num += tamSubarbol[u];
                }

                suma[nodo] += num;
            }
        }

        /*
            Segunda pasada:
            Consultamos el trie y acumulamos intersecciones.
        */
        for(int d = 1; d <= 2 * m / T; d++) {
            int nodo = 1;
            int valor = (d * T) ^ m;

            lli num = 0;

            for(int bit = 19; bit >= 0; bit--) {
                int x = (valor >> bit) & 1;

                num += cantidadTrie[nodo];

                if((m >> bit) & 1) {
                    int u = hijo[nodo][x ^ 1];

                    if(u) {
                        f[T] += suma[u] + num * tamSubarbol[u];
                    }
                }

                nodo = hijo[nodo][x];
                if(!nodo) break;
            }

            if(nodo) {
                f[T] += suma[nodo] + num * tamSubarbol[nodo];
            }
        }

        /*
            Tercera pasada:
            Limpiamos solo los nodos que hemos tocado para este T.
            Esto evita limpiar todo el trie cada vez.
        */
        for(int d = 1; d <= 2 * m / T; d++) {
            int nodo = 1;
            int valor = (d * T) ^ m;

            for(int bit = 19; bit >= 0; bit--) {
                int x = (valor >> bit) & 1;

                int u = hijo[nodo][x ^ 1];

                cantidadTrie[nodo] = 0;
                suma[nodo] = 0;

                if(u) {
                    cantidadTrie[u] = 0;
                    suma[u] = 0;
                }

                nodo = hijo[nodo][x];
                if(!nodo) break;
            }

            if(nodo) {
                cantidadTrie[nodo] = 0;
                suma[nodo] = 0;
            }
        }
    }
}

/*
    Añade los casos especiales:

        i == j  ->  i ^ j = 0
        j == k  ->  j ^ k = 0

    Si uno de los dos coeficientes es 0, la ecuación sigue pudiendo
    tener solución siempre que el otro XOR divida a n.
*/
lli contar_casos_xor_cero(int n, int m) {
    lli res = 0;

    for(int g = 1; g <= 2 * m; g++) {
        if(n % g != 0) continue;

        int nodo = 1;
        int valor = g ^ m;

        for(int bit = 19; bit >= 0; bit--) {
            int x = (valor >> bit) & 1;

            if((m >> bit) & 1) {
                int u = hijo[nodo][x ^ 1];

                if(u) {
                    /*
                        Factor 2:
                        - i == j
                        - j == k
                    */
                    res += 2LL * tamSubarbol[u];
                }
            }

            nodo = hijo[nodo][x];

            if(!nodo) break;
        }

        if(nodo) {
            res += 2;
        }
    }

    return res;
}

int solve() {
    int n, m;
    cin >> n >> m;

    /*
        Limpiamos estructuras del test anterior.
    */
    limpiar_trie_y_auxiliares();

    /*
        Necesitamos Möbius hasta 2*m porque los XOR relevantes
        están acotados por aproximadamente 2*m en esta solución.
    */
    calcular_mobius(2 * m);

    /*
        Construimos un trie con todos los números de 0 a m.
    */
    construir_trie(m);

    /*
        Calculamos f[T] para T = 1..2*m.
    */
    calcular_f(m);

    lli ans = 0;

    /*
        Inversión de Möbius.

        Queremos contar triples donde:

            gcd(i^j, j^k) | n

        Si d | n, sumamos los casos donde el gcd exacto es d.
        Eso se obtiene usando miu[j] * f[j*d].
    */
    for(int d = 1; d <= 2 * m; d++) {
        if(n % d != 0) continue;

        for(int j = 1; j <= 2 * m / d; j++) {
            ans += 1LL * miu[j] * f[j * d];
        }
    }

    /*
        Añadimos casos donde uno de los XOR es cero.
    */
    ans += contar_casos_xor_cero(n, m);

    cout << ans << '\n';

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

// https://codeforces.com/contest/2205/problem/G