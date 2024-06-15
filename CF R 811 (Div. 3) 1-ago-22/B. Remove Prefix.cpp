#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--){
    int n, el, sol=-1;
    map<int, vector<int>> rep;
    cin >> n;
    for (int i = 0; i<n; i++){
      cin >> el;
      rep[el].push_back(i);
    }
    for (auto c:rep){
      if (c.second.size()>1){
        sol = max(sol, c.second[c.second.size()-2]);
      }
    }
    cout << sol+1 << endl;
  }
  
  return 0;
}