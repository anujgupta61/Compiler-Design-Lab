#include <bits/stdc++.h>
using namespace std ;

vector<string> rhs ;
vector<char> lhs ;
map<char , vector<string> > partedProds ;
map<char , vector<char> > firstOfProds ;
map<char , vector<char> > lastOfProds ;
map<char , int> opIndex ;
int oi = 0 ;
vector<vector<char> > operatorTable ;

vector<string> partProd(string str) {
  vector<string> parts ;
  string temp = "" ;
  for(int i = 3 ; i < str . length() ; i ++) {
      int asc = (int)str[i] ;
      if((asc < 65 || asc > 90) && str[i] != '|') { // Terminal
        if(opIndex . find(str[i]) == opIndex . end()) // Not present
          opIndex[str[i]] = oi ++ ;  
      }
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
    //cout << "Finding first of " << ch << "\n" ;
  vector<string> prod = partedProds[ch] ;
  set<char> ans ;
  for(int i = 0 ; i < prod . size() ; i ++) {
    int j = 0 ;
    string p_str = prod[i] ; 
    while(j < p_str . length()) {
      int asc = (int)p_str[j] ;
      if(asc < 65 || asc > 90) { // Terminal
        ans . insert(p_str[j]) ;
        break ;
      } else { // Non-Terminal
        if(p_str[j] != ch) {
          findFirst(p_str[j]) ;
          vector<char> temp = firstOfProds[p_str[j]] ;
          for(int k = 0 ; k < temp . size() ; k ++) 
            ans . insert(temp[k]) ;
        } 
      }
      j ++ ;
    }
  }
  vector<char> temp ;
  for(set<char> :: iterator it = ans . begin() ; it != ans . end() ; it ++)
    temp . push_back(*it) ;
  firstOfProds[ch] = temp ;
}

void findLast(char ch) {
  vector<string> prod = partedProds[ch] ;
  set<char> ans ;
  for(int i = 0 ; i < prod . size() ; i ++) {
    string p_str = prod[i] ;
    int j = p_str . length() - 1 ; 
    while(j >= 0) {
      int asc = (int)p_str[j] ;
      if(asc < 65 || asc > 90) { // Terminal
        ans . insert(p_str[j]) ;
        break ;
      } else { // Non-Terminal
        if(p_str[j] != ch) {
          findLast(p_str[j]) ;
          vector<char> temp = lastOfProds[p_str[j]] ;
          for(int k = 0 ; k < temp . size() ; k ++) 
            ans . insert(temp[k]) ;
        } 
      }
      j -- ;
    }
  }
  vector<char> temp ;
  for(set<char> :: iterator it = ans . begin() ; it != ans . end() ; it ++)
    temp . push_back(*it) ;
  lastOfProds[ch] = temp ;
}

void buildTable() {
  opIndex['$'] = oi ++ ;
  for(int i = 0 ; i < oi ; i ++) { // Initializing operator table
    vector<char> temp ;
    for(int j = 0 ; j < oi ; j ++)
      temp . push_back('_') ;
    operatorTable . push_back(temp) ;
  }
  for(int i = 0 ; i < lhs . size() ; i ++) {
    char ch = lhs[i] ;
    string prod = rhs[i] ;
    int len = prod . length() ;
    for(int i = 0 ; i < len - 1 ; i ++) {
      int asc1 = (int)prod[i] ;
      int asc2 = (int)prod[i + 1] ;
      int asc3 = (int)prod[i + 2] ;
      if((asc1 < 65 || asc1 > 90) && (asc2 < 65 || asc2 > 90)) { // Both xi and xi+1 are terminals
        int i1 = opIndex[prod[i]] ;
        int i2 = opIndex[prod[i + 1]] ;
        operatorTable[i1][i2] = '=' ;
      }
      if((i < len - 2) && (asc1 < 65 || asc1 > 90) && (asc2 >= 65 && asc2 <= 90) && (asc3 < 65 || asc3 > 90)) { // i < n - 2 , xi and xi+2 terminals , xi+1 non-terminal 
        int i1 = opIndex[prod[i]] ;
        int i2 = opIndex[prod[i + 2]] ; 
        operatorTable[i1][i2] = '=' ;  
      }
      if((asc1 < 65 || asc1 > 90) && (asc2 >= 65 && asc2 <= 90)) { // xi - terminal , xi+1 - non-terminal
        vector<char> firsts = firstOfProds[prod[i + 1]] ;
        for(int j = 0 ; j < firsts . size() ; j ++) {
          int i1 = opIndex[prod[i]] ;
          int i2 = opIndex[firsts[j]] ;
          operatorTable[i1][i2] = '<' ;
        }
      }
      if((asc1 >= 65 && asc1 <= 90) && (asc2 < 65 || asc2 > 90)) { // xi - non-terminal , xi+1 - terminal
        vector<char> lasts = lastOfProds[prod[i]] ;
        for(int j = 0 ; j < lasts . size() ; j ++) {
          int i1 = opIndex[lasts[j]] ;
          int i2 = opIndex[prod[i + 1]] ;
          operatorTable[i1][i2] = '>' ;
        }
      } 
    }
  }
  vector<char> firsts = firstOfProds['S'] ;
  for(int j = 0 ; j < firsts . size() ; j ++) {
    int i1 = opIndex['$'] ;
    int i2 = opIndex[firsts[j]] ;
    operatorTable[i1][i2] = '<' ;
  }
  vector<char> lasts = lastOfProds['S'] ;
  for(int j = 0 ; j < lasts . size() ; j ++) {
    int i1 = opIndex[lasts[j]] ;
    int i2 = opIndex['$'] ;
    operatorTable[i1][i2] = '>' ;
  }
}

void printOperatorTable() {
  cout << "\nOperator precendence table -\n" ;
  vector<char> ti(oi) ;
  for(map<char , int> :: iterator it = opIndex . begin() ; it != opIndex . end() ; it ++)
    ti[it -> second] = it -> first ;
  cout << "\t" ;
  for(int i = 0 ; i < oi ; i ++)
    cout << ti[i] << "\t" ;
  cout << "\n" ;
  for(int i = 0 ; i < operatorTable . size() ; i ++) {
    cout << ti[i] << "\t" ;
    vector<char> prec = operatorTable[i] ;
    for(int j = 0 ; j < prec . size() ; j ++)
      cout << prec[j] << "\t" ;
    cout << "\n" ;
  }
  cout << "\n" ;
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
  cout << "\t" ;
  if(stk1 . empty()) {
    cout << "_\t" ;
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
}

void parse(string str) {
  stack<char> s , s1 ;
  queue<char> q ;
  s . push('$') ;
  cout << "\nStack\tNTs\tString\tOperation\n\n" ;
  for(int i = 0 ; i < str . length() ; i ++)
    q . push(str[i]) ;
  q . push('$') ;
  printStkQ(s , s1 , q) ;
  cout << "_\t_\n" ;
  s . push(q . front()) ;
  q . pop() ;
  printStkQ(s , s1 , q) ;
  cout << "_\tShift\n" ;
  while(q . front() != '$' || s . top() != '$') {
    //cout << "top\n" ;
    int i1 = opIndex[s . top()] ;
    int i2 = opIndex[q . front()] ;
    char pre = operatorTable[i1][i2] ;
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
      cout << "\tShift\n" ;
    } else { // Reduce
        string str ;
        if(pre == '=') {
          char ch1 = q . front() ;
          q . pop() ;
          s . push(ch1) ;
          printStkQ(s , s1 , q) ;
          cout << "\tShift\n" ;
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
              cout << "Error in parsing ...\n" ;
              return ;
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
              cout << "Error in parsing ...\n" ;
              return ;
            } 
            //cout << "below\n" ;
          } else {
            if(s1 . empty()) {
              cout << "Error in parsing ...\n" ;
              return ;
            }
            char ch2 = s1 . top() ; 
            s1 . pop() ;
            if(s . empty()) {
              cout << "Error in parsing ...\n" ;
              return ;
            }
            char op = s . top() ;
            s . pop() ;
            if(s1 . empty()) {
              cout << "Error in parsing ...\n" ;
              return ;
            }
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
                  cout << "Error in parsing ...\n" ;
                  return ;
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
        //cout << "reduced ..\n" ;
        int pos = find(rhs . begin() , rhs . end() , str) - rhs . begin() ;
        char ch = lhs[pos] ;
        s1 . push(ch) ;
        printStkQ(s , s1 , q) ;
        cout << "\tReduce\n" ;
    }
    if(! s1 . empty() && s1 . top() == 'S' && s1 . size() == 1 && q . front() == '$' && s . top() == '$') {
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
    cout << "\tReduce\n" ;
  }
  if(! s1 . empty() && s1 . top() == 'S' && s1 . size() == 1 && q . front() == '$' && s . top() == '$') {
    cout << "String parsed ...\n" ;
  } else {
    cout << "Error in parsing ...\n" ;
  }
}

int main() {
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
    partedProds[prods[i][0]] = temp ;
  }
  for(int i = n - 1 ; i >= 0 ; i --) {
    if(firstOfProds . find(prods[i][0]) == firstOfProds . end()) // First not calculated yet
      findFirst(prods[i][0]) ;
  }
  cout << "\nCalculated Firsts -\n" ;
  for(map<char , vector<char> > :: iterator it = firstOfProds . begin() ; it != firstOfProds . end() ; it ++) {
    vector<char> temp = firstOfProds[it -> first] ;
    cout << "first(" << it -> first << ") : {" ;
    for(int i = 0 ; i < temp . size() ; i ++) {
      cout << temp[i] ;
      if(i != temp . size() - 1)
        cout << " , " ;
    }
    cout << "}\n" ;  
  }
  for(int i = n - 1 ; i >= 0 ; i --) {
    if(lastOfProds . find(prods[i][0]) == lastOfProds . end()) // First not calculated yet
      findLast(prods[i][0]) ;
  }
  cout << "\nCalculated Lasts -\n" ;
  for(map<char , vector<char> > :: iterator it = lastOfProds . begin() ; it != lastOfProds . end() ; it ++) {
    vector<char> temp = lastOfProds[it -> first] ;
    cout << "last(" << it -> first << ") : {" ;
    for(int i = 0 ; i < temp . size() ; i ++) {
      cout << temp[i] ;
      if(i != temp . size() - 1)
        cout << " , " ;
    }
    cout << "}\n" ;  
  }
  buildTable() ;
  printOperatorTable() ;
  cout << "Enter string to parse : " ;
  string str ;
  cin >> str ;
  parse(str) ;
  cout << "\n" ;
  return 0 ;
}
/*
S->S+T|T
T->T*F|F
F->(S)|t
*/
/*
S->A
A->Bc
B->D
D->t
*/
