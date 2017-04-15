#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Passcode
{
	string code;
	int length;
};

Passcode* pswd(int* fwd, int* bkwd, int findex, int bindex, Passcode* pass)
{
	if (fwd[findex] == bkwd[bindex])
	{
		pass->code = to_string(fwd[findex]) + " " + pass->code;
		if (findex != 0 && bindex != 0) pass->length = pswd(fwd, bkwd, findex-1, bindex-1, pass)->length;
		else pass->length = 1;
		return pass;
	}
	else
	{
		if (findex != 0 && bindex != 0)
		{
			Passcode pass1 = *pass, pass2 = *pass;
			pass1.length = pswd(fwd, bkwd, findex-1, bindex, &pass1)->length;
			pass2.length = pswd(fwd, bkwd, findex, bindex-1, &pass2)->length;
			pass->code = (pass1.length > pass2.length ? pass1.code : pass2.code) + " " + pass->code;
			pass->length += (pass1.length > pass2.length ? pass1.length : pass2.length);
			return pass;
		}
		else return 0;
	}
}

string password(int* code, int index)
{
	int *diff = new int[index+1], *ffid = new int[index+1];
	Passcode* pass;
	for (int ii = 0; ii <= index; ii++) 
	{
		diff[ii] = code[ii];
		ffid[ii] = code[index-ii];
	}
	pswd(diff, ffid, index, index, pass);
	return pass->code;
}

char* StoC(string str)
{
	const char* convert = str.c_str();
	return (char*)convert;
}

int* showPattern(char* hint, int length)
{
	int* pattern = new int[length];
	int ii = 1, last = 0;
	while (ii < length)
	{
		if (hint[ii] == hint[last])
		{
			last++;
			pattern[ii] = last;
			ii++;
		}
		else
		{
			if (last != 0)
			{
				last = pattern[last-1];
			}
			else
			{
				pattern[ii] = 0;
				ii++;
			}
		}
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
	int* diff = new int[keylength];
	int ki = 0, hi = 0, di = 0, temp = -1;
	while (ki < keylength)
	{
		if (key[ki] == hint[hi])
		{
			ki++;
			hi++;
		}
		if (hi == hintlength)
		{
			if (temp != -1) diff[di++] = (ki-hi) - temp;
			temp = ki - hi;
			hi = pattern[hi-1];
		}
		else if (ki < keylength && key[ki] != hint[hi])
		{
			if (hi != 0) hi = pattern[hi-1];
			else ki++;
		}
	}
	cout << password(diff, di-1);
	
	return 0;
}
