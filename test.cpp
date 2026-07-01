#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAXN = 1e6;

int n;
ll val[MAXN + 1];
char type[MAXN + 1];
int ans[MAXN + 1];
int lastS[MAXN + 1];

struct BIT {
    int bit[MAXN + 1];

    void clear() {
        for (int i = 1; i <= n; i++) bit[i] = 0;
    }

    void add(int i, int v) {
        for (; i <= n; i += i & -i)
            bit[i] += v;
    }

    int sum(int i) {
        int s = 0;
        for (; i > 0; i -= i & -i)
            s += bit[i];
        return s;
    }

    int find_kth(int k) {
        int pos = 0;
        for (int step = 1 << __lg(n); step; step >>= 1) {
            if (pos + step <= n && bit[pos + step] <= k) {
                k -= bit[pos + step];
                pos += step;
            }
        }
        return pos + 1;
    }

} fenwick;

void solve() {
    cin >> n;

    // Leer input
    for (int i = 1; i <= n; i++) {
        cin >> type[i] >> val[i];
        if (type[i] == 'p') ans[i] = val[i]; // Si sabes el valor, almacenalo en ans
        else val[i] = 1LL * i * (i - 1) / 2 - val[i]; // Cambia de la cantidad de inversiones a la cantidad de "no inversiones"
    }

    // Precalcular último índice con 's'
    for (int i = 1; i <= n; i++) {
        if (type[i] == 's') lastS[i] = i;
        else lastS[i] = lastS[i - 1];
    }

    // Inicializar BIT con todos los valores disponibles
    fenwick.clear();
    for (int i = 1; i <= n; i++) fenwick.add(i, 1);

    // Quitar los ya conocidos del sufijo
    for (int i = lastS[n] + 1; i <= n; i++) {
        fenwick.add(ans[i], -1);
    }

    // Procesar intervalos de derecha a izquierda
    for (int i = lastS[n]; i > 0; i = lastS[i - 1]) {

        int L = lastS[i - 1];
        ll delta = val[i] - val[L];

        // Procesar bloque (L, i)
        for (int j = i - 1; j > L; j--) {
            delta -= fenwick.sum(ans[j] - 1);
            fenwick.add(ans[j], -1);
        }

        delta += (i - L - 1);

        for (int j = i - 1; j > L; j--) {
            fenwick.add(ans[j], 2);
        }

        ans[i] = fenwick.find_kth(delta);

        for (int j = i - 1; j > L; j--) {
            fenwick.add(ans[j], -2);
        }

        fenwick.add(ans[i], -1);
    }

    // Output
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}