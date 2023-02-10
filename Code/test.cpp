#include<bits/stdc++.h>
#include<regex>
#include<string>
using namespace std;
const string sepraretor="[#<>,;\\{\\}\\(\\)]|(\\s)+";
const string keyword[] ={"int","float","char","double","return"};

string recognize_keyword(string s){
    for(int i=0;i<5;i++){
        if(keyword[i]==s){
            return "KEYWORD";
        }
    }
    return "IDENTIFIRE";
}
string recognize_seperator(string str){
    if(str=="#"){
        return "PREPROCESSOR";
    }
    else if(str=="<"){
        return "OPEN_ANGULAR_BRACKET";
    }
    else if(str==">"){
        return "CLOSE_ANGULAR_BRACKET";
    }
    else if(str==","){
        return "COMA_OPERATOR";
    }
    else if(str==";"){
        return "SEMECLON";
    }
    else if(str=="{"){
        return "OPEN_CERLIBASE";
    }
    else if(str=="}"){
        return "CLOSE_CERLIBASE";
    }
    else if(regex_match(str,regex("\\s+"))){
        return "SPACE";
    }
    else{
        return "NOT_RECOGNIZE";
    }
}
string recognize_header(string str){
    if(str=="include"){
        return "PREPROSESSOR_TYPE";
    }else{
        return "HEADER";
    }
}
int main()
{
    fstream fs;
    string source_code="sourceCode.c";
    fs.open(source_code);
    regex check_singel_comment("//");
    regex check_multiline_comment_start("/\\*");
    regex check_multiline_comment_end("\\*/");
    string line;
    smatch m;
    vector<pair<string,string>> Tokens;
    bool is_multiline_comment=false;
    while(getline(fs,line))
    {
        if(is_multiline_comment){
                if(regex_search(line,m,check_multiline_comment_end))
                {
                    line=m.suffix();
                    is_multiline_comment=false;
                }else{
                    continue;
                }
        }
        else if(regex_search(line,m,check_singel_comment)){
            line=m.prefix();
        }
        else if(regex_search(line,m,check_multiline_comment_start))
        {
            is_multiline_comment=true;
            line=m.prefix();
            string strip_after_comment;
            strip_after_comment=m.suffix();
            if(regex_search(line,m,check_multiline_comment_end))
            {
                line+=m.suffix();
                 is_multiline_comment=false;
            }
        }
        start:
        cout<<"line processing: "<<line<<endl;
        if(regex_search(line,m,regex(sepraretor))){
            if(m.prefix()!=""){
                string prefix_name;
                prefix_name=recognize_keyword(m.prefix());
                Tokens.push_back({prefix_name,m.prefix()});
            }
            cout<<"prefix name :"<<m.prefix()<<",'"<<m.str()<<"'"<<endl;
            cout<<"suff : "<<m.suffix()<<endl;
            string separetor_name;
            separetor_name=recognize_seperator(m.str());
            Tokens.push_back({separetor_name,m.str()});
            cout<<"suff2 : "<<m.suffix()<<endl;
            if(m.suffix()!=""){
                line=m.suffix();
                cout<<"suffix :"<<line<<endl;
                goto start;

            }

        }
    }
    for(pair<string,string> token : Tokens){
        cout<<"'"<<token.first<<"' = '"<<token.second<<"'"<<endl;
    }
    //cout<<"line processing: "<<line<<endl;
}
