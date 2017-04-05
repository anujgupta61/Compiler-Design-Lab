#include <bits/stdc++.h>

using namespace std ;

string to_string(int i) {
    stringstream ss ;
    ss << i ;
    return ss.str() ;
}

int main() {
  int a = 4 ;
  string str = to_string(a) ;
  cout << str << "\n" ;
  return 0 ;
}
