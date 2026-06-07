#ifdef DEBUG
#define _GLIBCXX_DEBUG
#endif

#include<bits/stdc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx2")

#ifdef DEBUG
#include "lib/debug.h"
#else
#define debug(...) 228
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
    os << "[";//Quita esto si no quieres los corchetes o cambia lo que quieras poner
    for(const auto& elem : vec) {
        os << elem << " ";
    }
    os << "]" << endl;
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

vector<vector<char>> nine = {
    {60, 60, 64, 64, 70, 70, 72, 72, 73},
    {60, 61, 64, 65, 70, 71, 72, 73, 73},
    {61, 61, 65, 65, 71, 71, 74, 75, 75},
    {62, 63, 63, 85, 86, 86, 74, 74, 75},
    {62, 62, 63, 85, 85, 86, 77, 76, 76},
    {66, 67, 67, 83, 84, 84, 77, 77, 76},
    {66, 66, 67, 83, 83, 84, 81, 78, 78},
    {69, 68, 68, 82, 81, 81, 80, 78, 79},
    {69, 69, 68, 82, 82, 80, 80, 79, 79}
};
vector<vector<char>> reduce_corner = {
    {60, 60, 62, 62, 63, 63},
    {60, 61, 62, 65, 63, 64},
    {61, 61, 65, 65, 64, 64}
};

vector<vector<char>> Resultado;
int indice = 0;

void printTriangle(vi cords){
    for (int i = 0; i<6; i+=2){
        Resultado[cords[i+1]-1][cords[i]-1] += indice;
        cout << cords[i] << " " << cords[i+1] << " ";
    }
    cout << endl;
    indice++;
}

void printMap(int offX, int offY, vector<vector<char>>& triangles){
    unordered_map<char, vi> res;
    for (int y = 0; y<triangles.size(); y++){
        for (int x = 0; x<triangles[y].size(); x++){
            if (res.find(triangles[y][x]) == res.end()){
                res[triangles[y][x]] = {};
            }
            res[triangles[y][x]].PB(x+offX);
            res[triangles[y][x]].PB(y+offY);
        }
    }
    for (auto tri:res){
        printTriangle(tri.second);
    }
}

void printEven(int n){
    for (int x = 1; x+2<=3*n; x+=3){
        for (int y = 1; y+1<=3*n; y+=2){
            printTriangle((vi) {x, y, x+1, y, x, y+1});
            printTriangle((vi) {x+1, y+1, x+2, y, x+2, y+1});
        }
    }
}

void printOdd(int n, int offX = 1, int offY = 1){
    if (n - (offX-1)/3 == 3){
        printMap(offX, offY, nine);
        return ;
    }
    // Corner
    printMap(offX, offY, reduce_corner);
    // BorderIzq
    for (int x = 0; x+2<6; x+=3){
        for (int y = 3; offY+y+1<=3*n; y+=2){
            printTriangle((vi) {offX+x, offY+y, offX+x+1, offY+y, offX+x, offY+y+1});
            printTriangle((vi) {offX+x+1, offY+y+1, offX+x+2, offY+y, offX+x+2, offY+y+1});
        }
    }
    //cerr << Resultado << endl;
    // BorderArr
    for (int x = 6; offX+x+2<=3*n; x+=3){
        for (int y = 0; y+1<6; y+=2){
            printTriangle((vi) {offX+x, offY+y, offX+x+1, offY+y, offX+x, offY+y+1});
            printTriangle((vi) {offX+x+1, offY+y+1, offX+x+2, offY+y, offX+x+2, offY+y+1});
        }
    }
    //cerr << Resultado << endl;
    printOdd(n, offX+6, offY+6);
}

int solve() {
    // Code aquí
    int n; cin >> n;
    indice = 1;
    Resultado = vector<vector<char>>(n*3, vector<char>(n*3, 32));
    if (n == 1){
        cout << 2 << endl;
        printTriangle((vi) {1, 1, 1, 2, 2, 1});
        printTriangle((vi) {2, 3, 3, 2, 3, 3});
    } else if (n % 2 == 0){
        cout << n*n*3 << endl;
        printEven(n);
    } else {
        cout << n*n*3 << endl;
        printOdd(n);
    }
    //cerr << Resultado << endl;
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

// https://codeforces.com/contest/2195/problem/H