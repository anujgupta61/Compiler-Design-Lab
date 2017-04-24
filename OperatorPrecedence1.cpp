#include <bits/stdc++.h>
using namespace std ;

map<char , map<char , char> > opTable ;
vector<string> rhs ;
vector<char> lhs ;

void buildTable() {
  // Row-wise
  map<char , char> op1 ; // For id (t)
  op1['t'] = '_' ;
  op1['+'] = '<' ;
  op1['*'] = '<' ;
  op1['$'] = '<' ;
  op1['('] = '<' ;
  op1[')'] = '_' ;
  opTable['t'] = op1 ;
  map<char , char> op2 ; // For +
  op2['t'] = '>' ;
  op2['+'] = '>' ;
  op2['*'] = '>' ;
  op2['$'] = '<' ;
  op2['('] = '<' ;
  op2[')'] = '>' ;
  opTable['+'] = op2 ;
  map<char , char> op3 ; // For *
  op3['t'] = '>' ;
  op3['+'] = '<' ;
  op3['*'] = '>' ;
  op3['$'] = '<' ;
  op3['('] = '<' ;
  op3[')'] = '>' ;
  opTable['*'] = op3 ;
  map<char , char> op4 ; // For $
  op4['t'] = '>' ;
  op4['+'] = '>' ;
  op4['*'] = '>' ;
  op4['$'] = '_' ;
  op4['('] = '_' ;
  op4[')'] = '>' ;
  opTable['$'] = op4 ;
  map<char , char> op5 ; // For (
  op5['t'] = '_' ;
  op5['+'] = '<' ;
  op5['*'] = '<' ;
  op5['$'] = '<' ;
  op5['('] = '<' ;
  op5[')'] = '_' ;
  opTable['('] = op5 ;
  map<char , char> op6 ; // For )
  op6['t'] = '>' ;
  op6['+'] = '>' ;
  op6['*'] = '>' ;
  op6['$'] = '_' ;
  op6['('] = '=' ;
  op6[')'] = '>' ;
  opTable[')'] = op6 ;
}

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

void printStkQ(stack<char> stk , stack<char> stk1 , queue<char> q) {
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
  cout << "\t\t" ;
  if(stk1 . empty()) {
    cout << "_\t\t" ;
  } else {
    stack<char> temp_stk1 ;
    int n1 = stk1 . size() ;
    for(int j = 0 ; j < n1 ; j ++) {
      temp_stk1 . push(stk1 . top()) ;
      stk1 . pop() ;
    }
    for(int j = 0 ; j < n1 ; j ++) {
      cout << temp_stk1 . top() ;
      stk1 . push(temp_stk1 . top()) ;
      temp_stk1 . pop() ;
    }
    cout << "\t\t" ;
    queue<char> temp_q ;
    n = q . size() ;
    for(int j = 0 ; j < n ; j ++) {
      cout << q . front() ;
      temp_q . push(q . front()) ;
      q . pop() ;
    }
    q = temp_q ;
  }
}

void parse(string str) {
  stack<char> s , s1 ;
  queue<char> q ;
  s . push('$') ;
  cout << "\nStack\t\tNT-Stack\t\tString\t\tOperation\n\n" ;
  for(int i = 0 ; i < str . length() ; i ++)
    q . push(str[i]) ;
  q . push('$') ;
  printStkQ(s , s1 , q) ;
  cout << "\t\t_\t\t_\n" ;
  s . push(q . front()) ;
  q . pop() ;
  printStkQ(s , s1 , q) ;
  cout << "\t\t_\t\tShift\n" ;
  while(q . front() != '$' || s . top() != '$') {
    //cout << "top\n" ;
  	char pre = opTable[q . front()][s . top()] ;
    //cout << "pre : " << pre << "\n" ;
	  if(pre == '_') {
	  	cout << "Error in parsing ...\n" ;
	  	return ;
	  }
	  if(pre == '<') { // Shift
	  	char ch = q . front() ;
	  	q . pop() ;
	  	s . push(ch) ;
      printStkQ(s , s1 , q) ;
      cout << "\t\tShift\n" ;
	  } else { // Reduce
        string str ;
        bool error = false ;
        if(pre == '=') {
          char ch1 = q . front() ;
          q . pop() ;
          s . push(ch1) ;
          printStkQ(s , s1 , q) ;
          cout << "\t\tShift\n" ;
          //cout << "reducing=\n" ;
          char ch = s1 . top() ;
          s1 . pop() ;
          str = "" ;
          str += "(" ;
          s . pop() ;
          str += ch ;
          str += ")" ;
          s . pop() ;
          string temp = "" ;
          temp += ch ;
          while(find(rhs . begin() , rhs . end() , str) == rhs . end()) { // String not found in R.H.S.
            if(find(rhs . begin() , rhs . end() , temp) == rhs . end()) {
              error = true ;
              break ;
            } else {
              temp = "" ;
              temp += ch ;
              int pos = find(rhs . begin() , rhs . end() , temp) - rhs . begin() ;
              ch = lhs[pos] ;
            }
            str = "" ;
            str += "(" ;
            str += ch ;
            str += ")" ; 
          }
        } else {
          //cout << "reducing>\n" ;
          if(s . top() == 't') {
            //cout << "above\n" ;
            str = "" ;
            str += s . top() ;
            s . pop() ;
            if(find(rhs . begin() , rhs . end() , str) == rhs . end()) {
              error = true ;
            } 
            //cout << "below\n" ;
          } else {
            char ch2 = s1 . top() ; 
            s1 . pop() ;
            char op = s . top() ;
            s . pop() ;
            char ch1 = s1 . top() ;
            s1 . pop() ;
            str = "" ;
            str += ch1 ;
            str += op ;
            str += ch2 ;
            char beg = ch1 ;
            while(find(rhs . begin() , rhs . end() , str) == rhs . end()) { // String not found in R.H.S.
              string temp1 = "" ;
              temp1 += ch1 ;
              if(find(rhs . begin() , rhs . end() , temp1) == rhs . end()) {
                string temp2 = "" ;
                temp2 += ch2 ;
                if(find(rhs . begin() , rhs . end() , temp2) == rhs . end()) {
                  error = true ;
                  break ;
                } else {
                  ch1 = beg ;
                  temp2 = "" ;
                  temp2 += ch2 ;
                  int pos = find(rhs . begin() , rhs . end() , temp2) - rhs . begin() ;
                  ch2 = lhs[pos] ;
                }
              } else {
                temp1 = "" ;
                temp1 += ch1 ;
                int pos = find(rhs . begin() , rhs . end() , temp1) - rhs . begin() ;
                ch1 = lhs[pos] ;
              }
              str = "" ;
              str += ch1 ;
              str += op ;
              str += ch2 ;
            }
          }
  	    }
        if(error) {
          cout << "Error in parsing ...\n" ;
          return ;
        } else {
          //cout << "reduced ..\n" ;
          int pos = find(rhs . begin() , rhs . end() , str) - rhs . begin() ;
          char ch = lhs[pos] ;
          s1 . push(ch) ;
          printStkQ(s , s1 , q) ;
          cout << "\t\tReduce\n" ;
        }   
    }
    if(! s1 . empty() && s1 . top() == 'S' && s1 . size() == 1 && q . front() == '$') {
      cout << "String parsed ...\n" ;
      return ;
    } 
  }
  char ch = s1 . top() ;
  str = "" ;
  str += ch ;
  while(find(rhs . begin() , rhs . end() , str) != rhs . end()) {
    int pos = find(rhs . begin() , rhs . end() , str) - rhs . begin() ;
    ch = lhs[pos] ;
    str = "" ;
    str += ch ;
    s1 . pop() ;
    s1 . push(ch) ;
    printStkQ(s , s1 , q) ;
    cout << "\t\tReduce\n" ;
  }
  if(! s1 . empty() && s1 . top() == 'S' && s1 . size() == 1 && q . front() == '$') {
    cout << "String parsed ...\n" ;
  } else {
    cout << "Error in parsing ...\n" ;
  }
}

int main() {
  buildTable() ;
  cout << "Enter the number of productions : " ;
  int n ;
  cin >> n ;
  cout << "Enter " << n << " productions -\n" ;
  vector<string> prods(n) ;
  for(int i = 0 ; i < n ; i ++) {
    cin >> prods[i] ;
  }
  for(int i = 0 ; i < n ; i ++) {
    vector<string> temp = partProd(prods[i]) ;
    for(int j = 0 ; j < temp . size() ; j ++) {
      rhs . push_back(temp[j]) ;
      lhs . push_back(prods[i][0]) ;
    }
  }
  cout << "Enter string to parse : " ;
  string str ;
  cin >> str ;
  parse(str) ;
  return 0 ;
}
/*
S->S+T|T
T->T*F|F
F->(S)|t
*/