#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
	unordered_map<string, double> umap;
	unordered_map<string, double>::iterator it;
	umap.insert(make_pair("Pi", 3.14169));
	umap.insert(make_pair("e", 2.718));
	while (true)
	{
	string expression = "";
	getline(cin, expression);
	if (expression == "quit") break;
	
	//check keyword
		//do keyword command
		//continue to beginning
	//convert to expression
	//analyze and convert variables
	//do the math
	//spit out answer
	
	}
	return 0;
}

