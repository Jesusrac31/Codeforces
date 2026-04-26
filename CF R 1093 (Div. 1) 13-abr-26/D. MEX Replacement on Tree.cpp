#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include <bits/stdc++.h>
#pragma GCC optimize("O3")
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

#define INF INT_MAX
double pi = 2*acos(0.0);

int MEX_FILLER = 0;

class Mex {
private:
    vector<int> frequency; // Optimizado: O(1) en vez de map (O(log N))
    set<int> missing_numbers;
    vector<int> A;
    int max_val;
public:
    Mex(vector<int> const& A): A(A), max_val(A.size() + 1), frequency(A.size() + 2, 0) {
        for (int i = 0; i <= max_val; i++)
            missing_numbers.insert(i);
        for (int x: A) {
            if (x <= max_val) {
                if (++frequency[x] == 1) {
                    missing_numbers.erase(x);
                }
            }
        }
    }
    int mex() {
        return *missing_numbers.begin();
    }
    int mex2() {
        auto it = missing_numbers.begin();
        if (it == missing_numbers.end()) return 0;
        auto it2 = it;
        ++it2;
        if (it2 == missing_numbers.end()) return *it + 1;
        return *it2;
    }
    void update(int idx, int new_value) {
        int old_value = A[idx];
        if (old_value <= max_val) {
            if (--frequency[old_value] == 0)
                missing_numbers.insert(old_value);
        }
        
        A[idx] = new_value;
        
        if (new_value <= max_val) {
            if (++frequency[new_value] == 1)
                missing_numbers.erase(new_value);
        }
    }
};

class BIT {
public:
    int n; vector<long long> bit;
    BIT(int n): n(n), bit(n+1, 0) {}
    void add(int i, long long x){ for (; i<=n; i+=i&-i) bit[i]+=x; }
    long long sum(int i) const {
        long long r = 0;
        for (; i>0; i-=i&-i) r+=bit[i];
        return r;
    }
    long long query(int l, int r) const {
        if (l > r) return 0;
        return sum(r)-sum(l-1);
    }
};

void getSol(vector<int>& sol, Mex& op, vector<vi>& tree, vector<int>& value, int n, int change, int node = 0, int padre = -1, int depth = 0){
    op.update(depth, value[node]);
    sol[node] = op.mex();
    if (change == node){
        op.update(depth, sol[node]);
        sol[node] = op.mex();
    }
    for (auto v:tree[node])
        if (v != padre) 
            getSol(sol, op, tree, value, n, change, v, node, depth+1);
    op.update(depth, MEX_FILLER);
}

void bruteForce(int n, vector<int>& values, vector<vi>& tree){
    vector<int> initialArrayMex(n, MEX_FILLER);
    Mex mexOp(initialArrayMex);
    vector<vector<int>> sol(n, vector<int>(n));
    for (int i = 0; i<n; i++) getSol(sol[i], mexOp, tree, values, n, i);
    for (int i = 0; i<n; i++) cout << sol[i] << endl;
    int maxi = 0;
    for (int i = 0; i<n; i++){
        int suma = 0;
        for (int j = 0; j<n; j++) suma +=sol[i][j];
        maxi = max(maxi, suma);
        cout << suma << " ";
    }
    cout << endl;
    cout << maxi << endl;
}

void getMex1(vector<int>& f, Mex& op, vector<vi>& tree, vector<int>& value, int n, int node = 0, int padre = -1, int depth = 0){
    op.update(depth, value[node]);
    f[node] = op.mex();
    for (auto v:tree[node])
        if (v != padre)
            getMex1(f, op, tree, value, n, v, node, depth+1);
    op.update(depth, MEX_FILLER);
}

void getMex2(vector<int>& f, Mex& op, vector<vi>& tree, vector<int>& value, int n, int node = 0, int padre = -1, int depth = 0){
    op.update(depth, value[node]);
    f[node] = op.mex2();
    for (auto v:tree[node])
        if (v != padre)
            getMex2(f, op, tree, value, n, v, node, depth+1);
    op.update(depth, MEX_FILLER);
}

// Asigna a cada nodo un rango de nodos que son sus hijos. Esto lo hace con una lista de nodos siguiendo un preorder (orden dfs)
void dfsEuler(vector<vi>& tree, vector<int>& order, vector<int>& tin, vector<int>& tout, int node = 0, int padre = -1){
    tin[node] = (int)order.size();
    order.push_back(node);
    for (auto v:tree[node])
        if (v != padre)
            dfsEuler(tree, order, tin, tout, v, node);
    tout[node] = (int)order.size();
}

struct EulerGroups {
    vector<int> tin;
    vector<int> tout;
    vector<vector<int>> groups;
    vector<vector<int>> groupPos;
};

EulerGroups buildEulerGroups(vector<vi>& tree, vector<int>& mex1){
    int n = (int)tree.size();
    vector<int> order, tin(n), tout(n);
    order.reserve(n);
    dfsEuler(tree, order, tin, tout);

    int maxMex = n + 1;
    vector<vector<int>> groups(maxMex + 1);
    vector<vector<int>> groupPos(maxMex + 1);
    for (int i = 0; i < n; i++) {
        groups[mex1[i]].push_back(i);
        groupPos[mex1[i]].push_back(tin[i]);
    }
    for (int g = 0; g <= maxMex; g++) sort(groupPos[g].begin(), groupPos[g].end());

    return {tin, tout, groups, groupPos};
}

vector<long long> getSumMex2SameMex1(vector<vi>& tree, vector<int>& values, vector<int>& mex1, vector<int>& mex2){
    int n = (int)tree.size();
    // 1) Euler tour + grupos por mex1
    auto eg = buildEulerGroups(tree, mex1);

    // Cuenta cuantos nodos del grupo caen en el subarbol [l, r)
    auto countInSubtree = [&](const vector<int>& pos, int l, int r) {
        auto itL = lower_bound(pos.begin(), pos.end(), l);
        auto itR = lower_bound(pos.begin(), pos.end(), r);
        return (int)(itR - itL);
    };

    // 3) Para cada grupo (mismo mex1), calcular sumas con corte en values[v]
    vector<long long> sumMex2(n, 0);
    
    // OPTIMIZACIÓN CLAVE: Instanciar los BIT fuera del bucle para no re-crear memoria.
    // BITs sobre el Euler tour: sumas de mex2 y conteos de activados
    BIT bitSum(n), bitCnt(n);
    
    for (int g = 0; g < (int)eg.groups.size(); g++) {
        auto& nodes = eg.groups[g];
        if (nodes.empty()) continue;

        // Orden por mex2 para ir activando los nodos cuyo mex2 <= values[v]
        vector<int> byMex2 = nodes;
        sort(byMex2.begin(), byMex2.end(), [&](int a, int b){
            if (mex2[a] != mex2[b]) return mex2[a] < mex2[b];
            return a < b;
        });
        // Orden por values para procesar consultas de menor a mayor
        vector<int> byVal = nodes;
        sort(byVal.begin(), byVal.end(), [&](int a, int b){
            if (values[a] != values[b]) return values[a] < values[b];
            return a < b;
        });

        int idx = 0;
        for (int v : byVal) {
            // Activa nodos del grupo con mex2 <= values[v]
            while (idx < (int)byMex2.size() && mex2[byMex2[idx]] <= values[v]) {
                int u = byMex2[idx++];
                bitSum.add(eg.tin[u] + 1, mex2[u]);
                bitCnt.add(eg.tin[u] + 1, 1);
            }
            // Suma de mex2 (<= values[v]) dentro del subarbol de v
            long long sumLe = bitSum.query(eg.tin[v] + 1, eg.tout[v]);
            long long cntLe = bitCnt.query(eg.tin[v] + 1, eg.tout[v]);
            // Total de nodos del grupo dentro del subarbol
            long long cntTotal = countInSubtree(eg.groupPos[g], eg.tin[v], eg.tout[v]);
            // Nodos con mex2 > values[v] aportan values[v]
            sumMex2[v] = sumLe + (cntTotal - cntLe) * 1LL * values[v];
        }
        
        // Rollback: Limpiamos los BIT para el siguiente grupo sin gastar O(N)
        for(int i = 0; i < idx; i++) {
            int u = byMex2[i];
            bitSum.add(eg.tin[u] + 1, -mex2[u]);
            bitCnt.add(eg.tin[u] + 1, -1);
        }
    }

    return sumMex2;
}

vector<long long> getSumRestMex1(vector<vi>& tree, vector<int>& values, vector<int>& mex1){
    int n = (int)tree.size();
    auto eg = buildEulerGroups(tree, mex1);

    auto countInSubtree = [&](const vector<int>& pos, int l, int r) {
        auto itL = lower_bound(pos.begin(), pos.end(), l);
        auto itR = lower_bound(pos.begin(), pos.end(), r);
        return (int)(itR - itL);
    };

    vector<int> mex1Sorted = mex1;
    sort(mex1Sorted.begin(), mex1Sorted.end());
    vector<long long> pref(mex1Sorted.size() + 1, 0);
    for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + mex1Sorted[i];

    auto totalMinMex1 = [&](int t) {
        int cntLe = upper_bound(mex1Sorted.begin(), mex1Sorted.end(), t) - mex1Sorted.begin();
        long long sumLe = pref[cntLe];
        return sumLe + 1LL * (n - cntLe) * t;
    };

    vector<long long> sumRestMex1(n, 0);
    for (int v = 0; v < n; v++) {
        long long total = totalMinMex1(values[v]);
        long long cntSet = countInSubtree(eg.groupPos[mex1[v]], eg.tin[v], eg.tout[v]);
        long long subSum = cntSet * 1LL * min(mex1[v], values[v]);
        sumRestMex1[v] = total - subSum;
    }

    return sumRestMex1;
}

int solve() {
    // Input
    DBG_COUT(cout << "--------------------" << endl);
    int n; cin >> n;
    MEX_FILLER = n + 1;
    vi values(n); for (int i = 0; i<n; i++) cin >> values[i];
    vector<vi> tree(n);
    int x, y;
    for (int i = 0; i<n-1; i++){
        cin >> x >> y;
        x--; y--;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    // 0. Para n = 1, la respuesta siempre es 1, al ser la única excepción, imprimimos automaticamente
    if (n == 1){ cout << 1 << endl; return 0; }

    // 1. Obten el mex1 de todos los caminos, puedes utilizar la clase mex.
    vector<int> initialArrayMex(n, MEX_FILLER);
    Mex mexOp(initialArrayMex);
    vector<int> mex1(n);
    getMex1(mex1, mexOp, tree, values, n);

    DBG_COUT(cout << "MEX1 hasta cada nodo: " << mex1 << endl);

    // 2. Obten el mex2 de todos los caminos, puedes utilizar la clase mex.
    vector<int> mex2(n);
    getMex2(mex2, mexOp, tree, values, n);

    DBG_COUT(cout << "MEX2 hasta cada nodo: " <<  mex2 << endl);
    // 3. Por cada nodo v, obten la suma del mex2 de todos sus hijos (incluyendose a si mismo) que tengan el mismo mex1.
    //    Si el mex2 de alguno de los hijos es superior a values[v], suma values[v]
    vector<long long> sumMex2 = getSumMex2SameMex1(tree, values, mex1, mex2);
    
    DBG_COUT(cout << "Suma de los MEX2 de todos los hijos que tengan el mismo mex1: " << sumMex2 << endl);
    // 4. Por cada nodo v, obten la suma del mex1 del resto de nodos. Si algún mex1 es mayor a values[v], suma values[v]
    vector<long long> sumRestMex1 = getSumRestMex1(tree, values, mex1);

    DBG_COUT(cout << "Suma de MEX1 del resto de hijos: " << sumRestMex1 << endl);
    // 5. El punto 4 y punto 3 deben devolver listas de la misma longitud (ls4 y ls3 respectivamente), para todo i, calcula ls3[i] + ls4[i]
    vector<long long> posibilidades(n);
    for (int i = 0; i<n; i++) posibilidades[i] = sumMex2[i] + sumRestMex1[i];

    DBG_COUT(cout << "Mezcla de ambos pasos: " << posibilidades << endl);
    // 6. Llama maxi al número más grande obtenido en el paso 5
    long long maxi = LLONG_MIN;
    int operacion = -1;
    for (int i = 0; i < n; i++) {
        long long val = posibilidades[i];
        if (maxi < val){
            maxi = val;
            operacion = i;
        }
    }

    DBG_COUT(cout << "Valor máximo del paso anterior: " << maxi << endl);
    DBG_COUT(cout << "Operación efectuada: " << operacion << endl);
    // 7. Obten la suma de todos los mex1 (resultado sin operar)
    long long sumaTotal = 0;
    for (auto x:mex1) sumaTotal += x;

    DBG_COUT(cout << "Suma del arbol sin operaciones: " << sumaTotal << endl);
    // 8. Si maxi es menor que la suma sin operaciones, di que maxi es la suma sin operaciones
    if (maxi < sumaTotal) maxi = sumaTotal;

    DBG_COUT(cout << "RELU del valor máximo del paso anterior: " << maxi << endl);

    cout << maxi << endl;

    DBG_COUT(cout << "Solucion fuerza bruta: " << endl; bruteForce(n, values, tree));

    return 0;
}

signed main() {
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

// https://codeforces.com/contest/2219/problem/D