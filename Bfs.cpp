#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

void bfs(vector <int> *g, int *dist){
    bool visited[MAXN] = {};
    queue<int> q;
    dist[1] = 0;
    visited[1] = true;
    q.push(1);

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(auto v : g[u]){
            if(visited[v]) continue;
            visited[v] = true;
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  vector <int> g[MAXN];
  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= m; i++){
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
  }
  
  int dist[MAXN] = {};
  bfs(g, dist);
  for (int i = 1; i <= n; i++){
      cout << dist[i] << "\n";
  }
  

  return 0;
}