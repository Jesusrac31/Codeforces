#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef pair<int, int> pii;
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

void Imprime(vll vect) {
    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i] << " ";
    }
    cout << "\n";
}

void Imprime2d(vector<vll> vect) {
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

bool nextComb(vi& comb, int n){
    bool exist = false;
    for (int i = n-1; i>=0; i--){
        comb[i]++;
        if (comb[i] == i+2) {
            comb[i]=0;
            continue;
        }
        exist = true;
        break;
    }
    return exist;  
}

int solve() {
    /*
    Para este programa, en vez de plantear todas las combinaciones posibles, buscamos todas las formas de hacer cada combinación posible de eliminación. Es decir,
    lo que buscamos es cuantas formas hay de eliminar el token en la posición 0, luego el 1, y luego el 2. Y así con todas las combinaciones.

    Para ello, nosotros sabemos que un número puede ser eliminado si pertenece al intervalo [a_i, i]. Por lo cual, buscamos todas los intervalos posibles que puedan contener cada posición del token a eliminar.
    Esto es simple, si denotamos nuestro intervalo como [l_i, r_i], y decimos que p_i (la posición donde se encuentra el token que se eliminará el iésimo) pertenece a dicho intervalo.
    Siguiendo esa condición, los valores que puede tomar l_i es la cantidad de posiciones antes de p_i (incluido), es decir, tiene p_i posibilidades.
    Por otro lado, los valores de r_i son todo lo contrario, la cantidad de posiciones a la derecha, la denotamos como (n-p_i+1), esto dice cuantos números tiene p_i a la derecha incluyendo p_i (+1)
    Debemos que tener en cuenta que r_i es semejante a i en nuestro problema, por lo que no se pueden repetir ningún r_i, por lo que existirían n-p_i+1-i posibilidades si ordenamos nuestras p_i en orden decreciente.
    En total, nos quedan p_i * (n-p_i+1-i) intervalos posibles para p_i.

    Esta sería la base del problema, la implementación ahora consiste en programación dinámica:
    Partimos de dos variables:
        - i: El número de operaciones efectuadas (incluyendo la de no hacer nada que sería cuando a_i = 0) contando desde el principio
        - j: El número de tokens eliminados
    Definamos la función f(i, j) representando las posibilidades para llegar a la situación de i operaciones eliminando j tokens.

    Por lo que nosotros sabemos que si i = 0 y j = 0 la solución será 1 (solo existe una combinación que elimina 0 tokens con 0 números, el conjunto vacío)
    Además, todas las combinaciones en las que j>i daran 0 combinaciones, ya que no es posible eliminar más tokens que operaciones hechas.
    Cualquier otro caso se puede separar en los siguientes dos (f(i-1,j)):
    - Caso 1: p_i ya ha sido eliminada o a_i es igual a 0.
        Este caso se llega cuando aumenta el número de operaciones sin aumentar el número de tokens, por lo que las posibilidades serían:
        1.  Valores posibles para r_i: Para cada valor de r_i que tenga un intervalo que contenga una p_i ya eliminada y r_i debe estar a la derecha de la posición que estamos inspeccionando. 
            Es decir, si hemos hecho i operaciones, r_i no puede tener un valor anterior a i, por lo que sus posibles valores serán (n-i+1), ya razonamos antes el porqué.
        2.  Los valores posibles de p_i para que se de esta situación son el número de tokens ya eliminados +1 representando la posibilidad de que a_i sea 0. En este caso, los posibles valores de l_i son (j+1) valores. 
        3.  Esta situación llega desde f(i-1, j). Por lo que debemos tener en cuenta que por cada posibilidad de esta, tenemos las dos anteriormente seleccionadas.
    
        Finalmente, teniendo en cuenta estos puntos, decimos que hay (j+1)*(n-i+1)*f(i-1, j) posibles combinaciones por este caso.

    - Caso 2: p_i es un valor completamente nuevo que hay que eliminar.
        En este caso es mucho más simple. Para eliminar p_i, sabemos que solo hay una única posición donde debe eliminarse, la última. Todas las demás ya fueron revisadas por el caso 1.
        De esa forma, al solo existir una posible combinación, este caso es igual a f(i-1, j-1)
    
    Así, llegamos a la conclusión de que f(i, j) = f(i-1, j-1) + (j+1)*(n-i+1)*f(i-1, j)
    */
    int n, m;
    cin >> n >> m;
    vector<vll> soluciones(n+1, vll(n+1, 0));
    soluciones[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j>0){
                soluciones[i][j] += soluciones[i - 1][j - 1];
                soluciones[i][j] %= m;
            }
            soluciones[i][j] += (soluciones[i - 1][j] * (n - i + 1) % m * (j + 1)) % m;
            soluciones[i][j] %= m;
        }
    }
    lli result = 0;
    for (int j = 0; j <= n; ++j) {
        result += soluciones[n][j];
        result %= m;
    }
    cout << result << endl;
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
// https://codeforces.com/contest/2119/problem/D
