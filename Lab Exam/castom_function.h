#ifndef CASTOM_FUNCTION_H_INCLUDED
#define CASTOM_FUNCTION_H_INCLUDED
#include<regex>
#include<istream>
using namespace std;

string getSeperatorName(string separator){
    if(separator=="("){
        return "OPEN_PARANTHESES";
    }else if(separator==")"){
        return "CLOSE_PARANTHESES";
    }else if(separator=="{"){
        return "OPEN_CURLY_BRACES";
    }else if(separator=="}"){
        return "CLOSE_CURLY_BRACES";
    }else if(separator=="["){
        return "OPEN_SQUARE_BRAKET";
    }else if(separator=="]"){
        return "CLOSE_SQUARE_BRAKET";
    }else if(separator=="<"){
        return "OPEN_ANGULAR_BRAKET";
    }else if(separator==">"){
        return "CLOSE_ANGULAR_BRAKET";
    }else if(separator==">="){
        return "RELATIONAL_OPERATOR";
    }else if(separator=="<="){
        return "RELATIONAL_OPERATOR";
    }else if(separator=="=="){
        return "RELATIONAL_OPERATOR";
    }else if(separator=="!="){
        return "RELATIONAL_OPERATOR";
    }else if(separator=="||"){
        return "LOGICAL_OPERATOR";
    }else if(separator=="&&"){
        return "LOGICAL_OPERATOR";
    }else if(separator=="!"){
        return "LOGICAL_OPERATOR";
    }else if(separator==","){
        return "COMA_DELIMATOR";
    }else if(separator=="."){
        return "DOT_OPERATOR";
    }else if(separator==";"){
        return "SEMECLONE";
    }else if(separator=="="){
        return "ASSIGNMENT_OPERATOR";
    }else if(separator=="+"){
        return "PLUS_OPERATOR";
    }else if(separator=="-"){
        return "MINOUS_OPERATOR";
    }else if(separator=="*"){
        return "MULTIPLICATION_OPERATOR";
    }else if(separator=="/"){
        return "DIVISSION_OPERATOR";
    }else{
        return "SPACES";
    }
}
string getType(string str){
    if(regex_match(str,regex(keywords))){
        return "KEYWORD";
    }else if(regex_match(str,regex(lattersValidName))){
        return "IDENTIFIRE";
    }else if(regex_match(str,regex(number))){
        return "CONSTANT_NUMBER";
    }else{
        return "UNKNOWN";
    }
}

string stripL(string input_str){
    int starting_pointer=0;
    while(input_str[starting_pointer]==' '){
        starting_pointer++;
    }
    return input_str.substr(starting_pointer);
}
string stripR(string input_str){
    int ending_pointer=input_str.size()-1;
    while(input_str[ending_pointer]==' '){
        ending_pointer--;
    }
    return input_str.substr(0,ending_pointer+1);
}
string strip(string input_str){
    string part = stripL(input_str);
    part = stripR(part);
    return part;
}

void error_message(int line,string message){
    cout<<"Error occur in line : "<<line<<endl;
    cout<<"Error message : "<<message<<endl;
    exit(1);
}

#endif // CASTOM_FUNCTION_H_INCLUDED
