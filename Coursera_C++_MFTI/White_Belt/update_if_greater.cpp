#include <cassert>

void UpdateIfGreater(const int,int&);

void testUpdateIfGreater_First_Less_Than_Second()
{
	int value = 5;
	UpdateIfGreater(4,value);
	assert(value == 5);
}


void testUpdateIfGreater_First_More_Than_Second()
{
	int value = 4;
	UpdateIfGreater(5,value);
	assert(value == 5);
}


void testUpdateIfGreater_First_Is_Equal_To_Second()
{
	int value = 4;
	UpdateIfGreater(4,value);
	assert(value == 4);

}

void UpdateIfGreater(const int first,int& second)
{
	if(first>second)
		second = first;	
}

int main()
{
	testUpdateIfGreater_First_Less_Than_Second();
	testUpdateIfGreater_First_More_Than_Second();
	testUpdateIfGreater_First_Is_Equal_To_Second();
	return 0;
}
