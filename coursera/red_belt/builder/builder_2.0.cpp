#include <iostream>
#include <vector>
#include <memory>
#include <numeric>
#include <map>
#include <functional>

class Flour
{
public:
  Flour() 
  {
    std::cout << "\tAdd 100 g of flour" << std::endl;
  }
};

class Water 
{
public:
  Water() 
  {
    std::cout << "\tAdd 250 ml of water" << std::endl;
  }
};

class Eggs 
{
public:
  Eggs()
  {
    std::cout << "\tAdd 1 egg" << std::endl;
  }
};

class Sugar
{
public:
  Sugar()
  {
    std::cout << "\tAdd 10 g of sugar" << std::endl;
  }
};

class Yeast
{
public:
  Yeast()
  {
    std::cout << "\tAdd 5 g of yeast" << std::endl;
  }
};

class Milk 
{
public:
  Milk()
  {
    std::cout << "\tAdd 250 ml of milk" << std::endl;
  }
};

class Food
{
public:
  virtual ~Food() = default;
};

class Pancakes : public Food
{
public:
  Pancakes( const std::vector< Flour >& vf,
            const std::vector< Milk >& vm,
            const std::vector< Eggs >& ve,
            const std::vector< Sugar >& vs )
  {
    std::cout << "Create pancake from\n" 
              << vf.size()*100 << " g of flour\n" 
              << vm.size()*250 << " ml of milk\n" 
              << ve.size() << " egg(s)\n"
              << vs.size()*10 << " g of sugar\n";
  }
};

class Bread : public Food
{
public:
  Bread( const std::vector< Flour >& vf,
            const std::vector< Water >& vw,
            const std::vector< Sugar >& vs,
            const std::vector< Yeast >& vy )
  {
    std::cout << "Create bread from\n" 
              << vf.size()*100 << " g of flour\n" 
              << vw.size()*200 << " ml of water\n" 
              << vs.size()*10 << " g of sugar\n"
              << vy.size()*5 << " g of yeast\n";
  }
};

class IFoodBuilder
{
public:
  virtual ~IFoodBuilder() = default;
  virtual void addFlour() = 0;
  virtual void addWater() = 0;
  virtual void addEggs() = 0;
  virtual void addSugar() = 0;
  virtual void addYeast() = 0;
  virtual void addMilk() = 0;
  virtual std::unique_ptr< Food > getFood() = 0;
};

class FoodBuilder : public IFoodBuilder
{
public:
  FoodBuilder( const std::string& foodName )
    : foodName_ { foodName } 
  {} 
  ~FoodBuilder() {}
  void addFlour() override
  {
    std::cout << foodName_ << " : ";
    vf.push_back( Flour() );
  }
  void addWater() override
  {
     std::cout << foodName_ << " : ";
     vw.push_back( Water() );
  }
  void addEggs() override
  {
     std::cout << foodName_ << " : ";
     ve.push_back( Eggs() );
  }
  void addSugar() override
  {
     std::cout << foodName_ << " : ";
     vs.push_back( Sugar() );
  }
  void addYeast() override
  {
     std::cout << foodName_ << " : ";
     vy.push_back( Yeast() );
  }
  void addMilk() override
  {
     std::cout << foodName_ << " : ";
     vm.push_back( Milk() );
  }
  virtual std::unique_ptr< Food > getFood() override
  {
     auto itFabric = FoodFabricMap.find(foodName_);
     if( itFabric != FoodFabricMap.cend() )
       return itFabric->second();
     return { nullptr };
  }

private:
  std::map< std::string, std::function< std::unique_ptr< Food >() >> FoodFabricMap
  {
    { "Pancakes", [this](){ return std::make_unique<Pancakes>( vf, vm, ve, vs ); }},
    { "Bread", [this](){ return std::make_unique<Bread>( vf, vw, vs, vy ); }}
  };
  const std::string foodName_;
  std::vector< Flour > vf;
  std::vector< Water > vw;
  std::vector< Eggs > ve;
  std::vector< Sugar > vs;
  std::vector< Yeast > vy;
  std::vector< Milk > vm;
};

int main()
{
  std::unique_ptr< IFoodBuilder > upFoodBuilder = std::make_unique< FoodBuilder >("Pancakes");
  upFoodBuilder->addFlour();
  upFoodBuilder->addEggs();
  upFoodBuilder->addMilk();
  upFoodBuilder->addSugar();
  upFoodBuilder->addFlour();

  auto pancake = upFoodBuilder->getFood();
  upFoodBuilder = std::make_unique< FoodBuilder >("Bread");
  upFoodBuilder->addFlour();
  upFoodBuilder->addMilk();
  upFoodBuilder->addWater();
  
  auto bread = upFoodBuilder->getFood();

  return 0;
}
