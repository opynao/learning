#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T>
void PrintCoeff(std::ostream &out, int i, const T &coef, bool printed)
{
    bool coeffPrinted = false;
    if (coef == 1 && i > 0)
    {
        out << (printed ? "+" : "");
    }
    else if (coef == -1 && i > 0)
    {
        out << "-";
    }
    else if (coef >= 0 && printed)
    {
        out << "+" << coef;
        coeffPrinted = true;
    }
    else
    {
        out << coef;
        coeffPrinted = true;
    }
    if (i > 0)
    {
        out << (coeffPrinted ? "*" : "") << "x";
    }
    if (i > 1)
    {
        out << "^" << i;
    }
}

template <typename T>
class Polynomial
{
private:
    std::vector<T> coeffs_ = {0};

    void Shrink()
    {
        while (coeffs_.size() > 1 && coeffs_.back() == 0)
        {
            coeffs_.pop_back();
        }
    }

private:
    class IndexProxy
    {
    public:
        IndexProxy(Polynomial<T> &poly, const size_t degree)
            : m_poly{poly}, m_degree{degree}
        {
        }
        IndexProxy &operator=(const T &value)
        {
            if (m_degree <= static_cast<size_t>(m_poly.Degree()))
                m_poly.coeffs_[m_degree] = value;

            else if (value != 0)
            {
                m_poly.coeffs_.resize(m_degree + 1);
                m_poly.coeffs_[m_degree] = value;
            }

            m_poly.Shrink();
            return *this;
        }
        operator T() const
        {
            return std::as_const(m_poly)[m_degree];
        }
        friend std::ostream &operator<<(std::ostream &os, const IndexProxy &indexProxy)
        {
            os << indexProxy.operator T();
            return os;
        }
        bool operator==(const T &value)
        {
            return operator T() == value;
        }

    private:
        Polynomial<T> &m_poly;
        size_t m_degree;
    };

public:
    Polynomial<T>() = default;
    Polynomial<T>(std::vector<T> coeffs)
        : coeffs_(std::move(coeffs))
    {
        Shrink();
    }

    template <typename Iterator>
    std::vector<T> &GetCoeffs() const
    {
        return coeffs_;
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
        return coeffs_.size() - 1;
    }

    Polynomial &operator+=(const Polynomial &r)
    {
        if (r.coeffs_.size() > coeffs_.size())
        {
            coeffs_.resize(r.coeffs_.size());
        }
        for (size_t i = 0; i != r.coeffs_.size(); ++i)
        {
            coeffs_[i] += r.coeffs_[i];
        }
        Shrink();
        return *this;
    }

    Polynomial &operator-=(const Polynomial &r)
    {
        if (r.coeffs_.size() > coeffs_.size())
        {
            coeffs_.resize(r.coeffs_.size());
        }
        for (size_t i = 0; i != r.coeffs_.size(); ++i)
        {
            coeffs_[i] -= r.coeffs_[i];
        }
        Shrink();
        return *this;
    }

    T operator[](size_t degree) const
    {
        return degree < coeffs_.size() ? coeffs_[degree] : 0;
    }

    IndexProxy operator[](size_t degree)
    {
        return IndexProxy{*this, degree};
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

int main()
{
    return 0;
}