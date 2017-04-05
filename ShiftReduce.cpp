#include <bits/stdc++.h>
using namespace std ;

vector<string> rhs ;
vector<char> lhs ;
map<char , bool> containsNull ;

vector<string> partProd(string str) {
  vector<string> parts ;
  string temp = "" ;
  for(int i = 3 ; i < str . length() ; i ++) {
      if(str[i] == '|') {
          if(temp == "$")
            containsNull[str[0]] = true ;
          else
            parts . push_back(temp) ;
          temp = "" ;
      } else {
            temp = temp + str[i] ;
      }
  }
  if(temp != "") {
    if(temp == "$")
      containsNull[str[0]] = true ;
    else
      parts . push_back(temp) ;
  }
  return parts ;
}

void printStkQ(stack<char> stk , queue<char> q) {
  stack<char> temp_stk ;
  int n = stk . size() ;
  for(int j = 0 ; j < n ; j ++) {
    temp_stk . push(stk . top()) ;
    stk . pop() ;
  }
  for(int j = 0 ; j < n ; j ++) {
    cout << temp_stk . top() ;
    stk . push(temp_stk . top()) ;
    temp_stk . pop() ;
  }
  cout << "\t" ;
  queue<char> temp_q ;
  n = q . size() ;
  for(int j = 0 ; j < n ; j ++) {
    cout << q . front() ;
    temp_q . push(q . front()) ;
    q . pop() ;
  }
  q = temp_q ;
}

void parseStr(string str) {
  stack<char> s ;
  queue<char> q ;
  s . push('$') ;
  cout << "\nStack\tString\tOperation\n\n" ;
  for(int i = 0 ; i < str . length() ; i ++)
    q . push(str[i]) ;
  q . push('$') ;
  printStkQ(s , q) ;
  cout << "\t_\n" ;
  s . push(q . front()) ;
  q . pop() ;
  printStkQ(s , q) ;
  cout << "\tShift\n" ;
  while(! q . empty()) {
      string temp = "" ;
      while(s . size() != 1) {
        temp += s . top() ;
        s . pop() ;
      }
      bool is_shift = true ;
      for(int i = temp . length() - 1 ; i >= 0 ; i --) {
        string temp1 = "" ;
        for(int j = i ; j >= 0 ; j --)
          temp1 += temp[j] ;
        //cout << "Finding " << temp1 << "\n" ;
        if(find(rhs . begin() , rhs . end() , temp1) != rhs . end()) { // Found in R.H.S.
            is_shift = false ;
            //cout << "inside\n" ;
            int pos = find(rhs . begin() , rhs . end() , temp1) - rhs . begin() ;
            char ch = lhs[pos] ;
            string temp2 = "" ;
            //cout << "Found at " << i << " " << temp . length() - 1 << "\n" ;
            for(int j = i + 1 ; j <= temp . length() - 1 ; j ++)
               temp2 += temp[j] ;
            //cout << "Remaining " << temp2 << "\n" ;
            temp = temp2 ;
            temp . insert(0 , 1 , ch) ;
            //cout << "After reduce - " << temp << "\n" ;
            break ;
        }
      }
      if(is_shift) {
        char ch = q . front() ;
        q . pop() ;
        if(ch != '$')
          temp . insert(0 , 1 , ch) ;
      }
      for(int i = temp . length() - 1 ; i >= 0 ; i --) {
        s . push(temp[i]) ;
      }
      printStkQ(s , q) ;
      if(! q . empty()) {
        if(is_shift)
          cout << "\tShift\n" ;
        else
          cout << "\tReduce\n" ;
      }
  }
  if(s . top() == 'S')
    cout << "\nString parsed ...\n" ;
  else
    cout << "\nString not parsed ...\n" ;
}

int main() {
  cout << "Enter the number of productions : " ;
  int n ;
  cin >> n ;
  vector<string> prods(n) ;
  for(int i = 0 ; i < n ; i ++) {
    cin >> prods[i] ;
  }
  for(int i = 0 ; i < n ; i ++)
    containsNull[prods[i][0]] = false ;
  for(int i = 0 ; i < n ; i ++) {
    vector<string> temp = partProd(prods[i]) ;
    for(int j = 0 ; j < temp . size() ; j ++) {
      rhs . push_back(temp[j]) ;
      lhs . push_back(prods[i][0]) ;
    }
  }
  /*
  cout << "Printing L.H.S. and R.H.S.\n" ;
  for(int i = 0 ; i < rhs . size() ; i ++)
    cout << rhs[i] << " " << lhs[i] << "\n" ;
  */
  cout << "Enter string to parse : " ;
  string str ;
  cin >> str ;
  parseStr(str) ;
  return 0 ;
}