#include <bits/stdc++.h>
using namespace std ;

map<char , int> sIndex ;
vector<vector<string> > lrTable ;
vector<string> prods ; 

void initialize() {
	sIndex['('] = 0 ;
	sIndex[')'] = 1 ;
	sIndex['x'] = 2 ;
	sIndex[','] = 3 ;
	sIndex['$'] = 4 ;
	sIndex['S'] = 5 ;
	sIndex['L'] = 6 ;

	string lrTable1[9][7] = {
		{"s2" , "_" , "s1" , "_" , "_" , "3" , "_"} ,
		{"r2" , "r2" , "r2" , "r2" , "r2" , "_" , "_"} ,
		{"s2" , "_" , "s1" , "_" , "_" , "6" , "4"} ,
		{"_" , "_" , "_" , "_" , "a" , "_" , "_"} ,
		{"_" , "s5" , "_" , "s7" , "_" , "_" , "_"} ,
		{"r1" , "r1" , "r1" , "r1" , "r1" , "_" , "_"} ,
		{"r3" , "r3" , "r3" , "r3" , "r3" , "_" , "_"} ,
		{"s2" , "_" , "s1" , "_" , "_" , "8" , "_"} ,
		{"r4" , "r4" , "r4" , "r4" , "r4" , "_" , "_"}
	} ;

	for(int i = 0 ; i < 9 ; i ++) {
		vector<string> temp ;
		for(int j = 0 ; j < 7 ; j ++)
			temp . push_back(lrTable1[i][j]) ;
		lrTable . push_back(temp) ;
	}

	prods . push_back("Z->S$") ;
	prods . push_back("S->(L)") ;
	prods . push_back("S->x") ;
	prods . push_back("L->S") ;
	prods . push_back("L->L,S") ;
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

void parse(string str) {
	stack<char> s ;
	queue<char> q ;
	s . push('0') ;
	for(int i = 0 ; i < str . length() ; i ++)
	  q . push(str[i]) ;
	q . push('$') ;
	cout << "Stack\t\t" << "String\t\t" << "Operation\n\n" ;
	while(true) {
		printStkQ(s , q) ;
		char ch1 = s . top() ;
		char ch2 = q . front() ;
		int i1 = (int)ch1 - 48 ;
		int i2 = sIndex[ch2] ;
		string op = lrTable[i1][i2] ;
		cout << "\t\t" << op << "\n" ;
		if(op[0] == 's') { // Shift
			s . push(ch2) ;
			s . push(op[1]) ;
			q . pop() ;
		}
		if(op[0] == 'r') { // Reduce
			int i = (int)op[1] - 48 ;
			string pstr = prods[i] ;
			int j = 0 ;
			int plen = 2 * (pstr . length() - 3) ;
			while(j < plen) {
				s . pop() ;
				j ++ ;
			}
			char st = s . top() ;
			s . push(pstr[0]) ;
			int i1 = (int)st - 48 ;
			int i2 = sIndex[pstr[0]] ;
			string ns = lrTable[i1][i2] ;
			s . push(ns[0]) ; 
		}
		if(op[0] == 'a') { // Accept
			cout << "String accepted ...\n" ;
			return ;
		}
		if(op[0] == '_') { // Error
			cout << "String not accepted ...\n" ;
			return ;	
		}
 	}
}

int main() {
	initialize() ;
	cout << "Enter string to parse : " ;
  	string str ;
  	cin >> str ;
  	parse(str) ;
	return 0 ;
}