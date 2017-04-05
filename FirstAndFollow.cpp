#include <bits/stdc++.h>
using namespace std ;

map<char , vector<string> > partedProds ;
set<char> ans ;
map<char , vector<char> > firstOfProds ;
map<char , vector<char> > followOfProds ;
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
          ans . insert(c) ;
          break ;
        }
      } else {
        ans . insert('$') ;
        break ;
      }
    }
  } else { // Terminals
    ans . insert(vec[i][j]) ;
  }
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
  for(int i = 0 ; i < n ; i ++) {
    char temp_ch = prods[i][0] ;
    findFirst(temp_ch , 0 , 0) ;
    if(containsNull[temp_ch])
      ans . insert('$') ;
    vector<char> ans2 ;
    for(set<char> :: iterator it = ans . begin() ; it != ans . end() ; it ++)
      ans2 . push_back(*it) ;
    firstOfProds[temp_ch] = ans2 ;
    ans . clear() ;
  }
  for(int i = 0 ; i < n ; i ++)
    findFollow(prods[i][0]) ;
  displayFirsts() ;
  displayFollows() ;
  return 0 ;
}
