#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cmath>

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
		int* makediff();
		string key, hint, code;
		int* diff; int* pattern;
		int klen, hlen, codelen, dii;
};

Password::Password(string key, string hint)
{
	// from main or diffid
	this->key = key; this->hint = hint;
	dii = 0; codelen = 0; code = "";
	klen = key.length(); hlen = hint.length();
	pattern = new int[hlen];
	showPattern(hint.c_str(), hlen, pattern);  // O(W)
	diff = makediff();
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

int max(int x, int y)
{
	if (x > y) return x;
	else return y;
}

string diffid(Password pass) // compares diff and ffid
{
	pass.dii++;
	int LCSmatrix[(int)pow(pass.dii, 2)];
	string result = "";
	int i = 0, ii = 0, jj = 0;
	while (i < (int)pow(pass.dii, 2))
	{
		ii = floor(i/pass.dii); jj = (i%pass.dii);
		if (ii == 0 || jj == 0) LCSmatrix[i] = 0;
		else if (pass.diff[jj-1] == pass.diff[pass.dii-ii-1]) LCSmatrix[i] = LCSmatrix[i-pass.dii-1] + 1;
		else LCSmatrix[i] = max(LCSmatrix[i-1], LCSmatrix[i-pass.dii]);
		i++;
	}
	i--;
	while (true)
	{
		int ii = floor(i/pass.dii), jj = (i%pass.dii);
		if (ii == 0 || jj == 0) break;
		if ((LCSmatrix[i-1] == LCSmatrix[i-pass.dii]) && (LCSmatrix[i-pass.dii] == LCSmatrix[i-pass.dii-1]))
		{
			if (LCSmatrix[i] > LCSmatrix[i-pass.dii-1]) result = to_string(pass.diff[jj-1]) + " " + result;
			i = i-pass.dii-1;
		}
		else
		{
			if (LCSmatrix[i-1] > LCSmatrix[i-pass.dii]) i--;
			else i = i-pass.dii;
		}
	}
	return result;
}

int main()
{
	int start = 1, end = 8;
	cin >> start >> end;
	for (int ii = start; ii <= end; ii++)
	{
		printf("Iteration:: %i\n", ii);
		string key = "", hint = "", correctAnswer = "", answer = "";
		ifstream input, output;
		string file1 = "/home/ogparry1/Documents/School/Classes/COP3530/Assignments/Project2/input" + to_string(ii) + ".txt";
		string file2 = "/home/ogparry1/Documents/School/Classes/COP3530/Assignments/Project2/output" + to_string(ii) + ".txt";
		input.open(file1);
		output.open(file2);
		getline(input, key);
		getline(input, hint);
		getline(output, correctAnswer);
		Password result = Password(key, hint);
		answer = diffid(result);
		printf("Correct Answer   :: %s\n", correctAnswer.c_str());
		printf("Calulated Answer :: %s\n\n", answer.c_str());
	}
	return 0;
}
