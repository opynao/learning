#include "ini.h"
#include "gtest/gtest.h"

#include <sstream>

using namespace std;

TEST(Basic, LoadIni)
{
    istringstream input(
        R"([july]
food=2500
sport=12000
travel=23400
clothes=5200

[august]
food=3250
sport=10000
travel=0
clothes=8300
jewelery=25000
)");

    const Ini::Document doc = Ini::Load(input);

    EXPECT_EQ(doc.SectionCount(), 2u);

    const Ini::Section expected_july = {
        {"food", "2500"},
        {"sport", "12000"},
        {"travel", "23400"},
        {"clothes", "5200"},
    };

    const Ini::Section expected_august = {
        {"food", "3250"},
        {"sport", "10000"},
        {"travel", "0"},
        {"clothes", "8300"},
        {"jewelery", "25000"},
    };

    EXPECT_EQ(doc.GetSection("july"), expected_july);
    EXPECT_EQ(doc.GetSection("august"), expected_august);
}

TEST(Basic, Document)
{
    Ini::Document doc;
    EXPECT_EQ(doc.SectionCount(), 0u);

    // Обратите внимание, как мы используем указатель для работы
    // с последней добавленной секцией. Эта техника может вам пригодиться
    // для реализации функции Load
    Ini::Section *section = &doc.AddSection("one");
    EXPECT_EQ(doc.SectionCount(), 1u);

    section->insert({"name_1", "value_1"});
    section->insert({"name_2", "value_2"});

    section = &doc.AddSection("two");
    section->insert({"name_1", "value_1"});
    section->insert({"name_2", "value_2"});
    section->insert({"name_3", "value_3"});

    section = &doc.AddSection("three");
    section->insert({"name_1", "value_1"});

    EXPECT_EQ(doc.SectionCount(), 3u);
    const Ini::Section expected_one = {{"name_1", "value_1"}, {"name_2", "value_2"}};
    const Ini::Section expected_two = {
        {"name_1", "value_1"}, {"name_2", "value_2"}, {"name_3", "value_3"}};
    const Ini::Section expected_three = {{"name_1", "value_1"}};

    EXPECT_EQ(doc.GetSection("one"), expected_one);
    EXPECT_EQ(doc.GetSection("two"), expected_two);
    EXPECT_EQ(doc.GetSection("three"), expected_three);
}

TEST(Basic, UnknownSection)
{
    Ini::Document doc;
    doc.AddSection("primary");
    bool IsException{false};
    try
    {
        doc.GetSection("secondary");
        // Assert(false,"Ini::Document::GetSection() should throw std::out_of_range for unknown section");
    }
    catch (out_of_range &)
    {
        IsException = true;
    }
    catch (...)
    {
        // Assert(false, "Ini::Document::GetSection() throws unexpected exception for unknown section");
    }
    EXPECT_EQ(IsException, true);
}

TEST(Basic, DuplicateSections)
{
    Ini::Document doc;
    doc.AddSection("one").insert({"key_1", "value_1"});
    doc.AddSection("one").insert({"key_2", "value_2"});

    const Ini::Section expected = {{"key_1", "value_1"}, {"key_2", "value_2"}};
    EXPECT_EQ(doc.GetSection("one"), expected);
}

TEST(Basic, SectionWithoutInfo)
{
    istringstream input("[july]");

    const Ini::Document doc = Ini::Load(input);

    EXPECT_EQ(doc.SectionCount(), 1u);

    const Ini::Section expected_july{};

    EXPECT_EQ(doc.GetSection("july"), expected_july);
}
