#include<iostream>
#include<regex>
#include<sstream>
#include<fstream>
using namespace std;
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
string get_subString(string str,char start_dilam,char end_dilam){
    stringstream ss(str);
    string part;
    getline(ss,part,end_dilam);
    ss = stringstream(part);
    getline(ss,part,start_dilam);

    getline(ss,part,start_dilam);
    return part;
}
void error_msg_show(int line,string message){
    cout<<"Error found in line : "<<line<<endl;
    cout<<"Error message : "<<message<<endl<<endl;
}
int main(){
    ifstream fs;
    string source_name="001source_code.c";
    fs.open(source_name);
    if(!fs){
        cout<<source_name<<" file not found in current directory."<<endl;
        return 0;
    }

    regex regex_header_start("(#\\s*include\\s*)(.*)");
        regex regex_header_line_valid("(#\\s*include\\s*<)(.*)>");
    regex regex_main("(.*) main(.*)");
        regex regex_main_parm("(.*) main()(.*)");
            regex regex_main_return_type_void("\\s*void(.*)");
            regex regex_main_return_type_int("\\s*int(.*)");
   // regex regex_starting_blocks("(.*){(.*)");
    //regex regex_ending_blocks("(.*)}(.*)");
    regex regex_return_statment("(.*)return\\s(.*)");
        regex regex_return_int("(.*)return\\s*-?([1-9][0-9]*)(.*)");
    regex regex_digit("[0-9]");
    regex regex_digits("([1-9][0-9]*)");
    regex regex_scop_start("(.*)\\{(.*)");
    regex regex_scop_end("(.*)\\}(.*)");
    regex regex_line_end("(.*);$");
    string line;
    int lineNumber=1;
    vector<pair<string,string>> tokens;
    bool return_need=false;
    bool scop_start=false;
    while(getline(fs,line)){
        line = strip(line);
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
    if(return_need){
        error_msg_show(lineNumber,"Return not found in the scope.");
        return 0;
    }
    if(scop_start){
        error_msg_show(lineNumber,"Scope not finished.");
        return 0;
    }
    cout<<"--------------Compilatin success.-------------------"<<endl;
    return 0;
}
