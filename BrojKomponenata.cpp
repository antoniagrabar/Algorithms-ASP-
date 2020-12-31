#include <bits/stdc++.h>

using namespace std;

#define MAXN 100001

vector <int> g[MAXN];
bool visited[MAXN];

void dfs(int u){
    visited[u] = true;
    for(auto v : g[u]){
        if (visited[v]) continue;
        dfs(v);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, ans = 0;
    cin >> n >> m;

    for (int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int u = 1; u <= n; u++){
        if(visited[u]) continue;
        dfs(u);
        ans++;
    }
    
    cout << ans;

    return 0;
}