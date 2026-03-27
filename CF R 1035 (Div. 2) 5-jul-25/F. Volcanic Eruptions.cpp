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

#define INF 1000000000 // En este caso el infinito no puede tener su valor máximo, ya que tenemos que operar con él
#define MAXN 500001

int st,dist[MAXN],w[MAXN],tim[MAXN],ans;
vi g[MAXN];

// Esta función recorre el arbol con un dfs desde el nodo u que le pusiste al principio
// Asigna a cada nodo la distancia con respecto al nodo inicialmente introducido
void getdis(int u,int fa){ //u es el nodo que tratamos y fa el nodo padre (para evitar bucles infinitos)
	for(int v:g[u]){ // Por cada nodo adyascente al nodo u
		if(v==fa) continue; // Si es el padre, no hago nada
		dist[v]=dist[u]+1; // Si es un nodo hijo, hacemos lo mismo desde el nodo hijo añadiendo 1 a la distancia con respecto a su padre
		getdis(v,u);
	}
}

// Nucleo del algoritmo. Los parámetros de esta función son:
// Nodo activo, padre del nodo activo, distancia mínima entre el camino y una arista <1,1>,
// indica si la secuencia que ha seguido el camino es 1, -1, 1, -1..., puntos de vida en el nodo activo, cuando puede llegar al nodo, distancia entre el nodo origen y el nodo activo
void dfs(int u,int fa,int k,bool inn,int hei,int TIM,int dis){
    if(hei<0){// Si los puntos de vida caen por debajo de 0
		TIM=max(TIM,(-hei+1)/2*2+k*2+dis);  // Tenemos que hacer Turn en una arista <1,1>, serán al menos 2 turns, por lo cual el recorrido completo será:
                                            // Número de Turn ((-hei+1)/2*2) + distancia de ida y vuelta hacia la arista con el turn (2*k) + distancia entre el nodo origen y el nodo actual (dis)
	}
	if(TIM<=dist[u]){// Si cuando llega al nodo no hay lava, podemos actualizar la respuesta
		ans=max(ans,dist[u]); // Buscamos la respuesta máxima, que sería el maximo entre la respuesta anteriormente obtenida, y cuanto tiempo puedo permanecer en el nodo
	} else{ // En caso de que el nodo esté cubierto de lava, no continuamos
		return;
	}
	for(int v:g[u]){
		if(v==fa) continue; // Si el nodo adyascente es el padre, no haces nada

		if(inn&&w[u]!=w[v]){ // Si estamos en un camino que de momento solo ha tenido la secuencia 1, -1
			dfs(v,u,min(k,tim[v]),inn,hei+w[v],TIM+1,dis+1); //Continuamos el camino pero podemos seguir calculando la distancia mínima hasta una arista <1, 1>
		}
		else{
			dfs(v,u,k,0,hei+w[v],TIM+1,dis+1); // En caso de que el camino ya no siga esa secuencia, está claro que no podemos asegurar que pasemos, así que podemos asumir que ya hemos pasado por una arista <1,1> y no podemos seguir obteniendo la distancia mínima
		}
	}
}

/*
En este problema, definiremos el peso de un nodo como w_x, siendo x el nodo al cual queremos referirnos
Además, para definir las aristas definiremos dos nomenclaturas:
    - (u, v): Indica una arista entre el nodo u y v
    - <a, b>: Indica una arista (u, v) que tiene pesos en los nodos w_u = a y w_v = b 
*/
int solve(){
    //Input
    int n;
    cin>>n>>st; // Numero de nodos y nodo inicial

    //Limpia las listas
	for(int i=1;i<=n;i++){
		dist[i]=0; // Distancia entre el nodo 1 y el nodo i
		tim[i]=INF; // Distancia a una arista <1,1>
		g[i].clear(); // El grafo en sí, es una lista de adyascencia
	}
    // Inicializa answer a 0
	ans=0;

    // Recoge los pesos
	for(int i=1;i<=n;i++){
		cin>>w[i];
	}
    // Crea la lista de adyascencia en g
    int u, v;
	for(int i=1;i<n;i++){ // Esta línea y la anterior estaban compactadas como for(int i=1, u, v;i<n;i++){ 
		cin>>u>>v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
    // Inicializa dist con las distancias desde el nodo 1 (desde donde sale la lava)
	getdis(1,-1);

    // Metemos en la cola q todas las aristas <1,1> y establecemos el tim de esas aristas a 0
	// Nota que metemos solo un nodo de la arista para más tarde meter el otro.
    queue<int> q;
    for(int i=1;i<=n;i++){
		for(int v:g[i]){
			if(w[i]==1&&w[v]==1){
				tim[i]=0;
				q.push(i);
				break;
			}
		}
	}

    // Por cada arista <1,1> hacemos un bfs pero solo consideraremos adyascentes a los nodos conectados con dicho nodo y que tengan un peso distinto.
    // De esta forma seguiremos una secuencia de pesos 1, -1 que sería la secuencia por la cual puede moverse nuestro protagonista manteniendo su nivel de salud.
    // No tiene sentido mirar los nodos con 1 y 1 ya que lo miraremos luego, y los -1, -1 podríamos no poder llegar
	// Nota que evaluamos todos los nodos a la vez y establecemos su distancia en tim bloqueando los que ya hemos recorrido
    while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int v:g[u]){ 
			if(tim[v]==INF&&w[v]!=w[u]){
				tim[v]=tim[u]+1;
				q.push(v);
			}
		}
	}

    // Obtenemos al fin la solucion
	dfs(st,-1,tim[st],true,w[st],1,1);
    // Devolvemos el resultado. Pero debemos tener en cuenta que siempre se mueve, para ello obtenemos el módulo 2 de la distancia entre la lava y el nodo final. 
    // En caso de que el modulo sea 0 ((dist[st]&1) == 0 cuando el último bit es 0, es decir, es múltiplo de 2), restamos 1 a la solución ya que tendremos que caminar hacia la lava cuando llegue al nodo de justo antes.
	cout<<ans+(dist[st]&1)-1<<'\n';

    return 0;
}

int main(){
	ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;
	cin>>T;
	while(T--){
		solve();
	}
    return 0;
}
// https://codeforces.com/contest/2119/problem/F
