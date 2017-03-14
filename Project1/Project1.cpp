#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

int min(int x, int y)
{
	return (x < y?x:y);
}

int delimiter(string* exp)
{
	int x = exp->find("(");
	int y = exp->find(")");
	int z = exp->find(" ");
	return min(x, min(y, z));
}

string delStr(string* str, int times)
{
	if (times == 1) return str->substr(0, delimiter(str));
	else 
	{
		string temp = str->substr(delimiter(str)+1, str->length()-1);
		return delStr(&temp, times-1);
	}
}

int main()
{
	unordered_map<string, double> umap;
	unordered_map<string, double>::iterator it;
	umap.insert(make_pair("Pi", 3.14169));
	umap.insert(make_pair("e", 2.718));
	while (true) //loops inputs
	{
	string expression = "";
	getline(cin, expression);  //input
	if (expression == "quit") break;
	string F1 = delStr(&expression, 1); //delimit F1
	cout << F1 << endl;
	if (F1 == "let") //check "let"
	{
		//string F2 = 
		//make var and continue
	}
	else
	{
		/*while (Fi != "")
		{
			//if Fi is a var, replace it with value
			//if value is not available, throw error
			//place in stack
			//repeat until expression is empty
		}*/
	}
	//do math
	}
	return 0;
}

