using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
    //useful variables
    vector<char> hexDigits = {'1','2','3','4','5','6','7','8','9','0','A','B','C','D','E','F'};
    vector<char> identDigits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T','U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c', 'd', 'e', 
                            'f', 'g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't','u', 'v', 'w', 'x', 'y', 'z','_'};

    //take input
    int numInputs;
    cin>>numInputs;
    cin.ignore();
    vector<string> inputs;
    for(int i=0; i<numInputs; i++){
        string s;
        getline(cin, s);
        inputs.push_back(s);
    }
    
    cout<<numInputs<<endl;
    for(int i=0; i<numInputs; i++){
        string s = inputs[i];
        string state = "INVALID!";

        cout<<i+1<<": "; 
        
        //"simple" checks
        if(s[0] == '\"' && s[s.size()-1] == '\"' && !count(s.begin(), s.end(), ' ') && count(s.begin(), s.end(), '\"') == 2)//string
            state = "String";
        else if(s=="PROCEDURE" || s=="IF" || s=="THEN" || s=="WHILE" || s=="FUNCTION" || s=="WRITE")//keyword
            state = "Keyword";
        else if(s.size()==3 && count(hexDigits.begin(), hexDigits.end(), s[0]) && count(hexDigits.begin(), hexDigits.end(), s[1]) && s[2]=='X')//character literal
            state = "Character";
        //less simple checks
        else{
            //check for hexadecimal
            if(s[s.size()-1] == 'H'){
                state = "Hexadecimal";
                for(int i=0; i<s.size()-1; i++){
                    if(!count(hexDigits.begin(), hexDigits.end(), s[i])){
                        state="INVALID!";//return to invalid state if not hex digit
                        break;
                    }
                } 
            }
            //check for identifier
            if(state=="INVALID!" && ((s[0]>='A' && s[0]<='Z') || (s[0]>='a' && s[0]<='z'))){
                state = "Identifier";
                for(int i=1; i<s.size(); i++){
                    if(!count(identDigits.begin(), identDigits.end(), s[i])){
                        state="INVALID!";
                        break;
                    }
                }
            }
            //check for types of numbers
            if(state=="INVALID!" && (((s[0]=='-' || s[0]=='+') && s.size()>1 && s[1]<='9' && s[1]>='0') || (s[0]<='9' && s[0]>='0'))){
                state="Integer";
                for(int i=1; i<s.size(); i++){
                    if(s[i]<='9' && s[i]>='0')
                        continue;
                    else if(state=="Integer" && s[i]=='.' && i+1<s.size() && s[i+1]<='9' && s[i+1]>='0')
                        state="Decimal";
                    else if(state=="Decimal" && s[i]=='E' && ((i+1<s.size() && s[i+1]<='9' && s[i+1]>'0') || //without sign after E 
                            (i+2<s.size() && (s[i+1]=='+' || s[i+1]=='-') && s[i+2]<='9' && s[i+2]>'0'))){ //with sign after E
                        state="Scientific";
                        i++;//prevent reading sign on next loop
                    }
                    else
                        state="INVALID!";
                }
            }
        }
        //output data type for current
        cout<<state<<endl;   
    }
}
