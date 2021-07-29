#include "pizza.h"
#include "pizza_store.h"

int main()
{
    auto store = std::make_shared<NYPizzaStore>();
    store->OrderPizza(PizzaType::Cheese);
    std::cout << std::endl;

    store->OrderPizza(PizzaType::Meat);
    std::cout << std::endl;

    // auto minskFactory = std::make_unique<MinskStylePizzaIngredientFactory>();
    // auto store = std::make_unique<PizzaStore>(minskFactory);
    // store->OrderPizza(PizzaType::Seafood);

    return 0;
}