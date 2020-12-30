#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001
const int INF = 0x3f3f3f3f;


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, s;
  vector <pair <int, int>> g[MAXN];

  cin >> n >> m >> s;

  for (int i = 0; i < m; i++){
      int u, v, w;
      cin >> u >> v >> w;

      // Svaki susjed vrha u je predstavljen kao par {v - susjed, w - težina brida od u do v}
      g[u].push_back({v,w});
      //Vrijedi i obratno kod neusmjerenog grafa
      g[v].push_back({u,w});
  }

  // Polje najkraćih udaljenosti postavi na INF
  int dist[MAXN];
  memset(dist, INF, sizeof(dist));

  // Min heap parova {udaljenost , vrh}
  priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

  // Udaljenost od početnog vrha je 0
  dist[s] = 0;
  pq.push({dist[s], s});

  while(!pq.empty()){
      int d, u;
      // Dohvati neobiđeni vrh s trenutno najmanjom otkrivenom udaljenosti od početnog
      tie(d,u) = pq.top();
      pq.pop();

      // Ako trenutno izvučena udaljenost iz prioritetnog reda nije aktualna preskoči
      if(dist[u] < d) continue;

      for(auto e : g[u]){
          int v, wuv;
          tie(v, wuv) = e;
          if(dist[u] + wuv < dist[v]){
              dist[v] = dist[u] + wuv;
              pq.push({dist[v], v});
          }
      }
  }

  for (int u = 1; u <= n; u++){
      cout << (dist[u] < INF ? dist[u] : -1) << "\n";
  }

  return 0;
}