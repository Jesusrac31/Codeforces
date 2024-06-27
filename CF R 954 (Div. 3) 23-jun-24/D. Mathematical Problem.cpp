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

bool sort_func(int a, int b) {
  if (a < b) {
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

vi lee(int n) {
  int el;
  vi vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

int solve(int T) {
  // Code aquí
  int n=0, sol = 0;
  cin >> n;
  string s;
  cin >> s;

  if (n == 2){
    cout << ((int)s[0] - 48)*10 + ((int)s[1] - 48) << endl;
  } else if (n == 3){
    int el1, el2, el3;
    el1 = (int)s[0] - 48;
    el2 = (int)s[1] - 48;
    el3 = (int)s[2] - 48;
    if (el1*el3 == 0){
      cout << 0 << endl;
    } else if (el2 == 0){
      cout << min(el1*el3,el1+el3) << endl;
    } else {
      cout << min(min(el1*10+el2+el3, (el1*10+el2)*el3), min(el1+el2*10+el3, el1*(el2*10+el3))) << endl;
    }
  } else {
    int doble;
    if (s[0] == '0' || s[1] == '0'){
        cout << 0 << endl;
        return 0;
    }
    doble = ((int)s[0] - 48)*10 + ((int)s[1] - 48);
    sol=doble;
    int sol2;
    for (int i = 2; i<n; i++){
        if (s[i] == '0'){
            cout << 0 << endl;
            return 0;
        }
        sol2 = sol-doble;
        if (s[i] != '1'){
          sol += (int)s[i] - 48;
        }
        sol2+=(int)s[i] - 48;
        if (s[i-1] != '1'){
          sol2 -= (int)s[i-1] - 48;
        }
        sol2 += ((int)s[i-1] - 48)*10;
        if (doble/10 != 1){
          sol2+=doble/10;
        }
        if (doble%10 != 1){
          sol2+=doble%10;
        }
        
        if (sol>sol2){
          doble=((int)s[i-1] - 48)*10+(int)s[i] - 48;
          sol = sol2;
        }
    }
    cout << sol << endl;
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
    solve(T);
  }
  return 0;
}