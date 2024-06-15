#include<bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
  int n, q, el, l, k, sol, sum;
  double log_2 = log(2);
  vector<int> a;
  map<int,int> b;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    cin >> el;
    a.push_back(el);
    b[el]++;
  }
  while (q--) {
    cin >> k >> l;
    b[a[k-1]]--;
    if (b[a[k-1]]==0){
      b.erase(b.find(a[k-1]));
    }
    a[k-1]=l;
    b[l]++;
    sol = 0;
    sum = 0;
    for (auto i:b){
      sum=i.second+floor(sum/pow(2,i.first-sol));
      sol = i.first;
    }
    if (sum == 0){
      cout << sol << "\n";
    }
    else {
      cout << sol+floor(log(sum)/log_2) << "\n";
    }
  }
  return 0;
}