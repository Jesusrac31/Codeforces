#include <bits/stdc++.h>
#include <iostream>
using namespace std;

vector<vector<int>> v;

void swap(int k) {
  int aux;
  for (int i = 0; i < v.size(); i++) {
    aux = v[i][k];
    v[i][k] = v[k][i];
    v[k][i] = aux;
  }
}

void imprime() {
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size(); j++) {
      cout << v[i][j] << " ";
    }
    cout << "\n";
  }
}

vector<vector<int>> solve(){
  
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, el;
    v.clear();
    cin >> n;
    for (int i = 0; i < n; i++) {
      v.push_back({});
      for (int j = 0; j < n; j++) {
        cin >> el;
        v[i].push_back(el);
      }
    }
    v=solve();
    imprime();
  }

  return 0;
}