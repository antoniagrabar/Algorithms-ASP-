#include <bits/stdc++.h>

using namespace std;

#define MAXN 101

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

//bfs 

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, ans = 0;
  string s[MAXN];
  bool visited[MAXN][MAXN] = {};
  pair <int, int> start;
  cin >> n >> m;

  for (int i = 0; i < n; i++){
      cin >> s[i];
      //dohvacanje pozicije starta
      for (int j = 0; j < m; j++){
          if(s[i][j] == 'S'){
              start = {i,j};
              break;
          }
      }
  }

  // red pozicija za posjetiti {{i, j}, dist}
  queue<pair <pair<int, int>, int> > q;

  // prva pozicija u redu je start na udaljenosti 0
  q.push({start, 0});
  visited[start.first][start.second] = true;

  // sve dok u redu ima pozicija koje treba posjetiti i jos nismo nasli odgovor
  while(!q.empty() && !ans){
      pair <int, int> u;
      int dist;

      tie(u, dist) = q.front();
      q.pop();

      //provjeri sve susjede od u
      for (int i = 0; i < 4; i++){
          int I = u.first + dx[i];
          int J = u.second + dy[i];

          //ako se izaslo iz mape preskoci
          if(I < 0 || I >= n || J < 0 || J >= m) continue;

          //ako je zid preskoci
          if(s[I][J] == '#') continue;

          //ako je vec bila ova pozicija preskoci
          if(visited[I][J]) continue;

          //rješenje
          if(s[I][J] == 'F') ans = dist + 1;

          // ako se ni jedan if nije ispunio, ubaci susjeda od u na udaljenosti dist+1 u red za posjetiti i oznaci visited
          q.push({{I,J}, dist+1});
          visited[I][J] = true;
      }
  }

  cout << ans;
  
  return 0;
}