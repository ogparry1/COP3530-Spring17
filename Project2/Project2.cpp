#include <iostream>
#include <string>

using namespace std;

int main()
{
	string key = "", hint = "", rkey = "", rhint = "";	// keys and hints
	string ficode = "", frcode = "";	// derived forward and reverse order codes
	getline(cin, key);	// get key
	getline(cin, hint);	// get hint
	int icode[key.length()], rcode[key.length()];	// define arrays for forward and reverse indexes
	int icodeIndex = -1, rcodeIndex = -1;	// index in icode and rcode
	int iHold = 0, rHold = 0; // traversal indexes
	int code[4] = {-1, -1, -1, -1};		// indexes to compare
	cout << "";		// default output of empty line
	for (int ii = key.length()-1; ii >= 0; ii--) // build rkey and rhint
	{
		if (ii <= (int)hint.length()-1) rhint += hint[ii];
		rkey += key[ii];
	}
	bool event = false;		// states if pattern was found
	for (int ii = 0; ii <= (int)(key.length()-hint.length()); ii++)
	{
		if (key.substr(ii, hint.length()) == hint) // finds hint across forward key
		{
			code[1] = ii;
			if (code[1] >= 0 && code[0] >= 0) 
			{
				int diff = code[1] - code[0];
				icode[++icodeIndex] = diff;
			}
			code[0] = code[1];
			event = true;
		}
		if (rkey.substr(ii, rhint.length()) == rhint) // finds hint across reverse key
		{
			code[3] = ii;
			if (code[3] >= 0 && code[2] >= 0) 
			{
				int diff = code[3] - code[2];
				rcode[++rcodeIndex] = diff;
			}
			code[2] = code[3];
			event = true;
		}
		if (icodeIndex >= 0 && rcodeIndex >= 0 && event) // creates longest final code comparing icode to rcode
		{
			if (key.substr(ii, hint.length()) == hint) // if event occurs in icode
			{
				for (int jj = rHold; jj < rcodeIndex+1; jj++) // search rcode for new icode insert
				{
					if (icode[icodeIndex] == rcode[jj])
					{
						ficode = ficode + to_string(icode[icodeIndex]) + " ";
						rHold = jj + 1;
						break;
					}
				}
			}
			if (rkey.substr(ii, rhint.length()) == rhint)// if event occurs in rcode
			{
				for (int jj = iHold; jj < icodeIndex+1; jj++) // search rcode for new icode insert
				{
					if (rcode[rcodeIndex] == icode[jj])
					{
						frcode = frcode + to_string(rcode[rcodeIndex]) + " ";
						iHold = jj + 1;
						break;
					}
				}
			}
			event = false;
		}
	}
	cout << (ficode.length() <= frcode.length() ? ficode : frcode) << endl;
	cout << (ficode.length() > frcode.length() ? ficode : frcode);
	return 0;
}

