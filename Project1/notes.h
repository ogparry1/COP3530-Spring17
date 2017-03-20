string nextToken(string* str)
{
	int delData = delimiter(*str);  										//finds index of delimit and type of delimit
	//possible error spot//
	if (delData == INT_MAX || *str == ")") 								//checks for last word
	{
		string output = *str;
		*str = "";
		return output;
	}
	//possible error spot//
	if (delData == 2 || delData == 3)
	{
		*str = str->substr(1, str->length());
		return (delData == 2?"(":")");
	}
	int type = delData%10; 												//1's place tells if " = ", " ", "(", or ")"
	int index = (delData-type)/10; 										//10's place divided by ten gives the index of the term
	string output = str->substr(0, index); 								//create substring of str from str[0..index]
	if (type == 0 || type == 1) 										//cut out space or equals
	*str = str->substr(index+(type == 0?3:1), str->length()); 
	else if (type == 2 || type == 3) 									//cut up to "(" or ")" but preserve delimiter
	*str = str->substr(index, str->length());
	else exit(49);
	return output;
}









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
