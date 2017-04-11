#include <iostream>
#include <string>

using namespace std;

int main()
{
	string key = "", hint = "";
	getline(cin, key);
	getline(cin, hint);
	int code[key.length()];
	int index = 0;
	cout << "";
	for (int ii = 0; ii <= (int)(key.length()-hint.length()); ii++)
	{
		if (key.substr(ii, hint.length()) == hint)
		{
			code[index] = ii;
			if (index != 0) 
			{
				cout << code[index] - code[index-1] << " ";
			}
			index++;
		}
	}
	return 0;
}

