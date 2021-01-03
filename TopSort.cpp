#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001
vector<int> g[MAXN], color(MAXN), ans;

bool dfs(int u){
    color[u] = 1;
    for(auto &v : g[u]){
        if(color[v] == 2) continue;
        if(color[v] == 1) return true;
        if(dfs(v)) return true;
    }
    ans.push_back(u);
    color[u] = 2;
    return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
  }

  for(int u = 1; u <= n; ++u){
      if(color[u] == 0 && dfs(u)) assert(false);
  }

  for(auto u : ans) cout << u << " ";
  cout << endl;

  return 0;
}