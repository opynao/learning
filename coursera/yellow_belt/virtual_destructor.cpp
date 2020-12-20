#include <iostream>
#include <memory>


class C
{
public:
	~C() {std::cout << __FUNCTION__ << std::endl;}
};

class A
{
public:
	virtual void foo() = 0;
	virtual ~A() {}
};

class B : public A
{
public:
	B() 
	{ 
		p = new C; 
	}
	virtual ~B()
	{
		delete p;
	}
	virtual void foo() override
	{
	}
	C* p;
};

int main()
{
	A* p = new B;
	delete p;
	return 0;
}
