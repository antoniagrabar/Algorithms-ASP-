#include <bits/stdc++.h>

using namespace std;


#define MAXN 100
#define ALPHA 127

struct HashTable {
  explicit HashTable (int size) : size(size) {
    table.resize(size);
  }
  vector<string> table;
  int size;

  int hash(string &k) {
    int ret = 0;
    for (auto c : k) {
      ret += ret*ALPHA + (int)c;
      ret %= size;
    }
    return ret;
  }

  int oahash(string &key, int i) {
    return (hash(key) + (i + (long long)i*i)/2) % size;
  }

  bool rehash(int new_size) {
    vector<string> oldtable = table;
    int oldsize = size;
    size = new_size;
    table.clear();
    table.resize(new_size);

    for (auto &key : oldtable) {
      if (key!="") {
        if (insert(key).first==-1) {
          table = oldtable;
          size = oldsize;
          return false;
        }
      }
    }
      return true;
      
      
  }

  pair<int, int> insert(string key) {
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

  // Za svaki pretinac u tablici ispisuje potreban broj ispitivanja za dohvat.
  void print_usage() {
    for (int slot = 0; slot<size; ++slot) {
      int num = -1;
      if (table[slot]!="") {
        while (num<size && oahash(table[slot], num++)!=slot);
      }
      cout << slot << " " << num+1 << '\n';
    }
  }
};


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, sz;
  cin >> n >> sz;
  HashTable ht(sz);
  for (int i = 0; i < n; ++i) {
    string typ;
    cin >> typ;
    if (typ=="i") {
      string key;
      cin >> key;
      if (ht.insert(key).first==-1) {
        cout << "Insert " << key << " failed.\n";
      }
    } else if (typ=="r") {
      cin >> sz;
      if (ht.rehash(sz)) {
        ht.print_usage();
      } else {
        cout << "Rehash to size " << sz << " failed.\n";
      }
    }
  }
  return 0;
}
