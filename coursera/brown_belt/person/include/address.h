#pragma once
#include <string>
#include <tuple>
#include <functional>

struct Address
{
    std::string city;
    std::string street;
    int building;

    bool operator==(const Address &other) const
    {
        return std::tie(city, street, building) ==
               std::tie(other.city, other.street, other.building);
    }
};

struct AddressHasher
{
    std::hash<std::string> sHash;
    std::hash<int> iHash;
    size_t operator()(const Address &address) const
    {
        size_t city = sHash(address.city);
        size_t street = sHash(address.street);
        size_t building = iHash(address.building);
        size_t x = 37;
        return (city * x * x + street * x + building);
    }
};