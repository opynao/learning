#include <iostream>
#include <memory>
#include <vector>

class Appliances
{
public:
  Appliances()
  {
    id_ = total_++;
  }
  virtual ~Appliances() 
  {}
  virtual void open() const = 0;
  virtual void close() const = 0;
protected:
  int id_;
  static size_t total_;
};

size_t Appliances::total_ = 0;

class RefrigeratorBuiltIn : public Appliances
{
public:
  void open() const override
  {
    std::cout << "You opened built-in refrigerator N " << id_ << std::endl;
  }
  void close() const override
  {
    std::cout << "You closed built-in refrigerator N " << id_ << std::endl;
  }
};

class RefrigeratorFreeStanding : public Appliances
{
public:
  void open() const override
  {
    std::cout << "You opened free standing refrigerator N " << id_ << std::endl;
  }
  void close() const override
  {
    std::cout << "You closed free standing refrigerator N " << id_ << std::endl;
  }
};

class MicrowaveOvenBuiltIn : public Appliances
{
public:
  void open() const override
  {
    std::cout << "You opened built-in microwave oven N " << id_ << std::endl;
  }
  void close() const override
  {
    std::cout << "You closed built-in microwave oven N " << id_ << std::endl;
  }
};

class MicrowaveOvenFreeStanding : public Appliances
{
public:
  void open() const override
  {
    std::cout << "You opened free standing microwave oven N " << id_ << std::endl;
  }
  void close() const override
  {
    std::cout << "You closed free standing microwave oven N " << id_ << std::endl;
  }
};

/*
class KitchenStove : public Appliances
{
public:
  void open() const override
  {
    std::cout << "You opened kitchen stove N " << id_ << std::endl;
  }
  void close() const override
  {
    std::cout << "You closed kitchen stove N " << id_ << std::endl;
  }
};
*/
class FactoryBuiltIn
{
public:
  virtual ~FactoryBuiltIn() {}
  virtual std::unique_ptr<Appliances> CreateRefrigerator() const = 0;
};

class FactoryFreeStanding
{
public:
  virtual ~FactoryFreeStanding() {}
  virtual std::unique_ptr<Appliances> CreateRefrigerator() const = 0;
};

class BuiltIn : public FactoryBuiltIn
{
public:
  std::unique_ptr< Appliances > CreateRefrigerator() const override
  {
    return std::make_unique< RefrigeratorBuiltIn >();
  }
};

class FreeStanding : public FactoryFreeStanding
{
public:
  std::unique_ptr< Appliances > CreateRefrigerator() const override
  {
    return std::make_unique< RefrigeratorFreeStanding >();
  }
};

int main()
{
  auto factoryBuiltIn = std::make_shared< BuiltIn >();
  auto factoryFreeStanding = std::make_shared< FreeStanding >();
  std::vector< std::unique_ptr<Appliances> > apps;
  apps.push_back( factoryBuiltIn->CreateRefrigerator() );
  apps.push_back( factoryFreeStanding->CreateRefrigerator() );
  for( int i = 0; i != 2; ++i )
  {
    apps[i]->open();
    apps[i]->close();
  }
  return 0;
}
