#include "gtest/gtest.h"
#include "spendings_json.h"
#include "json.h"

TEST(Basic, LoadFromJson)
{
    istringstream json_input(R"([
    {"amount": 2500, "category": "food"},
    {"amount": 1150, "category": "transport"},
    {"amount": 5780, "category": "restaurants"},
    {"amount": 7500, "category": "clothes"},
    {"amount": 23740, "category": "travel"},
    {"amount": 12000, "category": "sport"}
  ])");

    const vector<Spending> spendings = LoadFromJson(json_input);

    const vector<Spending> expected = {
        {"food", 2500},
        {"transport", 1150},
        {"restaurants", 5780},
        {"clothes", 7500},
        {"travel", 23740},
        {"sport", 12000}};
    EXPECT_EQ(spendings, expected);
}

TEST(Basic, JsonLibrary)
{
    // Тест демонстрирует, как пользоваться библиотекой из файла json.h

    istringstream json_input(R"([
    {"amount": 2500, "category": "food"},
    {"amount": 1150, "category": "transport"},
    {"amount": 12000, "category": "sport"}
  ])");

    Document doc = Load(json_input);
    const vector<Node> &root = doc.GetRoot().AsArray();
    EXPECT_EQ(root.size(), 3u);

    const map<string, Node> &food = root.front().AsMap();
    EXPECT_EQ(food.at("category").AsString(), "food");
    EXPECT_EQ(food.at("amount").AsInt(), 2500);

    const map<string, Node> &sport = root.back().AsMap();
    EXPECT_EQ(sport.at("category").AsString(), "sport");
    EXPECT_EQ(sport.at("amount").AsInt(), 12000);

    Node transport(map<string, Node>{{"category", Node("transport")}, {"amount", Node(1150)}});
    Node array_node(vector<Node>{transport});
    EXPECT_EQ(array_node.AsArray().size(), 1u);
}
