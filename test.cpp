#include<bits/stdc++.h>
using namespace std; // No tienes que usar el prefijo std::
typedef long long lli; // Cambia el nombre de una estructura de dato
#define int lli // Usa int como long long int
#define INF 10e9 // Cada vez que escribas INF se escribirá 10e9, funciona también con funciones
double pi = 2*acos(0.0); // pi


signed main() {
    int t;
    priority_queue<int> pq;
    pq.push(2);
    pq.push(3);
    cout << pq.top();

    return 0;
}