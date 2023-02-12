#include<bits/stdc++.h>
using namespace std;
/*
production rule
S--->+SS|-SS|a
*/
int i=0;
string str;
void S();
int main()
{
   while(cin>>str){
   i=0;
   int len=str.size();
   str+='$';
   S();
   if(i==len)
   {
       cout<<"string is accepted"<<endl;
   }
    else
    {
        cout<<"NOT accepted"<<endl;
    }

   }



return 0;
}
void S()
{
  if(str[i]=='+'||str[i]=='-')
  {
      i++;
      S();
      S();
  }
  else if(str[i]=='a')
  {
      i++;
  }else{
    i++;
  }
}
