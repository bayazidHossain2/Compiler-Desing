#ifndef LEXICAL_ANALYSIS_H_INCLUDED
#define LEXICAL_ANALYSIS_H_INCLUDED
#include<fstream>
#include"castom_function.h"
#include"variables.h"

void Lexer(string fileName){
    ifstream fs;
    fs.open(fileName);
    if (!fs) {
        cout << "Unable to open Source file";
        exit(1); // terminate with error
    }else{
        cout<<"File open success."<<endl;
    }

    bool multilineCommentOut{false};
    string line;
    int line_number=0;
    smatch match;
    tokens.clear();
    line_number_from_token_number.clear();
    while(getline(fs,line)){
        line = strip(line);
        line_number++;
        //cout<<"After strip line is : \""<<line<<"\""<<endl;
        ///Preprocessor
        if(line[0]=='#'){
            tokens.push_back({"PREPROCESSOR","#"});
            line_number_from_token_number.push_back(line_number);
            line = line.substr(1);
            if(regex_search(line,match,regex("<|(\\s)+"))){
                tokens.push_back({"PREPROCESSOR_TYPE",match.prefix()});
                line_number_from_token_number.push_back(line_number);
                tokens.push_back({getSeperatorName(match.str()),match.str()});
                line_number_from_token_number.push_back(line_number);
                line=match.suffix();
            }else{
                error_message(line_number,"Preprocessing Error.");
            }
            if(regex_search(line,match,regex(">|(\\s)+"))){
                if(match.str()==">"){
                    if(headers.count(match.prefix())){
                        error_message(line_number,"Header already included.");
                    }else{
                        headers.insert(match.prefix());
                        if(match.prefix()=="stdio.h"){
                            functions.insert("printf");
                        }else if(match.prefix()=="cat.h"){
                            variables["teeth"].first="int";
                            variables["teeth"].second="0";
                            variables["tail"].first="int";
                            variables["tail"].second="0";
                            functions.insert("elihw");
                        }
                    }
                    tokens.push_back({"HEADER_FILE",match.prefix()});
                    line_number_from_token_number.push_back(line_number);
                    tokens.push_back({getSeperatorName(match.str()),match.str()});
                    line_number_from_token_number.push_back(line_number);
                }else{
                    tokens.push_back({"CONSTANT_IDENTIFER",match.prefix()});
                    line_number_from_token_number.push_back(line_number);
                    tokens.push_back({getSeperatorName(match.str()),match.str()});
                    line_number_from_token_number.push_back(line_number);
                    tokens.push_back({"CONSTANT_VALUE",match.suffix()});
                    line_number_from_token_number.push_back(line_number);
                }
            }else{
                error_message(line_number,"Preprocessing Error.");
            }
            continue;
        }
        start:
        ///Skipping line checking or Comment out part
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
            }else{
                error_message(line_number,"Multi Line comment out not closed.");
            }
            if(line==""){
                continue;
            }
        }
        //cout<<"Processing line is : \""<<line<<"\""<<endl;
        if(line==""){
            //cout<<"Empty line"<<endl;
            continue;
        }
        ///Separator finding
        if(regex_search(line,match,regex(separators))){
            //cout<<"Separator found : \""<<match.str()<<"\""<<endl;
            //cout<<"Name is : "<<getSeperatorName(match.str())<<endl;
            if(match.prefix()!=""){
                //cout<<"prefix found : \""<<match.prefix()<<"\""<<endl;
                //cout<<"Name is : "<<getType(match.prefix())<<endl;
                tokens.push_back(make_pair(getType(match.prefix()),match.prefix()));
                line_number_from_token_number.push_back(line_number);
            }
            tokens.push_back(make_pair(getSeperatorName(match.str()),match.str()));
            line_number_from_token_number.push_back(line_number);
            line=match.suffix();
            goto start;
        }
    }
/*
    cout<<"----------Total Number of tokens : "<<tokens.size()<<endl;
    for(auto v : tokens){
        cout<<"Token Type'"<<v.first<<"', '"<<v.second<<"'"<<endl;
    }
*/
    fs.close();
}

#endif // LEXICAL_ANALYSIS_H_INCLUDED
