#include <bits/stdc++.h>
using namespace std ;

vector<string> rhs ;
vector<char> lhs ;
map<char , bool> containsNull ;
map<char , map<char , char> > opTable ;

void buildTable() {
  map<char , char> op1 ; // For id (t)
  op1['t'] = '=' ;
  op1['+'] = '<' ;
  op1['*'] = '<' ;
  op1['$'] = '<' ;
  opTable['t'] = op1 ;
  map<char , char> op2 ; // For +
  op2['t'] = '>' ;
  op2['+'] = '>' ;
  op2['*'] = '>' ;
  op2['$'] = '<' ;
  opTable['+'] = op2 ;
  map<char , char> op3 ; // For *
  op3['t'] = '>' ;
  op3['+'] = '<' ;
  op3['*'] = '>' ;
  op3['$'] = '<' ;
  opTable['*'] = op3 ;
  map<char , char> op4 ; // For $
  op3['t'] = '>' ;
  op3['+'] = '>' ;
  op3['*'] = '>' ;
  op3['$'] = '=' ;
  opTable['$'] = op4 ;
}

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
      map<char , char> pre = opTable[q . front()] ;
      char pr = pre[temp[0]] ;
      if(pr == '>') { // Reduce
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
      } else {
        if(is_shift) {
          char ch = q . front() ;
          q . pop() ;
          if(ch != '$')
            temp . insert(0 , 1 , ch) ;
        }
      }
      for(int i = temp . length() - 1 ; i >= 0 ; i --) {
        s . push(temp[i]) ;
      }
      if(! q . empty()) {
        printStkQ(s , q) ;
        if(is_shift)
          cout << "\tShift\n" ;
        else
          cout << "\tReduce\n" ;
      }
  }
  // Reduce
  char t = s . top() ;
  if(t != '$' && t != 'S') {
    while(true) {
      string temp = "" ;
      while(s . size() != 1) {
        temp += s . top() ;
        s . pop() ;
      }
      int start = 0 ;
      again :
      bool is_reduced = false ;
      for(int i = temp . length() - 1 ; i >= start ; i --) {
        string temp1 = "" ;
        //cout << temp << " : temp\n" ;
        for(int j = i ; j >= start ; j --)
          temp1 += temp[j] ;
        //cout << temp1 << "\n" ;
        //cout << "Finding " << temp1 << "\n" ;
        if(find(rhs . begin() , rhs . end() , temp1) != rhs . end()) { // Found in R.H.S.
            //cout << "inside\n" ;
            int pos = find(rhs . begin() , rhs . end() , temp1) - rhs . begin() ;
            char ch = lhs[pos] ;
            string temp2 = "" ;
            /*
            for(int j = start + 1 ; j <= temp . length() - 1 ; j ++)
              temp2 += temp[j] ;
            cout << "temp21 : " << temp2 << "\n" ;
            */
            //cout << "Found at " << i << " " << temp . length() - 1 << "\n" ;
            for(int j = 0 ; j < start ; j ++)
              temp2 += temp[j] ;
            temp2 += ch ;
            for(int j = i + 1 ; j <= temp . length() - 1 ; j ++)
               temp2 += temp[j] ;
            //cout << "temp22 : " << temp2 << "\n" ;

            //cout << "Remaining " << temp2 << "\n" ;
            /*
            for(int j = start + 1 ; j <= temp . length() - 1 ; j ++)
              temp2 += temp[j] ;
            */
            temp = temp2 ;
            //temp . insert(0 , 1 , ch) ;
            is_reduced = true ;
            //cout << "After reduce - " << temp << "\n" ;
            break ;
        }
      }
      //cout << "out\n" ;
      if(start == temp . length()) {
        //cout << "end here ..\n" ;
        for(int i = temp . length() - 1 ; i >= 0 ; i --) {
          s . push(temp[i]) ;
        }
        break ;
      }
      if(! is_reduced) {
        start ++ ;
        //cout << "next\n" ;
        goto again ;
      } else {
        for(int i = temp . length() - 1 ; i >= 0 ; i --) {
          s . push(temp[i]) ;
        }
        printStkQ(s , q) ;
        cout << "\tReduce\n" ;
      }
    }
  }
  //cout << "final -\n" ;
  printStkQ(s , q) ;
  if(s . top() == 'S' && s . size() == 2)
    cout << "\nString parsed ...\n" ;
  else
    cout << "\nString not parsed ...\n" ;
}

int main() {
  buildTable() ;
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
/*
S->T+S|T
T->F*T|F
F->t
*/
