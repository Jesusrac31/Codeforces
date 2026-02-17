/**
 * Problema: Contar pares de caminos idénticos en subárboles.
 * Enfoque: Programación Dinámica + Sumas de Sufijos 2D usando estructura Mint.
 * Complejidad: O(N^2)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

// --- Estructura Mint (Aritmética Modular Automática) ---
struct Mint {
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
    
    // Operadores de comparación
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

template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "[ ";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]\n";
    return os;
}

// --- Solución ---

void solve() {
    int n;
    if (!(cin >> n)) return;

    string s;
    cin >> s;
    string letters = " " + s; // 1-based indexing

    // Vectores de gestión del grafo y tiempos
    vector<vector<int>> adj(n + 1);
    vector<int> start_time(n + 1);
    vector<int> end_time(n + 1);
    vector<int> node_at_time(n + 1);
    
    // Matriz DP usando Mint
    // Inicializada a 0 (el constructor Mint(0) se encarga)
    vector<vector<Mint>> dp_sum(n + 2, vector<Mint>(n + 2, 0));

    // Lectura del árbol
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 1. Linearización (DFS Order)
    int timer = 0;
    auto dfs_linearize = [&](auto&& self, int u, int parent) -> void {
        timer++;
        start_time[u] = timer;
        node_at_time[timer] = u;

        for (int v : adj[u]) {
            if (v != parent) {
                self(self, v, u);
            }
        }
        end_time[u] = timer;
    };

    dfs_linearize(dfs_linearize, 1, 0);
    cout << start_time << end_time << node_at_time << endl;

    // 2. Helper para obtener suma de rectángulo con Mint
    // Inclusión-Exclusión para sumas de sufijos:
    // Rect = EsquinaSupIzq - Derecha - Abajo + EsquinaInfDer
    // (A + D) - B - C
    auto get_rect_sum = [&](int r1, int r2, int c1, int c2) -> Mint {
        if (r1 > r2 || c1 > c2) return 0;

        // Gracias a Mint, la resta maneja el módulo negativo automáticamente
        return dp_sum[r1][c1] 
             + dp_sum[r2 + 1][c2 + 1] 
             - dp_sum[r1][c2 + 1] 
             - dp_sum[r2 + 1][c1];
    };

    // 3. Cálculo DP (Orden inverso)
    for (int i = n; i >= 1; --i) {
        for (int j = n; j >= 1; --j) {
            int u = node_at_time[i];
            int v = node_at_time[j];

            // A. Si las letras coinciden
            if (letters[u] == letters[v]) {
                // Sumamos 1 (nodo actual) + combinaciones de los hijos
                Mint sum_children = get_rect_sum(
                    start_time[u] + 1, end_time[u],
                    start_time[v] + 1, end_time[v]
                );
                
                // Actualizamos el valor en la celda (i, j)
                dp_sum[i][j] += sum_children + 1;
            }

            // B. Convertir a Suma de Sufijos (Propagación 2D)
            // S[i][j] += S[i+1][j] + S[i][j+1] - S[i+1][j+1]
            dp_sum[i][j] += dp_sum[i + 1][j] 
                          + dp_sum[i][j + 1] 
                          - dp_sum[i + 1][j + 1];
        }
    }

    // 4. Salida
    for (int i = 1; i <= n; ++i) {
        // Obtenemos el rectángulo correspondiente al subárbol de i
        Mint ans = get_rect_sum(start_time[i], end_time[i], start_time[i], end_time[i]);
        cout << ans << (i == n ? "" : " ");
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}

// https://codeforces.com/contest/2183/problem/F