#pragma once
#include "pizza.h"
#include "pizza_types.h"
#include "utils.h"

#include <memory>
#include <map>
#include <functional>

class PizzaStore
{
public:
    virtual ~PizzaStore() = default;
    virtual std::unique_ptr<Pizza> OrderPizza(const PizzaType type)
    {
        LOGF;
        auto pizza = CreatePizza(type);
        LOGF;
        pizza->Prepare();
        LOGF;

        pizza->Bake();
        pizza->Cut();

        pizza->Box();
        LOGF;

        return pizza;
    }

protected:
    virtual std::unique_ptr<Pizza> CreatePizza(const PizzaType type) = 0;
};

class NYPizzaStore : public PizzaStore
{
public:
    NYPizzaStore()
    {
        LOGF;
    }

private:
    std::shared_ptr<NYStylePizzaIngredientFactory> m_ingredientFactory;

    std::map<PizzaType, std::function<std::unique_ptr<Pizza>()>> m_creators{
        {PizzaType::Cheese, [=]
         { return std::make_unique<CheesePizza>(m_ingredientFactory); }},
        {PizzaType::Meat, [=]
         { return std::make_unique<MeatPizza>(m_ingredientFactory); }},
        {PizzaType::Seafood, [=]
         { return std::make_unique<SeafoodPizza>(m_ingredientFactory); }}};

    std::unique_ptr<Pizza> CreatePizza(const PizzaType type) override
    {
        LOGF;
        return m_creators[type]();
    }
};

class MinskPizzaStore : public PizzaStore
{
private:
    std::shared_ptr<MinskStylePizzaIngredientFactory> m_ingredientFactory;

    std::map<PizzaType, std::function<std::unique_ptr<Pizza>()>> m_creators{
        {PizzaType::Cheese, [=]
         { return std::make_unique<CheesePizza>(m_ingredientFactory); }},
        {PizzaType::Meat, [=]
         { return std::make_unique<MeatPizza>(m_ingredientFactory); }},
        {PizzaType::Seafood, [=]
         { return std::make_unique<SeafoodPizza>(m_ingredientFactory); }}};

    std::unique_ptr<Pizza> CreatePizza(const PizzaType type) override
    {
        return m_creators[type]();
    }
};