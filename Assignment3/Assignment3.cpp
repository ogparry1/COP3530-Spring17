#include <iostream>
#include <cstdlib>
#include <array>
#include <cmath>
#include <string>

using namespace std;

class BinNode
{
	public:
		BinNode(int index);
		BinNode* LeftChild;
		BinNode* RightChild;
		int getValue() { return value; };
		int getIndex() { return index; };
		void setValue(int value) { this->value = value; };
		void preorder();
		void inorder();
		void postorder();
		BinNode* next;
	private:
		int value;
		int index;
};

BinNode::BinNode(int index)
{
	LeftChild = NULL;
	RightChild = NULL;
	value = 0;
	this->index = index;
	next = NULL;
}

void BinNode::preorder()
{
	cout << value << " ";
	if (LeftChild != NULL) { LeftChild->preorder(); };
	if (RightChild != NULL) { RightChild->preorder(); };
}

void BinNode::inorder()
{
	if (LeftChild != NULL) { LeftChild->inorder(); };
	cout << value << " ";
	if (RightChild != NULL) { RightChild->inorder(); };
}

void BinNode::postorder()
{
	if (LeftChild != NULL) { LeftChild->postorder(); };
	if (RightChild != NULL) { RightChild->postorder(); };
	cout << value << " ";
}

class Queue
{
	public:
		Queue();
		void push(BinNode*);
		BinNode* pop();
		bool isEmpty() { return (front == dummy); };
	private:
		BinNode* front;
		BinNode* rear;
		BinNode* dummy;
};

Queue::Queue()
{
	dummy = new BinNode(0);
	front = dummy;
	rear = dummy;
	dummy->next = dummy;
}

void Queue::push(BinNode* node)
{
	if (isEmpty())
	{
		dummy->next = node;
		front = node;
		rear = node;
		node->next = dummy;
	}
	else
	{
		rear->next = node;
		node->next = dummy;
		rear = node;
	}
}

BinNode* Queue::pop()
{
	if (isEmpty())
	{
		return NULL;
	}
	else
	{
		BinNode* tmp = front;
		if (front == rear) { rear = dummy; };
		front = front->next;
		dummy->next = front;
		tmp->next = NULL;
		return tmp;
	}
}

class BinTree
{
	public:
		BinTree(int);
		BinNode* root;
		void construct();
		BinNode* reconstruct(int Apost[], int Bin[]);
	private:
		BinNode** init;
		int size;
};

BinTree::BinTree(int N)
{
	init = new BinNode*[N];
	for (int ii = 0; ii < N; ii++)
	{
		init[ii] = new BinNode(ii);
	}
	root = init[0];
	size = N;
}

void BinTree::construct()
{
	int value = 0, lc = 0, rc = 0;
	for (int ii = 0; ii < size; ii++)
	{
		cin >> value >> lc >> rc;
		init[ii]->setValue(value);
		init[ii]->LeftChild = (lc != -1?init[lc]:NULL);
		init[ii]->RightChild = (rc != -1?init[rc]:NULL);
	}
}

BinNode* BinTree::reconstruct(int Apost[], int Bin[])
{
	BinNode* node = NULL; BinNode* hold = NULL;
	int i = 0, j = 1, n = 0;
	while (i < size)
	{
		if (i == 0)
		{
			node = new BinNode(-1);
			node->setValue(Bin[i]);
			i++;
		}
		else
		{
			hold = node;
			node = new BinNode(-1);
			node->setValue(Bin[i]);
			node->LeftChild = hold;
			while (Apost[j] != Bin[i])
			{
				j++;
				n++;
			}
			int pos[n];
			int in[n];
			for (int ii = j-n; ii < j; ii++)
			{
				pos[ii] = Apost[ii];
			}
			for (int ii = i+1; ii <= i+n; ii++)
			{
				in[ii] = Bin[ii];
			}
			node->RightChild = reconstruct(pos, in);
			j++;
			i = j;
		}
	}
	return node;
}

int main()
{
	int N = 0;
	cin >> N;  //input number of Nodes
	BinTree tree(N);
	/* Problem 1 P/I/P order traversal
	 tree.construct();
	 tree.root->preorder();
	 cout << endl;
	 tree.root->inorder();
	 cout << endl;
	 tree.root->postorder();
	 * */
	 
	 /* Problem 2 Level order traversal
	 tree.construct();
	 Queue queue;
	 BinNode* temp = tree.root;
	 while (temp != NULL)
	 {
		 if (temp->LeftChild != NULL)
		 {
			queue.push(temp->LeftChild);
		 }
		 if (temp->RightChild != NULL)
		 {
			queue.push(temp->RightChild);
		 }
		 cout << temp->getValue() << " ";
		 temp = queue.pop();
	 }
	 * */
	 
	 /* Problem 3
	 * */
	 int Apost[N]; int Bin[N];
	 for (int ii = 0; ii < N; ii++)
	 {
		 cin >> Apost[ii];
	 }
	 for (int ii = 0; ii < N; ii++)
	 {
		 cin >> Bin[ii];
	 }
	 tree.root = tree.reconstruct(Apost, Bin);
	 Queue queue;
	 while (tree.root != NULL)
	 {
		 if (tree.root->LeftChild != NULL)
		 {
			queue.push(tree.root->LeftChild);
		 }
		 if (tree.root->RightChild != NULL)
		 {
			queue.push(tree.root->RightChild);
		 }
		 cout << tree.root->getValue() << " ";
		 tree.root = queue.pop();
	 }
	 
	return 0;
}

