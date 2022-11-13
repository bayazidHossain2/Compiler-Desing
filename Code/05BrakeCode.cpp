#include<iostream>
#include<regex>
#include<vector>
#include<fstream>
#include<string>

using namespace std;

string stripL(string );
string stripR(string );
string strip(string );
string getSeperatorName(string );
string getType(string );

const string separators = "[=\\s+<>\\(\\)\\{\\},\\.;\\[\\]]";
const string keywords = "(auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)|(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(int)|(long)|(register)|(return)|(short)|(signed)|(sizeof)|(static)|(struct)|(switch)|(typedef)|(union)|(unsigned)|(void)|(volatile)|(while)";
const string number = "0|(-?[1-9][0-9]*)";
const string lattersValidName = "[A-Za-z_][A-Za-z0-9_]*";

int main(){
    //freopen("output.txt","w",stdout);
    if(regex_match("=",regex(separators))){
        cout<<"match"<<endl;
    }else{
        cout<<"Not "<<endl;
    }
    string fileName="sourceCode.c";
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
    smatch match;
    vector<pair<string,string>> tokens;
    while(getline(fs,line)){
        line = strip(line);
        cout<<"After strip line is : \""<<line<<"\""<<endl;
        if(line[0]=='#'){
            tokens.push_back({"PREPROSESSOR","#"});
            line = line.substr(1);
            if(regex_search(line,match,regex("[\\s<]+"))){
                tokens.push_back({"PREPROSESSOR_TYPE",match.prefix()});
                tokens.push_back({getSeperatorName(match.str()),match.str()});
                line=match.suffix();
            }
            if(regex_search(line,match,regex("[\\s>]+"))){
                if(match.str()==">"){
                    tokens.push_back({"HEADER_FILE",match.prefix()});
                    tokens.push_back({getSeperatorName(match.str()),match.str()});
                }else{
                    tokens.push_back({"CONSTANT_IDENTIFER",match.prefix()});
                    tokens.push_back({getSeperatorName(match.str()),match.str()});
                    tokens.push_back({"CONSTANT_VALUE",match.suffix()});
                }
            }continue;
        }
        start:
        ///Skiping line checking
        if(multilineCommentOut){
            //cout<<"commented"<<endl;
            if(regex_search(line,match,regex("\\*/"))){
                //cout<<"Finished comment"<<endl;
                line=match.suffix();
                multilineCommentOut=false;
                goto start;
            }continue;

        }else if(line==""||regex_match(line,regex("^//.*"))){
            //cout<<"empty line or comment line"<<endl;
            continue;
        }
        else if(regex_search(line,match,regex("//"))){
            //cout<<"sub comment line"<<endl;
            line = strip(match.prefix());
            //cout<<"Remaining line is : \""<<line<<"\""<<endl;
        }else if(regex_search(line,match,regex("/\\*"))){
            //cout<<"MultiLine comment out found"<<endl;
            line = match.prefix();
            multilineCommentOut=true;
            string commentString=match.suffix();
            if(regex_search(commentString,match,regex("\\*/"))){
                //cout<<"Finish in same line"<<endl;
                line+=match.suffix();
                multilineCommentOut=false;
                goto start;
            }
            if(line==""){
                continue;
            }
        }
        cout<<"Processing line is : \""<<line<<"\""<<endl;
        if(line==""){
            cout<<"Empty line"<<endl;
            continue;
        }
        ///Separator finding
        if(regex_search(line,match,regex(separators))){
            cout<<"Separator found : \""<<match.str()<<"\""<<endl;
            cout<<"Name is : "<<getSeperatorName(match.str())<<endl;
            if(match.prefix()!=""){
                cout<<"prefix found : \""<<match.prefix()<<"\""<<endl;
                cout<<"Name is : "<<getType(match.prefix())<<endl;
                tokens.push_back(make_pair(getType(match.prefix()),match.prefix()));
            }
            tokens.push_back(make_pair(getSeperatorName(match.str()),match.str()));
            line=match.suffix();
            goto start;
        }

    }
    cout<<endl<<"********* Tokens are ***********"<<endl<<endl;
    for(pair<string,string> token : tokens){
        cout<<" <'"<<token.first<<"', '"<<token.second<<"'> "<<endl;
    }cout<<endl;

}

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
    }else if(separator==","){
        return "COMA_DELIMATOR";
    }else if(separator=="."){
        return "DOT_OPERATOR";
    }else if(separator==";"){
        return "SEMECLONE";
    }else if(separator=="="){
        return "ASSIGNMENT_OPERATOR";
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
