#include <iostream>
#include <string>

using namespace std;

int main()
{
	string key = "", rkey = "", hint = "";
	string icode = "", rcode = "";
	getline(cin, key);
	getline(cin, hint);
	int code[4] = {-1, -1, -1, -1};
	cout << "";
	for (int ii = key.length()-1; ii >= 0; ii--) 
	{
		rkey += key[ii];
	}
	for (int ii = 0; ii <= (int)(key.length()-hint.length()); ii++)
	{
		if (key.substr(ii, hint.length()) == hint)
		{
			code[1] = ii;
			if (ii != 0)
			{
				if (code[0] >= 0) 
				{
					int diff = code[1] - code[0];
					icode = icode + to_string(diff) + " ";
				}
				code[0] = code[1];
			}
			else code[0] = code[1];
		}
		if (rkey.substr(ii, hint.length()) == hint)
		{
			code[3] = ii;
			if (ii != 0)
			{
				if (code[2] >= 0) 
				{
					int diff = code[3] - code[2];
					rcode = rcode + to_string(diff) + " ";
				}
				code[2] = code[3];
			}
			else code[2] = code[3];
		}
	}
	cout << (icode.length() > rcode.length() ? icode : rcode);
	return 0;
}

