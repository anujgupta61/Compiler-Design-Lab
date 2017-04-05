keyword alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char16_t|char32_t|class|compl|concept|const|constexpr|const_cast|continue|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|import|inline|int|long|module|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq
operator (\:\:)|(\+\+)|(\-\-)|(\.)|(\-\>)|(\~)|(\!)|(\*)|(\.\*)|(\-\>\*)|(\*)|(\/)|(\%)|(\+)|(\-)|(\<\<)|(\>\>)|(\<)|(\>)|(\<\=)|(\>\=)|(\=\=)|(\!\=)|(\&)|(\^\=)|(\|\=)|(\|)|(\&\&)|(\|\|)|(\=)|(\*\=)|(\/\=)|(\%\=)|(\+\=)|(\-\=)|(\>\>\=)|(\<\<\=)|(\&\=)|(\^\=)|(\|\=)
reserve std|main|cin|cout
delimiter [,;]
bracket [(){}]
%{
  #include <iostream>
  using namespace std ;
  int line_no = 1 ;
%}

%%
\n {
        line_no ++ ;
        cout << "\n" ;
   }

\"[^\"]*\" {
            cout << yytext << "\tLiteral at Line:" << line_no << "\n" ;
           }

#.* {
        cout << yytext << " : Macro at Line:" << line_no << "\n" ;
    }

{keyword} {
            cout << yytext << " : Keyword at Line:" << line_no << "\n" ;
          }

{reserve} {
          cout << yytext << " : Reserved word at Line:" << line_no << "\n" ;
        }

{operator} {
            cout << yytext << " : Operator at Line:" << line_no << "\n" ;
           }

{delimiter} {
           cout << yytext << " : Delimiter at Line:" << line_no << "\n" ;
          }

{bracket} {
         cout << yytext << " : Bracket at Line:" << line_no << "\n" ;
        }

[a-zA-Z_][a-zA-Z0-9_]* {
                            cout << yytext << " : Valid identifier at Line:" << line_no << "\n" ;
                       }

[ \t]* ;

[0-9]*[a-zA-Z_][a-zA-Z0-9_]* {
            cout << yytext << " : Invalid identifier at Line:" << line_no << "\n" ;
       }

[0-9]* {
            cout << yytext << " : Constant at Line:" << line_no << "\n" ;
       }

. {
    cout << yytext << " : Invalid identifier at Line:" << line_no << "\n" ;
  }
%%

int yywrap() {
  return 1 ;
}

int main() {
  yyin = fopen("test4.cpp" , "r") ;
  yylex() ;
  fclose(yyin) ;
  return 0 ;
}
