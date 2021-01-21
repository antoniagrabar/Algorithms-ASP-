#include <bits/stdc++.h>

using namespace std;


#define MAXN 100
#define ALPHA 127

struct HashTable {
  vector<list<string>> table;
  int size;
  explicit HashTable (int size) : size(size) {
    table.resize(size);
  }

  int hsh(string &k) {
    int ret = 0;
    for (auto c : k) {
      ret += ret*ALPHA + (int)c;
      ret %= size;
    }
    return ret;
  }

  int insert(string &k) {
    for (auto &el : table[hsh(k)]) {
      if (el==k) return 0;
    }
    table[hsh(k)].push_back(k);
    //svaki puta kada se ubaci novi element, vraca se ukupan broj elemenata u tom pretincu
    //ne trebamo racunati prosjek
    return table[hsh(k)].size();
  }

  bool get(string &k) {
    for (auto &el : table[hsh(k)]) {
      if (el==k) return true;
    }
    return false;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, mlo, mhi;
  cin >> n >> mlo >> mhi;

  string keys[MAXN];
  for (int i = 0; i < n; i++){
      cin >> keys[i];
  }

  //za svaku velicinu tablice od mlo do mhi - odrediti prosjecnu duljinu lista u tablici
  //trazimo velicinu tablicu ans na kojoj je prosjecno najmanje elemenata po pretincu
  int min = 999999;
  int ans = MAXN;
  for(int size = mlo; size <= mhi; size++){
      HashTable ht(size);

      int sum = 0;
      //dodajemo sve kljuceve
      for (int i = 0; i < n; i++){
          sum += ht.insert(keys[i]);
      }

      if(sum < min){
          min = sum;
          ans = size;
      }
  }

  cout << ans << endl;
  
  return 0;
}
