#include "xml.h"
#include "gtest/gtest.h"
#include "spendings_xml.h"

using namespace std;

TEST(Basic, LoadFromXml)
{
    istringstream xml_input(R"(<july>
    <spend amount="2500" category="food"></spend>
    <spend amount="1150" category="transport"></spend>
    <spend amount="5780" category="restaurants"></spend>
    <spend amount="7500" category="clothes"></spend>
    <spend amount="23740" category="travel"></spend>
    <spend amount="12000" category="sport"></spend>
  </july>)");

    const vector<Spending> spendings = LoadFromXml(xml_input);

    const vector<Spending> expected = {
        {"food", 2500},
        {"transport", 1150},
        {"restaurants", 5780},
        {"clothes", 7500},
        {"travel", 23740},
        {"sport", 12000}};
    EXPECT_EQ(spendings, expected);
}

TEST(Basic, XmlLibrary)
{
    // Тест демонстрирует, как пользоваться библиотекой из файла xml.h

    istringstream xml_input(R"(<july>
    <spend amount="2500" category="food"></spend>
    <spend amount="23740" category="travel"></spend>
    <spend amount="12000" category="sport"></spend>
  </july>)");

    Document doc = Load(xml_input);
    const Node &root = doc.GetRoot();
    EXPECT_EQ(root.Name(), "july");
    EXPECT_EQ(root.Children().size(), 3u);

    const Node &food = root.Children().front();
    EXPECT_EQ(food.AttributeValue<string>("category"), "food");
    EXPECT_EQ(food.AttributeValue<int>("amount"), 2500);

    const Node &sport = root.Children().back();
    EXPECT_EQ(sport.AttributeValue<string>("category"), "sport");
    EXPECT_EQ(sport.AttributeValue<int>("amount"), 12000);

    Node july("july", {});
    Node transport("spend", {{"category", "transport"}, {"amount", "1150"}});
    july.AddChild(transport);
    EXPECT_EQ(july.Children().size(), 1u);
}
