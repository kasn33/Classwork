#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

string token;
string endMessage = "CORRECT";

void getToken() {
  if(!(cin>>token))
    token = "E O F";
}

void error(string err){
    endMessage = "INVALID!\nError: " + err + ", got \"" + token + "\"";
}

bool is_digit(char c){
    return c>='0' && c<='9';
}

bool is_Integer( string& s ){
  int i = 0;
  int state = 0;
  
  while ( i < s.length() ){
    switch(state){
      case 0 : if ( s[i] == '+' || s[i] == '-' ) state = 0;
               else if ( is_digit(s[i]) ) state = 1;
               else return false;
      case 1 : if ( is_digit(s[i]) ) state = 1;
               else return false;
	}
	i++;
  }
  if ( state != 1 ) return false;
  return true;
}

bool is_Decimal( string& s ){
  int i = 0;
  int state = 0;
  
  while ( i < s.length() ){
    switch(state){
      case 0 : if ( s[i] == '+' || s[i] == '-' ) state = 0;
               else if ( is_digit(s[i]) ) state = 1;
               else return false;
      case 1 : if ( is_digit(s[i]) ) state = 1;
               else if (s[i] == '.') state = 2;
               else return false;
      case 2 : if ( is_digit(s[i]) ) state = 3;
               else return false;
      case 3 : if ( is_digit(s[i]) ) state = 3;
               else return false;
	}
	i++;
  }
  if ( state != 3 ) return false;
  return true;
}

bool is_String( string& s ){
  return (s[0] == '\"' && s[s.size()-1] == '\"' && count(s.begin(), s.end(), '\"') == 2);
}

bool is_letter( char c ){
  return ((c >= 65 && c <= 90) || (c >= 97 && c<= 122));
}

bool is_Identifier( string& s ){
  if(s == "WRITE")
    return false;
  if(!is_letter(s[0]))
    return false;
  for(int i=1; i<s.size(); i++){
    if(!is_letter(s[i]) && !is_digit(s[i]))
      return false;
  }
  return true;
}

void parse_MulOperator(){
  if ( token == "*" || token == "/" || token == "AND" ) {
    getToken();
  } 
  else error("Expected MulOperator ☜(ಠ_ಠ☜)");
}

void parse_AddOperator(){
  if ( token == "+" || token == "OR" || token == "-" || token == "&" ) {
    getToken();
  } 
  else error("Expected AddOperator");
}

void parse_Factor();

void parse_Term(){
  parse_Factor();
  while ( token == "*" || token == "/" || token == "AND" )
  {
    parse_MulOperator();
    parse_Factor();
  } 
}

void parse_SimpleExpression(){
    parse_Term();
    while ( token == "+" || token == "-" || token == "OR" || token == "&" )
    {
        parse_AddOperator();
        parse_Term();
    }
}

void parse_Relation(){
  if ( token == "<" || token == ">" || token == "=" || token == "#" ){
    getToken();
  } 
  else error("Expected Relation");
}

void parse_Expression(){
  parse_SimpleExpression();
  if( token == "<" || token == ">" || token == "=" || token == "#" ){
    parse_Relation();
    parse_SimpleExpression();
  }
}

void parse_Factor(){
  if ( is_Integer( token ) || is_Decimal( token ) || is_String( token ) || is_Identifier( token ))
    getToken();
  else if ( token == "(" ) {
    getToken();
    parse_Expression();
    if ( token == ")" ) {
      getToken();
    }
    else error("Expected \")\" (눈_눈) ");
  }
  else if ( token == "~" ){
    getToken();
    parse_Factor();
  }
  else error("Expected Factor (>_<)");
}

void parse_WriteStatement(){
  if ( token == "WRITE" ) {
    getToken();
    if( token == "(" ) {
      getToken();
      parse_Expression();
      if( token == ")" ){
        getToken();
      }
      else error("Expected \")\"");
    }
    else error("Expected \"(\"");
  }
  else error("Expected WRITE  (ಠ ∩ ಠ) ");
}

void parse_Selector(){
  if( token == "." ){
    getToken();
    if(is_Identifier( token ))
      getToken();
    else
      error("Expected Identifier");
  }
  else if (token == "["){
    getToken();
    parse_Expression();
    if(token == "]")
      getToken();
    else
      error("Expected ]");
  }
  else 
    error("Expected Selector");
}

void parse_Designator(){
  if(is_Identifier(token)){
    getToken();
    while(token[0] == '.' || token[0] == '['){
      parse_Selector();
    }
  }
  else
    error("Expected Identifier");
}

void parse_Assignment(){
  parse_Designator();
  if( token == ":=" ){
    getToken();
    parse_Expression();
  }
  else 
    error("Expected \":=\"");
}

void parse_Statement(){
  if ( is_Identifier( token )) parse_Assignment();
  else if ( token == "WRITE" ) parse_WriteStatement();
  else
    error("Expected Statement (╯°□°)╯︵ ┻━┻ ");
}

void parse_StatementSequence(){
  parse_Statement();
  while ( token == ";" ) {
    getToken();
    parse_Statement();
  }
}

int main(){
  getToken();
  parse_StatementSequence();

  cout << endMessage << endl;

  return 0;
  /*
  getToken();
  if(token == "E O F")
    cout << "no input" << endl;
  parse_StatementSequence();
  if(token == "E O F")
    cout << endMessage << endl;
  else
    cout << "Expected end of input" << endl;
  return 0;
  */
}
