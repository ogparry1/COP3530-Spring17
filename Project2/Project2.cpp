#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>

using namespace std;

void showPattern(const char* hint, int length, int* pattern)  //shows the pattern of hint
{
	// from Password constructor
	int last = 0, ii = 1;
	pattern[0] = 0;
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
	// to Password constructor
}

class Password  // class that holds the all provided info
{
	public:
		Password(string, string);
		Password(Password, int, int);
		void reverse(int*);
		int* makediff();
		string key, hint, code;
		int* diff; int* ffid; int* pattern;
		int klen, hlen, codelen, dii, fii;
};

Password::Password(string key, string hint)
{
	// from main or diffid
	this->key = key; this->hint = hint;
	dii = 0; fii = 0; codelen = 0; code = "";
	klen = key.length(); hlen = hint.length();
	pattern = new int[hlen];
	showPattern(hint.c_str(), hlen, pattern);  // O(W)
	reverse(makediff());
}

void Password::reverse(int* differences) //resizes the arrays of diff and ffid to fit their data
{
	// from makediff
	fii = dii;
	diff = new int[dii]; ffid = new int[fii];
	for (int ii = 0; ii < dii; ii++) 
	{
		diff[ii] = differences[ii];
		ffid[ii] = differences[dii-ii-1];
	}
	// to main or diffid
}

int* Password::makediff()
{
	// from Password constructor
	int ki = 0, hi = 0, temp = -1;
	int* differences = new int[klen];
	while (ki < klen)
	{
		if (key[ki] == hint[hi])
		{
			ki++;
			hi++;
		}
		if (hi == hlen)
		{
			if (temp != -1) 
			{
				differences[dii] = (ki-hi) - temp;
				dii++;
			}
			temp = ki - hi;
			hi = pattern[hi-1];
		}
		else if (ki < klen && key[ki] != hint[hi])
		{
			if (hi != 0) hi = pattern[hi-1];
			else ki++;
		}
	}
	return differences;
}

Password diffid(Password pass) // compares diff and ffid
{
	// from main or diffid
	cout << "Diff:: ";
	for (int ii = 0; ii < pass.dii; ii++) 
	{
		printf("%i ", pass.diff[ii]);
	}
	cout << endl << "FFid:: ";
	for (int ii = 0; ii < pass.fii; ii++) 
	{
		printf("%i ", pass.ffid[ii]);
	}
	cout << endl;
	printf("(%i, %i)\n", pass.diff[pass.dii-1], pass.ffid[pass.fii-1]);
	if (pass.diff[pass.dii-1] == pass.ffid[pass.fii-1])
	{
		printf("Code:: adding %s to %s\n\n", to_string(pass.diff[pass.dii-1]).c_str(), pass.code.c_str());
		pass.code = to_string(pass.diff[pass.dii-1]) + " " + pass.code;
		if (pass.dii-1 != 0 && pass.fii-1 != 0) 
		{
			pass.dii--; pass.fii--;
			pass.codelen += 1 + diffid(pass).codelen;
		}
		else 
		{
			pass.codelen += 1;
			cout << endl << "Hit Base with code = " << pass.code << endl;
		}
		cout << endl << "Returning " << pass.code << endl;
		return pass;
	}
	else // pass.diff[pass.dii] != pass.ffid[pass.fii]
	{
		if (pass.dii-1 != 0 && pass.fii-1 != 0)
		{
			Password pass1 = Password(pass), pass2 = Password(pass);
			pass1.dii--; pass2.fii--;
			pass1 = diffid(pass1); pass2 = diffid(pass2);
			pass.code = (pass1.codelen > pass2.codelen ? pass1.code : pass2.code) + " " + pass.code;
			pass.codelen += (pass1.codelen > pass2.codelen ? pass1.codelen : pass2.codelen);
		}
		cout << endl << "Returning " << pass.code << endl;
		return pass;
	}
	// to main
}

int main()
{
	string key = "", hint = "";
	getline(cin, key);
	getline(cin, hint);
	Password result = Password(key, hint);
	cout << diffid(result).code;
	return 0;
}
