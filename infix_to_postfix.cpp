#include <bits/stdc++.h>
using namespace std ;

int getPrecedence(char ch) {
	if(ch == '|')
		return 1 ;
	if(ch == '.')
		return 2 ;
	if(ch == '*')
		return 3 ;
}

string convertToPostfix(string str) {
	vector<char> pre_op ;
	pre_op . push_back('|') ;
	pre_op . push_back('.') ;
	pre_op . push_back('*') ; 
	string postStr = "" ;
	vector<char> ops ;
	for(int i = 0 ; i < str . length() ; i ++) {
		if(str[i] == 'a' || str[i] == 'b')
			postStr = postStr + string(1 , str[i]) ;
		if(str[i] == '|' || str[i] == '*' || str[i] == '.') {
			if(ops . empty()) {
				ops . push_back(str[i]) ;
			} else { 
				if(getPrecedence(str[i]) > getPrecedence(ops[ops . size() - 1])) {
					ops . push_back(str[i]) ;
				} else {
					while(getPrecedence(str[i]) <= getPrecedence(ops[ops . size() - 1])) {
						char op = ops[ops . size() - 1] ;
						ops . pop_back() ;
						postStr = postStr + string(1 , op) ;
					}
					ops . push_back(str[i]) ;
				}
			}
		}
	}
	while(! ops . empty()) {
		char op = ops[ops . size() - 1] ;
		ops . pop_back() ;
		postStr = postStr + string(1 , op) ;
	}
	return postStr ;
}

int main() {
	string exp ;
	cin >> exp ;
	cout << convertToPostfix(exp) << "\n" ;
}
