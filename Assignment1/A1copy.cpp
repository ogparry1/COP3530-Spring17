#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


class Set
{
    public:
        Set(int x, int y, int z);
        int a;
        int b;
        int s;
};

Set::Set(int x, int y, int z)
{
    a = x;
    b = y;
    s = z;
}

class ListElement
{
    public:
        ListElement(int value);
        int getValue();
        ListElement* next;
        ~ListElement();
    private:
        int value;
};

ListElement::ListElement(int value)
{
    this->value = value;
}

int ListElement::getValue()
{
    return value;
}

ListElement::~ListElement()
{
    next = NULL;
}

class CircularList
{
    public:
        CircularList();
        ~CircularList();
        ListElement* front;
        ListElement* current;
        ListElement* previous;
        ListElement* rear;
        int listSize;
        void algorithm(Set* k);
        void insert(int input);
        void erase();
        void printList();
        bool check (int a, int b);
};

CircularList::CircularList()
{
    current = NULL;
    previous = NULL;
    int n;
    cin >> n;
    front = new ListElement(n);
    cin >> n;
    rear = new ListElement(n);
    front->next = rear;
    rear->next = front;
    listSize = 2;
}

bool CircularList::check(int a, int b) //true if both exist
{
    bool AE = false, BE = false;
    ListElement* pnt = front;
    for (int ii = 0; ii < listSize; ii++)
    {
        if (pnt->getValue()==a && AE == false) {
            AE = true;
        }
        else if (pnt->getValue()==b) {
            BE = true;
        }
        pnt = pnt->next;
    }
    return AE && BE;
}

void CircularList::insert(int input) //inserts element at rear
{
    ListElement* insert = new ListElement(input);
    rear->next = insert;
    insert->next = front;
    rear = insert;
    listSize++;
}

void CircularList::erase()
{
    if (current == front)
    {
        front = front->next;
    }
    if (current == rear)
    {
        rear = previous;
    }
    previous->next = current->next;
    current->~ListElement();
    current = previous->next;
    listSize--;
}

void CircularList::printList()
{
	if (listSize == 0)
	{
		cout << " ";
	}
    ListElement* pnt = front;
    do
    {
        cout << pnt->getValue() << ((pnt == rear) ? "" : " ");
        pnt = pnt->next;
    } while (pnt != front);
}

void CircularList::algorithm(Set* k)
{
    current = front; //set current and previous
    previous = rear;
    while (current->getValue() != k->a) //find element "a"
    {
        previous = current;
        current = current->next;
    }
    //second half of algorithm
    bool bFound = false;
    while (!bFound)
    {
		printList();
		cout << endl;
		if (k->s - 1 == 0)
		{
			if ((current->getValue() == k->b)) //if a b is found, that is last cycle
			{
				bFound = true;
			}
			erase();
			continue;
		}
        for (int ii = 0; ii < (k->s - 1); ii++)  //does the stepping while looking for "b" element
        {
            previous = current;
            current = current->next;
            if ((current->getValue() == k->b)) //if a b is found, that is last cycle
			{
				bFound = true;
			}
        }
        if (!bFound || current->getValue() == k->b)
        {
			erase();
			if ((current->getValue() == k->b)) //if a b is found, that is last cycle
			{
				bFound = true;
			}
		}
    }
}

CircularList::~CircularList()
{
    //delete all ListElements and pointers
}

int getData(fstream& input)
{
	string nextLine = "";
	getline(input, nextLine);
	cout << nextLine << endl;
	return atoi(nextLine.c_str());
}

int main()
{
	int N = 0, M = 0, n = 0, l = 0;
	string docName = "";
	cout << "What is the DocName?  ";
	cin >> docName;
	docName = "~/Desktop/TestCases/in/" + docName + ".txt";
	fstream myfile (docName.c_str(), ios::in);
	N = getData(myfile);
	cout << getData(myfile) << endl;
	cout << getData(myfile) << endl;
	cout << getData(myfile) << endl;
	cout << getData(myfile) << endl;
	cout << getData(myfile) << endl;
	cout << getData(myfile) << endl;

    //cin >> N;
    CircularList* PITA = new CircularList();
    for (int ii = 2; ii < N; ii++) // inserts all n elements O(n)
    {
        cin >> n;
        PITA->insert(n);
    }
    cin >> M;
    int mSets[3*M];
    for (int ii = 0; ii < 3*M; ii++) // inserts all M elements O(m)
    {
        cin >> l;
        mSets[ii] = l;
    }
    //algorithm starts
    for (int ii = 0; ii < M; ii++) // runs through all sets O(m) at O(n) thus O(m*n)
    {
        Set* m = new Set(mSets[3*ii], mSets[3*ii+1], mSets[3*ii+2]);
        if (PITA->check(m->a, m->b))
        {
            PITA->algorithm(m);
        }
        else
        {
            continue;
        }
    }
    PITA->printList();
    return 0;
}


