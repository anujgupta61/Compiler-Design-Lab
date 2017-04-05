#include <bits/stdc++.h>
using namespace std ;

map<char , vector<string> > partedProds ;
vector<char> ans ;

vector<string> partProd(string str) {
  vector<string> parts ;
  string temp = "" ;
  for(int i = 3 ; i < str . length() ; i ++) {
    if(str[i] == '|') {
      parts . push_back(temp) ;
      temp = "" ;
    } else {
      temp = temp + str[i] ;
    }
  }
  if(temp != "") {
    parts . push_back(temp) ;
  }
  return parts ;
}

void findFirst(char ch) {
  vector<string> vec = partedProds[ch] ;
  for(int i = 0 ; i < vec . size() ; i ++) {
    int asc = (int)vec[i][0] ;
    if(asc >= 65 && asc <= 90) { // Non-Terminals
      findFirst(vec[i][0]) ;
    } else { // Terminals
      if(find(ans . begin() , ans . end() , vec[i][0]) == ans . end()) // Not already present
        ans . push_back(vec[i][0]) ;
    }
  }
}

int main() {
  cout << "Enter the number of productions : " ;
  int n ;
  cin >> n ;
  vector<string> prods(n) ;
  for(int i = 0 ; i < n ; i ++) {
    cin >> prods[i] ;
  }
  for(int i = 0 ; i < n ; i ++) {
    vector<string> temp = partProd(prods[i]) ;
    partedProds[prods[i][0]] = temp ;
  }
  for(int i = 0 ; i < partedProds . size() ; i ++) {
    findFirst(prods[i][0]) ;
    cout << "First(" << prods[i][0] << ") : { " ;
    for(int j = 0 ; j < ans . size() ; j ++) {
      cout << ans[j] ;
      if(j != ans . size() - 1)
        cout << " , " ;
    }
    cout << " }\n" ;
    ans . clear() ;
  }
  return 0 ;
}
