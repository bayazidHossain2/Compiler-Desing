#include <iostream>
#include <regex>
using namespace std;
int main()
{
	string subject("rat\nthe cat\nthe bat");
	smatch match;
	string rg = "m";
	regex rr(rg);
	if(regex_match("jdsf",regex(".*f;"))){
        cout<<"__match "<<endl;
	}else{
        cout<<"__NOt matched"<<endl;
	}
	regex r(".*at");
	int i = 1;
	while (regex_search(subject, match, r)) {
		cout << "\nMatched string is " << match.str(0) << endl
			<< "and it is found at position "
			<< match.position(0)<<endl;
		i++;

		// suffix to find the rest of the string.
		subject = match.suffix().str();
		cout<<"subject is \""<<subject<<"\""<<endl;
	}
    subject = "Best bookseller today!";

    cout<<"\nGroup found : "<<endl;
	if (regex_search(subject, match, regex("book((sel)(ler))"))){

        cout << match[0] << endl;

        cout << match[1] << endl;

        cout << match[2] << endl;

        cout << match[3] << endl;
    }
	return 0;
}
