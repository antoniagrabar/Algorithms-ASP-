#include <bits/stdc++.h>

using namespace std;


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  map <char,char> zagrade = {{'(',')'}, {'[', ']'}};
  int n;
  cin >> n;

  for (int i = 0; i < n; i++){
      stack<char> st;
      string s;
      cin >> s;
      bool ispravan = true;
      for(auto c : s){
          //ako je c ( ili [ stavljamo ga u stack
          if(zagrade.count(c)){
              st.push(c);
          } else {
              ispravan &= !st.empty() && zagrade[st.top()] == c;
              if(!st.empty()) st.pop();
          }
      }
      cout << (ispravan && st.empty() ? "YES" : "NO") << "\n";
  }
  
  
  return 0;
}
