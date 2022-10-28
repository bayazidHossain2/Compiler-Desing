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
   // regex regex_starting_blocks("(.*){(.*)");
    //regex regex_ending_blocks("(.*)}(.*)");
    regex regex_line_ending("(.*);");
    regex regex_return_statment("(.*)return(.*)");
    regex regex_digit("[0-9]");
    regex regex_digits("([1-9][0-9]*)");
    string line;
    int lineNumber=1;
    vector<pair<string,string>> tokens;
    while(getline(fs,line)){
        line = strip(line);
        cout<<"strip line is : "<<line<<endl;
        if(regex_match(line,regex_header_start)){
            cout<<"Header found"<<endl;
            if(regex_match(line,regex_header_line_valid)){
                cout<<"A Valid header found"<<endl;
                string header = get_subString(line,'<','>');

                header=strip(header);
                cout<<"Header is :\""<<header<<"\""<<endl;
                if(header!="stdio.h"){
                    error_msg_show(lineNumber,header+" not defined header.");
                }
            }else{
                error_msg_show(lineNumber,"Invalid header type.");
            }
        }
        else if(regex_match(line,regex_main)){
            cout<<"Main function found."<<endl;
        }
        lineNumber++;
    }
}
