#include <iostream>
#include <cassert>
#include <utility>
#include <array>

void rotate(int a[], unsigned size, int shift);

void TestRotateArray()
{
	int ar1[] { 0,1,2,3,4,5,6,7,8,9 };
	int ar2[] { 8,9,0,1,2,3,4,5,6,7 };
	rotate(ar1, 10, 8);
	for ( size_t i {}; i != 10; ++i )
	{
	//	assert( ar1[i] == ar2[i] );
	std::cerr<<ar1[i] << " " << ar2[i] << std::endl;
	}
}

void swap(int *first, int *second)
{
	int temp = *first;
        *first = *second;
        *second = temp;
}

void rotate(int a[], unsigned size, int shift)
{
    if( shift == 0 )
        return;
    else if ( shift > size ) 
    {
        shift %= size;
    }    
    int k = shift;
    for (int i = 0; k < size; i++, k++)
	swap(a+i,a+k);
    k=shift;
    for (int i = size-shift; k <size; i++, k++)
	swap(a+i,a+k);
}

int main()
{
	TestRotateArray();
	int a[10] = {0,1,2,3,4,5,6,7,8,9};
	for(int i = 0; i < 10; i++)
	{
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
	rotate (a,10,3);
	for (int i = 0; i < 10; i++)
	{
		std::cout << a[i] << " ";
	}
	return 0;
}

