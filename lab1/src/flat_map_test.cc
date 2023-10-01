#include "flat_map.h"
#include "gtest/gtest.h"


namespace {

TEST(FlatMapTest, insert_and_access) {
    FlatMap map;

    map["banana"] = "yellow";
    map["apple"] = "red";
    map["orange"] = "orange";

    EXPECT_EQ(map["orange"], "orange");
    EXPECT_EQ(map["apple"], "red");
    EXPECT_EQ(map["banana"], "yellow");
}

TEST(FlatMapTest, contains) {
    FlatMap map;

    map["Cristiano"] = "Ronaldo";
    map["Karim"] = "Benzema";
    map["Lionel"] = "Messi";
    map["Artem"] = "Dzyuba";

    EXPECT_TRUE(map.contains("Artem"));
    EXPECT_TRUE(map.contains("Karim"));
    EXPECT_TRUE(map.contains("Lionel"));
    EXPECT_TRUE(map.contains("Cristiano"));

    EXPECT_FALSE(map.contains("Erling"));
    EXPECT_FALSE(map.contains("Didier"));
}

TEST(FlatMapTest, update) {
    FlatMap map;

    map["apple"] = "red";
    map["apple"] = "green";
    EXPECT_EQ(map["apple"], "green");
}

TEST(FlatMapTest, erase) {
    FlatMap map;

    map["Denis"] = "Zhdanov";

    EXPECT_EQ(map.erase("Denis"), 1);
    EXPECT_FALSE(map.contains("Denis"));
    EXPECT_EQ(map.erase("Miron"), 0);
}

TEST(FlatMapTest, size_and_clear) {
    FlatMap map;

    map["Vladimir"] = "Lenin";
    map["Felix"] = "Dzerzhinsky";

    EXPECT_EQ(map.size(), 2);
    map.clear();
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, copy_and_assign) {
    FlatMap map;

    map["Donetsk"] = "Russia";
    map["Kiev"] = "Ukraine";

    FlatMap map_copy = map;
    map_copy["Simferopol"] = "Russia";

    EXPECT_FALSE(map.contains("Simferopol"));
    EXPECT_TRUE(map_copy.contains("Simferopol"));

    FlatMap map_assigned;
    map_assigned = map_copy;

    EXPECT_TRUE(map_assigned.contains("Donetsk"));
}

TEST(FlatMapTest, MoveConstructor) {
    FlatMap original_map;
    original_map["key1"] = "value1";
    original_map["key2"] = "value2";

    FlatMap moved_map(std::move(original_map));

    EXPECT_EQ(original_map.size(), 0);

    EXPECT_EQ(moved_map.size(), 2);
    EXPECT_EQ(moved_map["key1"], "value1");
    EXPECT_EQ(moved_map["key2"], "value2");
}

}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
