#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <climits>
#include <cmath>
#include <cctype>


using namespace std;

string addSpacing(string str)
{
	int index = 0;
	while (index <= (int)str.length())
	{
		if (str[index] == '+' || str[index] == '-' || str[index] == '*' || str[index] == '/' || str[index] == '^')
		{
			str.insert(index, " ");
			str.insert(index+2, " ");
			index = index + 2;
		}
		index++;
	}
	return str;
}

int main()
{
	while(true)
	{
		string Fx = "";
		getline(cin, Fx);
		Fx = addSpacing(Fx);
		cout << Fx << endl;
	}
	return 0;
}

