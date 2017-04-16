#include <iostream>
#include <string>

using namespace std;

void showPattern()
{
	
}

int main()
{
	string key = "", hint = "";	// key and hint
	string ficode = "", frcode = "";	// derived forward and reverse order codes
	getline(cin, key);	// get key
	getline(cin, hint);	// get hint
	int icode[key.length()]; // define arrays for forward and reverse indexes
	int icodeIndex = -1, next = -1, first = -1, posi = 0, posr = 0; // index in icode, traversal index, indexes to compare
	cout << "";	// default output of empty line
	for (int ii = 0; ii <= (int)(key.length() - hint.length()); ii++)
	{
		if (key.substr(ii, hint.length()) == hint) // finds hint across forward key
		{
			next = ii;
			if (next >= 0 && first >= 0) 
			{
				int diff = next - first;
				icode[++icodeIndex] = diff;
			}
			first = next;
		}
	}
	int rcode[icodeIndex+1];
	for (int ii = 0; ii <= icodeIndex; ii++) { rcode[ii] = icode[icodeIndex-ii]; }
	for (int ii = 0; ii <= icodeIndex; ii++)
	{
		for (int jj = posi; jj <= icodeIndex; jj++)
		{
			if (icode[ii] == rcode[jj])
			{
				ficode += to_string(rcode[jj]) + " ";
				posi = jj+1;
				break;
			}
		}
		for (int jj = posr; jj <= icodeIndex; jj++)
		{
			if (rcode[ii] == icode[jj])
			{
				frcode += to_string(icode[jj]) + " ";
				posr = jj+1;
				break;
			}
		}
	}
	cout << (ficode.length() > frcode.length() ? ficode : frcode);
	return 0;
}

