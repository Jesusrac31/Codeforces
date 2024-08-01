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

void Imprime(vector<bool> vect) {
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
vector<vi> conexiones;
set<int> impar, par;
vector<bool> bloqueados_impar;
vector<bool> bloqueados_par;
bool Alice = false;

void resuelve(int turno, int nodo){
    /*cout << "Nodo: " << nodo << " --> ";
    cout << "Bloqueados_impar: " << endl;
    Imprime(bloqueados_impar);
    cout << "Bloqueados_par: " << endl;
    Imprime(bloqueados_par);*/
    if (Alice == false){
        //cout << "Alice falso - ";
        if (turno%2 == 0){
            //cout << "Vamos a pares - ";
            if (bloqueados_impar[nodo]){
                // Debes jugar con Alice
                //cout << "Activamos Alice - ";
                Alice = true;
            } else {
                par.insert(nodo);
                bloqueados_par[nodo] = true;
                //cout << "Recorremos nodo - ";
                for (int i = 0; i<conexiones[nodo].size(); i++){
                    if (!bloqueados_impar[conexiones[nodo][i]]){ // Si esta bloqueado no lo recorras pero no pasa nada
                        //cout << "New_Process" << endl;
                        resuelve(turno+1, conexiones[nodo][i]);
                    }
                }
            }
        } else {
            //cout << "Vamos a impares - ";
            if (bloqueados_par[nodo]){
                // Debes jugar con Alice
                //cout << "Activamos Alice - ";
                Alice = true;
            } else {
                impar.insert(nodo);
                bloqueados_impar[nodo] = true;
                //cout << "Recorremos nodo - ";
                for (int i = 0; i<conexiones[nodo].size(); i++){
                    if (!bloqueados_par[conexiones[nodo][i]]){ // Si esta bloqueado no lo recorras pero no pasa nada
                        //cout << "New_Process" << endl;
                        resuelve(turno+1, conexiones[nodo][i]);
                    }
                }
            }
        }
    }
    //cout << "Nodo Finalizado" << endl;
}

int solve() {
  // Code aquí
  int n, m;
  cin >> n;

  if (n == -1){
    return 1;
  }

  cin >> m;

  conexiones.clear();
  bloqueados_impar.clear();
  bloqueados_par.clear();
  impar.clear();
  par.clear();
  Alice = false;
  for (int i = 0; i<=n; i++){
    conexiones.PB({});
    bloqueados_impar.PB(false);
    bloqueados_par.PB(false);
  }
  int u, v;
  for (int i = 0; i<m; i++){
    cin >> u >> v;
    conexiones[min(u,v)].PB(max(u,v));
  }
  resuelve(1, 1); // Decide si debe ser Alice o Bob 
  /*cout << "Conexiones:" << endl;
  Imprime2d(conexiones);
  cout << "Impares:" << endl;
  Imprime_set(impar);
  cout << "Pares:" << endl;
  Imprime_set(par);
  cout << "Bloqueados_impar: " << endl;
  Imprime(bloqueados_impar);
  cout << "Bloqueados_par: " << endl;
  Imprime(bloqueados_par);
  cout << Alice << endl;*/

  if (Alice){
    cout << "Alice" << endl;
    cout.flush();
    int j, c;
    for (int i = 0; i<n; i++){
        cout << "1 2" << endl;
        cout.flush();
        cin >> j >> c;
    }
  } else {
    cout << "Bob" << endl;
    cout.flush();
    auto itr_impar = impar.begin();
    auto itr_par = par.begin();
    int a, b;
    for (int i = 0; i<n; i++){
        cin >> a >> b;
        if (itr_impar == impar.end()){
            cout << (*itr_par) << " " << max(a, b) << endl;
            cout.flush();
            itr_par++;
        } else if (itr_par == par.end()){
            cout << (*itr_impar) << " " << min(a, b) << endl;
            cout.flush();
            itr_impar++;
        } else {
            if (min(a,b) == 1){
                cout << (*itr_impar) << " " << min(a, b) << endl;
                cout.flush();
                itr_impar++;
            } else {
                cout << (*itr_par) << " " << max(a, b) << endl;
                cout.flush();
                itr_par++;
            }
        }
    }
  }

  
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr); 
  int T;
  cin >> T; // Número de casos
  int salir = 0;
  while (T-- && salir == 0) {
    salir = solve();
  }
  if (salir == 1){
    cout << "You Lost\n";
    cout.flush();
  }
  return 0;
}

//Eliminar comentario si el proyecto está terminado (Dinámica empezó el 21/06/2024)