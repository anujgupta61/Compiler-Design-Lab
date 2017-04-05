whitespace [ \t]
newline \n

%{
  #include <bits/stdc++.h>
  using namespace std ;
  int line_no = 1 ;
  bool do_remove = false ;
%}

%%
\"[^\"]*\" {
            cout << yytext ;
           }

\/\/.* ;

\/\* {
        do_remove = true ;
     }

\*\/ {
        do_remove = false ;
     }

{whitespace}{whitespace}+ ;

{newline}+ {
            if(! do_remove)
                cout << "\n\t" << ++line_no << "\t" ;
           }

. {
     if(! do_remove)
        cout << yytext ;
  }
%%

int yywrap() {
  return 1 ;
}

int main() {
  yyin = fopen("test.cpp" , "r") ;
  //yyout = fopen("test_out.cpp" , "w") ;
  cout << "\t" << line_no << "\t" ;
  yylex() ;
  cout << "\n" ;
  fclose(yyin) ;
  return 0 ;
}
