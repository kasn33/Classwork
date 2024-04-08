/* Kyle Seifert 18215069 */
		               /* ---- PROLOGUE ---- */
%{
#include <iostream>
#include <iomanip>
using namespace std;

int no_lines = 0, no_lexemes = 0;
%}
		              /* ---- DEFINITIONS ---- */
%option noyywrap
DIGIT		[0-9]
HEXDIGIT    [0-9A-F]
KEYWORD     ["FUNCTION"|"IF"|"THEN"|"ELSE"|"WHILE"|"END"|"WRITE"]
OPERATOR    [-+*/<>=&#]

%%  		              /* ---- REGULAR EXPRESSIONS ---- */

[ \t]                                               ;
\n                                                  { no_lines++; }
[+-]?{DIGIT}+                                       { cout << no_lexemes++ << ": TOKEN: INTCONST   " << "LEXEME: " << yytext << endl; }
[+-]?{DIGIT}+[\.]{DIGIT}+                           { cout << no_lexemes++ << ": TOKEN: DECCONST   " << "LEXEME: " << yytext << endl; }
[+-]?{DIGIT}+[\.]{DIGIT}+[E][+-]?[1-9]{DIGIT}*      { cout << no_lexemes++ << ": TOKEN: SCICONST   " << "LEXEME: " << yytext << endl; }
{HEXDIGIT}+[H]                                      { cout << no_lexemes++ << ": TOKEN: HEXCONST   " << "LEXEME: " << yytext << endl; }
[01]+[B]                                            { cout << no_lexemes++ << ": TOKEN: BINCONST   " << "LEXEME: " << yytext << endl; }
"FUNCTION"|"IF"|"THEN"|"ELSE"|"WHILE"|"END"|"WRITE" { cout << no_lexemes++ << ": TOKEN: KEYWORD    " << "LEXEME: " << yytext << endl; }
[\"][^ \"\n\t]+[\"]                                 { cout << no_lexemes++ << ": TOKEN: STRCONST   " << "LEXEME: " << yytext << endl; }
{HEXDIGIT}{2}"X"                                    { cout << no_lexemes++ << ": TOKEN: CHCONST    " << "LEXEME: " << yytext << endl; }
[A-Za-z][A-Za-z0-9_]*                               { cout << no_lexemes++ << ": TOKEN: IDENT      " << "LEXEME: " << yytext << endl; }
{OPERATOR}                                          { cout << no_lexemes++ << ": TOKEN: OPERATOR   " << "LEXEME: " << yytext << endl; }
[%][^\n]*                                           ;
.                                                   { cout << no_lexemes++ << ": TOKEN: ?          " << "LEXEME: " << yytext << endl; }



%%  		              /* ---- EPILOGUE ---- */

int main()
{
    yylex();
    cout << no_lines << " lines processed." << endl;
    
    return 0;
}
