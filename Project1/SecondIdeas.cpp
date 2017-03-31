#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <climits>
#include <cmath>
#include <cctype>
#include <cassert>

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

int delimiter(string* exp)
{
	for (int ii = 0; ii < (int)(*exp).length(); ii++)
	{
		if ((*exp)[ii] == ' ' || (*exp)[ii] == '	' ) return ii;
	}
	return exp->length();
}

string nextToken(string* str)
{
	string result = "";
	int index = delimiter(str);
	if (index == 0)
	{
		*str = str->substr(1, 10000);
		if (*str == "") return "";
		return nextToken(str);
	}
	else
	{
		if ((*str)[0] == '(')
		{
			result = "(";
			*str = str->substr(1, 10000);
		}
		else if ((*str)[0] == '+')
		{
			result = "+";
			*str = str->substr(2, 10000);
		}
		else if ((*str)[0] == '-')
		{
			result = "-";
			*str = str->substr(2, 10000);
		}
		else if ((*str)[0] == '*')
		{
			result = "*";
			*str = str->substr(2, 10000);
		}
		else if ((*str)[0] == '/')
		{
			result = "/";
			*str = str->substr(2, 10000);
		}
		else if (str->substr(0, 4) == "sin(" || str->substr(0, 4) == "cos(" || str->substr(0, 4) == "log(")
		{
			result = str->substr(0, 4);
			*str = str->substr(4, 10000);
		}
		else if ((*str)[0] == ')')
		{
			if (index == (int)str->length())
			{
				result = ")";
				*str = "";
			}
			else
			{
				result = ")";
				*str = str->substr(1, 10000);
			}
		}
		else if ((*str)[index-1] == ')')
		{
			result = str->substr(0, index-1);
			*str = str->substr(index-1, 10000);
		}
		else
		{
			if (index == (int)str->length())
			{
				result = *str;
				*str = "";
			}
			else
			{
				result = str->substr(0, index);
				*str = str->substr(index, 10000);
			}
		}
	}
	return result;
}

template <class T>
class Deque
{
	public:
		Deque();
		void push(T);
		T fpop();
		T rpop();
		void resize();
		bool isEmpty() { return (size == 0); };
		int getSize() { return size; };
	private:
		T* deque;
		int front, rear;
		int size;
};

template <class T>
Deque<T>::Deque()
{
	deque = new T[20]();
	front = 0;
	rear = 0;
	size = 0;
}

template <class T>
void Deque<T>::push(T num)
{
	if (front == rear && !isEmpty()) resize(); //cout << "resized Deque" << endl;
	deque[front] = num;
	front++;
	size++;
}

template <class T>
T Deque<T>::fpop()
{
	front--;
	size--;
	return deque[front];
}

template <class T>
T Deque<T>::rpop()
{
	rear++;
	size--;
	return deque[rear-1];
}

template <class T>
void Deque<T>::resize()
{
	T* temp = new T[2*size]();
	for (int ii = 0; ii < size; ii++)
	{
		temp[ii] = deque[(rear+ii)%size];
	}
	front = size - 1;
	rear = 0;
	deque = temp;
}

class Mathing
{
	public:
		Mathing();
		double doMath(string*, unordered_map<string, double>*);
		double calcNext(string*, unordered_map<string, double>*);
		bool convert(string*, unordered_map<string, double>*);
	private:
		Deque<double> doubles;
		Deque<char> operands;
		double result;
};

Mathing::Mathing()
{
	result = 0;
	doubles = Deque<double>();
	operands = Deque<char>();
}

bool Mathing::convert (string* token, unordered_map<string, double>* umap)  //converts a variable to its value
{
	if (((*token)[0] >= 'a' && (*token)[0] <= 'z') || ((*token)[0] >= 'A' && (*token)[0] <= 'Z'))//replace token with hashed value
	{
		if (*token != "sin(" && *token != "cos(" && *token != "log(") 
		{
			double tempValue = 0;
			auto tokenValue = umap->find(*token);
			if (tokenValue != umap->end()) 
			{
				tempValue = tokenValue->second;
				*token = to_string(tempValue);
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

double Mathing::calcNext(string* Fx, unordered_map<string, double>* umap)
{
	Mathing math = Mathing();
	string tempNext = nextToken(Fx); //direct token after * or /
	if (!convert(&tempNext, umap)) return INT_MIN; //replaces variables
	if (tempNext == "sin(" || tempNext == "cos(" || tempNext == "log(" || tempNext == "(") //need to start a new stack
	{
		*Fx = tempNext + *Fx; //put it back
		return math.doMath(Fx, umap); //return the calculation with doMath()
	}
	else if (tempNext[0] >= '0' && tempNext[0] <= '9') //tempNext is a double
	{
		if (*Fx != "") //if expression is not over
		{
			string exp = nextToken(Fx); //next token
			if (exp != "^") //if the next token is not ^
			{
				*Fx = exp + " " + *Fx; //put it back
				return atof(tempNext.c_str()); //return the poped number
			}
			else return pow(atof(tempNext.c_str()), calcNext(Fx, umap)); //if it is ^, do the return the power found by recursion
		}
		else return atof(tempNext.c_str()); //if the expression has ended, return the poped double
	}
	else
	{
		cout << "error" << endl;
		return 252;
	}
}

double Mathing::doMath(string* Fx, unordered_map<string, double>* umap)
{
	string token = "";
	while(*Fx != "")
	{
		token = nextToken(Fx);
		if (token == "") break;
		if (!convert(&token, umap)) return INT_MIN;
		if (token == "*" || token == "/" || token == "^")
		{
			double tempValue = 0;
			tempValue = calcNext(Fx, umap);
			if (token == "/" && tempValue == 0)
			{
				return INT_MAX;
			}
			else if ((int)tempValue == INT_MIN) return tempValue;
			else 
			{
				if (token == "*") tempValue = doubles.fpop()*tempValue;
				else if (token == "^") tempValue = pow(doubles.fpop(),tempValue);
				else tempValue = doubles.fpop()/tempValue;
				doubles.push(tempValue);
			}
		}
		else if (token == "sin(") 
		{
			Mathing nested = Mathing();
			doubles.push(sin(nested.doMath(Fx, umap)));
		}
		else if (token == "cos(") 
		{
			Mathing nested = Mathing();
			doubles.push(cos(nested.doMath(Fx, umap)));
		}
		else if (token == "log(") 
		{
			Mathing nested = Mathing();
			doubles.push(log(nested.doMath(Fx, umap)));
		}
		else if (token == "(") 
		{
			Mathing nested = Mathing();
			doubles.push(nested.doMath(Fx, umap));
		}
		else if (token == "+" || token == "-") operands.push((token == "+"?'+':'-'));
		else if (token[0] >= '0' && token[0] <= '9') doubles.push(atof(token.c_str()));
		else if (token == ")") break;
	}
	result = doubles.rpop();
	char operation;
	double next;
	//for (int ii = 0; ii < 3; ii++);
	while(!doubles.isEmpty())
	{
		operation = operands.rpop();
		next = doubles.rpop();
		//cout << result << operation << next << " = " << result + next << endl;
		if (operation == '+') result += next;
		else if (operation == '-') result -= next;
	}
	return result;
}

int main()
{
	/*
	string Fx = "";
	getline(cin, Fx);
	return 0;
	*/
	
	unordered_map<string, double> umap;
	unordered_map<string, double>::iterator it;
	umap.insert(make_pair("Pi", 3.14169));
	umap.insert(make_pair("e", 2.718));
	string constants[] = 
	{"quit", "let", "Pi", "e", "sin", "cos", "log"};					//all unchangable keys
	while (true) //loops inputs
	{
		string Fx = "";
		getline(cin, Fx);  												//input
		Fx = addSpacing(Fx);
		if (Fx == "") continue;											//check empty input
		if (Fx == "quit") break;										//check exit condition
		if (Fx == "Fuck You")
		{
			cout << "                     /´¯/)" << endl;
			cout << "                   ,/¯  /" << endl;
			cout << "                  /    /" << endl;
			cout << "              /´¯/'  '/´¯¯`·¸" << endl;
			cout << "          /'/   /    /   /¨¯\\" << endl;
			cout << "         ('(   ´   ´   ~/'   ')" << endl;
			cout << "          \\            '     /" << endl;
			cout << "..........''...\\.......... _.·´" << endl;
			cout << "............\\..............(" << endl;
			cout << "              \\.............\\" << endl;
			continue;
		}
		if (Fx.substr(0, 3) == "let") 									//check "let"
		{
			Mathing math = Mathing();
			nextToken(&Fx);												//deletes "let "
			string key = nextToken(&Fx);								//sets key to inputVariable
			for (int ii = 0; ii < 7; ii++) 
			{
				if (key == constants[ii]) continue;						//checks key against all constants
			}
			double value = math.doMath(&Fx, &umap);
			if ((int)value == INT_MIN) cout << "Undeclared-Variable" << endl;
			else if ((int)value == INT_MAX) cout << "Division-By-Zero" << endl;
			else if (umap.find(key) != umap.end())
			{
				umap.erase(key);
				umap.insert(make_pair(key, value));
			}
			else umap.insert(make_pair(key, value));					//hashes (key, value)
		}
		else
		{
			Mathing math = Mathing();
			double value = math.doMath(&Fx, &umap);
			if ((int)value == INT_MIN) cout << "Undeclared-Variable" << endl;
			else if ((int)value == INT_MAX) cout << "Division-By-Zero" << endl;
			else cout << value << endl;
		}
	}
	return 0;
}

