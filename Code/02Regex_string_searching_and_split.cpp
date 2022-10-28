#include <iostream>
#include <regex>
using namespace std;
int main()
{
	string subject("rat\nthe cat\nthe bat");
	smatch match;
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
	return 0;
}
