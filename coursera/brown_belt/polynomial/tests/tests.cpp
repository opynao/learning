#include "profile.h"
#include "gtest/gtest.h"
#include "polynomial.h"

using namespace std;

TEST(Basic, Creation)
{
    {
        Polynomial<int> default_constructed;
        EXPECT_EQ(default_constructed.Degree(), 0);
        EXPECT_EQ(default_constructed[0], 0);
    }
    {
        Polynomial<double> from_vector({1.0, 2.0, 3.0, 4.0});
        EXPECT_EQ(from_vector.Degree(), 3);
        EXPECT_EQ(from_vector[0], 1.0);
        EXPECT_EQ(from_vector[1], 2.0);
        EXPECT_EQ(from_vector[2], 3.0);
        EXPECT_EQ(from_vector[3], 4.0);
    }
    {
        const vector<int> coeffs = {4, 9, 7, 8, 12};
        Polynomial<int> from_iterators(begin(coeffs), end(coeffs));
        EXPECT_EQ(from_iterators.Degree(), coeffs.size() - 1);
        EXPECT_EQ(true, std::equal(cbegin(from_iterators), cend(from_iterators), begin(coeffs)));
    }
}

TEST(Basic, EqualComparability)
{
    Polynomial<int> p1({9, 3, 2, 8});
    Polynomial<int> p2({9, 3, 2, 8});
    Polynomial<int> p3({1, 2, 4, 8});

    EXPECT_EQ(p1, p2);
    EXPECT_EQ(true, p1 != p3);
}

TEST(Basic, Addition)
{
    Polynomial<int> p1({9, 3, 2, 8});
    Polynomial<int> p2({1, 2, 4});

    p1 += p2;
    EXPECT_EQ(p1, Polynomial<int>({10, 5, 6, 8}));

    auto p3 = p1 + p2;
    EXPECT_EQ(p3, Polynomial<int>({11, 7, 10, 8}));

    p3 += Polynomial<int>({-11, 1, -10, -8});
    EXPECT_EQ(p3.Degree(), 1);
    const Polynomial<int> expected{{0, 8}};
    EXPECT_EQ(p3, expected);
}

TEST(Basic, Subtraction)
{
    Polynomial<int> p1({9, 3, 2, 8});
    Polynomial<int> p2({1, 2, 4});

    p1 -= p2;
    EXPECT_EQ(p1, Polynomial<int>({8, 1, -2, 8}));

    auto p3 = p1 - p2;
    EXPECT_EQ(p3, Polynomial<int>({7, -1, -6, 8}));

    p3 -= Polynomial<int>({7, -5, -6, 8});
    EXPECT_EQ(p3.Degree(), 1);
    const Polynomial<int> expected{{0, 4}};
    EXPECT_EQ(p3, expected);
}

TEST(Basic, Evaluation)
{
    const Polynomial<int> default_constructed;
    EXPECT_EQ(default_constructed(0), 0);
    EXPECT_EQ(default_constructed(1), 0);
    EXPECT_EQ(default_constructed(-1), 0);
    EXPECT_EQ(default_constructed(198632), 0);

    const Polynomial<int64_t> cubic({1, 1, 1, 1});
    EXPECT_EQ(cubic(0), 1);
    EXPECT_EQ(cubic(1), 4);
    EXPECT_EQ(cubic(2), 15);
    EXPECT_EQ(cubic(21), 9724);
}

TEST(Basic, ConstAccess)
{
    const Polynomial<int> poly(std::initializer_list<int>{1, 2, 3, 4, 5});

    EXPECT_EQ(poly[0], 1);
    EXPECT_EQ(poly[1], 2);
    EXPECT_EQ(poly[2], 3);
    EXPECT_EQ(poly[3], 4);
    EXPECT_EQ(poly[4], 5);
    EXPECT_EQ(poly[5], 0);
    EXPECT_EQ(poly[6], 0);
    EXPECT_EQ(poly[608], 0);
}

TEST(Basic, NonconstAccess)
{
    Polynomial<int> poly;

    poly[0] = 1;
    poly[3] = 12;
    poly[5] = 4;
    EXPECT_EQ(poly.Degree(), 5);

    EXPECT_EQ(poly[0], 1);
    EXPECT_EQ(poly[1], 0);
    EXPECT_EQ(poly[2], 0);
    EXPECT_EQ(poly[3], 12);
    EXPECT_EQ(poly[4], 0);
    EXPECT_EQ(poly[5], 4);
    EXPECT_EQ(poly[6], 0);
    EXPECT_EQ(poly[608], 0);

    EXPECT_EQ(poly.Degree(), 5);

    poly[608] = 0;
    EXPECT_EQ(poly.Degree(), 5);

    poly[4] = 3;
    poly[5] = 0;
    EXPECT_EQ(poly.Degree(), 4);

    {
        LOG_DURATION("Iteration over const");
        for (size_t i = 10; i < 50000; ++i)
        {
            EXPECT_EQ(std::as_const(poly)[i], 0);
            EXPECT_EQ(poly.Degree(), 4);
        }
    }
    {
        LOG_DURATION("Iteration over non-const");
        for (size_t i = 10; i < 50000; ++i)
        {
            EXPECT_EQ(poly[i], 0);
            EXPECT_EQ(poly.Degree(), 4);
        }
    }
}