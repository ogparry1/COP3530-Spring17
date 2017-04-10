#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

using namespace std;

class Node
{
	public:
		Node(char);
		int getCount() { return count; };
		void setCount(int x) { count += x; };
		char getLetter() { return letter; };
		void setLetter(char x) { letter = x; };
		string getWord() { return word; };
		void setWord(string str) { word = str; };
		Node** alphabet;
	private:
		string word;
		int count;
		char letter;
};

Node::Node(char letter) 
{
	count = 0;
	this->letter = letter;
	alphabet = new Node*[26]();
	for (int ii = 0; ii < 26; ii++)
	{
		alphabet[ii] = NULL;
	}
}

class Trie
{
	 public:
		Trie();
		void postOrder() { postOrder(rootNode); };
		void postOrder(Node*);
		void increment(string);
		void decrement(string);
	 private:
		Node* rootNode;
};

Trie::Trie()
{
	rootNode = new Node('/');
	rootNode->setCount(-1);	
}

void Trie::postOrder(Node* pastNode)
{
	Node* current = pastNode;
	for (int ii = 'a'; ii <= 'z'; ii++)
	{
		if (current->alphabet[ii%26] != NULL) 
		{
			postOrder(current->alphabet[ii%26]);
		}
	}
	if (current->getCount() > 0)
	{
		cout << current->getWord() << ": " << current->getCount() << endl;
	}
}

void Trie::increment(string insert)
{
	Node* current = rootNode;
	string word = "";
	for (int ii = 0; ii < (int)insert.length(); ii++)
	{
		char x = insert[ii];
		if (x == ' ' && current == rootNode) continue;
		if (x != ' ')
		{
			if (current->alphabet[x%26] != NULL)
			{
				current = current->alphabet[x%26];
				word += current->getLetter();
			}
			else
			{
				current->alphabet[x%26] = new Node(x);
				current = current->alphabet[x%26];
				word += current->getLetter();
			}
		}
		else
		{
			current->setCount(1);
			current->setWord(word);
			current = rootNode;
			word = "";
		}
		
		if (ii == (int)insert.length()-1 && current != rootNode)
		{
			current->setCount(1);
			current->setWord(word);
		} 
	}
}

void Trie::decrement(string remove)
{
	Node* current = rootNode;
	for (int ii = 0; ii < (int)remove.length(); ii++)
	{
		char rm = remove[ii];
		if (rm == ' ' && current == rootNode) continue;
		if (rm != ' ')
		{
			if (current->alphabet[rm%26] != NULL)
			{
				current = current->alphabet[rm%26];
			}
			else
			{
				current = rootNode;
				while (remove[ii] != ' ' && ii < (int)remove.length())
				{
					ii++;
				}
			}
		}
		else
		{
			if (current->getCount() > 0) current->setCount(-1);
			current = rootNode;
		}
		if (ii == (int)remove.length()-1 && current->getCount() > 0)
		{
			current->setCount(-1);
		}
	}
}

int main()
{
	Trie ChristmasTrie = Trie();
	string insert = "", remove = "";
	getline(cin, insert);
	getline(cin, remove);
	ChristmasTrie.increment(insert);
	ChristmasTrie.decrement(remove);
	ChristmasTrie.postOrder();
	return 0;
}


