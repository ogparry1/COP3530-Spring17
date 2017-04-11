#include <iostream>
#include <string>

using namespace std;

int main()
{
	string key = "", hint = "";	// key and hint
	string ficode = "";	// derived forward and reverse order codes
	getline(cin, key);	// get key
	getline(cin, hint);	// get hint
	int icode[key.length()]; // define arrays for forward and reverse indexes
	int icodeIndex = -1, iHold = 0; // index in icode, traversal index
	int next = 0, first = 0; // indexes to compare
	cout << "";	// default output of empty line
	bool event = false;		// states if pattern was found
	cout << "key = " << key << " and hint = " << hint << endl;
	for (int ii = 0; ii <= (int)(key.length()-hint.length()); ii++)
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
				for (int jj = iHold; jj < icodeIndex+1; jj++) // search icode for new rcode insert
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
	cout << ficode << endl << frcode << endl;
	//cout << (ficode.length() <= frcode.length() ? ficode : frcode) << endl;
	//cout << (ficode.length() > frcode.length() ? ficode : frcode);
	return 0;
}

