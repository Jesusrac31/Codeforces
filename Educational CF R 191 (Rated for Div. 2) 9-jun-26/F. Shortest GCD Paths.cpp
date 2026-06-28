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

double pi = 2*acos(0.0);
const int INF = 1000000007;

vector<int> getDivisors(int n) {
    vector<int> divisores;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisores.push_back(i);
            if (n / i != i) 
                divisores.push_back(n / i);
        }
    }
    ord(divisores);
    return divisores;
}

void getMatrixCostSource(vector<int>& d, vector<vector<int>>& to_d){
    int sz = d.size();
    for (int i = 0; i < sz; i++){
		int u = 0;
		for (int j = i; j >= 0; j--){
			while(u < i && d[i] > d[u] * d[j]) u++;
			if (d[i] % d[j] == 0 && d[i] / d[j] == d[u]) to_d[i][j] = u;
		}
	}
}

void getCandidatesPerDivisor(vector<int>& d, vector<vector<int>>& dels_d){
    int sz = d.size();
    for (int i = 0; i < sz; i++){
		for (int j = 0; j <= i; j++){
			if (d[i] % d[j] == 0){
				dels_d[i].emplace_back(j);
			}
		}
	}
}
 
void solve(){
	int n, a, b;
	cin >> n >> a >> b;
 
    DBG_COUT(cout << "Test: " << n << " " << a << " " << b << endl);

    // Dividimos a y b por el mismo número para que sean coprimos
	int g = gcd(a, b);
	a /= g;
	b /= g;

    DBG_COUT(cout << "New values for a and b: " << a << " " << b << endl);
 
    // Obtenemos los divisores de a
	vector<int> d1 = getDivisors(a);
    int sz1 = d1.size();
    DBG_COUT(cout << "Divisores de a: " << d1 << endl);

    // Obtenemos los divisores de b
    vector<int> d2 = getDivisors(b);
    int sz2 = d2.size();
    DBG_COUT(cout << "Divisores de b: " << d2 << endl);
 
    // to_d1[i][j] = d1[i]/d1[j]. Si tuviera a = d1[i] y hago una operación de coste d1[j], llegaré a to_d1[i][j]
	vector<vector<int>> to_d1(sz1, vector<int> (sz1, -1));
	getMatrixCostSource(d1, to_d1);
    DBG_COUT(cout << "Destino si hago una operación de coste j desde i en d1: " << to_d1 << endl);
 
    // Lo mismo que to_d1 para d2
	vector<vector<int>> to_d2(sz2, vector<int> (sz2, -1));
	getMatrixCostSource(d2, to_d2);
    DBG_COUT(cout << "Destino si hago una operación de coste j desde i en d2: " << to_d2 << endl);
 
    // Obtiene para cada i, cuales d1[j] son divisores de d1[i]. Estos son los posibles costes de una operación desde este punto.
	vector<vector<int>> dels_d1(sz1);
    getCandidatesPerDivisor(d1, dels_d1);
    DBG_COUT(cout << dels_d1 << endl);
 
    // Lo mismo para d2
	vector<vector<int>> dels_d2(sz2);
	getCandidatesPerDivisor(d2, dels_d2);
    DBG_COUT(cout << dels_d2 << endl);
 
    // dp[i][j] es el coste mínimo para transformar d1[i] en 1 y d2[j] en 1
	vector<vector<int>> dp(sz1, vector<int> (sz2, -1));
 
	auto go = [&](auto&& self, int x, int y) -> int{
		if (dp[x][y] != -1) return dp[x][y]; // Si ya está calculado, devuelve el resultado
		if (x == 0 && y == 0) return 0; // Caso base, transformar el d1[0] = 1 en 1 es coste 0. Lo mismo aplica para d2[0]
		
        // Caso general
        dp[x][y] = INF; // Asumimos que el coste es infinito
		for (int dx : dels_d1[x]){ // Por cada uno de los candidatos de d1[i]
			for (int dy : dels_d2[y]){ // Por cada uno de los candidatos de d2[j]
				if (dx == 0 && dy == 0) continue;
                // El valor sería el máximo de ambos más la distancia de transformar los destinos a aplicar operaciones de estos costes en 1
				dp[x][y] = min(dp[x][y], max(d1[dx], d2[dy]) + self(self, to_d1[x][dx], to_d2[y][dy]));
			}
		}
		return dp[x][y];
	};
 
	cout << go(go, sz1 - 1, sz2 - 1) << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    auto start = chrono::high_resolution_clock::now();
    solve();
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2233/problem/F