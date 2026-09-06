#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
using ll = long long;
using pii = pair<int, int>;


int solve() {
    // Code aquí
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    vector<int> diff(n, 0);
    for(int i = 0; i < n; ++i) {
        int num = v[i];
        if(num == -1 || num == 0) {
            continue;
        } 
        int izq = max(0, i-num+1);
        int der = i+num;
        diff[izq] += 1;
        if(der < n) {
            diff[der] -= 1;
        }
    }
    int acum = 0;
    for(int i = 0; i < n; ++i) {
        acum += diff[i];
        diff[i] = acum;
    }
    bool ok = true;
    string sol(n, '0');
    for(int i = 0; i < n; ++i) {
        if(diff[i] == 0) {
            sol[i] = '1';
        }
    }
    for(int i = 0; i < n; ++i) {
        if(v[i] != -1) {
            int izq = i-v[i];
            int der = i+v[i];
            if(!((izq >= 0 && sol[izq] == '1') || (der < n && sol[der] == '1'))) {
                ok = false;
            }
        }
    }
    if(!ok) {
        cout << -1 << endl;
    } else {
        cout << sol << endl;
    }
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