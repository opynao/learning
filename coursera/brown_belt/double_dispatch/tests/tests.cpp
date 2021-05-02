#include "geo2d.h"
#include "game_object.h"
#include "gtest/gtest.h"
#include "collide.h"

#include <memory>

using namespace std;

TEST(Basic, AddingNewObjectOnMap)
{
    // Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
    // и мы хотим добавить на неё новый, например, построить новое здание или башню.
    // Мы можем его добавить, только если он не пересекается ни с одним из существующих.
    using namespace geo2d;

    const std::vector<std::shared_ptr<GameObject>> game_map{
        std::make_shared<Unit>(geo2d::Point{3, 3}),
        make_shared<Unit>(Point{5, 5}),
        make_shared<Unit>(Point{3, 7}),
        make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
        make_shared<Tower>(Circle{Point{9, 4}, 1}),
        make_shared<Tower>(Circle{Point{10, 7}, 1}),
        make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
    };

    for (size_t i = 0; i < game_map.size(); ++i)
    {
        EXPECT_EQ(Collide(*game_map[i], *game_map[i]), true);

        //    "An object doesn't collide with itself: " + to_string(i),true);

        for (size_t j = 0; j < i; ++j)
            EXPECT_EQ(!Collide(*game_map[i], *game_map[j]), true);

        //    "Unexpected collision found " + to_string(i) + ' ' + to_string(j), true);
    }

    auto new_warehouse = make_shared<Building>(Rectangle{{4, 3}, {9, 6}});
    EXPECT_EQ(!Collide(*new_warehouse, *game_map[0]), true);
    EXPECT_EQ(Collide(*new_warehouse, *game_map[1]), true);
    EXPECT_EQ(!Collide(*new_warehouse, *game_map[2]), true);
    EXPECT_EQ(Collide(*new_warehouse, *game_map[3]), true);
    EXPECT_EQ(Collide(*new_warehouse, *game_map[4]), true);
    EXPECT_EQ(!Collide(*new_warehouse, *game_map[5]), true);
    EXPECT_EQ(!Collide(*new_warehouse, *game_map[6]), true);

    auto new_defense_tower = make_shared<Tower>(Circle{{8, 2}, 2});
    EXPECT_EQ(!Collide(*new_defense_tower, *game_map[0]), true);
    EXPECT_EQ(!Collide(*new_defense_tower, *game_map[1]), true);
    EXPECT_EQ(!Collide(*new_defense_tower, *game_map[2]), true);
    EXPECT_EQ(Collide(*new_defense_tower, *game_map[3]), true);
    EXPECT_EQ(Collide(*new_defense_tower, *game_map[4]), true);
    EXPECT_EQ(!Collide(*new_defense_tower, *game_map[5]), true);
    EXPECT_EQ(!Collide(*new_defense_tower, *game_map[6]), true);
}