#include <bits/stdc++.h>
using namespace std ;

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

string findMatch(string str1 , string str2) {
  string matched = "" ;
  for(int i = 0 ; str1[i] != '\0' && str2[i] != '\0' ; i ++) {
    if(str1[i] == str2[i]) {
      matched = matched + str1[i] ;
    } else {
        break ;
    }
  }
  return matched ;
}

void removeLeftFact(char start , int &count , vector<string> parted) {
  string common = "" ;
  vector<int> matched , unmatched ;
  int i , j ;
  for(i = 0 ; i < parted . size() - 1 ; i ++) {
    for(j = i + 1 ; j < parted . size() ; j ++) {
      if(findMatch(parted[i] , parted[j]) != "") {
        common = findMatch(parted[i] , parted[j]) ;
        matched . push_back(i) ;
        matched . push_back(j) ;
        goto out ;
      }
    }
  }
    out :
    if(common != "") {
      for(int k = 0 ; k <= j ; k ++) {
        if(k != i && k != j)
          unmatched . push_back(k) ;
      }
      for(int k = j + 1 ; k < parted . size() ; k ++) {
        if(findMatch(common , parted[k]) != "") {
          common = findMatch(common , parted[k]) ;
          matched . push_back(k) ;
        } else {
          unmatched . push_back(k) ;
        }
      }
      char start1 = (char)(90 - count) ;
      vector<string> next_parted ;
      next_parted . push_back(common + (char)(90 - count)) ;
      for(int k = 0 ; k < unmatched . size() ; k ++) {
        next_parted . push_back(parted[unmatched[k]]) ;
      }
      count ++ ;
      removeLeftFact(start , count , next_parted) ;
      next_parted . clear() ;
      int len = common . length() ;
      for(int k = 0 ; k < matched . size() ; k ++) {
        next_parted . push_back(parted[matched[k]] . substr(len , parted[matched[k]] . length() - 1)) ;
      }
      count ++ ;
      removeLeftFact(start1 , count , next_parted) ;
    } else {
      cout << start << "->" ;
      for(int k = 0 ; k < parted . size() ; k ++) {
        if(k != 0)
          cout << "|" ;
        cout << parted[k]  ;
      }
      cout << "\n" ;
      return ;
    }
}

vector<string> removeLeftRec(int &count , string str) {
  vector<string> afterLeftRecProds ;
  string a = "" , b = "" ;
  vector<string> leftRecStr , betaStr ;
  string temp = "" ;
  bool isLeftRec = false ;
  vector<string> parted = partProd(str) ;
  for(int i = 0 ; i < parted . size() ; i ++) {
    if(parted[i][0] == str[0]) {
      leftRecStr . push_back(parted[i]) ;
      isLeftRec = true ;
    } else {
      betaStr . push_back(parted[i]) ;
    }
  }
  if(isLeftRec && ! betaStr . empty()) {
      string temp_str = "" ;
      temp_str += str[0] ;
      temp_str += "->" ;
      for(int j = 0 ; j < betaStr . size() ; j ++) {
        temp_str += betaStr[j] + (char)(90 - count) ;
        if(j == betaStr . size() - 1) {
          afterLeftRecProds . push_back(temp_str) ;
          cout << temp_str << "\n" ;
        } else {
          temp_str += "|" ;
        }
      }
      temp_str = (char)(90 - count) ;
      temp_str += "->" ;
      for(int i = 0 ; i < leftRecStr . size() ; i ++) {
        temp_str += leftRecStr[i]  . substr(1 , leftRecStr[i] . length() - 1) + (char)(90 - count) ;
        if(i == leftRecStr . size() - 1) {
          temp_str += "|$" ;
          afterLeftRecProds . push_back(temp_str) ;
          cout << temp_str << "\n" ;
        } else {
          temp_str += "|" ;
        }
      }
      count ++ ;
  } else {
    cout << str << "\n" ;
    afterLeftRecProds . push_back(str) ;
    if(betaStr . empty())
      cout << "Left Recursion can not be removed ...\n" ;
    else
      cout << "Left Recursion does not exist ...\n" ;
  }
return afterLeftRecProds ;
}

int main() {
  cout << "Input single line Production rule in form (A->aB|c) -\n" ;
  string input ;
  cin >> input ;
  cout << "\n" ;
  cout << "Production rules after removing Left Recursion are -\n" ;
  int count = 0 ;
  vector<string> strs = removeLeftRec(count , input) ;
  int pre_count = count ;
  cout << "\nProduction rules after removing Left Factoring are -\n" ;
  bool isLeftFact = false ;
  for(int i = 0 ; i < strs . size() ; i ++) {
    removeLeftFact(strs[i][0] , count , partProd(strs[i])) ;
    if(count != pre_count)
      isLeftFact = true ;
  }
  if(! isLeftFact)
    cout << "Left factoring does not exist ...\n" ;
  strs . clear() ;
  cout << "\nStart symbol : " << input[0] << "\n$ : Null symbol\n" ;
  return 0 ;
}
