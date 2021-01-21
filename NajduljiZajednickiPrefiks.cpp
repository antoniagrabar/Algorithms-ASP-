#include <bits/stdc++.h>

using namespace std;

#define MAXN 2001
const int MOD = 1e9+7;
int n, m;
string s[MAXN];
long long hsh[MAXN][MAXN];

int binary_search(int a, int b){
    int lo = -1, hi = m ;
    while(lo +1 < hi){
        int mid = (lo + hi)/2;
        if(hsh[a][mid] == hsh[b][mid]) lo = mid;
        else hi = mid;
    }
    return hi;

}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> n >> m;

  for (int i = 0; i < n; i++){
      cin >> s[i];
  }

  for (int i = 0; i < n; i++){
      for (int j = 0; j < m; j++){
          hsh[i][j] = j ? ((hsh[i][j-1]*127 + s[i][j]) % MOD) : s[i][0];
      }
  }
  

  int q;
  cin >> q;

  for(int k = 0; k < q; ++k){
      int a, b;
      cin >> a >> b;
      int ans = binary_search(a-1,b-1);
      cout << ans << "\n";
      }
  

  return 0;
}