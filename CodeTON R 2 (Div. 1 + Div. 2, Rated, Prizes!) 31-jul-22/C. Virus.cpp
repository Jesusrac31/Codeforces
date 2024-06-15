#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void Imprime(vector<int> vect) {
  for (int i = 0; i < vect.size(); i++) {
    cout << vect[i] << " ";
  }
  cout << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    int sol, n, m, el;
    vector<int> casas;
    cin >> n >> m;
    for (int i=0; i<m; i++){
      cin >> el;
      casas.push_back(el);
      sol++;
    }
    sort(casas.begin(), casas.end());
    for (int i = 0; i<casas.size(); i++){
      sol +=2;
      if (i==casas.size()-1)
      if(casas[i]+1==casas[i+1]){
        sol--;
      }
    }
    
  }

  return 0;
}