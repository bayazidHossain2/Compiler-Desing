#include<bits/stdc++.h>
using namespace std;
#define ll long long


string header[]={"#include<stdio.h>",
"#include<conio.h>",
"#include<stdlib.h>",
"#include<math.h>",
"#include<string.h>",
"#include<ctype.h>",
"#include<time.h>",
"#include<float.h>",
"#include<limits.h>",
"#include<wctype.h>",
"#include<stdio.hp>"
};

string key[]={"auto","double","int","long","char","float","scanf","printf"};
string var[100];
int va=0,finish=0;



int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   ll n,m,i,j,k,l,a,b,c,p,q,r,t,ans,sum,serial=0,main;
   string x;
   ifstream file("compiler design.txt");
   main=0;
   p=-6;
   while(getline(file,x))
   {
       serial++;
//       cout<<code<<endl;
       char code[100];
       for(i=0;i<x.size();i++)
       {
           code[i]=x[i];
       }
       code[i]='\0';
       l=strlen(code);
       cout<<code<<" "<<l<<endl;
       l=strlen(code);
       j=0,a=0;
       for(i=0;i<l;i++)
       {
           if(a==0)
           {
               if(code[i]==' ')
                continue;
                a=1;
                code[j++]=code[i];
           }
           else
           {
               code[j++]=code[i];
           }
       }
       code[j]='\0';
        l=strlen(code);
      //cout<<code<<" "<<l<<endl;


       for(i=l-1;i>=0;i--)
       {
           if(code[i]==' ')
            code[i]='\0';

           else break;
       }
       l=strlen(code);
       //cout<<code<<" "<<l<<endl;

if(strlen(code)==0)
{
    continue;
}

//cout<<code<<endl;


/// Header solve.............
       j=0;

       if(code[0]=='#')
       {
           a=0;
           code[j++]='#';
           for(i=1;i<l;i++)
           {
               if(code[i]=='<')
               {
                   code[j++]=code[i];
                   a=10;
               }
              else if(code[i-2]=='.' && code[i-1]=='h')
              {
                 for(;i<l;i++)
                 {
                     if(code[i]==' ')
                     {
                         continue;
                     }
                     else
                     {
                         code[j++]=code[i];
                         break;
                     }
                 }
              }
              else if(a==0)
               {
                   if(code[i]==' ')
                   {
                       continue;
                   }
                   a=1;
                   code[j++]=code[i];
               }
               else if(a<7)
               {
                   code[j++]=code[i];
                   a++;
                   if(a==7) a=0;
               }
               else
               {
                   code[j++]=code[i];
               }
           }
           code[j]='\0';

           a=0;
           for(int i=0;i<11;i++)
            {
                if(code==header[i])
                {
                    a=1;
                }
            }
            if(a==0 )
            {
                cout<<serial<<" number line header problem"<<endl;
            }
            continue;



       }

       //cout<<code<<endl;













/// main function.........



   char y[100];
    j=0;
    //cout <<"main "<< main<<endl;
    if(main==0)
    {
        a=0;
        for(i=0;i<l;i++)
        {
            if(code[i]==' ')
               {
                 a=1;
               }
            else if(a==0)
             y[j++]=code[i];
             else
             {
                 break;
             }
        }
        y[j]='\0';

       // cout<<y<<" "<<strlen(y)<<endl;

        if(y[0]='i' && y[1]=='n' && y[2]=='t' )
        {
           // cout<<"###"<<endl;
            j=0;
            if(code[i]=='m' && code[i+1]=='a' && code[i+2]=='i' && code[i+3]=='n')
            {
                i=i+4;
                for(;i<l;i++)
                {
                    if(code[i]!=' ')
                    {
                        y[j++]=code[i];
                    }
                }
                y[j]='\0';
                if(y[0]=='(' && y[1]==')')
                {
                     main=1;
                     p=serial;
                     continue;
                }
                else
                {
                    cout<<serial<<" number line Error exist in main function"<<endl;
                    continue;
                }

            }
            else
            {
                cout<<serial<<" number line Error  main function was not declear"<<endl;
                continue;
            }
        }
        else
        {
            cout<<serial<<" number line Error  main function was not declear"<<endl;
            continue;
        }



    }
    //cout<<"###"<<" "<<main<<" "<<serial<<" "<<p+1<<endl;
    if(main==1 && serial == p+1)
    {
       // cout<<"###"<<" "<<main<<" "<<serial<<" "<<p+1<<endl;
       j=0;
       for(i=0;i<l;i++)
       {
           if(code[i]!=' ')
           {
               y[j++]=code[i];
           }
       }
       y[j]='\0';
        //cout<<y<<endl;
        if(strlen(y)==1 && y[0]=='{')
            {
                 main=2;
                continue;
            }
            else
            {
                cout<<serial<<"number line error after main function must need 2nd bracket"<<endl;
                continue;
            }




    }
    if(finish==1)
    {
        cout<<serial<<"number line error "<<endl;
        continue;
    }
   // cout<<main<<endl;
    if(main==2 )
    {
        if(code[0]=='}' && strlen(code)==1)
        {
            finish=1;
            continue;
        }

        //cout<<code[l-1]<<" ## "<<code<<" "<<l<<endl;
         if(code[l-1]!=';')
            {
                cout<<serial<<" number line error for semicolon  "<<code<<endl;
                continue;
            }
        j=0;
        for(i=0;i<l;i++)
        {
            if(code[i]==' ')
            {
                break;
            }
            y[j++]=code[i];
        }
        y[j]='\0';
        a=0;
       // cout<<y<<endl;
        for(k=0;k<8;k++)
        {
            //cout<<y<<" "<<key[k]<<endl;
            if(y==key[k])
            {
                a=1;
                break;
            }
        }
        //cout<<a<<endl;
        if(a==0)
            {
                int pp=0;
                if(strlen(y)>=5)
                {
                    if(y[0]=='s' && y[1]=='c'&& y[2]=='a' && y[3]=='n' && y[4]=='f')
                    {
                        for(k=5;k<l;k++)
                        {
                            if(y[k]==' ')
                                continue;

                            if(pp==0 && y[k]=='(')
                            {
                                pp=1;
                                continue;

                            }
                            else if(pp==1)
                            {

                            }
                        }
                    }
                }



                cout<<serial<<" number line error for data type  "<<endl;
                continue;
            }
       else if(a==1)
        {
            for(;i<l;i++)
            {
                if(code[i]==' ')
                    continue;
                    break;

            }
            j=0;
            //cout<<j<<endl;
            for(k=l-2;k>=i;k--)
            {
              if(code[k]==',')
                {
                    y[j]='\0';
                    //cout<<y<<endl;
                    var[va++]=y;
                    j=0;
                    continue;
                }

              y[j++]=code[k];

            }
            y[j]='\0';
            var[va++]=y;
            //cout<<y<<endl;
            b=0;

            for(i=0;i<va;i++)
            {
                p=0;
               // cout<<var[i]<<"##"<<endl;
                for(k=0;i<var[i].size();k++)
                {
                    if(var[i][k]!=' ')
                        break;
                }
                if((var[i][k]>=65 && var[i][k]<=90)|| (var[i][k]>=97 && var[i][k]<=122)|| (var[i][k]=='_'))
                {
                    k++;
                    q=k;
                    for(k=var[i].size()-1;k>=q;k--)
                    {
                        if(p==0 && var[i][k]==' ' )
                            continue;
                        if((var[i][k]>=65 && var[i][k]<=90)|| (var[i][k]>=97 && var[i][k]<=122)|| (var[i][k]>=48 && var[i][k]<=57) || (var[i][k]=='_')||var[i][k]=='$')
                        {
                            p=1;
                            continue;
                        }
                        else
                        {
                            //cout<<var[i]<<endl;

                            b=1;
                            break;
                        }
                    }
                }
                else
                {
                    b=1;
                }
                if(b==1)
                {
                    break;
                }
            }
            if(b==1)
            {
                cout<<serial<<" number line error for variable  "<<code<<endl;
                continue;
            }
    }
    }

   }
   file.close();

    return 0;

}
