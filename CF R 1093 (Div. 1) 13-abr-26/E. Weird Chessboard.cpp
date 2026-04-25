#include<bits/stdc++.h>
using namespace std; 
typedef long long lli; 
//#define int lli 
#define INF 10e9 
#define MAXN 5010
double pi = 2*acos(0.0); 


template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    os << "";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << std::setw(6) << elem;
    }
    os << "\n";
    return os;
}

void refresh(int i, int j, vector<vector<bool>>& sol, vector<vector<int>>& suma, int n){
    queue<pair<int, int>> refreshes;
    refreshes.push({i, j});
    refreshes.push({i, j+1});
    refreshes.push({i+1, j});
    while(!refreshes.empty()){
        i = refreshes.front().first;
        j = refreshes.front().second;
        refreshes.pop();
        if (i >= n || j >= n) continue;
        if (i == 0 && j == 0) {
            suma[i][j] = 0;
        } else if (i == 0){
            suma[i][j] = suma[i][j-1] + sol[i][j-1];
        } else if (j == 0){
            suma[i][j] = suma[i-1][j] + sol[i-1][j];
        } else {
            suma[i][j] = suma[i][j-1] + sol[i][j-1] + suma[i-1][j] + sol[i-1][j] - suma[i-1][j-1] - sol[i-1][j-1];
        }
    }
}

void update(bool val, int x, int y, vector<vector<bool>>& sol, vector<vector<int>>& suma, int n){
    sol[x][y] = val;
    refresh(x, y, sol, suma, n);
}


vector<vector<int8_t>> dp(MAXN, vector<int8_t>(MAXN, -1));

bool getBit(int i, int j){
    if (dp[i][j] != -1) return dp[i][j];
    if (i == 1) dp[i][j] = 1;
    else if (i == 2) dp[i][j] = (j & 1);
    else if (j == 1) dp[i][j] = 1;
    else if (i == j) dp[i][j] = 0;
    else if (j == i-1) dp[i][j] = 1;
    else dp[i][j] = getBit(i-2, j-1) ^ getBit(i-2, j);
    return dp[i][j];
}

bool solve(){
    // Code
    int n; cin >> n;
    int expected = ((int)((n*n)/10))*3;
    cerr << "----------------------\n" << "Test case: " << n << endl;
    cerr << "Expected: " << expected << endl;
    vector<vector<bool>> solucion(n, vector<bool>(n, 0));
    vector<vector<int>> suma(n, vector<int>(n, 0));

    for (int i = 0; i<n; i++){
        update(1, i, n-i-1, solucion, suma, n);
    }

    for (int i = 1; i<n; i++){
        bool bit = getBit(n, i+1);
        update(bit, i, n-1, solucion, suma, n);
        for(int j = i+1; j<n; j++){
            if (suma[j][n-j+i] & 1) update(1, j, n-j+i-1, solucion, suma, n);
            else update(0, j, n-j+i-1, solucion, suma, n);
        }
    }

    cerr << "Number of 1s: " << suma[n-1][n-1]+1  << endl;
    
    cerr << (suma[n-1][n-1]+1 >= expected ? "\033[32mPERFECT":"\033[31mWRONG") << endl;
    cerr << "Diferencia: " << suma[n-1][n-1]+1-expected << "\033[0m" << endl;
    
    for (auto x: solucion){
        for (auto y:x) cout << y << " ";
        cout << endl;
    }
    return (suma[n-1][n-1]+1 >= expected);
}

signed main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout.tie(nullptr); 
    int T; cin >> T;
    while(T--) solve();
    return 0;
}

//https://codeforces.com/contest/2219/problem/E