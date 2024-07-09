//Librerías incluidas en #include<bitstdc++.h>
#include<algorithm>
#include<array>
#include<atomic>
#include<bitset>
#include<ccomplex>
#include<cerrno>
#include<cfenv>
#include<cfloat>
#include<chrono>
#include<cinttypes>
#include<ciso646>
#include<climits>
#include<clocale>
#include<cmath>
#include<complex>
#include<condition_variable>
#include<csetjmp>
#include<csignal>
#include<cstdalign>
#include<cstdarg>
#include<cstdbool>
#include<cstddef>
#include<cstdint>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctgmath>
#include<ctime>
#include<cwchar>
#include<cwctype>
#include<deque>
#include<exception>
#include<forward_list>
#include<fstream>
#include<functional>
#include<future>
#include<initializer_list>
#include<iomanip>
#include<ios>
#include<iosfwd>
#include<iostream>
#include<istream>
#include<iterator>
#include<limits>
#include<list>
#include<locale>
#include<map>
#include<memory>
#include<mutex>
#include<new>
#include<numeric>
#include<ostream>
#include<queue>
#include<random>
#include<ratio>
#include<regex>
#include<scoped_allocator>
#include<set>
#include<sstream>
#include<stack>
#include<stdexcept>
#include<streambuf>
#include<string>
#include<system_error>
#include<thread>
#include<tuple>
#include<type_traits>
#include<typeindex>
#include<typeinfo>
#include<unordered_map>
#include<unordered_set>
#include<utility>
#include<valarray>
#include<vector>
#include <stdlib.h>
using namespace std;

typedef vector<int> vi;
typedef vector<long long int> vll;
typedef long long int lli;
typedef pair<int, int> pii;
typedef map<string, int> msi;
typedef map<int, vector<int>> miv;

// Funciones vector
#define PB(a) push_back(a);

bool sort_func(pii a, pii b) {
  if (a.first < b.first) {
    return true;
  } else {
    return false;
  }
}
#define ord(vect) sort(vect.begin(), vect.end(), sort_func);

#define borra_el(vect, el) vect.erase(vect.find(el));
#define borra_range(vect, a, b) vect.erase(a, b);
#define borra(vect, n) vect.erase(vect.begin() + n);
#define B begin();
#define E end();
#define copia(v1, v2)                                                          \
  ;                                                                            \
  copy(v1.begin(), v1.end(), back_inserter(v2));

// Funciones map
#define F first;
#define S second;

// Logaritmo de 2
double log_2 = log(2);
double log2(int a) { return (log(a) / log_2); }

void Imprime(vi vect) {
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

vector<pii> lee(int n) {
  int el;
  pii obj;
  vector<pii> vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    obj.first=el;
    obj.second=i;
    vect.PB(obj);
  }
  return (vect);
}

int solve() {
  // Code aquí
  int n, changes=0;
  cin >> n;
  vector<pii> a, b, a_c, b_c;
  a = lee(n);
  b = lee(n);
  copia(a,a_c);
  copia(b,b_c);
  ord(a);
  ord(b);
  for (int i = 0; i<n; i++){
    if (a[i].first != b[i].first){
        cout << "NO" << endl;
        return 1;
    }
    a_c[a[i].second].second = i;
    b_c[b[i].second].second = i;
  }
  for (int i = 0; i<n; i++){
    if (a[i].first!=a_c[i].first){
        changes++;
        // a_c[a[i].second].second --> indice del elemento que se va a colocar
        // a_c[i].second --> indice del elemento por el que se intercambiará
        pii save;
        save = a_c[a[i].second];
        a_c[a[i].second] = a_c[i]; 
        a_c[i] = save;
        a[a_c[a[i].second].second].second = a[i].second;
        a[i].second = i;
    }
  }
  if (changes%2 == 1){
    pii save;
    save = b_c[1];
    b_c[1]=b_c[0];
    b_c[0]=save;
    b[b_c[0].second].second=0;
    b[b_c[1].second].second=1;
  }
  //cout << b_c[0].first << " " << b_c[1].first << endl;
  changes = 0;
  for (int i = 0; i<n; i++){
    if (b[i].first!=b_c[i].first){
        //cout << i << " ";
        changes++;
        pii save;
        save = b_c[b[i].second];
        b_c[b[i].second] = b_c[i]; 
        b_c[i] = save;
        b[b_c[b[i].second].second].second = b[i].second;
        b[i].second = i;
    }
  }
  if (changes%2 == 0){
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
  }

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