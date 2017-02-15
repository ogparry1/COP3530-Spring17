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
	delete next;
}
