#include <bits/stdc++.h>

using namespace std;



void read_list(list<int> &l) {
  l.clear();
  while (true) {
    string s;
    cin >> s;
    if (!isdigit(s[0])) break;
    //stoi pretvara brojcani string u brojeve
    l.push_back(stoi(s));
  }
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  list<int> prva, druga;
  
  while(true) {
    int menu_choice;
    cin >> menu_choice;
    switch (menu_choice) {
      case 1:
        prva.merge(druga);
        break;
      case 2:
        for (auto v : prva) {
          cout << v << " ";
        }
        if (!prva.empty()) cout << endl;
        break;
      case 3:
        read_list(prva);
        read_list(druga);
        break;
      case 4:
        return 0;
    }
  }
  return 0;
}