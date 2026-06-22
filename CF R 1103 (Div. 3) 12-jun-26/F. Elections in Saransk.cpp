#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
// #pragma GCC optimize("O3")
#pragma GCC optimize("O3,unroll-loops") // En este problema en concreto le da el empujón que le falta para entrar en tiempo
// #pragma GCC target("avx2")

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

const int MOD = 1e9 + 7; // Módulo del problema, cambiar en caso de no ser ese. NO TIENE PORQUÉ SER CONSTANTE, SOLO GLOBAL

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

vector<int> P;

void criba(int n){
    vector<bool> us(n);
    for (int i = 2; i < n; ++i) {
        if (!us[i]) {
            P.push_back(i);
            for (int j = i * i; j < n; j += i) {
                us[j] = true;
            }
        }
    }
}

void getFactors(int &x, map<int, int>& cnt) {
    for (auto w : P) {
        if (w * w > x) break;
        while (x % w == 0){
            x /= w;
            cnt[w]++;
        }
    }
    if (x > 1) cnt[x]++;
}

int solve() {
    // Code aquí
    int n, x; cin >> n >> x;
    vi a(n); rep(i, n) cin >> a[i];
    DBG_COUT(cout << "Test: " << x << " -> " << a << endl);

    // Buscamos x * lcm(p[1], p[2], ..., p[n]) = p[1] * p[2] * ... * p[n]
    // Para x = 1, necesitamos que todos los elementos sean primos entre sí, es decir, al factorizarlos no pueden compartir ningún número primo
    // Entonces cada número primo tiene 1+sum(expV(p[i], pr)) posibilidades. Donde expV(x, y) es el máximo número k tal que y^k | x y pr es el número primo que tratamos
    // Tan solo multiplica estos valores

    // Si x > 1, es divisible por algún primo, llamemosle pr. Se debe cumplir que sum(expV(p[i], pr)) = max(expV(p[i], pr)) + expV(x, pr)
    // Entonces, para x = 1, sum(expV(p[i], pr)) = max(expV(p[i], pr)) + expV(1, pr) <-> sum(expV(p[i], pr)) = max(expV(p[i], pr)). La solución es 1+sum(expV(p[i], pr))
    // En caso contrario usaremos dp por cada pr que divida a x para hayar cuantas formas se pueden repartir cada número primo.
    // Los pr que no dividan a x, se pueden calcular de forma tradicional como si x = 1

    // dp[i][mx][s] = De cuantas formas puedes elegir los elementos hasta p[i] si:
    // - max(expV(p[j], pr)) = mx
    // - sum(expV(p[i], pr)) = s
    // La solución que buscamos sería sum(dp[n][i][i + j] | 1 <= i+j <= sum(expV(p[i], pr)))

    // Como por las constraints del problema expV(p[j], pr) <= 18 (2^18 > 5*10^5), lo máximo es que expV(a[i], pr) = 18 y expV(x, pr) = 18. Por lo que 1 <= S <= 36
    // De la misma forma, mx <= 18, por lo que aunque parezca un dp de grandes dimensiones, no es tan grande

    // Las transiciones son:
    // - Añado e veces pr en la posición i pero e <= mx: dp[i+1][mx][s+e] += dp[i][mx][s]
    // - Añado e veces pr en la posición i pero e > mx: dp[i+1][e][s+mx] += dp[i][mx][s]

    // Primos de x
    map<int, int> cnt;
    getFactors(x, cnt);
    DBG_COUT(cout << "Primes for x = " << x << ":" << endl; for (auto i:cnt) cout << i.first << " -> " << i.second << " times" << endl);

    // w1 almacena el exponente del iésimo elemento divisible entre pr
    map<int, vector<int>> w1;
    for (int i = 0; i < n; ++i) {
        for (auto w: P) {
            if (w * w > a[i]) {
                break;
            }
            int sum = 0;
            while (a[i] % w == 0) {
                a[i] /= w;
                sum++;
            }
            if (sum > 0) {
                w1[w].push_back(sum);
            }
        }
        if (a[i] > 1) {
            w1[a[i]].push_back(1);
        }
    }
    DBG_COUT(cout << "w1: " << endl; for (auto i:w1) cout << i.first << " -> " << i.second << endl);

    Mint Ans = 1;
    for (auto [id, e]: w1) {
        // Busca la posición donde pueda poner una mayor cantidad de veces el primo id
        int mx = 0;
        for (auto s: e) {
            mx = max(mx, s);
        }

        // Recuerda, sum(expV(p[i], pr)) = max(expV(p[i], pr)) + expV(x, pr). cnt[id] = expV(x, pr); mx = max(expV(p[i], pr))
        vector<vector<Mint>> dp(cnt[id] + 1, vector<Mint>(mx + 1));
        dp[0][0] = 1;
        for (auto w: e) {
            vector<vector<Mint>> dp1(cnt[id] + 1, vector<Mint>(mx + 1));
            for (int i = 0; i <= w; ++i)
                for (int j = 0; j <= cnt[id]; ++j) 
                    for (int k = 0; k <= mx; ++k) 
                        if (j + min(i, k) <= cnt[id]) 
                            dp1[j + min(i, k)][max(i, k)] += dp[j][k];
            swap(dp, dp1);
        }
        Mint s = 0;
        for (int i = 0; i <= mx; ++i) {
            s += dp[cnt[id]][i];
        }
        Ans *= s;
        cnt[id] = 0;
    }

    for (auto s: cnt) if (s.second > 0) Ans = 0; // Si queda algún primo sin tratar, la respuesta es 0
        
    DBG_COUT(cout << "Solucion: ");
    cout << Ans << endl;
    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    auto start = chrono::high_resolution_clock::now();
    int T;
    cin >> T; // Número de casos
    criba(1e4);
    while (T--) {
        solve();
        DBG_COUT(cout << "===================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2236/problem/F1
// https://codeforces.com/contest/2236/problem/F2