#include <iostream>
#include <string>

using namespace std;



char* StoC(string str)
{
	const char* convert = str.c_str();
	return (char*)convert;
}

int* showPattern(char* hint, int length)
{
	int pattern[length];
	int ii = 1;
	while (ii < length)
	{
		if ()
	}
	return pattern;
}

int main()
{
	string tmp = "";
	getline(cin, tmp);
	int keylength = tmp.length();
	char* key = StoC(tmp);
	getline(cin, tmp);
	int hintlength = tmp.length();
	char* hint = StoC(tmp);
	int* pattern = showPattern(hint, hintlength);  // O(W)
	
	
	return 0;
}
