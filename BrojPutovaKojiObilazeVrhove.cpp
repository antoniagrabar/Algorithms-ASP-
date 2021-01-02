#include <bits/stdc++.h>

using namespace std;


vector<int> g[9];
int visited[9], ans = 0, N, M, sum_visited = 0;

void dfs(int u){
    visited[u] = 1;
    sum_visited++;
    if(sum_visited == N) ans++;
    for(auto v: g[u]){
        if(visited[v]) continue;
        dfs(v);
    }
    visited[u] = 0;
    sum_visited--;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  cout << ans << endl;
  return 0;
}