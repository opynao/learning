#include "singleton.h"
#include <iostream>

class A : public Singleton<A>
{
public:
};

int main()
{
    auto ins = Singleton<A>::GetInstance();
    //  std::cout << ins->value();
    //Singleton<A> singleton;
    return 0;
}