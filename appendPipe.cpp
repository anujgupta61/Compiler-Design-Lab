#include <bits/stdc++.h>
using namespace std ;

int main() {
    ifstream din("operators.txt") ;
    ofstream dout("operatorsPipe.txt") ;
    string op ;
    while(getline(din , op)) {
        dout << "(" ;
        for(int i = 0 ; i < op . length() ; i ++)
            dout << "\\" << op[i] ;
        dout << ")|" ;
    }
    din . close() ;
    dout . close() ;
}
