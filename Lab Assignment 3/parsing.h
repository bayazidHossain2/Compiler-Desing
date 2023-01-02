#ifndef PARSING_H_INCLUDED
#define PARSING_H_INCLUDED

#include<bits/stdc++.h>
#include"castom_function.h"
using namespace std;

int code_preprossing();
string calculate(vector<pair<string,string>> );
bool logical_calculation(pair<string,string> exp1,pair<string,string> op,pair<string,string> exp2);

void Parser(){
    int pointer = code_preprossing();
    int if_occur=0;
    bool res=false;
    if(pointer==-1){
        cout<<"Error : main function not declared."<<endl;
        exit(1);
    }

    for(;pointer<tokens.size();pointer++){
        /// Declaring a new variable
        if(tokens[pointer].second=="int"||tokens[pointer].second=="float"||tokens[pointer].second=="double"||tokens[pointer].second=="char"){
            string type = tokens[pointer].second;
            pointer++;
            while(tokens[pointer].second!=";"){
                if(!variables.count(tokens[pointer+1].second)){
                    variables[tokens[pointer+1].second].first=type;
                    variables[tokens[pointer+1].second].second="0";
                    pointer+=2;
                }else{
                    error_message(line_number_from_token_number[pointer],"Variable must be unique.");
                }
            }
        }else if(tokens[pointer].second=="printf"){
            const regex r("(%d|%c|%lf|%f|%s)");;
            string out = "";
            pointer+=2;
            while(!regex_search(tokens[pointer].second,regex(".*\"$"))){
                  out+=tokens[pointer].second;
                  pointer++;
            }out+=tokens[pointer++].second;
            //cout<<"_____________________fi : "<<out<<endl;
            while (regex_search(out, r)) {
                //cout<<"var -----------"<<variables[tokens[pointer+1].second].second<<endl;
                out = regex_replace(out, r, variables[tokens[pointer+1].second].second,regex_constants::format_first_only);
                pointer+=2;
            }
            cout<<"-> "<<out.substr(1,out.length()-2)<<endl;
        }
        ///Assigning a value to a existing variable
        else if(tokens[pointer].first=="IDENTIFIRE"){
            string id = tokens[pointer].second;
            //cout<<"--------------------id"<<endl;
            if(tokens[pointer+1].second=="="){
            //cout<<"--------------------id  ass"<<endl;
                if(variables.count(tokens[pointer].second)){
                    vector<pair<string,string>> expressions;
                    pointer+=2;
                    while(tokens[pointer].second!=";"){
                        expressions.push_back(tokens[pointer]);
                        pointer++;
                    }
                    variables[id].second = calculate(expressions);
                    //cout<<"returned value is : "<<variables[id].second<<endl;
                }else{
                    error_message(line_number_from_token_number[pointer],"variable "+tokens[pointer].second+" not declared in this scope.");
                }
            }else{
                error_message(line_number_from_token_number[pointer],"invalid grammar. Identifier never followed by space.");
            }

        }
        ///Conditional Statement
        else if(tokens[pointer].second=="if"){
            if_occur++;
            pointer+=2;
            res = logical_calculation(tokens[pointer],tokens[pointer+1],tokens[pointer+2]);
            //cout<<"______________________"<<res<<endl;
            pointer+=2;
            if(!res){
                stack<string> stk;
                while(pointer<tokens.size()){
                    if(tokens[pointer].second=="{"){
                        stk.push("{");
                    }else if(tokens[pointer].second==")"){
                        if(!stk.empty()){
                            stk.pop();
                        }
                    }
                    if(stk.empty()){
                        break;
                    }
                    pointer++;
                }
            }
        }

        if(tokens[pointer].second=="else"){
            if(if_occur){
                if_occur--;
                if(res){
                    pointer++;
                    stack<string> stk;
                    while(pointer<=tokens.size()){
                        if(tokens[pointer].second=="{"){
                            stk.push("{");
                        }
                        if(tokens[pointer].second=="}"){
                            if(!stk.empty()){
                                stk.pop();
                            }
                        }
                        if(stk.empty()){
                            break;
                        }
                        pointer++;
                    }
                }
            }else{
                error_message(line_number_from_token_number[pointer],"Else statement is not allowed without if statement.");
            }
        }



    }
}

int code_preprossing(){
    int main_pointer=-1;
    stack<char> stk;
    int last_opening_token_number;
    for(int i=0;i<tokens.size();i++){
        if(tokens[i].first == "PREPROCESSOR"){
            i++;
            if(tokens[i].second == "include"){
                headers.push_back(tokens[i+2].second);
                i+=3;
            }else{
                variables[tokens[i+2].second].first = "global_const";
                variables[tokens[i+2].second].second = tokens[i+4].second;
                i+=4;
            }
        }else if(i+2<tokens.size()&&tokens[i].first=="KEYWORD"&&tokens[i+2].second=="main"){
            i+=4;
            main_pointer = i+2;
        }else if(main_pointer!=-1){
            if(tokens[i].second=="{"){
                stk.push('{');
                last_opening_token_number=i;
            }else if(tokens[i].second=="}"){
                if(!stk.empty()){
                    stk.pop();
                }else{
                    error_message(line_number_from_token_number[i],"} not balanced.");
                }
            }
        }else{
            error_message(line_number_from_token_number[i],"This grammar is not allowed.");
        }
    }
    if(!stk.empty()){
        error_message(line_number_from_token_number[last_opening_token_number],"{ not balanced.");
    }

    return main_pointer;
}

int precedence(string op){
    if(op == "+"||op == "-"){
        return 1;
    }
    if(op == "*"||op == "/"){
        return 2;
    }
    return 0;
}

int arrithmeticOperation(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
        default: return 0;
    }
}

string calculate(vector<pair<string,string>> exp){
    stack <int> stk_val;
    stack <string> stk_op;
    for(int i = 0; i < exp.size(); i++){
        if(exp[i].second == "("){
            stk_op.push(exp[i].second);
        }else if(exp[i].second == ")"){
            while(!stk_op.empty() && stk_op.top() != "("){
                int v2 = stk_val.top();
                stk_val.pop();
                int v1 = stk_val.top();
                stk_val.pop();

                string op = stk_op.top();
                stk_op.pop();

                stk_val.push(arrithmeticOperation(v1, v2, op[0]));
            }
            if(!stk_op.empty()){
                stk_op.pop();
            }
        }else if(exp[i].first=="CONSTANT_NUMBER"){
            int num = stoi(exp[i].second);
            stk_val.push(num);
        }else if(exp[i].first=="IDENTIFIRE"){
            int num = stoi(variables[exp[i].second].second);
            stk_val.push(num);
        }else{
            while(!stk_op.empty() && precedence(stk_op.top())
                                >= precedence(exp[i].second)){
                int v2 = stk_val.top();
                stk_val.pop();

                int v1 = stk_val.top();
                stk_val.pop();

                string op = stk_op.top();
                stk_op.pop();
                stk_val.push(arrithmeticOperation(v1, v2, op[0]));
            }
            stk_op.push(exp[i].second);
        }
    }
    while(!stk_op.empty()){
        int v2 = stk_val.top();
        stk_val.pop();

        int v1 = stk_val.top();
        stk_val.pop();

        string op = stk_op.top();
        stk_op.pop();
        //cout<<"-------------------------"<<arrithmeticOperation(v1, v2, op[0])<<endl;
        stk_val.push(arrithmeticOperation(v1, v2, op[0]));
    }
    return to_string(stk_val.top());
}


bool logical_calculation(pair<string,string> exp1,pair<string,string> op,pair<string,string> exp2){
    int a,b;
    if(exp1.first=="CONSTANT_NUMBER"){
        a = stoi(exp1.second);
    }else{
        a = stoi(variables[exp1.second].second);
    }
    if(exp2.first=="CONSTANT_NUMBER"){
        b = stoi(exp2.second);
    }else{
        b = stoi(variables[exp2.second].second);
    }
    if(op.second=="==") return a==b;
    if(op.second==">=") return a>=b;
    if(op.second=="<=") return a<=b;
    if(op.second=="!=") return a!=b;
    if(op.second==">") return a>b;
    if(op.second=="<") return a<b;
    if(op.second=="&&") return a&&b;
    if(op.second=="||") return a||b;
    return true;
}

#endif // PARSING_H_INCLUDED
