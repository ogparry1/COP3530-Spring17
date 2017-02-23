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
		
	private:
		BinNode** init;
};

BinTree::BinTree(int N)
{
	int value = 0, lc = 0, rc = 0;
	init = new BinNode*[N];
	for (int ii = 0; ii < N; ii++)
	{
		init[ii] = new BinNode(ii);
	}
	for (int ii = 0; ii < N; ii++)
	{
		cin >> value >> lc >> rc;
		init[ii]->setValue(value);
		init[ii]->LeftChild = (lc != -1?init[lc]:NULL);
		init[ii]->RightChild = (rc != -1?init[rc]:NULL);
	}
	root = init[0];
}

int main()
{
	int N = 0;
	cin >> N;  //input number of Nodes
	BinTree tree(N);
	/* Problem 1 P/I/P order traversal
	 tree.root->preorder();
	 cout << endl;
	 tree.root->inorder();
	 cout << endl;
	 tree.root->postorder();
	 * */
	 
	 /* Problem 2 Level order traversal
	 * */
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
	 
	 
	 /* Problem 3
	 * */
	return 0;
}

