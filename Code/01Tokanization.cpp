#include<iostream>
#include<fstream>

using namespace std;
int main(){
    int sum = 0;
    int x;
    ifstream inFile;

    inFile.open("source.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    while (inFile >> x) {
        sum = sum + x;
        cout<<x<<endl;
    }

    inFile.close();
    cout << "Sum = " << sum << endl;
    return 0;
}
