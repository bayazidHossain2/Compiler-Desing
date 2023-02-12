#include<iostream>
#include"constants.h"
#include"castom_function.h"
#include"Lexical_Analysis.h"
#include"parsing.h"

using namespace std;
int main(){
    //freopen("01output.txt","w",stdout);
    string fileName="sourceCode.c";
    Lexer(fileName);

    /*for(int i=0;i<tokens.size();i++){
        cout<<i<<' '<<line_number_from_token_number[i]<<' '<<tokens[i].first<<' '<<tokens[i].second<<endl;
    }*/
    Parser();
    return 0;
}
