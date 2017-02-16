#include <iostream>
#include <cstdlib>

using namespace std;

int max(int k, int l)
{
	return ((k > l)?k:l);
}

int min(int k, int l)
{
	return ((k < l)?k:l);
}

void mergeSort(int* keys, int N)
{
	if (N == 2)
	{
		int temp = min(keys[0], keys[1]);
		keys[0] = max(keys[0], keys[1]);
		keys[1] = temp;
	}
	else if (N == 3)
	{
		int a = keys[0], b = keys[1], c = keys[2];
		keys[0] = max(max(a,b),c);
		keys[2] = min(min(a,b),c);
		keys[1] = (a > keys[2] && a < keys[0]?a:(b > keys[2] && b < keys[0]?b:c));
	}
	else
	{
		int i = 0, j = 0;
		int lastOdd = 0;
		int* fHalf = new int[N/2]; 
		int* sHalf = new int[N/2];
		if (N % 2 != 0) lastOdd = keys[N-1]; //if N is odd, point to last element and insert it last
		for (int ii = 0; ii < N/2; ii++) //fill in halves
		{
			fHalf[ii] = keys[ii];
			sHalf[ii] = keys[N/2+ii+1];
		}
		mergeSort(fHalf, N/2);
		mergeSort(sHalf, N/2);
		for (int ii = 0; ii < N; ii++) //merge halves
		{
			if (lastOdd > fHalf[i] && lastOdd > sHalf[i] && lastOdd != 0)
			{
				keys[ii] = lastOdd;
				lastOdd = 0;
			}
			if (i != N/2 && j != N/2)
			{
				if (fHalf[i] >= sHalf[j])
				{
					keys[ii] = fHalf[i];
					i++;
				}
				else
				{
					keys[ii] = sHalf[j];
					j++;
				}
			}
			else if (i == N/2)
			{
				for (int kk = ii; kk < N; kk++) //fill in halves
				{
					keys[ii] = sHalf[j];
					j++;
				}
				break;
			}
			else if (j == N/2)
			{
				for (int kk = ii; kk < N; kk++) //fill in halves
				{
					keys[ii] = fHalf[i];
					i++;
				}
				break;
			}
		}
	}
}

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
	//if (hash(mapped->value))
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
	int N = 0; // maxProduct = -1;
	cin >> N;  // make hash map 2*k in size
	HashTable factors(N);
	int keys[N];
	for (int ii = 0; ii < N; ii++)
	{
		int k = 0;
		cin >> k; //take input
		factors.insert(k); //factor a number into its product pairs and insert them in hash table
		keys[ii] = k;
	}
	mergeSort(keys, N); //sort keys in descending order
	//retreive hashed factor pairs and try them against the lesser inputs than their product
	//return the first key to pass test or return -1
	//check for a,b,c and return c or -1
	for (int ii = 0; ii < N; ii++)
	{
		
	}
	return 0;
}

