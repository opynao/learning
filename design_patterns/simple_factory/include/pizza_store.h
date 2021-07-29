#pragma once
#include "simple_pizza_factory.h"
#include "pizza.h"

class PizzaStore
{
public:
    PizzaStore(std::unique_ptr<SimplePizzaFactory> factory)
        : m_factory{std::move(factory)}
    {
    }

    std::shared_ptr<Pizza> OrderPizza(PizzaType type)
    {
        std::shared_ptr<Pizza> pizza = m_factory->CreatePizza(type);
        pizza->Prepare();
        pizza->Bake();
        pizza->Cut();
        pizza->Box();
        return pizza;
    }

private:
    std::unique_ptr<SimplePizzaFactory> m_factory;
};