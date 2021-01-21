#include <bits/stdc++.h>

using namespace std;


#define MAXN 100
#define ALPHA 127

struct HashTable {
  explicit HashTable (int size, double c1, double c2) : size(size), c1(c1), c2(c2) {
    table.resize(size);
  }
  vector<string> table;
  int size;
  double c1, c2;

  int hash(string &k) {
    int ret = 0;
    for (auto c : k) {
      ret += ret*ALPHA + (int)c;
      ret %= size;
    }
    return ret;
  }

  int oahash(string &key, int i) {
    return ((int)round(hash(key) + i*c1 + i*i*c2)) % size;
  }

  pair<int, int> insert(string &key) {
    for (int i = 0; i < size; i++) {
      int slot = oahash(key, i);
      if (table[slot]=="") {
        table[slot] = key;
        return make_pair(slot, i);
      } else if (table[slot]==key) {
        return make_pair(slot, i);
      }
    }
    return make_pair(-1, -1);
  }

  string get(string &k) {
    for (int i = 0; i < size; i++) {
      int slot = oahash(k, i);
      if (table[slot]=="") break;
      if (table[slot]== k) {
        return table[slot];
      }
    }
    return "";
  }
};


//trazi minimalni jedinstveni broj adresa
int kapacitet(HashTable &ht) {
    int bio[ht.size];
    int ans = ht.size;

    // i - pretinac iz kojeg se krece
    for(int i = 0; i < ht.size; ++i){
        memset(bio, 0, sizeof(bio));
        int count = 0;
        for(int j = 0; j < ht.size; ++j){
            // za svaki pretinac i, size puta se mijenjaju j vrijednosti s kojima se mnoze konstante
            int slot = ((int)round(i + j*ht.c1 + j*j*ht.c2)) % ht.size;
            if(!bio[slot]) count++;
            bio[slot] = 1;
        }
        ans = min(ans, count);
    }
    return ans;
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int m;
  double c1, c2;
  cin >> m >> c1 >> c2;
  HashTable ht(m, c1, c2);
  cout << kapacitet(ht) << endl;
  return 0;
}
