#include <iostream>
#include <cstdlib>
#include <array>
#include <cmath>
#include <string>

using namespace std;

void printLine(int* arr, int N)
{
	for (int ii = 0; ii < N; ii++)
	{
		cout << arr[ii] << " ";
	}
	cout << endl;
}

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
	value = index;
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
		int peek();
		bool isEmpty() { return (front == dummy); };
		int getSize() { return size; };
	private:
		int size;
		BinNode* front;
		BinNode* rear;
		BinNode* dummy;
};

Queue::Queue()
{
	size = 0;
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
		size++;
	}
	else
	{
		rear->next = node;
		node->next = dummy;
		rear = node;
		size++;
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
		BinNode* temp = front;
		if (front == rear) { rear = dummy; };
		front = front->next;
		dummy->next = front;
		temp->next = NULL;
		size--;
		return temp;
	}
}

int Queue::peek()
{
	return (isEmpty()?-1:front->getValue());
}

class Stack
{
	public:
		Stack(int);
		void push(int);
		BinNode* pop(BinNode*);
		int pop();
		bool isEmpty() { return (top == -1); };
		void resize();
	private:
		int top;
		int length;
		int* stack;
};

Stack::Stack(int amt)
{
	top = -1;
	length = amt;
	stack = new int[length];
}

void Stack::push(int value)
{
	if (top == length-1) resize();
	stack[++top] = value;
}

void Stack::resize()
{
	int temp[2*length];
	for (int ii = 0; ii <= top; ii++)
	{
		temp[ii] = stack[ii];
	}
	stack = temp;
}

BinNode* Stack::pop(BinNode* getBinNode)
{
	if (isEmpty())
	{
		cout << "Stack is empty" << endl;
		return NULL;
	}
	return new BinNode(stack[top--]);
}

int Stack::pop()
{
	if (isEmpty())
	{
		cout << "Stack is empty" << endl;
		return -1;
	}
	return stack[top--];
}

class BinTree
{
	public:
		BinTree(int);
		BinNode* reconstruct(Queue PO, Queue REV);
		BinNode* root;
		void construct();
		void lvlorder();
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

BinNode* BinTree::reconstruct(Queue PO, Queue REV)
{
	int r = PO.pop()->getValue();
	BinNode* output = new BinNode(r);
	if (r == REV.peek())
	{
		REV.pop();
		output->LeftChild = (PO.isEmpty()?NULL:reconstruct(PO, REV));
		return output;
	}
	Queue po; Queue rev; const int length = PO.getSize();
	for (int ii = 0; ii < length; ii++)
	{
		int i = REV.pop()->getValue();
		if (i != r) 
		{ 
			int p = PO.pop()->getValue();
			rev.push(new BinNode(i));
			po.push(new BinNode(p));
		}
		else
		{
			output->RightChild = reconstruct(po, rev);
			output->LeftChild = reconstruct(PO, REV);
			break;
		}
	}
	return output;
}

void BinTree::lvlorder()
{
	Queue queue;
	BinNode* rt = root;
	while (rt != NULL)
	{
		if (rt->LeftChild != NULL)
		{
			queue.push(rt->LeftChild);
		}
		if (rt->RightChild != NULL)
		{
			queue.push(rt->RightChild);
		}
		cout << rt->getValue() << " ";
		rt = queue.pop();
	}
}

int main()
{
	int N = 0;
	cin >> N;  //input number of Nodes
	BinTree tree(N);
//Problem 1 P/I/P order traversal
	//tree.construct();
	//tree.root->preorder(); cout << endl;
	//tree.root->inorder(); cout << endl;
	//tree.root->postorder();
//Problem 2 Level order traversal
	//tree.construct();
	//tree.lvlorder();
	 
//Problem 3 Reconstruction and lvlorder
	int input = 0;
	Stack stackPO(N), stackIN(N);
	Queue PO; Queue IN;
	for (int ii = 0; ii < N; ii++) //insert postorder
	{
		cin >> input;
		stackPO.push(input);
	}
	for (int ii = 0; ii < N; ii++) //insert inorder
	{
		cin >> input;
		stackIN.push(input);
	}
	for (int ii = 0; ii < N; ii++)
	{
		PO.push(new BinNode(stackPO.pop()));
		IN.push(new BinNode(stackIN.pop()));
	}
	tree.root = tree.reconstruct(PO, IN);
	tree.lvlorder(); cout << endl;
	tree.root->preorder(); cout << endl;
	tree.root->inorder();cout << endl;
	tree.root->postorder();
	return 0;
}

