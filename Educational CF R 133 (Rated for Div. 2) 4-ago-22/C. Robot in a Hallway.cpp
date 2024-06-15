#include <bits/stdc++.h>
#include <iostream>
using namespace std;
#define INF INFINITY;

vector<vector<int>> tiempo, rec;
int seconds = -1, m, recorridas = 1, debug, best = INF;

void Imprime(vector<vector<int>> a) {
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a[i].size(); j++) {
      cout << a[i][j] << ", ";
    }
    cout << "\n";
  }
}

bool solve(int x, int y) {
  seconds++;
  rec[x][y] = 1;
  cout << x << " " << y << " " << seconds << " " << recorridas << endl;
  Imprime(rec);
  cin >> debug;
  if (m * 2 == recorridas) {
    best = min(seconds, best);
    recorridas--;
    seconds--;
    rec[x][y] = 0;
    return (true);
  }
  int mov = 0, posibles = 4;
  if (x > 0 && x < m - 1) {
    if (rec[x + 1][y] == 0 && rec[x - 1][y] == 0) {
      seconds--;
      recorridas--;
      rec[x][y] = 0;
      return false;
    }
  }
  for (int i = -2; i < 3; i++) {
    if (i == 0) {
      continue;
    }
    if (x + (i % 2) > -1 && x + (i % 2) < m && y + (i / 2) > -1 &&
        y + (i / 2) < 2) {
      if (rec[x + (i % 2)][y + (i / 2)] == 0) {
        if (tiempo[x + (i % 2)][y + (i / 2)] <= seconds) {
          recorridas++;
          mov += solve(x + (i % 2), y + (i / 2));
        }
      } else {
        posibles--;
      }
    } else {
      posibles--;
    }
  }
  if (mov < posibles) {
    mov += solve(x, y);
  }

  if (rec[x][y]==1){
    recorridas--;
  }
  rec[x][y] = 0;
  seconds--;
  return (mov);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    int el;
    bool posible;
    cin >> m;
    for (int i = 0; i < m; i++) {
      cin >> el;
      tiempo.push_back({el, 0});
      rec.push_back({0, 0});
    }
    for (int i = 0; i < m; i++) {
      cin >> el;
      tiempo[i][1] = el;
    }
    rec[0][0] = 1;
    posible = solve(0, 0);
    cout << best << "\n";
  }

  return 0;
}