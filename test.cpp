#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef __int128_t int128; // Evita el overflow de (10^18 * 10^9)

void solve() {
    ll n;
    int m;
    ll d;
    if (!(cin >> n >> m >> d)) return;

    vector<ll> p(m), r(m);
    for (int i = 0; i < m; i++) {
        cin >> p[i] >> r[i];
    }

    // Precalculamos las sumas acumuladas de r
    vector<ll> pref_r(m + 1, 0);
    for (int i = 0; i < m; i++) {
        pref_r[i + 1] = pref_r[i] + r[i];
    }

    // Función O(log m) para obtener W(k)
    auto get_W = [&](ll k) -> ll {
        if (k <= 0) return 0;
        if (k >= n) return n * d + pref_r[m];
        int idx = upper_bound(p.begin(), p.end(), k) - p.begin();
        return k * d + pref_r[idx];
    };

    ll W_n = get_W(n);

    // 1. Construimos el conjunto reducido de PUNTOS CRÍTICOS K (|K| <= 4002)
    vector<ll> K;
    K.push_back(0);
    if (n - 1 > 0) K.push_back(n - 1);
    for (int i = 0; i < m; i++) {
        if (p[i] < n) K.push_back(p[i]);
        if (p[i] - 1 >= 0 && p[i] - 1 < n) K.push_back(p[i] - 1);
    }

    sort(K.begin(), K.end());
    K.erase(unique(K.begin(), K.end()), K.end());

    // 2. Comprobación 1: Rendimiento asintótico de un bloque individual
    for (ll k : K) {
        if (k < n) {
            ll W_k = get_W(k);
            if ((int128)W_k * n > (int128)W_n * (k + 1)) {
                cout << "YES\n";
                return;
            }
        }
    }

    // 3. Comprobación 2: Evaluamos todas las parejas de bloques (k1, k2)
    for (ll k1 : K) {
        ll W_k1 = get_W(k1);
        for (ll k2 : K) {
            ll W_k2 = get_W(k2);
            ll L = k1 + 1 + k2; // Longitud total del arreglo a
            
            ll f_a = W_k1 + W_k2;
            ll q = L / n;
            ll rem = L % n;
            ll f_I = q * W_n + get_W(rem);

            if (f_a > f_I) {
                cout << "YES\n";
                return;
            }
        }
    }

    cout << "NO\n";
}

int main() {
    // Magia de I/O para Linux/Codeforces
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr); 
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}