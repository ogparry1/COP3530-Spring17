#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <climits>
#include <cmath>

using namespace std;

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
	cout << *str << endl;
	int index = delimiter(str);
	cout << "index = " << index << " and length = " << str->length() << endl;
	if (index == 0)
	{
		*str = str->substr(1, 10000);
		return nextToken(str);
	}
	else
	{
		if ((*str)[0] == '(')
		{
			result = "(";
			*str = str->substr(1, 10000);
			cout << result << " added" << endl;
		}
		else if ((*str)[0] == '+')
		{
			result = "+";
			*str = str->substr(2, 10000);
			cout << result << " added" << endl;
		}
		else if ((*str)[0] == '-')
		{
			result = "-";
			*str = str->substr(2, 10000);
			cout << result << " added" << endl;
		}
		else if ((*str)[0] == '*')
		{
			result = "*";
			*str = str->substr(2, 10000);
			cout << result << " added" << endl;
		}
		else if ((*str)[0] == '/')
		{
			result = "/";
			*str = str->substr(2, 10000);
			cout << result << " added" << endl;
		}
		else if (str->substr(0, 4) == "sin(" || str->substr(0, 4) == "cos(" || str->substr(0, 4) == "log(")
		{
			result = str->substr(0, 4);
			*str = str->substr(4, 10000);
			cout << result << " added" << endl;
		}
		else if ((*str)[index-1] == ')')
		{
			if (index == (int)str->length())
			{
				result = *str;
				*str = "";
			}
			else
			{
				result = str->substr(0, index-1);
				*str = str->substr(index-1, 10000);
			}
			cout << result << " added" << endl;
		}
		else if ((*str)[0] == ')')
		{
			result = ")";
			*str = str->substr(2, 10000);
			cout << result << " added" << endl;
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
	if (front == rear && !isEmpty()) resize();
	deque[front] = num;
	front++;
}

template <class T>
T Deque<T>::fpop()
{
	front--;
	return deque[front];
}

template <class T>
T Deque<T>::rpop()
{
	return deque[rear++];
}

template <class T>
void Deque<T>::resize()
{
	T* temp = new T[2*size]();
	for (int ii = 0; ii < size; ii++)
	{
		temp[rear+ii] = deque[(rear+ii)%size];
		front = rear+ii;
	}
	deque = temp;
}

class Mathing
{
	public:
		Mathing();
		double doMath(string*);
		void printMath(string* Fx) { cout << doMath(Fx) << endl; };
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

double Mathing::doMath(string* Fx)
{
	string token = "";
	while(*Fx != "")
	{
		token = nextToken(Fx);
		//cout << token << endl;
		if (token[0] >= '0' || token[0] <= '9') doubles.push(atof(token.c_str()));
		else if (token == "*" || token == "/")
		{
			string tempNext = nextToken(Fx);
			if (tempNext == "sin" || tempNext == "cos" || tempNext == "log" || tempNext == "(")
			{
				*Fx = tempNext + *Fx;
				double tempValue = doMath(Fx);
				if (token == "/" && tempValue == 0)
				{
					cout << "Division-By-Zero" << endl;
				}
				else 
				{
					((token == "*") ? doubles.push(doubles.fpop()*tempValue) : doubles.push(doubles.fpop()/tempValue));
				}
			}
		}
		else if (token == "+" || token == "-") operands.push((token == "+"?'+':'-'));
		else if (token == "sin(") doubles.push(sin(doMath(Fx)));
		else if (token == "cos(") doubles.push(cos(doMath(Fx)));
		else if (token == "log(") doubles.push(log(doMath(Fx)));
		else if (token == "(") doubles.push(doMath(Fx));
		else if (token == ")") break;
	}
	//if (doubles.isEmpty()) exit(189);
	result = doubles.rpop();
	while(!doubles.isEmpty())
	{
		//rpop all pieces doing their respective +/-
		char operation = operands.rpop();
		if (operation == '+') result += doubles.rpop();
		else result -= doubles.rpop();
	}
	if (!operands.isEmpty()) exit(198);
	return result;
}

int main()
{
	/*string Fx = "";
	getline(cin, Fx);
	cout << delimiter(&Fx) << endl;
	return 0;*/
	
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
		if (Fx == "quit") break;										//check exit condition
		if (Fx.substr(0, 3) == "let") 									//check "let"
		{
			nextToken(&Fx);												//deletes "let "
			string key = nextToken(&Fx);								//sets key to inputVariable
			for (int ii = 0; ii < 7; ii++) 
			{
				if (key == constants[ii]) continue;						//checks key against all constants
			}
			Mathing math = Mathing();
			double value = math.doMath(&Fx);
			umap.insert(make_pair(key, value));							//hashes (key, value)
		}
		else
		{
			Mathing math = Mathing();
			math.printMath(&Fx);
		}
	}
	return 0;
}

