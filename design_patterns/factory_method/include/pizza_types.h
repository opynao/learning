#pragma once
#include "pizza.h"
#include "utils.h"

class SeafoodPizza : public Pizza
{
public:
    SeafoodPizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory)
        : Pizza(ingredientFactory)
    {
        m_name = m_ingredientFactory->GetPizzaStyle() + "seafood pizza";
    }
    void Prepare() override
    {
        m_dough = m_ingredientFactory->CreateDough();
        m_sauce = m_ingredientFactory->CreateSause();
        m_mushroom = m_ingredientFactory->CreateMushroom();
        m_onion = m_ingredientFactory->CreateOnion();
    }
};

class MeatPizza : public Pizza
{
public:
    MeatPizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory)
        : Pizza(ingredientFactory)
    {
        m_name = m_ingredientFactory->GetPizzaStyle() + "meat pizza";
    }
    void Prepare() override
    {
        m_dough = m_ingredientFactory->CreateDough();
        m_sauce = m_ingredientFactory->CreateSause();
        m_mushroom = m_ingredientFactory->CreateMushroom();
        m_sausage = m_ingredientFactory->CreateSasauge();
        m_onion = m_ingredientFactory->CreateOnion();
    }
};

class CheesePizza : public Pizza
{
public:
    CheesePizza(std::shared_ptr<PizzaIngredientFactory> ingredientFactory)
        : Pizza(ingredientFactory)
    {
        LOGF;
        m_name = ingredientFactory->GetPizzaStyle() + "cheese pizza";
    }
    void Prepare() override
    {
        LOGF;
        m_dough = m_ingredientFactory->CreateDough();
        m_sauce = m_ingredientFactory->CreateSause();
        m_mushroom = m_ingredientFactory->CreateMushroom();
        m_sausage = m_ingredientFactory->CreateSasauge();
        m_onion = m_ingredientFactory->CreateOnion();
    }
};