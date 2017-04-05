#include <bits/stdc++.h>

using namespace std ;

string removeSpaces(string input) {
  input.erase(remove(input.begin() , input.end() , ' ') , input.end());
  input.erase(remove(input.begin() , input.end() , '\t') , input.end());
  return input;
}

int main() {
  ifstream file1("test.cpp") ;
  ofstream file2("test1.cpp") ;

  bool remove = false , do_replace ;

  if(file1 . is_open()) {
    int i = 1 ;
    string str ;

    while(getline(file1 , str)) {
      do_replace = true ;

      if(str . find("//") != string::npos) {
        size_t pos1 = 0 , pos2 = 0 ;
        size_t pos = str . find("//" , pos1) ;
        size_t posf = str . find("\"" , pos2) ;
        size_t posl = str . find("\"" , posf + 1) ;
        while(pos != string::npos) {
          if(! (pos > posf && pos < posl)) {
            size_t temp1 = str . find("\"" , posl + 1) ;
            size_t temp2 = str . find("\"" , temp1 + 1) ;
            if((pos < temp1 && pos < temp2) || temp1 == string::npos || temp2 == string::npos) {
              str . replace(str . begin() + pos , str . end() , "") ;
              break ;
            } else {
              pos1 = posl + 1 ;
              pos2 = posl + 1 ;
            }
          } else {
            pos1 = posl + 1 ;
            pos2 = posl + 1 ;
          }
          pos = str . find("//" , pos1) ;
          posf = str . find("\"" , pos2) ;
          posl = str . find("\"" , posf + 1) ;
        }
      }

      size_t npos1 = str . find("/*" , 0) ;
      size_t npos2 = str . find("*/" , npos1 + 2) ;
      if(npos1 != string::npos && npos2 != string::npos) {
        do_replace = false ;
        size_t pos1 = 0 , pos2 = 0 ;
        size_t posf = str . find("\"" , pos2) ;
        size_t posl = str . find("\"" , posf + 1) ;
        while(npos1 != string::npos && npos2 != string::npos) {
          if(! (npos1 > posf && npos1 < posl && npos2 > posf && npos2 < posl)) {
            str . replace(str . begin() + npos1 , str . begin() + npos2 + 2 , "") ;
          } else {
            pos1 = posl + 1 ;
            pos2 = posl + 1 ;
          }
          npos1 = str . find("/*" , pos1) ;
          npos2 = str . find("*/" , npos1 + 2) ;
          posf = str . find("\"" , pos2) ;
          posl = str . find("\"" , posf + 1) ;
        }
      }

      if(npos1 != string::npos && npos2 == string::npos && do_replace) {
        remove = true ;
        str . replace(str . begin() + npos1 , str . end() , "") ;
        do_replace = false ;
      }

      if(npos1 == string::npos && npos2 != string::npos && do_replace) {
        size_t pos = str . find("*/") ;
        str . replace(str . begin() , str . begin() + npos2 + 2 , "") ;
        remove = false ;
      }

      if(remove && do_replace) {
        str . replace(str . begin() , str . end() , "") ;
      }
      string temp = removeSpaces(str) ;
      if(temp != "")
        file2 << i ++ << " : " << str << "\n";
    }
    file1 . close() ;
  } else {
    cout << "Unable to open file ..\n" ;
  }
  return 0 ;
}
