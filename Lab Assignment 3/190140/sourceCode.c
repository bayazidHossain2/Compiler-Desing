#include<stdio.h>
#include<conio.h>a
#define pi   3.14159

int main(){
    int a,b,c;
    a=3;
    b=5;
    c=(a+b)/2;
    printf("value of a = %d and value of b = %d ",a,b);
    printf("average of a and b is = %d ",c);

    if(a<=b){
        c=2*c;
    }
    printf("after updating value of c is = %d ",c);
    printf("value of constant variable pi is : %lf",pi);


    return 0;
}
