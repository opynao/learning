#include <iostream>

class A
{
public:
	virtual void foo()
	{
		std::cout << "A" << std::endl;
	}
};

class B : public A
{
public:
	virtual void foo() override
	{
		std::cout << "B" << std::endl;
	}
};

void P(A* p)
{
	p->foo();
}

void R(A& r)
{
	r.foo();
}

void C(A a)
{
	a.foo();
}

int main()
{
	B b;
	P(&b);
	R(b);
	C(b);
	return 0;
}
