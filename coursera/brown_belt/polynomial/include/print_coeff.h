#pragma once
#include <ostream>

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