#include <iostream>
#include <string>

using namespace std;

int main()
{
	string key = "", hint = "", rkey = "", rhint = "";
	string ficode = "", frcode = "", finalcode = "";
	getline(cin, key);
	getline(cin, hint);
	int icode[key.length()], rcode[key.length()];
	int iIndex = -1, rIndex = -1;
	int code[4] = {-1, -1, -1, -1};
	cout << "";
	for (int ii = key.length()-1; ii >= 0; ii--) 
	{
		if (ii <= (int)hint.length()-1) rhint += hint[ii];
		rkey += key[ii];
	}
	bool statement = false;
	for (int ii = 0; ii <= (int)(key.length()-hint.length()); ii++)
	{
		if (key.substr(ii, hint.length()) == hint) //finds hint across forward code
		{
			code[1] = ii;
			if (code[1] >= 0 && code[0] >= 0) 
			{
				int diff = code[1] - code[0];
				icode[iIndex++] = diff;
			}
			code[0] = code[1];
			statement = true;
		}
		if (rkey.substr(ii, rhint.length()) == rhint) //finds hint across reverse code
		{
			code[3] = ii;
			if (code[3] >= 0 && code[2] >= 0) 
			{
				int diff = code[3] - code[2];
				rcode[rIndex++] = diff;
			}
			code[2] = code[3];
			statement = true
		}
		if (iIndex >= 0 && rIndex >= 0 && statement)
		{
			if ()// creates longest finalcode comparing icode to rcode
			{
				
			}
			if ()// creates longest finalcode comparing rcode to icode
			{
				
			}
		}
		
	}
	string finalcode = "";
	for (int ii = 0; ii < (int)icode.length(); ii++)
	{
		for (int jj = 0; jj < (int)icode.length(); jj++)
		{
			if () finalcode += rcode[jj] ;
		}
	}
	cout << (icode.length() <= rcode.length() ? icode : rcode) << endl;
	cout << (icode.length() > rcode.length() ? icode : rcode);
	return 0;
}

