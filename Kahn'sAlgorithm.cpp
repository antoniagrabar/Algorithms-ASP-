#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  vector<int> g[MAXN];
  vector<int> ans;
  /*polje in sadrzi ulazne tezine cvorova, tj broj cvorova o kojima i-ti cvor ovisi*/
  int in[MAXN] = {};

  for (int i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;

      g[u].push_back(v);
      in[v]++; //iz u se moze doci do v
  }

  queue<int> q;

  for (int u = 1; u <= n; u++){
      if(in[u] == 0) q.push(u);
  }

  while(!q.empty()){
      int u = q.front();
      q.pop();

      ans.push_back(u);

      for(auto v : g[u]){
          in[v]--;
          if(in[v] == 0) q.push(v);
      }
  }

  reverse(ans.begin(), ans.end());

  for(auto u : ans) cout << u << " ";
  cout << endl;
  
  return 0;
}