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
#define rep(x,n) for(int x = 0; x < n; ++x)
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

void lee(int n, vi& vect) {
  rep(i, n) cin >> vect[i];
  return ;
}

int solve() {
    // Code aquí
    int n;
    cin >> n;
    vll a(n);
    vll suma(n, 0); 
    lli maxi = 0;
    for(int i = 0; i<n; i++){
        cin >> a[i];
        if (i>0){
            suma[i] = suma[i-1]+a[i];
        } else {
            suma[i] = a[i];
        }
        
        maxi = max(maxi, a[i]);
    }
    if (maxi > suma.back()/2 || suma.back()%2){
        cout << -1 << endl;
        return 0;
    }
    int i;
    for (i = 0; suma[i]<=suma.back()/2; i++){
        if (suma[i] == suma.back()/2){
            cout << 1 << endl;
            Imprime(a);
            return 0;
        }
    }

    // Las únicas soluciones son -1, 1, 2
    cout << 2 << endl;
    
    lli suma_med = suma[i];
    lli resta = suma.back()-suma_med;
    int j;
    vll arr1(n, 0);

    for (j = 0; suma[j]<(suma.back()-2*resta)/2; j++){
        arr1[j] = 0;
    }
    arr1[j] = suma[j]-(suma.back()-2*resta)/2;
    resta -= arr1[j];
    int k;
    for(k = j+1; resta>0; k++){
        arr1[k] = min(a[k], resta);
        resta -= arr1[k];
    }

    for (k = i+1; k<arr1.size(); k++){
        arr1[k] = a[k];
    }
    Imprime(arr1);

    for (int i = 0; i<n; i++){
        cout << a[i]-arr1[i] << " ";
    }
    cout << endl;

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
