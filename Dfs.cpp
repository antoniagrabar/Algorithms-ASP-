#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

vector <int> g[MAXN], ans;
bool visited[MAXN];


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= m; i++){
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      g[v].push_back(u);
  }

  dfs(1);

  for(auto a : ans){
      cout << a << "\n";
  }
  
  return 0;
}