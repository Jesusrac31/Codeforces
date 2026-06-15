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

#define INF 1e9
double pi = 2*acos(0.0);

// Algoritmo de euclides extendido
lli gcd(lli a, lli b, lli &x, lli &y){
    if(b == 0){
        x= 1; y = 0;
        return a;
    }
    lli x1, y1;
    lli d = gcd(b, a%b, x1, y1);
    x = y1;
    y = x1 - y1*(a/b);
    return d;
}

int solve() {
    // Code aquí
	lli n, a, b, k;
    cin >> n >> a >> b >> k;
	DBG_COUT(cout << "Test: " << n << " " << a << " " << b << " " << k << endl);
	DBG_COUT(cout << "Ecuaciones: " << a << " * x[i+1] + " << b << " * x[i] = " << k << endl);

	// Partimos de la ecuación diofántica a * x[i+1] + b * x[i] = k. Siendo x[i] el número de minutos que calientas un pancake 
	// antes de mover los pancakes de sarten. Entonces la ecuación si se cunple, significa que el pancake i+1 se cocina bien (cookedness = k)

	// Define g como el máximo común divisor de a y b
    lli g = __gcd(a, b);
	DBG_COUT(cout << "GCD(a, b) = " << g << endl);

	// En caso de k no ser divisible por g, como en cualquier ecuación diofántica, ninguna tiene solución.
    if(k % g != 0){
		DBG_COUT(cout << "No se pueden satisfacer las ecuaciones..." << endl << "Solucion: ");
        cout << "0\n";
        return 0;
    }

	// Dividimos todos los valores entre g. Esto hace que se simplifiquen las ecuaciones y a efectos prácticos el número de soluciones permanece constante.
    a /= g; b /= g; k /= g;

	// Si a y b son 1 (a y b originales eran el mismo número), como sabemos que las ecuaciones tienen solución, el resultado es n, al haber n ecuaciones
    if(a == 1 && b == 1) {
		DBG_COUT(cout << "a = b, todas son soluciones." << endl << "Solucion: ");
        cout << n << "\n";
        return 0;
    }
	DBG_COUT(cout << "Nuevos valores: " << a << " " << b << " " << k << endl);

    // Si no es uno de los casos bases, empezamos el proceso general:

	// Paso 1: Cocina los primeros pancakes. La ecuación del pancake 0 es a * x[0] = k, así que lo que tenemos que hacer es satisfacer dicha ecuación si fuera posible.
	// Continuamos con todas las demás ecuaciones hasta que nos sea imposible satisfacer la siguiente.
    DBG_COUT(cout << "Empezando paso 1..." << endl);
	lli ans = 0;
    if(k % a == 0) { // Si se puede satisfacer a * x[0] = k
        ans++; n--; // Reducimos el número de ecuaciones y aumentamos el número de ecuaciones satisfechas
        lli x = k / a; // Fija el valor de x[0]
        while(n > 0) { // Mientras que queden ecuaciones disponibles
            DBG_COUT(cout << "Ultima x: " << x << endl);
			if(k - (x * b) < 0 || (k - x * b) % a != 0) break; // En caso de no poder satisfacer la siguiente ecuación, pasa al paso 2
			// En caso de satisfacerla, añade 1 al número de ecuaciones satisfechas y reduce el número de ecuaciones restantes
			// Fija tambien el nuevo x[i]
            x = (k - x * b) / a;
            ans++;
            n--;
        }
    }
	DBG_COUT(cout << "Soluciones del paso 1: " << ans << endl);

    // Paso 2: Busca cual es la secuencia más larga de x[0], x[1], ..., x[v] donde x[i+1] = (k - b * x[i])/a [Ecuación recursiva obtenida del principio]
	// Ten en cuenta que todas las x[i] deben ser enteros no negativos. ¿Cuál es el valor máximo de v?
    
    // En vez de hacer una secuencia, vamos a usar una función f(x) = (k - b * x[i])/a. De esta forma, x[0] = f(x), x[2] = f(f(f(x))). Digamos que x[i] corresponde a f^(i+1)(x)
    // Entonces, f^i(x) = (-b/a)^i * (x - L) + L. Donde L es el punto tal que f(x) = x, L = k/(a+b)

    lli v = 0;
    if(k % (a + b) == 0) v = INF; // Bucle infinito, la secuencia converge en un número entero por lo que la solución es máxima y la secuencia tiene longitud infinita (v = INF)
    else {
        if(a < b) swap(a, b);
        // Estaremos resolviendo la ecuación diofántica (a + b) x + m y = k
        // Esta sale de la formula x[i+1] = (k - b * x[i])/a. Esto sigue una progresión afin. 
        // Define e[i] = x[i] - x[i-1]. Entonces, e[i] = (k - b * x[i-1])/a - (k - b * x[i-2])/a = b * (x[i-1] - x[i-2])/a = b * e[i-1] / a. 
        // Entonces e[v] sigue una progresión geométrica. Así que e[v] = (b/a)^v (e[0])
        // Podemos decir entonces que a^v * e[v] - b^v * e[0] = 0.
        // Si decimos que e[v] = y, x[0] = x[1] + a^v * y.
        // Como a * x[1] + b * x[0] = k <-> a * x[1] + b * (x[1] + a ^ v * y) = k <-> (a+b) x[1] + b * a^v * y
        // Definimos m = b * a^v y x[1] 0 x. Entonces nos queda resolver la ecuación (a+b) * x + m * y = k
        // Esta parte del código tan solo aumenta v poco a poco 

		lli m = b; // m = b * a^v, al inicio v = 0, por lo que m = b
        while(true) {
            lli x, y;
            gcd(a + b, m, x, y); // Obten una solución a la ecuacion diofántica

            if(x < 0) {x += m; y -= a + b;} // Haz que la solucion tenga una x no negativa
            x *= k; y *= k; // Adapta la solución para que de k
            lli d = x / m; 
        	x -= d * m; y += d * (a + b); // Obtiene la solución positiva


        	if(m / b * y + x < 0) break;

        	// Aunque exista solución, solo comprueba que el inicio y el fin están correctos, por lo que buscamos si las soluciones intermedias son correctas
        	bool ok = true;
        	lli x1 = x, x2 = m / b * y + x;
        	for(int _=0; _<v; _++)
        	{
        	    if(a * x1 + b * x2 != k) ok = false;

        	    if((k - b * x1) % a)
        	    {
        	        ok = false;
        	        break;
        	    }

        	    x2 = x1;
        	    x1 = (k - b * x1) / a;
        	}

        	if(!ok) break;

        	v++;

        	if(a > k / m) break;
        	m *= a;
    	}
    }

    DBG_COUT(cout << "Valor obtenido del paso 2: " << v << endl);
	DBG_COUT(cout << "Numero de ecuaciones satisfechas por el paso 2: " << (n - (n + v) / (v + 1)) << endl);

	DBG_COUT(cout << "Solucion: ");
    cout << ans + (n - (n + v) / (v + 1)) << "\n"; // Cada v + 1 números, hay v correctos y 1 incorrecto
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
		DBG_COUT(cout << "========================================" << endl);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2232/problem/F