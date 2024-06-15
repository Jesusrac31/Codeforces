#include <bits/stdc++.h>
#include <iostream>
#include <vector>
using namespace std;

int main(){
  int T, n, k, el, a, b;
  cin >> T;
  while (T--){
    cin>>n>>k;
    map<int, vector<int>> u;
		for (int i=0;i<n;i++){
			cin>>el;
			u[el].push_back(i);
		}
		cout<<endl;
		while (k--){
			cin>>a>>b;
			if (u.count(a)>0 && u.count(b)>0){
				if (u[b][u[b].size()-1]>u[a][0]) {
          cout<<"YES"<<endl;
        }
				else {
          cout<<"NO"<<endl;
        }
			}
			else{
        cout<<"NO"<<endl;
      }
		}
  }
  return 0;
}