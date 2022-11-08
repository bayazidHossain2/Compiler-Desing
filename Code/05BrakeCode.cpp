#include<iostream>
#include<regex>
#include<vector>
#include<fstream>

using namespace std;

string stripL(string );
string stripR(string );
string strip(string );

const string seperators = "[\\s<>\\(\\)\\{\\},;]";

int main(){
    freopen("output.txt","w",stdout);
    /*if(regex_match(";",regex(seperators))){
        cout<<"match"<<endl;
    }else{
        cout<<"Not "<<endl;
    }*/
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
    smatch match;
    while(getline(fs,line)){
        start:
        line = strip(line);
        cout<<"After strip line is : \""<<line<<"\""<<endl;
        ///Skiping line checking
        if(multilineCommentOut){
            cout<<"commented"<<endl;
            if(regex_search(line,match,regex("\\*/"))){
                cout<<"Finished comment"<<endl;
                line=match.suffix();
                multilineCommentOut=false;
                goto start;
            }continue;

        }else if(line==""||regex_match(line,regex("^//.*"))){
            cout<<"empty line or comment line"<<endl;
            continue;
        }
        else if(regex_search(line,match,regex("//"))){
            cout<<"sub comment line"<<endl;
            line = strip(match.prefix());
            cout<<"Remaining line is : \""<<line<<"\""<<endl;
        }else if(regex_search(line,match,regex("/\\*"))){
            cout<<"MultiLine comment out found"<<endl;
            line = match.prefix();
            multilineCommentOut=true;
            string commentString=match.suffix();
            if(regex_search(commentString,match,regex("\\*/"))){
                cout<<"Finish in same line"<<endl;
                line+=match.suffix();
                multilineCommentOut=false;
                goto start;
            }
            if(line==""){
                continue;
            }
        }
        cout<<"Processing line is : \""<<line<<"\""<<endl;
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
