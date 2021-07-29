#pragma once
#include <iostream>

class Dough
{
public:
    virtual ~Dough() = default;
};

class ThickDough : public Dough
{
public:
    ThickDough()
    {
        std::cout << "Knead thick dough\n";
    }
};

class ThinDough : public Dough
{
public:
    ThinDough()
    {
        std::cout << "Knead thin dough\n";
    }
};

class Mushroom
{
public:
    virtual ~Mushroom() = default;
};

class WhiteMushroom : public Mushroom
{
public:
    WhiteMushroom()
    {
        std::cout << "Add white mushroom\n";
    }
};

class ChampignonMushroom : public Mushroom
{
public:
    ChampignonMushroom()
    {
        std::cout << "Add champignons\n";
    }
};

class Sauсe
{
public:
    virtual ~Sauсe() = default;
};

class TomatoSauсe : public Sauсe
{
public:
    TomatoSauсe()
    {
        std::cout << "Add tomato sauce\n";
    }
};

class CezarSauce : public Sauсe
{
public:
    CezarSauce()
    {
        std::cout << "Add cezar sauce\n";
    }
};

class Onion
{
public:
    virtual ~Onion() = default;
};

class RedOnion : public Onion
{
public:
    RedOnion()
    {
        std::cout << "Add red onion\n";
    }
};

class WhiteOnion : public Onion
{
public:
    WhiteOnion()
    {
        std::cout << "Add white onion\n";
    }
};

class Sausage
{
public:
    virtual ~Sausage() = default;
};

class DoctorsSausage : public Sausage
{
public:
    DoctorsSausage()
    {
        std::cout << "Add doctors sausage\n";
    }
};

class SalamiSausage : public Sausage
{
public:
    SalamiSausage()
    {
        std::cout << "Add salami sausage\n";
    }
};