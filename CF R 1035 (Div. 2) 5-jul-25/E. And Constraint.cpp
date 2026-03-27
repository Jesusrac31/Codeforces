#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef pair<int, int> pii;
typedef pair<int, lli> pil;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones vector
#define PB(a) push_back(a);

bool sort_func(int a, int b) {
    if (a < b) {
        return true;
    } else {
        return false;
    }
}
#define ord(vect) sort(vect.begin(), vect.end(), sort_func);

#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
#define B begin();
#define E end();
#define copia(v1, v2)                                                                                                                    \
    ;                                                                                                                                                        \
    copy(v1.begin(), v1.end(), back_inserter(v2));

// Funciones map
#define F first;
#define S second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

void Imprime(vi vect) {
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << "\n";
}

void Imprime2d(vector<vi> vect) {
    for (int j = 0; j<vect.size(); j++){
        for (int i = 0; i < vect[j].size(); i++) {
                cout << vect[j][i] << " ";
        }
        cout << "\n";
    }
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

vi lee(int n) {
    int el;
    vi vect;
    for (int i = 0; i < n; i++) {
        cin >> el;
        vect.PB(el);
    }
    return (vect);
}

#define BITS 30
#define Imposible "-1"
const lli inf=0x3f3f3f3f3f3f3f3f; //Definimos un valor como infinito 

int solve(){
    // Detecta el input
    int n;
    cin >> n;
    vector<int> a(n+1), b(n+2), objetivo(n);
    a[0] = 0;
    for (int i = 1; i<n; i++){
        cin >> a[i];
    }
    for (int i = 1; i<=n; i++){
        cin >> b[i];
    }

    // Creamos f y g, son los arrays que almacenarán los candidatos para x[i-1] y x[i] respectivamente,
    // siendo x el array que contendría el array final de b
    vector<pil> f, g = {}; // Cada elemento representa el valor de su x y el coste que acarrea del anterior índice
    f.PB(pil({0, 0}));  // Para x[0] el coste de operaciones sería 0, ya que expandimos a de forma que empiece con un 0
                        // De esta forma, el coste que acarrea es 0 y el coste de hacer esa operación es 0 tambien (asume que b[0] = 0)

    for (int i = 1; i<=n; i++){ // Por cada valor de i, cada elemento en la lista b
        int x = 0;  // Esta variable tomará valores escalonados solo si el bit que va a añadir está en b.
                    // Solo utilizamos los escalonados porque nos sirven como candidatos de forma que optimizaos en iteraciones.
                    // Esto se debe a que b[i] = a[i] | (b[i-1] & b[i]) que es una fórmula que se deduce de la premisa principal y de que b[i] = a[i-1] | a[i].
                    // De esta forma minimizamos el número de 1s que metemos en nuestros candidatos, ya que introducir una gran cantidad dificulta la operación and y aumenta las operaciones.
        for (int j = BITS; j>=-1; j--){ // Por cada bit posible
            int y = x | a[i-1] | a[i];  // El valor y contiene el candidato para x[i], este tiene que contener al menos los bits en a[i] | a[i-1]. Además, cada candidato debe contener los bits de su escalonado.
            if (j != -1){ // Pasamos por todos los valores válidos (tienen los bits de a[i-1] | a[i]) que además sea mayor o igual a b[i], terminando en b[i] con el -1
                y |= (1<<j);
            }
            if (y >= b[i]){ // Solo en caso de que y>=b[i], en caso contrario no es un candidato ya que mi operación solo permite sumar 1
                lli minimo = inf; //Aquí almacenaremos el coste mínimo de este candidato. Inicialmente el coste es infinito, ya que se asume de que no se puede usar dicho candidato porque no cumple la premisa
                for (pil l:f){  // Por cada candidato anterior, vamos a revisar si cumple la premisa del problema (x[i-1] & x[i] == a[i-1])
                                // En caso de que sea así, actualizatemos el coste mínimo.
                    if ((l.first&y) == a[i-1]){
                        minimo = min(minimo, l.second+(y-b[i])); // El coste de este caso sería el coste que acarrea más la diferencia entre el elemento b[i] y el valor candidato actual (y)
                    }
                }
                if (minimo<inf){ // En caso de que haya un candidato que cumpla las condiciones, añadimos el nuevo candidato a g
                    g.PB(pil({y,minimo}));
                }
            }
            x |= ((1<<j) & b[i]); // Actualizamos el valor escalonado si el bit que vamos a añadir está activo en b
                                  // Ayuda a que al seleccionar el bit y>b[i]
        }
        swap(f, g); // Intercambian f y g, ya que en la siguiente iteración, f debe ser la actual g
        g.clear();  // Limpiamos g para la siguiente iteración
    }
    // Buscamos el candidato que acarree el menor coste
    lli minimo = inf;
    for (pil l:f){
        minimo = min(minimo, l.second);
    }

    if (minimo == inf){ // No se puede obtener la solución
        cout << Imposible << endl;
    } else {
        cout << minimo << endl;
    }

    return 0;
}

int main() {
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
// https://codeforces.com/contest/2119/problem/E
