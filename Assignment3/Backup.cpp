#include <iostream>
#include <cstdlib>
#include <array>
#include <cmath>

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
}

void BinNode::preorder()
{
	cout << value << " " << endl;
	if (LeftChild != NULL) { LeftChild->preorder(); };
	if (RightChild != NULL) { RightChild->preorder(); };
}

void BinNode::inorder()
{
	if (LeftChild != NULL) { LeftChild->preorder(); };
	cout << value << " " << endl;
	if (RightChild != NULL) { RightChild->preorder(); };
}

void BinNode::postorder()
{
	if (LeftChild != NULL) { LeftChild->preorder(); };
	if (RightChild != NULL) { RightChild->preorder(); };
	cout << value << " " << endl;
}

class BinTree
{
	public:
		BinTree(int);
	private:
		BinNode* root;
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
		init[ii]->LeftChild = init[lc];
		init[ii]->RightChild = init[rc];
	}
}

int main()
{
	int N = 0;
	cin >> N;  //input number of Nodes
	BinTree tree(N);
	for (int ii = 0; ii < N; ii++) 
	{
		//input all Node values and their child 
	}
	return 0;
}

