#include <bits/stdc++.h>
using namespace std;

void Solve() 
{
    int n; cin >> n;
    
    vector <int> a(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i];
    }
    
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    
    for (int i = n; i >= 1; i--){
        vector <int> good(n + 1, -1);
        int curr = a[i];
        
        dp[i][i] = curr;
        
        for (int j = i + 1; j <= n; j++){
            if (a[j] < a[i]){ // Si es menor, no puede añadirse
                continue;
            }
            
            if (a[j] == a[i]){ // Si es igual, se puede añadir
                curr += 1;
                dp[i][j] = curr;
                continue;
            }
            
            // Si es mayor, solo puede añadirse en caso de que sea óptimo hacerlo y el número no sea mayor a la longitud del array b
            if (good[a[j]] == -1 && a[j] <= curr + 1){ // Comprueba la longitud del array para ver si entra
                good[a[j]] = j;
            }
            
            if (good[a[j]] != -1){ // Comprueba si es óptimo con el máximo entre no añadirlo y añadirlo. (Imagina que estamos con a[i] = 3, y ahora a[i] = 5. Si hemos llegado a este paso, significa que hay al menos dos 3s. Por lo que si añadieramos el 5, la única forma sería {x, x, 3, 3, 5, ...})
                int idx = good[a[j]];
                curr = max(curr, dp[idx][j]);
            }
        }
    }
    
    // Recorre el array a buscando la forma óptima desde a[1] aprovechando las anotaciones de dp
    int curr = 0;
    vector <int> good(n + 1, -1);
    for (int j = 1; j <= n; j++){
        if (good[a[j]] == -1 && a[j] <= curr + 1){
            good[a[j]] = j;
        }
        
        if (good[a[j]] != -1){
            int idx = good[a[j]];
            curr = max(curr, dp[idx][j]);
        }
    }
    
    cout << curr << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        Solve();
    }
    return 0;
}
// https://codeforces.com/contest/2124/problem/H
