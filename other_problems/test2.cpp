#include <cassert>
#include <iostream>

struct Cls {
    Cls(char c_, double d_, int i_):c{c_},d{d_},i{i_}
    {}

private:
    char c;
    double d;
    int i;
};

Cls cls('a',2.0,3);

char &get_c(Cls &cls)
{
    char *ch = (char*)&cls;
    return *ch;
}

double &get_d(Cls &cls)
{
	double *d = (double*)(&get_c(cls)+8);
	return *d;
}

int &get_i(Cls &cls)
{
	int *i = (int*)(&get_d(cls) + 8);
	return *i;
}

void test_getC()
{
	assert(get_c(cls) == 'a');
	get_c(cls) = 'd';
	assert(get_c(cls) == 'd');
}

void test_getI()
{
	assert(get_i(cls) == 3);
	get_i(cls) = 3445532;
	assert(get_i(cls) == 3445532);
}

void test_getD()
{
	assert(get_d(cls) == 2.0);
	get_d(cls) = 9.9;
	assert(get_d(cls) == 9.9);
}

int main()
{
	std::cerr << sizeof(cls) <<std::endl << sizeof(char) << std::endl << sizeof(double) << std::endl << sizeof(int) <<std::endl;
	test_getC();
	test_getD();
	return 0;
}
