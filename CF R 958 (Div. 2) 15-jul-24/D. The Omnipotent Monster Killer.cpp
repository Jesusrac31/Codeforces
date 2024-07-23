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

void ImprimeBool(vector<bool> vect) {
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

vll lee(int n) {
  lli el;
  vll vect = {0};
  for (int i = 0; i < n; i++) {
    cin >> el;
    vect.PB(el);
  }
  return (vect);
}

vi camino;
lli valor_camino;
vector<vi> nodos;
vll attacks;
vi camino_actual;
lli sumando;
vector<bool> bloqueados;
vector<bool> muertos;

void max_path(int nodo_act = 0){
    // Recorremos todos los nodos posteriores para hacer los posibles caminos
    for (int i = nodo_act+1; i<nodos.size(); i++){
        if (!bloqueados[i]){ // Solo si el nodo no está bloqueado
            //cout << "nodo: " << i << " sumando: " << sumando << endl;
            
            // Camino actual, sumando y bloqueados podrían meterse en la función recursiva pero trae problemas de memoria
            // La solución es actualizarlas antes de acceder y al terminar devolverlas a su valor inicial
            camino_actual.PB(i);
            sumando += attacks[i];
            // Bloqueamos todos los nodos adyascentes al nodo actual
            for (int j = 0; j<nodos[i].size(); j++){
                bloqueados[nodos[i][j]] = true;
            }

            max_path(i);

            camino_actual.pop_back();
            sumando -= attacks[i];
            for (int j = 0; j<nodos[i].size(); j++){
                if (!muertos[nodos[i][j]]){ // Solo desbloqueamos los monstruos que no hayamos matado
                    bloqueados[nodos[i][j]] = false;
                }
            }
        }
    }

    //Una vez hecho el camino completo (todos los nodos han sido seleccionados o están bloqueados), comprobamos si es el máximo para almacenarlo
    if (sumando > valor_camino){
        valor_camino = sumando;
        camino.clear();
        copia(camino_actual, camino);
    }
}

int solve() {
  
  // Reseteamos los arrays globales attacks, nodos, bloqueados y muertos que usaremos más adelante
  attacks.clear();
  nodos.clear();
  bloqueados.clear();
  muertos.clear();

  // Obtenemos el número de monstruos o nodos
  int n;
  cin >> n;

  // Recogemos el ataque de cada monstruo o el peso del nodo
  attacks = lee(n);

  /* Preparamos la matriz nodos donde cada columna nos indica cuales nodos bloquearíamos si seleccionamos un nodo en concreto.
     Ej: En nodos[4] hay un array de indices, los nodos que comparten un segmento con el nodo 4
     Además decimos que ningún nodo está bloqueado ni muerto y calculamos la suma de todos los ataques */
  lli total = 0;

  for(int i = 0; i<=n; i++){
    nodos.PB({});
    bloqueados.PB(false); // No están bloqueados al principio
    muertos.PB(false); // No están muertos al principio
    total += attacks[i];
  }

  // Inicializamos la matriz nodos donde cada columna nos indica cuales nodos bloquearíamos si seleccionamos un nodo en concreto.
  // Ej: En nodos[4] hay un array de indices, los nodos que comparten un segmento con el nodo 4
  int x, y;

  for (int i = 0; i<n-1; i++){
    cin >> x >> y;
    nodos[min(x, y)].PB(max(x,y)); // Por como está hecho el algoritmo, un nodo con un indice grande no podrá acceder a un nodo con indice chico, así que no lo incluimos.
    // Ej: El nodo 4 nunca podrá acceder al nodo 1, pero el nodo 1 sí al nodo 4.
  }

  // Iniciamos la variable donde estará el daño recibido
  lli suma = 0;
  
  //cout << "total: " << total << endl;
  while (total != 0){
    // Reset variables globales del algoritmo
    valor_camino = 0;
    sumando = 0;
    camino.clear();
    camino_actual.clear();

    // Aplica daño
    suma += total;

    // Calculo de monstruos que matamos y cuanto daño nos ahorramos
    max_path();
    total -= valor_camino;

    // Bloqueamos y matamos los monstruos a los que matamos para representar su muerte
    for (int i = 0; i<camino.size(); i++){
        bloqueados[camino[i]] = true;
        muertos[camino[i]] = true;
    }
    //cout << "total: " << total << ", valor_camino: " << valor_camino << endl;
    //Imprime(camino);
    //ImprimeBool(bloqueados);
  }
  cout << suma << endl;
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
// Muy lento :(