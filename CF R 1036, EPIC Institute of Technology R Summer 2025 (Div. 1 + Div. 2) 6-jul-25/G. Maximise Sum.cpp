#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

#define INF 1e9

const int maxN = 1e6 + 10;
int a[maxN];           // array original
ll best[maxN];         // best[cost] = mejor suma con operación de costo >= cost, array solución
ll pref[maxN];         // suma de mínimos hasta cada índice, suma de mínimos de los prefijos
int sec_mn[maxN];      // segundo mínimo hasta cada índice, el segundo número más pequeño hasta cada índice
ll pref_sec[maxN];     // suma de segundos mínimos, suma de segundos mínimos de prefijos
int MN[maxN];          // mínimo hasta cada índice
int f[maxN];           // para cada mínimo, indica hasta dónde se mantiene (siguiente cambio)

// Procesa un caso de prueba
void solve() {
    int n;
    cin >> n;

    // Leer el arreglo 1-indexado
    for (int i = 1; i <= n; i++) cin >> a[i];

    // Inicializar best[cost] a cero
    for (int i = 0; i <= n - 1; i++) {
        best[i] = 0;
    }

    // suf_max guarda índices j con valores crecientes de derecha a izquierda
    vector<int> suf_max;
    suf_max.reserve(n); // Le decimos que ese vector debe contener al menos n elementos
    for (int i = n; i >= 1; i--) { // Recorremos el array de derecha a izquierda almacenando índices de forma creciente
        if (suf_max.empty() || a[i] > a[suf_max.back()]) { 
            suf_max.emplace_back(i);
        }
    }

    // Construcción de mínimos y segundos mínimos de prefijos
    int mn = INF; // Al principio establecemos los mínimos como infinito
    sec_mn[0] = INF;
    MN[0] = INF;
    int ind = -1;

    for (int i = 1; i <= n; i++) {
        sec_mn[i] = sec_mn[i - 1]; // Por defecto decimos que el segundo mínimo es el mismo que en el índice anterior

        // Si encontramos un nuevo mínimo, guardamos el anterior como segundo mínimo
        if (a[i] < mn) {
            if (ind != -1) f[ind] = i; // f[ind] = dónde cambia el mínimo
            sec_mn[i] = mn;
            mn = a[i];
            ind = i; // Cambia el valor de ind (la posición del último mínimo)
        } else if (a[i] < sec_mn[i]) { // Puede que el número sea mayor que el primer mínimo pero no que el segundo, actualizamos solo el segundo entonces
            sec_mn[i] = a[i];
        }

        MN[i] = mn; // Actualizamos el valor de mínimo con el valor obtenido
        pref[i] = pref[i - 1] + mn;           // suma de mínimos del prefijo
        pref_sec[i] = pref_sec[i - 1] + sec_mn[i]; // suma de segundos mínimos del prefijo
    }

    f[ind] = n + 1;  // marcador para el final

    // base sin operación
    best[0] = pref[n]; // Para coste 0, es sin operación lo cual es la suma de los mínimos del prefijo de longitud n

    // Monotonic stack para mantener candidatos donde se puede extender el mínimo
    vector<int> st{n + 1}; // Empieza con n+1 para indicar el final de la lista en la siguiente parte, ya que a[n+1] = 0
    a[n + 1] = -1e9;

    // Iteramos de derecha a izquierda
    for (int i = n; i >= 1; i--) {
        // Solo consideramos operación si `a[i]` es menor que el mínimo hasta i-1
        if (MN[i - 1] > a[i]) { // Cuando lleguemos al siguiente mínimo
            for (int id : suf_max) {// Ten en cuenta que solo merece la pena operar con números mayores al último, sino el coste sería menor para una suma menor
                                    // Por cada candidato
                if (id <= i) break; // mientras que el candidato esté a la derecha de nuestro número

                // simulamos a[i] += a[j]
                int cur_mn = min(a[i] + a[id], MN[i - 1]); // El nuevo valor que iría en la posición i

                // buscar índice donde termina este mínimo extendido
                int l = 0, r = st.size();
                while (r - l > 1) { // Usa busqueda dicotómica
                    int mid = (l + r) / 2;
                    if (a[st[mid]] <= cur_mn) l = mid;
                    else r = mid;
                }
                // En st[l], tenemos el primer índice que es menor o igual a nuestro mínimo

                // Vemos hasta que índice tenemos que actualizar. En caso de que el índice id sea menor al obtenido en la búsqueda binaria, tendremos que actualizar solo hasta el final
                int upto = min(id - 1, st[l] - 1);

                // En val almacenamos la nueva suma hasta el elemento upto. Ten en cuenta que todos los sumandos entre i y upto son cur_min, ese era el objetivo de la bísqueda binaria
                ll val = pref[i - 1] + cur_mn * 1LL * (upto - i + 1);

                // entre upto+1 y id-1 tendremos que usar los segundos mínimos
                if (upto + 1 < id) {
                    int upup = min(f[i], id); // Recuerda siempre coger el minimo entre id y otro número a la hora de seleccionar un índice para hacer el recorte correctamente
                    
                    // El valor extra de la suma sería sustituir la suma de los segundos por la suma de los primeros
                    val += pref_sec[upup - 1] - pref_sec[upto]; // Aquí añade la suma de los segundos mínimos
                    val += pref[id - 1] - pref[upup - 1]; // Aquí elimina la suma de los primeros mínimos
                }

                int cost = id - i; // El coste es de id (j) menos el índice del mínimo que cambiaremos (i)
                best[cost] = max(best[cost], val); // Almacena el mayor

                // si el mínimo ya no mejora, rompemos el ciclo
                if (a[i] + a[id] >= MN[i - 1]) break;
            }
        }

        // Hace que en el stack los índices sea siempre de elementos en orden creciente
        while (!st.empty() && a[i] <= a[st.back()]) st.pop_back();
        st.emplace_back(i);
    }

    // Ahora en best[i] está la mejor combinación para un coste exactamente de i. 
    // Como queremos de un coste de al menos i, si la solución de b[i+1] es mayor que b[i], b[i] = b[i+1]
    for (int i = n - 2; i >= 0; i--) {
        best[i] = max(best[i], best[i + 1]);
    }

    // Imprimir resultado
    for (int i = 0; i < n; i++) cout << best[i] << " ";
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tst;
    cin >> tst;
    while (tst--) {
        solve();
    }
    return 0;
}
// https://codeforces.com/contest/2124/problem/G
