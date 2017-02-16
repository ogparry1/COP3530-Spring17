#include <iostream>
#include <cstdlib>
#include <array>

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
		Node(int key);
		~Node() { delete next; };
		Node* next;
		int* getFactors() { return factors; };
		int getKey() { return key; };
		int getSize() { return size; };
		void factor();
	private:
		int key;
		int* factors;
		int size;
};

Node::Node(int key)					//Good To Go
{
	this->key = key;
	next = NULL;
	size = 0;
	factor();
}

void Node::factor()
{
	int N = 0;
	for (int ii = 2; ii < key/2; ii++)
	{
		if (key%ii==0) N++;
	}
	factors = new int[2*N];
	for (int ii = 2; ii < key/2; ii++)
	{
		if (key%ii==0) 
		{
			factors[ii] = key/ii;
			factors[ii+1] = key/factors[ii];
		}
	}
	size = N;
}

class HashTable							//Good To Go
{
	public:
		HashTable(int N);
		~HashTable();
		Node* find(int key);
		int hash(int key);
		void insert(int key);
		bool checkFactors(int key, int* inputs, int K, int N);
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

int HashTable::hash(int key)			//Good To Go
{
	return key % b;
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
		delete temp;
	}
}

Node* HashTable::find(int key)			//
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

bool HashTable::checkFactors(int key, int* inputs, int K, int N)
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
	for (int ii = 0; ii < N; ii++) //retreive hashed factor pairs and try them against the lesser inputs than their product
	{
		if (factors.checkFactors(keys[ii], keys, ii, N))
		{
			cout << keys[ii] << endl;  //return the first key to pass test
			return 0;
		}
	}
	return -1;
}

