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
#define index second
#define value first

vector<Mint> factorial = {1};
Mint fact(int n){
    while (factorial.size() <= n) {
        factorial.PB(factorial.back()*factorial.size());
    }
    return factorial[n];
}


bool isProperElement(vll& a, int i, int l, int r) {
    lli expected = ((lli)i + 1LL - (lli)l) * ((lli)r - (lli)i);
    return a[i] == expected;
}


pair<lli, int> getProperElement(vll& a, int l, int r) {
    int left = l;
    int right = r - 1;

    /*
        Buscamos desde los dos extremos.

        Si el pivote está cerca de un extremo, lo encontramos rápido.
        Si está en el centro, el intervalo se divide bastante equilibrado.
    */
    while (left <= right) {
        if (isProperElement(a, left, l, r)) {
            return {a[left], left};
        }

        if (left != right && isProperElement(a, right, l, r)) {
            return {a[right], right};
        }

        left++;
        right--;
    }

    return {-1, -1};
}


Mint calculatePosibles(vll& a, int l, int r) {
    if (l == r) return Mint(1);

    DBG_COUT(cout << "Inspecting range " << l << " " << r << endl);

    pair<lli, int> element = getProperElement(a, l, r);

    if (element.index == -1) {
        DBG_COUT(cout << "No valid element found\n");
        return Mint(0);
    }

    DBG_COUT(
        cout << "Obtained element at " << element.index
             << " with value " << element.value << endl;
    );

    lli expected =
        ((lli)element.index + 1LL - (lli)l) *
        ((lli)r - (lli)element.index);

    if (element.value != expected) {
        DBG_COUT(cout << "Oops, that value was impossible" << endl);
        return Mint(0);
    }

    if (r - l <= 1) return Mint(1);

    int len = r - l;
    int leftSize = element.index - l;
    int rightSize = r - 1 - element.index;

    Mint combinaciones =
        fact(len - 1) / (fact(leftSize) * fact(rightSize));

    Mint sol = combinaciones;

    DBG_COUT(cout << "Solution before recursion: " << sol << endl);

    sol *= calculatePosibles(a, l, element.index);
    sol *= calculatePosibles(a, element.index + 1, r);

    return sol;
}

int solve(int T) {
    // Code aquí
    int n; cin >> n;
    vll a(n); rep(i, n) cin >> a[i];

    // En primer lugar, veamos propiedades de la lista a de longitud n 0-indexed
    // 1. En la posición a[i] solo puede haber un número en [1, (i+1)*(n-i)]
    // 2. El 1 va en aquel a[i] = (i+1)*(n-i)
    // 3. Solo puede haber un elemento a[i] = (i+1)*(n-i)
    // 4. Al colocar el primer elemento, divides el array en 2 subarrays. ¿Cuántas formas hay de distribuir los elementos?
    //      Resulta que si el 1 está en la posición i, en un subarray habrá i elementos y en el otro n-i-1 elementos
    //      Aprovechando esto, ¿cuántas formas hay de seleccionar i elementos entre n-1? Claramente es n-1 sobre i
    //      (n-1)!/(i! * (n-1-i)!)
    // 5. Por cada subarray, debemos repetir el proceso

    // Visto todo lo anterior, podemos aplicar una estrategia divide y vencerás, 
    // Queda un problema pos solucionar y es el método de búsqueda del elemento donde colocar el número que toque
    // Según el índice l y r, en la posición i debe haber un número u otro para ser válido.
    // Si tenemos seleccionado un rango [l,r) y dos posiciones son posibles, al seleccionar una de ellas, la otra no podrá usarse, lo que significa que para cada rango que usemos solo puede haber un candidato.
    // Necesitamos poder buscar de forma eficiente el valor que cumpla con la condición si existe.

    Mint sol = calculatePosibles(a, 0, n);

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
        solve(T);
    }
    auto finish = chrono::high_resolution_clock::now();
    DBG_COUT(
        chrono::duration<double> elapsed = finish - start;
        cout << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
        cerr << "Tiempo de ejecucion: " << elapsed.count() << " segundos\n";
    );
    return 0;
}

// https://codeforces.com/contest/2234/problem/E