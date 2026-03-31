#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353; //Modulo en el que tenemos que devolver la respuesta

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]";
    return os;
}

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

void Imprime2d(vector<vector<Mint>>& v){
    for (int i = 0; i<v.size(); i++){
        for (int j = 0; j<v[i].size(); j++){
            cout << v[i][j].v << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void Imprime(vector<Mint>& v){
    for (int i = 0; i<v.size(); i++){
        cout << v[i].v << " ";
    }
    cout << endl;
}

// En este problema usaremos la nomenclatura a_i para refirirnos al elemento i de la lista a, que sería el array de tamaño n que contabiliza el problema.
void solve() {
    //Input
    int N, K;
    cin >> N >> K;

    vector<vector<bool>> banned(N, vector<bool>(N));    // En esta matriz se almacenan como true la combinación de valores que no se pueden utilizar.
                                                        // En concreto, si la fila x columna y es true (banned[x][y]==true) el elemento a_x != y.
                                                        // Es importante que el tamaño sea de N, aunque sea suficiente N-1, a la hora de computar chain aprovecharemos los 0 del final de la lista
    for (int i = 0; i < K; ++i) {
        int x, y;
        cin >> x >> y;
        banned[x - 1][y - 1] = true; // Adapta los índices de 1 a N -> 0 a N-1
    }

    // Este es la forma de calcular los resultados, el resultado de tot[i] es la suma de todo dp[i][j] para cualquier valor de j
    vector<Mint> tot(N + 1); // Usamos N+1 para poder tratar el caso inicial de añadir una secuencia vacia explicado en la siguiente línea
    tot[N] = 1; // El número de llenar los índices de N a N será de 1. Es lo equivalente a que la lista esté llena por lo cual lo único que podemos añadir es una permutación vacía

    // En dp[i][j] almacenaremos el número de formas en las que podemos rellenar los índices de i a n de tal forma que a_i = j
    vector<vector<Mint>> dp(N + 1, vector<Mint>(N + 1));
    
    // Chain es una lista la cual debemos tener precalculada, consiste en saber la k máxima de forma que a[i+p] = j+p para todo p entre 0 y k. En caso de que la posición i+p tenga una restricción con el número j+p, k = p.
    // Esto se puede obtener tan simple como si banned[i][j] (si hay una restricción que no permite que j esté en la posición i) chain(i, j) = 0. En caso contrario, chain(i, j) = chain(i+1, j+1)+1
    vector<vector<int>> chain(N + 1, vector<int>(N + 1));
    for (int i = N - 1; i >= 0; --i) { // Como tenemos que mirar chain(i+1, j+1), hacemos los bucles de N-1 a 0 (los índices van de 0 a N-1 pese a que el problema los de de 1 a N)
        for (int j = N - 1; j >= 0; --j) {
            chain[i][j] = 1 + chain[i + 1][j + 1]; // Por defecto chain(i, j) = chain(i+1, j+1) +1
            if (banned[i][j]) chain[i][j] = 0; // En caso de que esté restringido, chain(i, j) = 0
        }
    }

    // ssum[i][j] es el número de formas en las que podemos añadir el número j para completar la lista de i a n sin tener en cuenta las restricciones.
    // El calculo sería sumar todos los dp2(x+j-1) para todos los x entre i y n de forma que chain(x, 1) >= j-1
    vector<vector<Mint>> ssum(N + 2, vector<Mint>(N + 1));

    for (int i = N - 1; i >= 0; --i) { // Empezamos con i = N
        for (int j = 0; j <= N - i; ++j) { // j empieza a 0, y llega a N-1
            if (j == 0) { // En caso de que sea el primer elemento del bucle de j
                // Este sistema permite evitar combinaciones repetidas
                // Lo que hace es, en caso de que no haya restricciones que lo prohiban, asume que puede utilizar todas las combinaciones anteriores. Pero luego anula las combinaciones pertenecientes a dp[i+len][j+len], que serían aquellas. Si la añadieramos, obtendríamos ... 1, 2, ..., len-1, len, len+1...
                // Esta combinación es repetida ya que sería como añadir la secuencia más larga desde el 1. Esas combinaciones deben ser eliminadas y para esto sirve este paso.  
                for (int len = 1; len <= N - i; ++len) { // Por cada número entre 1 y N-i
                    bool ok = chain[i][0] >= len; // En caso de que sea menor o igual que chain(i, 0), continua las instrucciones, sino rompe el bucle ya que incumple una restricción
                    if (!ok) break;
                    // Le añadimos a dp la suma total de los dp de la fila i+len
                    dp[i][j] += tot[i + len];
                    // Además, le restamos la cantidad de combinaciones en dp[i+len][j+len]
                    dp[i][j] -= dp[i + len][j + len];
                }
            } else { // Si no es el caso de que busquemos a_i == 0
                // Estos bloques de operaciones no empiezan con 1, así que no trae problemas de repetición. Solo tenemos que calcular todas las posibilidades
                if (chain[i][j]) { // Si no está restringido
                    dp[i][j] += ssum[i + 1][j]; //Suma a dp[i][j] sssum[i+1][j], el número de formas en la que insertar j para completar la lista de i+1 a n
                    if (i + 1 + chain[i][j] <= N) { //En caso de que i+longitud máxima de k para a_i == j + 1 sea menor o igual que N
                        dp[i][j] -= ssum[i + 1 + chain[i][j]][j]; // Le restamos la cantidad de sufijos para la lista entre i+1+chain(i,j) añadiendo j en a_i
                    }
                }
            }
            tot[i] += dp[i][j]; // El total de los dp de la fila i se le suma el dp calculado
            //Imprime2d(dp);
        }

        // Calculo de los sufijos
        for (int j = 1; j < N; ++j) {
            ssum[i][j] = ssum[i + 1][j]; // Cada sufijo es igual al sufijo de una fila después, sufijos entre i+1 y n
            if (chain[i][0] >= j) { //En caso de que chain(i, 0) sea mayor o igual que j
                ssum[i][j] += tot[i + j]; // Suma la suma de todos los dp[i+j]
            }
        }
    }
    // cout << dp << endl;
    // cout << ssum << endl;
    cout << tot[0].v << '\n';
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        solve();
    }
    
    return 0;
}
// https://codeforces.com/contest/2124/problem/F1
// https://codeforces.com/contest/2124/problem/F2