#include<iostream>
#include<sstream>
#include<fstream>
#include<regex>
#include<vector>

using namespace std;
string stripL(string );
string stripR(string );
string strip(string );

const int numberOfTokan=20;
string className[numberOfTokan];
string regexString[numberOfTokan];

const string preprossor="PREPROSSOR";
const string keyword="KEYWORD";
const string openAlgularBraket="OPEN_ANGULAR_BRAKET";
const string closeAlgularBraket="CLOSE_ANGULAR_BRAKET";
const string openCurlyBraces="OPEN_CURLY_BRACES";
const string closeCurlyBraces="CLOSE_CURLY_BRACES";
const string openParentheses="OPEN_PARANTHESES";
const string closeParentheses="CLOSE_PARANTHESES";
const string openSquareBraket="OPEN_SQUARE_BRAKET";
const string CLOSESquareBraket="CLOSE_SQUARE_BRAKET";
const string header="HEADER";
const string punctuation="PUNCTUATION";
const string number="NUMBER";
const string other="OTHER";

int main(){
    className[0] = "PREPROSSOR";
    regexString[0] = "^#.*";
    className[1] = "KEYWORD";
    regexString[1] = "^[a-z][a-z]*";
    className[2] = "OPEN_ANGULAR_BRAKET";
    regexString[2] = "^<.*";
    className[3] = "CLOSE_ANGULAR_BRAKET";
    regexString[3] = "^>.*";
    className[4] = "OPEN_CURLY_BRACES";
    regexString[4] = "^\\{.*";
    className[5] = "CLOSE_CURLY_BRACES";
    regexString[5] = "^\\}.*";
    className[6] = "OPEN_PARANTHESES";
    regexString[6] = "^\\(.*";
    className[7] = "CLOSE_PARANTHESES";
    regexString[7] = "^\\).*";
    className[8] = "OPEN_SQUARE_BRAKET";
    regexString[8] = "^\\[.*";
    className[9] = "CLOSE_SQUARE_BRAKET";
    regexString[9] = "^\\].*";
    className[10] = "HEADER";
    regexString[10] = "[a-z\\.]+";
    className[11] = "PUNCTUATION";
    regexString[11] = "[;,]";
    className[12] = "NUMBER";
    regexString[12] = "0|-?([1-9][0-9]*)";
    className[11] = "OTHER";
    regexString[11] = ".*";

    string fileName="source.txt";
    ifstream fs;
    fs.open(fileName);
    if (!fs) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }else{
        cout<<"File open success."<<endl;
    }
    bool multilineCommentOut{false};
    string line;
    while(getline(fs,line)){
        line = strip(line);
        ///Comment checking
        if(regex_match(line,regex("^\\\\\\")))


        cout<<"strip line is : "<<line<<endl;
        if(regex_match(line,regex_scop_start)){
            scop_start=true;
        }
        if(regex_match(line,regex_header_start)){
            cout<<"Header found"<<endl;
            if(regex_match(line,regex_header_line_valid)){
                cout<<"A Valid header found"<<endl;
                string header = get_subString(line,'<','>');

                header=strip(header);
                cout<<"Header is :\""<<header<<"\""<<endl;
                if(header!="stdio.h"){
                    error_msg_show(lineNumber,header+" not defined header.");
                    return 0;
                }
            }else{
                error_msg_show(lineNumber,"Invalid header type.");
                return 0;
            }
        }
        else if(regex_match(line,regex_main)){
            cout<<"Main found."<<endl;
            if(regex_match(line,regex_main_parm)){
                cout<<"Main function found."<<endl;
                if(regex_match(line,regex_main_return_type_int)){
                    cout<<"Main should be return an integer."<<endl;
                    return_need = true;
                }else if(regex_match(line,regex_main_return_type_void)){
                    cout<<"Main return not need."<<endl;
                }else{
                    error_msg_show(lineNumber,"Invalid return type of Main function.");
                    return 0;
                }

            }else{
                error_msg_show(lineNumber,"Invalid main function declaration.");
                return 0;
            }
        }
        else if(regex_match(line,regex_return_statment)){
            cout<<"Return statement found"<<endl;
            if(!scop_start){
                error_msg_show(lineNumber,"Not in a scope.");
                return 0;
            }
            if(regex_match(line,regex_return_int)){
                cout<<"Return type an integer found."<<endl;
                return_need = false;
            }else{
                error_msg_show(lineNumber,"Return type not an integer.");
                return 0;
            }
            if(!regex_match(line,regex_line_end)){
                error_msg_show(lineNumber,"Line not finished. A ; need end of line.");
                return 0;
            }
        }
        if(regex_match(line,regex_scop_end)){
            scop_start=false;
        }
        lineNumber++;
    }
    string line;
    strip("lkdsjl");

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

