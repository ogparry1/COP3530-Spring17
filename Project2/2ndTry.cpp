#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

int* showPattern(const char* hint, int length)  //shows the pattern of hint
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

class Password  // class that holds the all provided info
{
	public:
		Password(string, string);
		Password(Password, int, int);
		void resize();
		void makediff();
		string key, hint, code;
		int *diff, *ffid, *pattern;
		int klen, hlen, codelen, dii, fii;
};

Password::Password(string key, string hint)
{
	this->key = key; this->hint = hint;
	code = "";
	klen = key.length(); hlen = hint.length();
	pattern = showPattern(hint.c_str(), hlen);  // O(W)
	diff = new int[klen], ffid = new int[klen];
	dii = 0; fii = 0; codelen = 0;
	makediff();
}

void Password::resize() //resizes the arrays of diff and ffid to fit their data
{
	int tmp1[dii], tmp2[dii];
	for (int ii = 0; ii < dii; ii++) 
	{
		tmp1[ii] = diff[ii];
		tmp2[ii] = ffid[dii-ii];
	}
	diff = tmp1; ffid = tmp2;
	dii--; fii = dii;
}

void Password::makediff()
{
	int ki = 0, hi = 0, temp = -1;
	while (ki < klen)
	{
		if (key[ki] == hint[hi])
		{
			ki++;
			hi++;
		}
		if (hi == hlen)
		{
			if (temp != -1) diff[dii++] = (ki-hi) - temp;
			temp = ki - hi;
			hi = pattern[hi-1];
		}
		else if (ki < klen && key[ki] != hint[hi])
		{
			if (hi != 0) hi = pattern[hi-1];
			else ki++;
		}
	}
	resize();
}

Password diffid(Password pass) // compares diff and ffid
{
	if (pass.diff[pass.dii-1] == pass.ffid[pass.fii-1])
	{
		pass.code = to_string(pass.diff[pass.dii]) + " " + pass.code;
		if (pass.dii != 0 && pass.fii != 0) 
		{
			pass.dii--; pass.fii--;
			pass.codelen += 1 + diffid(pass).codelen;
		}
		else pass.codelen += 1;
		return pass;
	}
	else
	{
		if (pass.dii != 0 && pass.fii != 0)
		{
			Password pass1 = Password(pass), pass2 = Password(pass);
			pass1.dii--; pass2.fii--;
			pass1 = diffid(pass1); pass2 = diffid(pass2);
			pass.code = (pass1.codelen > pass2.codelen ? pass1.code : pass2.code) + " " + pass.code;
			pass.codelen += (pass1.codelen > pass2.codelen ? pass1.codelen : pass2.codelen);
		}
		return pass;
	}
}

int main()
{
	string key = "", hint = "";
	getline(cin, key);
	getline(cin, hint);
	Password result = Password(key, hint);
	diffid(result);
	cout << result.code;
	return 0;
}
