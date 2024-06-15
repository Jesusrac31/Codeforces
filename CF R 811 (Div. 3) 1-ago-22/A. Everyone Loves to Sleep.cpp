#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int T;
  cin >> T;
  while(T--){
    int n, h, m, h2, m2, solh=25, solm=61;
    cin >> n >> h >> m;
    while(n--){
      cin >> h2 >> m2;
      h2-=h;
      if (h2<0){
        h2+=24;
      }
      
      m2-=m;
      if (m2<0){
        h2--;
        m2+=60;
      }
      
      if (h2<solh){
        solh=h2;
        solm=m2;
      }
      else if(solh==h2 && solm>m2){
        solm=m2;
      }
    }
    cout << solh << " " << solm << endl;
  }
  return 0;
}