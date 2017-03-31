#include <iostream>
#include <cstdlib>

using namespace std;

class CircularList
{
	public:
		CircularList(int N);
		~CircularList();
		void insert();
		void erase();
		void printList();
		void delSeq(int set);
		int Msets[];
		ListElement* front;
		ListElement* current[2];
		ListElement* rear;
	private:
		int newValue;
};

CircularList::CircularList(int N) //assembles initial LinkedList
{
	cin >> newValue;
	front = new ListElement(newValue);
	cin >> newValue;
	rear = new ListElement(newValue);
	front->next = rear;
	rear->next = front;
	current[0] = front;  // current = [current, previous]
	current[1] = rear;
	for (int ii = 2; ii < N; ii++)
	{
		insert();
	}
	int M = 0, m = 0;
	cin >> M;
	for (int ii = 0; ii < M; ii++)
	{
		cin >> m;
		Msets[ii] = m;
	}
}

void CircularList::insert()
{
	cin >> newValue;
	ListElement* insert = new ListElement(newValue);
	rear->next = insert;
	insert->next = front;
	rear = insert;
}

void CircularList::erase()
{
	current[1]->next = current[0]->next;
	current[0]->~ListElement();
	current[0] = current[1]->next;
}

void CircularList::printList()
{
	current[0] = front;
	do 
	{
		cout << current[0]->getValue() << " ";
		current[0] = current[0]->next;
	}while (current[0] != front);
}

void CircularList::delSeq(int set)
{
	
}

CircularList::~CircularList()
{
	//delete all ListElements and pointers
}

