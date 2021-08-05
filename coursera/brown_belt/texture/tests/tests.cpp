#include "gtest/gtest.h"
#include "canvas.h"

using namespace std;

TEST(Basic, AddShape_ShapeIsInsideImage)
{
    Canvas canvas;
    canvas.SetSize({5, 3});

    canvas.AddShape(ShapeType::Rectangle, {1, 0}, {3, 3}, nullptr);

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "#######\n"
        "# ... #\n"
        "# ... #\n"
        "# ... #\n"
        "#######\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, AddShape_NonDefaultFill)
{
    Canvas canvas;
    canvas.SetSize({5, 3});

    canvas.AddShape(ShapeType::Rectangle, {1, 0}, {3, 3},
                    MakeTextureSolid({3, 3}, '*'));

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "#######\n"
        "# *** #\n"
        "# *** #\n"
        "# *** #\n"
        "#######\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, AddShape_TextureIsEmpty)
{
    Canvas canvas;
    canvas.SetSize({5, 3});

    canvas.AddShape(ShapeType::Rectangle, {1, 0}, {3, 3},
                    MakeTextureSolid({0, 0}, '*'));

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "#######\n"
        "# ... #\n"
        "# ... #\n"
        "# ... #\n"
        "#######\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, AddShape_SizeOfShapeIsNull)
{
    Canvas canvas;
    canvas.SetSize({5, 3});

    canvas.AddShape(ShapeType::Rectangle, {1, 0}, {0, 0}, nullptr);

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "#######\n"
        "#     #\n"
        "#     #\n"
        "#     #\n"
        "#######\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, AddShape_ImageEmpty)
{
    Canvas canvas;
    canvas.SetSize({0, 0});

    canvas.AddShape(ShapeType::Rectangle, {1, 0}, {0, 0}, nullptr);

    stringstream output;
    canvas.Print(output);

    const std::string answer{};

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, AddShape_ShapeIsMoreThanImage)
{
    Canvas canvas;
    canvas.SetSize({5, 3});

    canvas.AddShape(ShapeType::Rectangle, {1, 0}, {5, 5}, nullptr);

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "#######\n"
        "# ....#\n"
        "# ....#\n"
        "# ....#\n"
        "#######\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, AddShape_ShapeIsOutsideImage)
{
    Canvas canvas;
    canvas.SetSize({5, 3});

    canvas.AddShape(ShapeType::Rectangle, {6, 6}, {5, 5}, nullptr);

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "#######\n"
        "#     #\n"
        "#     #\n"
        "#     #\n"
        "#######\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, SmallTexture)
{
    Canvas canvas;
    canvas.SetSize({6, 4});

    canvas.AddShape(ShapeType::Rectangle, {1, 1}, {4, 2},
                    MakeTextureSolid({3, 1}, '*'));

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "########\n"
        "#      #\n"
        "# ***. #\n"
        "# .... #\n"
        "#      #\n"
        "########\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, Cow)
{
    Canvas canvas;
    canvas.SetSize({18, 5});

    canvas.AddShape(ShapeType::Rectangle, {1, 0}, {16, 5}, MakeTextureCow());

    stringstream output;
    canvas.Print(output);

    // Здесь уместно использовать сырые литералы, т.к. в текстуре есть символы '\'
    const auto answer =
        R"(####################)"
        "\n"
        R"(# ^__^             #)"
        "\n"
        R"(# (oo)\_______     #)"
        "\n"
        R"(# (__)\       )\/\ #)"
        "\n"
        R"(#     ||----w |    #)"
        "\n"
        R"(#     ||     ||    #)"
        "\n"
        R"(####################)"
        "\n";

    EXPECT_EQ(answer, output.str());
}

TEST(Basic, Cpp)
{
    Canvas canvas;
    canvas.SetSize({77, 17});

    // Буква "C" как разность двух эллипсов, один из которых нарисован цветом фона
    canvas.AddShape(ShapeType::Ellipse, {2, 1}, {30, 15},
                    MakeTextureCheckers({100, 100}, 'c', 'C'));
    canvas.AddShape(ShapeType::Ellipse, {8, 4}, {30, 9},
                    MakeTextureSolid({100, 100}, ' '));

    // Горизонтальные чёрточки плюсов
    auto h1 = canvas.AddShape(ShapeType::Rectangle, {54, 7}, {22, 3},
                              MakeTextureSolid({100, 100}, '+'));
    canvas.DuplicateShape(h1, {30, 7});

    // Вертикальные чёрточки плюсов
    auto v1 = canvas.DuplicateShape(h1, {62, 3});
    canvas.ResizeShape(v1, {6, 11});
    canvas.DuplicateShape(v1, {38, 3});

    stringstream output;
    canvas.Print(output);

    const auto answer =
        "###############################################################################\n"
        "#                                                                             #\n"
        "#            cCcCcCcCcC                                                       #\n"
        "#        CcCcCcCcCcCcCcCcCc                                                   #\n"
        "#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
        "#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
        "#   CcCcCcCcC                          ++++++                  ++++++         #\n"
        "#   cCcCcCc                            ++++++                  ++++++         #\n"
        "#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
        "#  CcCcCc                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
        "#  cCcCcC                      ++++++++++++++++++++++  ++++++++++++++++++++++ #\n"
        "#   cCcCcCc                            ++++++                  ++++++         #\n"
        "#   CcCcCcCcC                          ++++++                  ++++++         #\n"
        "#    CcCcCcCcCcCc                      ++++++                  ++++++         #\n"
        "#      cCcCcCcCcCcCcCcCcCcCcC          ++++++                  ++++++         #\n"
        "#        CcCcCcCcCcCcCcCcCc                                                   #\n"
        "#            cCcCcCcCcC                                                       #\n"
        "#                                                                             #\n"
        "###############################################################################\n";

    EXPECT_EQ(answer, output.str());
}