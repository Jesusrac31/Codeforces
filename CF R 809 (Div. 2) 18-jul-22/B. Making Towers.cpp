#include <iostream>
#include <vector>
using namespace std;

void Imprime(vector<int> vect){
  for (int i=0; i<vect.size(); i++){
    cout << vect[i]<<" ";
  }
  cout << endl;
}

int main() {
  int n, t, el;
  vector<int> c, s;
  vector <int> elant;
  cin >> t;
  for (int mamawebo = 0; mamawebo < t; mamawebo++) {
    cin >> n;
    c = {};
    s = {};
    elant = {};
    for (int p = 0; p < n; p++) {
      cin >> el;
      c.push_back(el);
      elant.push_back(-1);
      s.push_back(0);
    }
    for (int i = 0; i < n; i++) {
      if (elant[c[i]-1] == -1) {
        s[c[i]-1]++;
        elant[c[i]-1] = i;
      } 
      else {
        if ((i - elant[c[i]-1]) % 2 == 1) {
          s[c[i]-1]++;
          elant[c[i]-1] = i;
        }
      }
    }
    Imprime(s);
  }
  return 0;
}