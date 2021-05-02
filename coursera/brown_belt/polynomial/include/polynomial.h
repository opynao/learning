#pragma once
#include "print_coef.h"

#include <iostream>
#include <algorithm>
#include <vector>

template <typename T>
class Polynomial
{
public:
    Polynomial() = default;
    Polynomial(std::vector<T> coeffs) : coeffs_(std::move(coeffs))
    {
        Shrink();
    }

    template <typename Iterator>
    Polynomial(Iterator first, Iterator last) : coeffs_(first, last)
    {
        Shrink();
    }

    bool operator==(const Polynomial &other) const
    {
        return coeffs_ == other.coeffs_;
    }

    bool operator!=(const Polynomial &other) const
    {
        return !operator==(other);
    }

    int Degree() const
    {
        Shrink();
        return coeffs_.size() - 1;
    }

    Polynomial &operator+=(const Polynomial &r)
    {
        if (r.coeffs_.size() > coeffs_.size())
            coeffs_.resize(r.coeffs_.size());

        for (size_t i = 0; i != r.coeffs_.size(); ++i)
            coeffs_[i] += r.coeffs_[i];

        Shrink();
        return *this;
    }

    Polynomial &operator-=(const Polynomial &r)
    {
        if (r.coeffs_.size() > coeffs_.size())
            coeffs_.resize(r.coeffs_.size());

        for (size_t i = 0; i != r.coeffs_.size(); ++i)
            coeffs_[i] -= r.coeffs_[i];

        Shrink();
        return *this;
    }

    T operator[](size_t degree) const
    {
        return degree < coeffs_.size() ? coeffs_[degree] : 0;
    }

    T &operator[](size_t degree)
    {
        if (coeffs_.size() < degree)
            coeffs_.resize(degree);
        return coeffs_[degree];
    }

    // Реализуйте неконстантную версию operator[]

    T operator()(const T &x) const
    {
        T res = 0;
        for (auto it = coeffs_.rbegin(); it != coeffs_.rend(); ++it)
        {
            res *= x;
            res += *it;
        }
        return res;
    }

    using const_iterator = typename std::vector<T>::const_iterator;

    const_iterator begin() const
    {
        return coeffs_.cbegin();
    }

    const_iterator end() const
    {
        return coeffs_.cend();
    }

private:
    mutable std::vector<T> coeffs_ = {0};

    void Shrink()
    {
        while (coeffs_.size() > 1 && coeffs_.back() == 0)
            coeffs_.pop_back();
    }

    class IndexProxy
    {
    public:
        IndexProxy(Polynomial &poly, size_t degree)
            : poly_{poly}, degree_{degree}
        {
        }
        IndexProxy operator=(Polynomial& poly)

    private:
        Polynomial &poly_;
        size_t degree_;
    };
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const Polynomial<T> &p)
{
    bool printed = false;
    for (int i = p.Degree(); i >= 0; --i)
    {
        if (p[i] != 0)
        {
            PrintCoeff(out, i, p[i], printed);
            printed = true;
        }
    }
    return out;
}

template <typename T>
Polynomial<T> operator+(Polynomial<T> lhs, const Polynomial<T> &rhs)
{
    lhs += rhs;
    return lhs;
}

template <typename T>
Polynomial<T> operator-(Polynomial<T> lhs, const Polynomial<T> &rhs)
{
    lhs -= rhs;
    return lhs;
}