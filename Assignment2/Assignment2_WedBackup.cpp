#include <iostream>
#include <cstdlib>

using namespace std;

class Node								//Good To Go
{
	public:
		Node(int value);
		~Node();
		int value;
		Node* next;
};

Node::Node(int value)					//Good To Go
{
	this->value = value;
	next = NULL;
}

Node::~Node()							//Good To Go
{
	delete next;
}

class HashTable							//Good To Go
{
	public:
		HashTable(int N);
		~HashTable();
		void sort(Node* mapped, Node* temp);
		int hash(int value);
		void insert(int value);
		bool find(Node* mapped);
	private:
		Node** map;  //take in each input and hash it into the correct bucket
		int b;
};

HashTable::HashTable(int N)				//Good To Go
{
	b = 2*N;
	map = new Node*[b];
	for (int ii = 0; ii < b; ii++) //sets hash table to all NULL
	{
		map[ii] = NULL;
	}
}

int HashTable::hash(int value)			//Good To Go
{
	return value % b;
}

void HashTable::insert(int value)		//Good To Go
{
	int key = hash(value);
	if (map[key] == NULL)
	{
		map[key] = new Node(value);
	}
	else //first hashed int has a NULL next and is pointed to by a chain of everything after it
	{
		Node* temp = new Node(value);
		if (temp->value <= map[key]->value)
		{
			temp->next = map[key];
			map[key] = temp;
		}
		else
		{
			if (map[key]->next == NULL)
			{
				map[key]->next = temp;
			}
			else
			{
				sort(map[key], temp);
			}
		}
		delete temp;
	}
}

void HashTable::sort(Node* mapped, Node* temp)		//Good To Go
{
	if (temp->value <= mapped->next->value)
	{
		temp->next = mapped->next;
		mapped->next = temp;
	}
	else
	{
		sort(mapped->next, temp);
	}
}


bool HashTable::find(Node* mapped)			//Empty
{
	if (hash(mapped->value)
	return 0;
}

HashTable::~HashTable()					//Good To Go*
{
	for (int ii = 0; ii < b; ii++) //sets hash table to all NULL
	{
		delete map[ii];
	}
}

int main()								//Needs Work and to check input
{
	int N = 0;// maxProduct = -1;
	cin >> N;  //make hash map 2*k in size
	HashTable ass2(N);
	int mem[N];
	for (int ii = 0; ii < N; ii++)
	{
		int k = 0;
		cin >> k;
		ass2.insert(k);
		mem[ii] = k;
	}
	//check for a,b,c and return c or -1
	for (int ii = 0; ii < N; ii++)
	{
		
	}
	return 0;
}

