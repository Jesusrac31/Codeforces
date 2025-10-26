#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
#include<unordered_set>
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
template<typename T> std::ostream& operator<<(std::ostream& os, const Mint& m) {
    os << m.v << " ";
    return os;
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
#define x first
#define sl second

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

template<typename T, typename Q> std::ostream& operator<<(std::ostream& os, const std::pair<T, Q>& p) {
    os << "(" << p.first << ", " << p.second << ")";
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

#define MAXQ 5005

Mint fact[MAXQ], inv[MAXQ];

int solve() {
    // Input
    int n, m, q;
    cin >> n >> m >> q;
    vector<Mint> b(n);
    for (int i = 0; i<n; i++){
        cin >> b[i];
        b[i] -= i;
    }
    vector<pair<Mint, Mint>> ops(q);
    for (int i = 0; i<q; i++){
        cin >> ops[i].sl >> ops[i].x;
        ops[i].sl -= 1;
        ops[i].x -= ops[i].sl;
    }
    sort(ops.begin(), ops.end());

    vector<Mint> ans(n);
    for (int slider = 0; slider < n; slider++){
        Mint cl = 0, cr = 0;
        bool flag = true;
        for (int op_f = 0; op_f < q; op_f++){
            if ((ops[op_f].sl <= slider && ops[op_f].x>=b[slider]) || (ops[op_f].sl>=slider && ops[op_f].x<b[slider])){
                flag = false;
            }
            if(ops[op_f].sl<=slider){
                cr=cr+1;
            }
        }
        if (flag){
            ans[slider] = b[slider]+slider;
            continue;
        }

        for(int j=0;j<q;j++){
			if(ops[j].sl<=slider)cr-=1; // Si es una operacion tipo max o assign
			if(ops[j].sl==slider){ // Si es una operación tipo assign
				/*
				Para las e=x de las operaciones de assign, la probabilidad de que termine en la posición e no es más que la probabilidad de que dicha operación assign sea la última que tenga efecto
				Teniendo en cuenta que las operaciones que tienen efecto son cr+cl+1 (+1 para incluir a la propia operación) 
				la probabilidad sería de 1/(cr+cl+1)
				*/
                ans[slider]=(ans[slider]+(ops[j].x+slider)*inv[(cl+cr+1).v]);
            }
			if(ops[j].sl<slider) // Si es una operacion tipo max
			{
				/*
				En caso de que la operación sea tipo max, tenemos que tener en cuenta 2 casos:
					1.  La única operación que afecta es la propia operación max y la posición inicial está a la izquierda.
						En este caso, la probabilidad de que esta operación sea la única que afecte a la posición final es del 100%
					2.  La posición inicial está a la derecha o hay operaciones que tambien afectan.
						En este caso, la probabilidad sería que esta operación sea la última que tenga efecto (1/(cl+cr+1)) al igual que la operación assign
						pero debes contar con que necesitas que justo antes, el slider esté a la izquierda, por lo que debes añadir la probabilidad de que la anterior operación sea tipo min
						esto es cl/(cl+cr) (aquí no sumamos 1, porque la operación que estamos tratando asumimos que está colocada) multiplicamos por cl a 1/(cl+cr) debido a que cualquier operación min que afecte (contabilizadas por cl) podría ir justo antes.
				*/
				if(cl==0&&cr==0&&b[slider]<=ops[j].x)ans[slider]=(ans[slider]+ops[j].x+slider);
				else ans[slider]=(ans[slider]+(ops[j].x+slider)*inv[(cl+cr+1).v]*inv[(cl+cr).v]*cl);
			}
			if(ops[j].sl>slider) // Si es una operación tipo min
			{
				/*
				Este caso es exactamente igual que el de arriba pero simetrico.
				*/
				if(cl==0&&cr==0&&b[slider]>ops[j].x)ans[slider]=(ans[slider]+ops[j].x+slider);
				else ans[slider]=(ans[slider]+(ops[j].x+slider)*inv[(cl+cr+1).v]*inv[(cl+cr).v]*cr);
			}
			if(ops[j].sl>=slider)cl+=1; // Si es una operación tipo min o assign
		}

    }
    for(int x = 0;x < n;x ++){	
		cout<< ans[x]*fact[q] << ' ';
	}
	cout << endl;

    return 0;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int T;
    cin >> T; // Número de casos

    fact[0]=1;
	for(int i=1;i<=5000;i++)fact[i]=fact[i-1]*i;
	inv[1]=1;
	for(int i=2;i<=5000;i++){
        inv[i]=(Mint)(MOD-MOD/i)*inv[MOD%i];
    }

    while (T--) {
        solve();
    }
    return 0;
}