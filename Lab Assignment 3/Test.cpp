#include<bits/stdc++.h>

using namespace std;
string strip(string );

int main(){/*
    string str = "ab        cd";
    smatch match;
    regex_search(str,match,regex("\\s+"));
    cout<<match.prefix()<<","<<endl;
    cout<<match.suffix()<<","<<endl;
    if(regex_match(str,regex(".*\\s+.*"))){
        cout<<"Get"<<endl;
    }else{
        cout<<"Not get"<<endl;
    }*/
    //cout<<"'"<<strip("ab")<<"'"<<endl;
    ifstream fi;
    fi.open("sourceCode.c");
    if(fi.is_open()){
        cout<<"File open success"<<endl;
    }else{
        cout<<"File open failed"<<endl;
    }
    string line;
    vector<pair<string,string>> tokens;
    vector<int> line_number_from_token_ind;
    int line_number=0;
    while(getline(fi,line)){
        line = strip(line);
        line_number++;
        if(line==""){
            continue;
        }
        cout<<line<<endl;
        if(line[0]=='#'){
            cout<<"Preprocessor"<<endl;
            tokens.push_back({"Preprocessor","#"});
            line_number_from_token_ind.push_back(line_number);
            line = line.substr(1);
            cout<<"Remaining line is : "<<line<<endl;
            if()
        }

    }
}

string strip(string str){
    int l=0,r=str.size()-1;
    while(str[l]==' '){
        l++;
    }
    while(str[r]==' '){
        r--;
    }
    //cout<<l<<' '<<r<<endl;
    if(l>=r){
        return "";
    }
    return str.substr(l,(r-l)+1);
}
