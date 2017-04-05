#include <bits/stdc++.h>
using namespace std ;

string intTostring(int num) {
	stringstream ss ;
	ss << num ;
	return ss.str() ;
}

vector<vector<string> > v ;

int main() {
  string str ;
  cin >> str ;
  vector<int> pos ;
  vector< vector<string> > transv ;
  queue<int> stateq ;
  stateq . push(0) ;
  for(int i = 0 ; i < str . length() ; i ++) {
    if(str[i] == '(')
      pos . push_back(i) ;
    if(str[i] == ')') {
      int pos1 = pos[pos . size() - 1] ;
      pos . pop_back() ;
      string temp = "" ;
      for(int j = pos1 + 1 ; j <= i - 1 ; j ++) {
        temp += str[j] ;
				if(str[j] == '.' || str[j] == '|' || str[j] == '*') {

	        switch(str[j]) {
	          case '|' : {
							vector<string> v(4) ;
							int ai = 1 , af = 2 , bi = 3 , bf = 4 ;
			        int state = stateq . front() ;
			        v[0] = intTostring(state) ;
			        stateq . pop() ;
							v[1] = "_" ;
	            v[2] = "_" ;
	            v[3] = intTostring(ai) + " , " + intTostring(bi) ;
	            stateq . push(ai) ;
							stateq . push(bi) ;
							transv . push_back(v) ;

							state = stateq . front() ;
							v[0] = intTostring(state) ;
			        stateq . pop() ;
	            v[1] = intTostring(state + 1) ;
	            v[2] = "_" ;
	            v[3] = "_" ;
	            stateq . push(state + 1) ;
							transv . push_back(v) ;

							state = stateq . front() ;
							v[0] = intTostring(state) ;
			        stateq . pop() ;
	            v[1] = "_" ;
	            v[2] = "_" ;
	            v[3] = intTostring(bf + 1) ;
	            stateq . push(bf + 1) ;
							transv . push_back(v) ;

	            break ;
	          }
	          case '.' : {
							vector<string> v(4) ;
			        int state = stateq . front() ;
			        v[0] = intTostring(state) ;
			        stateq . pop() ;
							v[1] = intTostring(state + 1) ;
	            v[2] = "_" ;
	            v[3] = "_" ;
	            stateq . push(state + 1) ;
							transv . push_back(v) ;

							state = stateq . front() ;
							v[0] = intTostring(state) ;
			        stateq . pop() ;
	            v[1] = "_" ;
	            v[2] = "_" ;
	            v[3] = intTostring(state + 1) ;
	            stateq . push(state + 1) ;
							transv . push_back(v) ;

							state = stateq . front() ;
							v[0] = intTostring(state) ;
			        stateq . pop() ;
							v[1] = "_" ;
							v[2] = intTostring(state + 1) ;
							v[3] = "_" ;
	            stateq . push(state + 1) ;
							transv . push_back(v) ;
	            break ;
	          }
	          case '*' : {
							vector<string> v(4) ;
							int ai , af ;
			        int state = stateq . front() ;
			        v[0] = intTostring(state) ;
			        stateq . pop() ;
							v[1] = "_" ;
	            v[2] = "_" ;
	            v[3] = intTostring(state + 1) ;
	            stateq . push(state + 1) ;
							transv . push_back(v) ;

							state = stateq . front() ;
							ai = state ;
							af = state + 1 ;
							v[0] = intTostring(state) ;
			        stateq . pop() ;
							v[1] = intTostring(state + 1) ;
	            v[2] = "_" ;
							v[3] = "_" ;
	            stateq . push(state + 1) ;
							transv . push_back(v) ;

							state = stateq . front() ;
							v[0] = intTostring(state) ;
			        stateq . pop() ;
							v[1] = "_" ;
	            v[2] = "_" ;
							v[3] = intTostring(ai) + " , " + intTostring(state + 1) ;
	            stateq . push(state + 1) ;
							transv . push_back(v) ;
	            break ;
	          }
	        }

	      }
			}
      cout << temp << "\n" ;
    }
  }
  cout << "State\t" << "a\t" << "b\t" << "E\n" ;
  for(int i = 0 ; i < transv . size() ; i ++) {
    cout << transv[i][0] << "\t" << transv[i][1] << "\t" << transv[i][2] << "\t" << transv[i][3] << "\n" ;
  }
  return 0 ;
}
