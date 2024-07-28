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
bool sort_func_listas(vi a, vi b) {
  if (a.size() < b.size()) {
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

vi lee(int n) {
  int el;
  vi vect;
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

vector<vi> niveles;
vector<vi> nodos;
vector<vi> conexiones;
vi raices;

int establecer(int nodo_ant = 1, int nodo_act = 1){
    raices[nodo_act] = nodo_ant;
    int deep = 0;
    for (int i = 0; i<nodos[nodo_act].size(); i++){
        if (nodos[nodo_act][i] != nodo_ant){
            deep = max(establecer(nodo_act, nodos[nodo_act][i]), deep);
            copia(conexiones[nodos[nodo_act][i]],conexiones[nodo_act]);
        }
    }
    conexiones[nodo_act].PB(nodo_act);
    niveles[deep].PB(nodo_act);

    return(deep+1);
}

int solve() {
  // Code aquí
  int n;
  cin >> n;
  niveles.clear();
  nodos.clear();
  conexiones.clear();
  raices.clear();
  vector<bool> bloqueados;
  for (int i = 0; i<=n; i++){
    raices.PB(1);
    nodos.PB({});
    niveles.PB({});
    conexiones.PB({});
    bloqueados.PB(true);
  }
  int x, y;
  for (int i = 0; i<n-1; i++){
    cin >> x >> y;
    nodos[x].PB(y);
    nodos[y].PB(x);
  }
  int depth_max = establecer()-1;

  /*Imprime2d(niveles);
  cout << "-------------------" << endl;
  Imprime2d(conexiones);
  cout << "-----end-----------" << endl;*/

  sort(conexiones.begin(), conexiones.end(), sort_func_listas);
  int depth = 0, resp, contador_eliminados = 0;
  int i = 0;
  vi cadena_final;
  //set<int> eliminados;
  while (i >= n) {
    while(bloqueados[i]){
        i++;
    }
    cout << "? " << conexiones[i][conexiones[i].size()-1] << endl;
    fflush(stdout);
    cin >> resp;
    if (resp == 0){
        for (int j = 0; j<niveles[depth].size(); j++){
            //eliminados.insert(niveles[depth][j]);
            if (!bloqueados[niveles[depth][j]]){
                bloqueados[niveles[depth][j]]=true;
                contador_eliminados++;
            }
        }
        for (int j = 0; j<conexiones[i].size(); j++){
            //eliminados.insert(conexiones[i][j]);
            if (!bloqueados[niveles[depth][j]]){
                bloqueados[conexiones[i][j]] = true;
                contador_eliminados++;
            }
        }
        depth++;
        if (cadena_final.size() == 0){
            bloqueados[raices[conexiones[i][conexiones[i].size()-1]]] = false;
            cadena_final.PB(raices[conexiones[i][conexiones[i].size()-1]]);
        } else {
            bloqueados[raices[cadena_final[cadena_final.size()-1]]] = false;
            cadena_final.PB(raices[conexiones[i][conexiones[i].size()-1]]);
        }
        contador_eliminados--;
    } else {
        for (int j = 1; j<=n; j++){
            bloqueados[j] = true;
        }
        for (int j = 0; j<conexiones[i].size(); j++){
            bloqueados[conexiones[i][j]] = false;
        }
        contador_eliminados = n-conexiones[i].size();
    }
    if (contador_eliminados == n-1){
        for (int j = 0; j<=n; j++){
            if (!bloqueados[j]){
                cout << "! " << j << endl;
                fflush(stdout);
            }
        }
        return 0;
    }
    i++;
  }
  // Queda una cadena de una fila

  
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

//Eliminar comentario si el proyecto está terminado (Dinámica empezó el 21/06/2024)