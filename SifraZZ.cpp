#include <bits/stdc++.h>

using namespace std;

//26 slova eng abecede
vector <int> g[26];
int visited[26], can[26][26];

//provjerava dokle seze povezanost pocetnog slova
void dfs(int s, int u){
    can[s][u] = 1;
    visited[u] = 1;

    for (auto &v : g[u]){
        if(!visited[v]) dfs(s, v);
    }
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m;
  cin >> n >> m;

  for (int i = 1; i <= n; i++){
      char c1, c2;
      cin >> c1 >> c2;
      //pretvori char u ascii vrijednost
      g[c1 - 'a'].push_back(c2 - 'a');
  }
  
  for (int i = 0; i < 26; i++){
      memset(visited, 0, sizeof(visited));
      dfs(i, i);
  }

  for (int i = 0; i < m; i++){
      string a, b;
      cin >> a >> b;
      if(a.size() != b.size()){
          cout << "no" << endl;
          continue;
      }
      
      bool ans = 1;
      for (int j = 0; j < (int)a.size(); j++){
          ans &= can[a[j] - 'a'][b[j] - 'a'];
      }

      cout << (ans ? "yes" : "no") << endl;
      
  }

  return 0;
}
