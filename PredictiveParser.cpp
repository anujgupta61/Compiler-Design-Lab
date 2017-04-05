#include <bits/stdc++.h>
using namespace std ;

map<char , vector<string> > partedProds ;
set<char> ans ;
char ans_ch ;
int ans_i ;
map<char , vector<char> > firstOfProds ;
map<char , vector<char> > followOfProds ;
map<char , bool> containsNull ;
vector<char> nts ;
vector<char> ts ;
int p_count = 0 ;
map<char , map<char , int> > fullParseTable ;
map<char , int> parseTable ;
vector<char> nullFirsts ;
map<string , int> prodNos ;

vector<string> partProd(string str) {
  vector<string> parts ;
  string temp = "" ;
  nts . push_back(str[0]) ;
  for(int i = 3 ; i < str . length() ; i ++) {
      if(str[i] == '|') {
          if(temp == "$") {
            string temp_s = "" ;
            temp_s += str[0] ;
            temp_s += "->" ;
            temp_s += temp ;
            if(prodNos . find(temp_s) == prodNos . end())
              prodNos[temp_s] = ++ p_count ;
            containsNull[str[0]] = true ;
          }
          else {
            string temp_s = "" ;
            temp_s += str[0] ;
            temp_s += "->" ;
            temp_s += temp ;
            if(prodNos . find(temp_s) == prodNos . end())
              prodNos[temp_s] = ++ p_count ;
            parts . push_back(temp) ;
          }
          temp = "" ;
      } else {
            int asc = (int)str[i] ;
            if(asc < 65 || asc > 90) {
              if(str[i] != '$')
                ts . push_back(str[i]) ;
            }
            temp = temp + str[i] ;
      }
  }
  if(temp != "") {
    if(temp == "$") {
      string temp_s = "" ;
      temp_s += str[0] ;
      temp_s += "->" ;
      temp_s += temp ;
      if(prodNos . find(temp_s) == prodNos . end())
        prodNos[temp_s] = ++ p_count ;
      containsNull[str[0]] = true ;
    }
    else {
      string temp_s = "" ;
      temp_s += str[0] ;
      temp_s += "->" ;
      temp_s += temp ;
      if(prodNos . find(temp_s) == prodNos . end())
        prodNos[temp_s] = ++ p_count ;
      parts . push_back(temp) ;
    }
  }
  return parts ;
}

void findFirst(char ch , int i , int j) {
  vector<string> vec = partedProds[ch] ;
  if(i == vec . size())
    return ;
  if(ch == vec[i][j]) {
      cout << "\nProductions with left-recursion are not accepted ...\n" ;
      exit(0) ;
  }
	int asc = (int)vec[i][j] ;
  if(asc >= 65 && asc <= 90) { // Non-Terminals
    char c = vec[i][j] ;
    findFirst(c , 0 , 0) ;
    while(containsNull[c]) {
      if(j < vec[i] . length() - 1) {
        c = vec[i][++ j] ;
        int asc = (int)c ;
        if(asc >= 65 && asc <= 90)
          findFirst(c , 0 , 0) ;
        else {
          string temp_s = "" ;
          temp_s += ans_ch ;
          temp_s += "->" ;
          vector<string> vec1 = partedProds[ans_ch] ;
          temp_s += vec1[ans_i] ;
          parseTable[c] = prodNos[temp_s] ;
          ans . insert(c) ;
          break ;
        }
      } else {
        ans . insert('$') ;
        nullFirsts . push_back(ch) ;
        break ;
      }
    }
  } else { // Terminals
    string temp_s = "" ;
    temp_s += ans_ch ;
    temp_s += "->" ;
    vector<string> vec1 = partedProds[ans_ch] ;
    temp_s += vec1[ans_i] ;
    parseTable[vec[i][j]] = prodNos[temp_s] ;
    ans . insert(vec[i][j]) ;
  }
  if(ch == ans_ch)
    ans_i = i + 1 ;
  findFirst(ch , i + 1 , 0) ;
}

void displayFirsts() {
  cout << "\nDisplaying the firsts -\n" ;
  for(map<char , vector<char> > :: iterator it = firstOfProds . begin() ; it != firstOfProds . end() ; it ++) {
  	cout << "First(" << (*it) . first << ") : { " ;
  	vector<char> f = (*it) . second ;
  	for(int j = 0 ; j < f . size() ; j ++) {
      cout << f[j] ;
      if(j != f . size() - 1)
        cout << " , " ;
    }
    cout << " }\n" ;
  }
}

void findFollow(char ch) {
	if(followOfProds . find(ch) != followOfProds . end()) // Follow already calculated
		return ;
	set<char> ans1 ;
	if(ch == 'S')
		ans1 . insert('#') ;
	for(map<char , vector<string> > :: iterator it = partedProds . begin() ; it != partedProds . end() ; it ++) {
		char ch1 = (*it) . first ;
		vector<string> prods = (*it) . second ;
		for(int i = 0 ; i < prods . size() ; i ++) {
			string prod = prods[i] ;
			int pos = prod . find(ch) ;
			if(pos != string::npos) { // ch found in production
				if(pos == prod . length() - 1) {
          if(ch != ch1) {
  					findFollow(ch1) ;
  					vector<char> follow_ch1 = followOfProds[ch1] ;
  					for(int j = 0 ; j < follow_ch1 . size() ; j ++) {
  						ans1 . insert(follow_ch1[j]) ;
  					}
          }
				} else {
			    	label :
			    	int asc1 = (int)prod[pos + 1] ;
					if(asc1 >= 65 && asc1 <= 90) { // Non-terminals
						vector<char> first_temp = firstOfProds[prod[pos + 1]] ;
				    	for(int j = 0 ; j < first_temp . size() ; j ++) {// Adding first to follow
                if(first_temp[j] != '$')
                  ans1 . insert(first_temp[j]) ;
						  }
						if(find(first_temp . begin() , first_temp . end() , '$') != first_temp . end()) {// $ present
							if(pos + 2 < prod . length()) {
 								pos ++ ;
								goto label ;
							} else {
                if(ch != ch1) {
        					findFollow(ch1) ;
        					vector<char> follow_ch1 = followOfProds[ch1] ;
        					for(int j = 0 ; j < follow_ch1 . size() ; j ++) {
        						ans1 . insert(follow_ch1[j]) ;
        					}
                }
              }
						}
					} else {
						ans1 . insert(prod[pos + 1]) ;
					}
				}
			}
		}
	}
  vector<char> ans3 ;
  for(set<char> :: iterator it = ans1 . begin() ; it != ans1 . end() ; it ++)
    ans3 . push_back(*it) ;
	followOfProds[ch] = ans3 ;
}

void displayFollows() {
  cout << "\nDisplaying the follows -\n" ;
  for(map<char , vector<char> > :: iterator it = followOfProds . begin() ; it != followOfProds . end() ; it ++) {
  	cout << "Follow(" << (*it) . first << ") : { " ;
  	vector<char> f = (*it) . second ;
  	for(int j = 0 ; j < f . size() ; j ++) {
      cout << f[j] ;
      if(j != f . size() - 1)
        cout << " , " ;
    }
    cout << " }\n" ;
  }
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
  stack<char> stk ;
  queue<char> q ;
  stk . push('$') ;
  stk . push('S') ;
  cout << "\nStack\tString\tProduction no.\n\n" ;
  for(int i = 0 ; i < str . length() ; i ++)
    q . push(str[i]) ;
  q . push('$') ;
  while(! stk . empty() && ! q . empty()) {
    char ch1 = stk . top() ;
    char ch2 = q . front() ;
    if(ch1 == ch2) {
      printStkQ(stk , q) ;
      stk . pop() ;
      q . pop() ;
      cout << "\t_\n" ;
    } else {
      if(ch1 < 65 || ch1 > 90) {
        cout << "Invalid string ...\n" ;
        exit(0) ;
      } else {
        map<char , int> pr = fullParseTable[ch1] ;
        if(pr . find(ch2) == pr . end()) { // No such production exists
          cout << "Invalid string ...\n" ;
          exit(0) ;
        } else {
          int prod_num = pr[ch2] ;
          string prod_str ;
          for(map<string , int> :: iterator it = prodNos . begin() ; it != prodNos . end() ; it ++) {
            if((*it) . second == prod_num) {
              prod_str = (*it) . first ;
              break ;
            }
          }
          printStkQ(stk , q) ;
          stk . pop() ;
          if(prod_str[3] != '$') {
            for(int z = prod_str . length() - 1 ; z >= 3  ; z --)
              stk . push(prod_str[z]) ;
          }
          cout << "\t" << prod_num << "\n" ;
        }
      }
    }
  }
  cout << "Valid string ...\n" ;
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
    partedProds[prods[i][0]] = temp ;
  }
  ts . push_back('#') ;
  for(int i = 0 ; i < n ; i ++) {
    char temp_ch = prods[i][0] ;
    ans_ch = temp_ch ;
    ans_i = 0 ;
    findFirst(temp_ch , 0 , 0) ;
    fullParseTable[temp_ch] = parseTable ;
    parseTable . clear() ;
    if(containsNull[temp_ch]) {
      nullFirsts . push_back(temp_ch) ;
      ans . insert('$') ;
    }
    vector<char> ans2 ;
    for(set<char> :: iterator it = ans . begin() ; it != ans . end() ; it ++)
      ans2 . push_back(*it) ;
    firstOfProds[temp_ch] = ans2 ;
    ans . clear() ;
  }
  for(int i = 0 ; i < n ; i ++)
    findFollow(prods[i][0]) ;
  for(int i = 0 ; i < nullFirsts . size() ; i ++) {
    char temp_ch = nullFirsts[i] ;
    vector<char> ch_follow = followOfProds[temp_ch] ;
    for(int k = 0 ; k < ch_follow . size() ; k ++) {
      map<char , int> temp_p_table = fullParseTable[temp_ch] ;
      string temp_s = "" ;
      temp_s += temp_ch ;
      temp_s += "->$" ;
      temp_p_table[ch_follow[k]] = prodNos[temp_s] ;
      fullParseTable[temp_ch] = temp_p_table ;
    }
  }
  displayFirsts() ;
  displayFollows() ;
  cout << "\nProduction numbers -\n" ;
  for(map<string , int> :: iterator it = prodNos . begin() ; it != prodNos . end() ; it ++)
    cout << (*it) . second << " : " << (*it) . first << "\n" ;
  cout << "\nParsing table -\n" ;
  cout << "\t" ;
  for(int i = 0 ; i < ts . size() ; i ++) {
    cout << ts[i] << "\t" ;
  }
  cout << "\n" ;
  for(int i = 0 ; i < nts . size() ; i ++) {
    char p_ch = nts[i] ;
    cout << p_ch << "\t" ;
    map<char , int> p_table = fullParseTable[p_ch] ;
    for(int j = 0 ; j < ts . size() ; j ++) {
      char p_ch1 = ts[j] ;
      if(p_table . find(p_ch1) != p_table . end())
        cout << p_table[p_ch1] << "\t" ;
      else
        cout << "_\t" ;
    }
    cout << "\n" ;
  }
  cout << "\nInput string to parse -\n" ;
  string parse_str ;
  cin >> parse_str ;
  parseStr(parse_str) ;
  return 0 ;
}

/*
S->TZ
Z->+TZ|$
T->FY
Y->*FY|$
F->(S)|a
*/

/*
S->ABCD
A->a|$
B->b|$
C->c|$
D->d
*/
