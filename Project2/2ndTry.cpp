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
		if (hi == hintlength)
		{
			if (temp != -1)
			{
				diff[di] = (ki-hi) - temp;
				di++;
			}
			temp = ki - hi;
		}
		
		if (key[ki] == hint[hi])
		{
			ki++;
			hi++;
		}
		else
		{
			if (hi != 0) hi = pattern[hi-1];
			else
			{
				ki++;
			}
		}
	}
	
	return 0;
}
