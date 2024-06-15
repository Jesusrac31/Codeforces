#include <iostream>
#include <vector>
using namespace std;
#define repite(n) for (int i = 0; i < n; i++)

int main() {
  int T, n, el, ref, salto;
  long long int sol, suma, MIN;
  vector<int> h;
  vector<int> compara;
  cin >> T;
  while (T--) {
    cin >> n;
    h = {};
    sol = 0LL;
    repite(n) {
      cin >> el;
      h.push_back(el);
    }
    if (n % 2 == 1) {
      for (int i = 1; i < n; i += 2) {
        ref = max(h[i - 1], h[i + 1]);
        if (h[i] <= ref) {
          sol += ref - h[i] + 1LL;
        }
      }
    } else {
      suma = 0LL;
      for (int i = 1; i < n; i += 2) {
        ref = max(h[i - 1], h[i + 1]);
        if (h[i] <= ref) {
          suma += ref - h[i] + 1;
        }
      }
      MIN = suma;
      salto = n-1;
      for (int i = n-2; i > 0; i -= 2) {
        ref = max(h[i - 1], h[i + 1]);
        if (h[i] <= ref) {
          suma += ref - h[i] + 1;
        }
        ref = max(h[i - 2], h[i]);
        if (h[i-1] <= ref) {
          suma -= ref - h[i-1] + 1;
        }
        if (suma < MIN){
          MIN = suma;
          salto = i-1;
        }
      }
      for (int i = 1; i < salto; i += 2) {
        ref = max(h[i - 1], h[i + 1]);
        if (h[i] <= ref) {
          sol += ref - h[i] + 1LL;
        }
      }
      for (int i = salto+1; i < n; i += 2) {
        ref = max(h[i - 1], h[i + 1]);
        if (h[i] <= ref) {
          sol += ref - h[i] + 1LL;
        }
      }
    }
    cout << sol << "\n";
  }
  return 0;
}