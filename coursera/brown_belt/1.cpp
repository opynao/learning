#include <iostream>

class Base
{
public:
    //virtual
    Base()
    {
        std::cout << "hello Base" << std::endl;
    }
    virtual ~Base()
    {
        std::cout << "Hello from ~Base()" << std::endl;
    }
/*     virtual void foo()
    {
    }
 */};

class Derived : public Base
{
public:
    Derived()
    {
        std::cout << "hello derived" << std::endl;
    }
    ~Derived()
    {
        // Здесь могла бы быть очистка ресурсов
        std::cout << "Hello from ~Derived()" << std::endl;
    }
};

int main()
{
    Base *obj = new Derived();
    delete obj;
}