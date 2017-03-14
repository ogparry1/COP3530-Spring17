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
	string output = str->substr(0, delimiter(str));
	string* temp = str;
	*str = str->substr(delimiter(str)+1, str->length()-1);
	delete temp;
	if (times == 1) return output;
	else return delStr(&output, times-1);
}

class StackObj
{
	public:
		StackObj(string);
		string getValue(string) { return value; };
		double getValue(double) { return atof(value.c_str()); };
		int rank; 
	private:
		string value;
};

StackObj::StackObj(string value)
{
	this->value = value;
	if (value.length() == 1)
	{
		char val = value[0];
		if (val >= 48 && val <= 58) rank = 1;      //1:double
		else if (val == 43 || val == 45) rank = 2; //2:add or subtract
		else if (val == 42 || val == 47) rank = 3; //3:multiply or divide
		else if (val == 40 || val == 41) rank = 4; //4:parenthases
		else cout << "Unrecognized-Character :: line 48" << endl;
	}
}

void StackMath(stack<StackObj> mathStack) //needs a stack parameter
{
	
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
			string F2 = delStr(&expression, 1);
			string F4 = delStr(&expression, 2);
			umap.insert(make_pair(F2, atof(F4.c_str())));
		}
		else
		{
			stack<StackObj> mathStack;
			/*while (Fi != "")
			{
				//if Fi is a var, replace it with value
				//if value is not available, throw error
				//place in stack
				//repeat until expression is empty
			}*/
			StackMath(mathStack);
		}
		
	}
	return 0;
}

