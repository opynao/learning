#pragma once
#include "address.h"

struct Person
{
    std::string name;
    int height;
    double weight;
    Address address;

    bool operator==(const Person &other) const
    {
        return std::tie(name, height, weight, address) ==
               std::tie(other.name, other.height, other.weight, other.address);
    }
};

struct PersonHasher
{
    size_t operator()(const Person &person) const
    {
        size_t name = sHash(person.name);
        size_t height = iHash(person.height);
        size_t weight = dHash(person.weight);
        size_t address = addressHasher(person.address);
        size_t a = 2'946'901;
        return (name * a * a * a + height * height * a * a + weight * weight * weight * a + address);
    }
    std::hash<std::string> sHash;
    std::hash<int> iHash;
    std::hash<double> dHash;
    AddressHasher addressHasher;
};