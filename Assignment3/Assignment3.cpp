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
		BinNode* init;
};

BinTree::BinTree(int N)
{
	BinNode temp[N](0);
	init = temp;
	for (int ii = 0; ii < N; ii++)
	{
		
	}
	for (int ii = 0; ii < N; ii++)
	{
		
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

