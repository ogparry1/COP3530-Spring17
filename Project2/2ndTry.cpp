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
		void resize();
		string key, hint, code;
		int *diff, *ffid, *pattern;
		int klen, hlen, codelen, dii, fii;
};

Password::Password(string key, string hint)
{
	this->key = key; this->hint = hint;
	code = "";
	klen = key.length; hlen = hint.length;
	pattern = showPattern(hint.c_str(), hlen);  // O(W)
	int *diff = new int[klen], *ffid = new int[klen];
	dii = 0; fii = 0; codelen = 0;
}

void Password::resize()
{
	int tmp1[dii], tmp2[dii]
	for (int ii = 0; ii < dii; ii++) 
	{
		tmp1[ii] = diff[ii];
		tmp2[ii] = ffid[index-ii];
	}
	diff = tmp1; ffid = tmp2;
}

Password diffid(Password pass)
{
	if (pass.diff[pass.dii] == ffid[pass.fii])
	{
		pass.code = to_string(pass.diff[pass.dii]) + " " + pass.code;
		cout << pass.code << endl;
		if (pass.dii != 0 && pass.fii != 0) pass.codelen = diffid.codelen;
		else pass.length = 1;
		return pass;
	}
	else
	{
		if (pass.dii != 0 && pass.fii != 0)
		{
			Password *pass1 = new Password{pass.code, pass.length}, *pass2 = new Password{pass.code, pass.length};
			pass1.length = pswd(fwd, bkwd, pass.dii-1, pass.fii, pass1).length;
			pass2.length = pswd(fwd, bkwd, pass.dii, pass.fii-1, pass2).length;
			pass.code = (pass1.length > pass2.length ? pass1.code : pass2.code) + " " + pass.code;
			pass.length += (pass1.length > pass2.length ? pass1.length : pass2.length);
			return pass;
		}
		else return 0;
	}
}

string passcode(Password pass)
{
	pass.resize();
	
	return pass.code;
}

int main()
{
	string key = "", hint = "";
	getline(cin, key);
	getline(cin, hint);
	Password code = Password(key, hint);
	int ki = 0, hi = 0, di = 0, temp = -1;
	while (ki < key.length)
	{
		if (key.code[ki] == hint.code[hi])
		{
			ki++;
			hi++;
		}
		if (hi == hint.length)
		{
			if (temp != -1) diff[di++] = (ki-hi) - temp;
			temp = ki - hi;
			hi = pattern[hi-1];
		}
		else if (ki < key.length && key.code[ki] != hint.code[hi])
		{
			if (hi != 0) hi = pattern[hi-1];
			else ki++;
		}
	}
	cout << password(diff, di-1);
	
	return 0;
}
