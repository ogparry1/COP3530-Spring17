#include <iostream>
#include <cstdlib>
#include <array>
#include <cmath>

using namespace std;


class Node								//Good To Go
{
	public:
		Node(int key);
		~Node() { delete next; };
		Node* next;
		int* getFactors() { return factors; };
		int getKey() { return key; };
		int getSize() { return N; };
		void factor();
	private:
		int key;
		int* factors;
		int N;
};

Node::Node(int key)					//Good To Go
{
	this->key = key;
	next = NULL;
	N = 0;
	factor();
}

void Node::factor()
{
	int i = 0;
	for (int ii = 1; ii <= (int)sqrt((double)key); ii++)
	{
		if (key%ii==0) N++;
	}
	factors = new int[2*N];
	for (int ii = 1; ii <= (int)sqrt((double)key); ii++)
	{
		if (key%ii==0) 
		{
			factors[i] = key/ii;
			i++;
			factors[i] = key/factors[i-1];
			i++;
		}
	}
}

class HashTable							//Good To Go
{
	public:
		HashTable(int N);
		~HashTable();
		Node* find(int key);
		int hash(int key);
		void insert(int key);
		void printTable();
		bool checkFactors(int key, int* inputs, int K);
	private:
		Node** map;  //take in each input and hash it into the correct bucket
		int N;
};

HashTable::HashTable(int N)				//Good To Go
{
	this->N = N;
	map = new Node*[N];
	for (int ii = 0; ii < N; ii++) //sets hash table to all NULL
	{
		map[ii] = NULL;
	}
}

void HashTable::printTable()
{
	Node* current;
	for (int ii = 0; ii < N; ii++)
	{
		current = map[ii];
		while (current != NULL)
		{
			current = current->next;
		}
	}
}

int HashTable::hash(int key)			//Good To Go
{
	int H = key % N;
	return H;
}

void HashTable::insert(int key)		//Good To Go
{
	int index = hash(key);
	if (map[index] == NULL)
	{
		map[index] = new Node(key);
	}
	else //first hashed int has a NULL next and is pointed to by a chain of everything after it
	{
		Node* temp = new Node(key);
		temp->next = map[index];
		map[index] = temp;
	}
}

Node* HashTable::find(int key)
{
	Node* temp = map[hash(key)];
	do //check key of map[index]
	{
		if (temp->getKey() == key)
		{
			return temp;
		}
		else
		{
			temp = temp->next;
		}
	} while (temp != NULL);
	return NULL;
}

bool HashTable::checkFactors(int key, int* inputs, int K)
{
	Node* temp = find(key);
	int* factors = temp->getFactors();
	for (int ii = 0; ii < temp->getSize(); ii++) //cycles through factor pairs
	{
		int a = factors[2*ii], b = factors[2*ii+1];
		bool A = false, B = false;
		for (int jj = K; jj < N; jj++) //cycles through factor pairs   // check very carefully*****
		{
			if (a != b)
			{
				if (inputs[jj] == a)
				{
					A = true;
				}
				if(inputs[jj] == b)
				{
					B = true;
				}
			}
			else
			{
				if (inputs[jj] == a && !A)
				{
					A = true;
				}
				if(inputs[jj] == a && A)
				{
					B = true;
				}
			}
			if (A && B) return 1;
		}
	}
	return 0;
}

HashTable::~HashTable()					//Good To Go*
{
	for (int ii = 0; ii < N; ii++) //sets hash table to all NULL
	{
		delete map[ii];
	}
}

int main()								//Needs Work and to check input
{
	// Initial Variables //
	int N = 0, input = 0;
	cin >> N;  // make hash map 2*input in size
	HashTable factors(N);
	int keys[N];
	// Initial Variables //
	
	// Receives input, inserts and sorts it //
	for (int ii=0; ii<N; ii++) //cycle through to take in all inputs
	{
		// Checks Input //
		if (!(cin>>input) || input < 0)
		{
			cout << -1 << endl;
			return 0;
		}
		// Checks Input //
		
		// Inserts Input into HashMap //
		factors.insert(input); //factor a number into its product pairs and insert them in hash table
		// Inserts Input into HashMap //
		
		//insert sort//
		if (ii == 0)
		{
			keys[ii] = input;
		}
		else
		{
			int i = ii;
			while (input > keys[i-1] && i > 0)
			{
				keys[i] = keys[i-1];
				i--;
			}
			keys[i] = input;
		}
		//insert sort//
	}
	// Receives input, inserts and sorts it //	
	
	// Checks factor pairs and compares to inputs //
	for (int ii = 0; ii < N; ii++) //retreive hashed factor pairs and try them against the lesser inputs than their product
	{
		if (factors.checkFactors(keys[ii], keys, ii+1))
		{
			cout << keys[ii] << endl;  //return the first inputey to pass test
			return 0;
		}
	}
	// Checks factor pairs and compares to inputs //
	cout << -1 << endl;
	return 0;
}

