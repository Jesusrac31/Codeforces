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
    os << "]\n";
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

void processN(vector<vector<char>>& dp, int r, int c){
    dp[r][c] = 'N';
    c--;
    r++;
    while(c >= 0){
        dp[r][c] = 'D';
        c--;
        r++;
    }
    c += r;
    r = 0;
    while(dp[r][c] != 'N'){
        dp[r][c] = 'R';
        c--;
        r++;
    }
    dp[r][c] = '?';
}
void processD(vector<vector<char>>& dp, int r, int c){
    while(c >= 0){
        dp[r][c] = 'D';
        c--;
        r++;
    }
}
void processR(vector<vector<char>>& dp, int r, int c){
    while(r >= 0){
        dp[r][c] = 'R';
        c++;
        r--;
    }
}

int solve() {
    // Code aquí
    int n, k; cin >> n >> k;
    vector<vector<char>> dp(n, vector<char>(n, '?'));

    // dp[i][j] es si la casilla en la fila i columna j llega una serpiente por su izquierda ('R'), por arriba ('D')
    // O la serpiente que aparece es nueva 'N'. Entonces se cumple que:
    // dp[0][0] = 'N'
    // dp[i][j] = 'N' -> dp[i-1][j+1] = 'R'
    // dp[i][j] = 'N' -> dp[i+1][j-1] = 'D'
    // dp[i][j] = 'R' -> dp[i-1][j+1] = 'R'
    // dp[i][j] = 'D' -> dp[i+1][j-1] = 'D'
    // Finalmente transformamos todas las no determinadas como interrogantes y las que tienen 'N' tambien. Ahora decimos que cada serpiente
    // puede empezar su trayecto en una diagonal negativa, solo tenemos que determinar cuantas posibilidades hay de colocar cada serpiente y multiplicarlo
    // El número de posibilidades es el número de '?' que hay en cada diagonal así que tan solo cuentalas y multiplica.
    dp[0][0] = '?'; // Inicio serpiente
    while (k--){
        int l, r, c; cin >> l >> r >> c; r--; c--;
        string s; if (l > 1) cin >> s;
        DBG_COUT( cout << r << " " << c << " " << s << endl);
        processN(dp, r, c);
        for (auto x:s){
            DBG_COUT(cout << x << endl);
            if (c+r >= n-1) break;
            if (x == 'R'){
                c++;
                processR(dp, r, c);
            } else {
                r++;
                processD(dp, r, c);
            }
        }
    }
    
    Mint sol = 1;
    for (int i = 0; i<n; i++){
        int col = i;
        int row = 0;
        Mint d = 0;
        while (col >= 0){
            if (dp[row][col] == '?') d+=1;
            row++;
            col--;
        }
        sol *= d;
    }
    cout << sol << endl;
    

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

// https://codeforces.com/contest/2232/problem/E