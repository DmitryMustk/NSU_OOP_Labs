#include "flat_map.h"
#include "gtest/gtest.h"

namespace {
TEST(FlatMapTest, insert_and_access) {
    FlatMap<std::string, std::string> map;

    map["banana"] = "yellow";
    map["apple"] = "red";
    map["orange"] = "orange";

    EXPECT_EQ(map["orange"], "orange");
    EXPECT_EQ(map["apple"], "red");
    EXPECT_EQ(map["banana"], "yellow");
}

TEST(FlatMapTest, contains) {
    FlatMap<std::string, std::string> map;

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
    FlatMap<std::string, std::string> map;

    map["apple"] = "red";
    map["apple"] = "green";
    EXPECT_EQ(map["apple"], "green");
}

TEST(FlatMapTest, erase) {
    FlatMap<std::string, std::string> map;

    map["Denis"] = "Zhdanov";

    EXPECT_EQ(map.erase("Denis"), 1);
    EXPECT_FALSE(map.contains("Denis"));
    EXPECT_EQ(map.erase("Miron"), 0);
}

TEST(FlatMapTest, size_and_clear) {
    FlatMap<std::string, std::string> map;

    map["Vladimir"] = "Lenin";
    map["Felix"] = "Dzerzhinsky";

    EXPECT_EQ(map.size(), 2);
    map.clear();
    EXPECT_EQ(map.size(), 0);
}

TEST(FlatMapTest, copy_and_assign) {
    FlatMap<std::string, std::string> map;

    map["Donetsk"] = "Russia";
    map["Kiev"] = "Ukraine";

    FlatMap<std::string, std::string> map_copy = map;
    map_copy["Simferopol"] = "Russia";

    EXPECT_FALSE(map.contains("Simferopol"));
    EXPECT_TRUE(map_copy.contains("Simferopol"));

    FlatMap<std::string, std::string> map_assigned;
    map_assigned = map_copy;

    EXPECT_TRUE(map_assigned.contains("Donetsk"));
}

TEST(FlatMapTest, move_constructor) {
    FlatMap<std::string, std::string> original_map;
    original_map["key1"] = "value1";
    original_map["key2"] = "value2";

    FlatMap<std::string, std::string> moved_map(std::move(original_map));

    EXPECT_EQ(original_map.size(), 0);

    EXPECT_EQ(moved_map.size(), 2);
    EXPECT_EQ(moved_map["key1"], "value1");
    EXPECT_EQ(moved_map["key2"], "value2");
}

TEST(FlatMapTest, move_assigment_operator) {
    FlatMap<std::string, std::string> map1;
    map1["key1"] = "value1";
    map1["key2"] = "value2";

    FlatMap<std::string, std::string> map2;
    map2["key3"] = "value3";

    map2 = std::move(map1);

    EXPECT_EQ(map2.size(), 2);
    EXPECT_EQ(map2["key1"], "value1");
    EXPECT_EQ(map2["key2"], "value2");
    EXPECT_FALSE(map2.contains("key3"));

    EXPECT_EQ(map1.size(), 0);
}

TEST(FlatMapIteratorTest, DereferenceOperator) {
    FlatMap<std::string, std::string> myMap;
    myMap["one"] = "1";

    FlatMap<std::string, std::string>::FlatMapIterator it = myMap.begin();
    EXPECT_EQ((*it).key, "one");
    EXPECT_EQ((*it).value, "1");
}

TEST(FlatMapIteratorTest, ArrowOperator) {
    FlatMap<std::string, std::string> myMap;
    myMap["one"] = "1";

    FlatMap<std::string, std::string>::FlatMapIterator it = myMap.begin();
    EXPECT_EQ(it->key, "one");
    EXPECT_EQ(it->value, "1");
}

TEST(FlatMapIteratorTest, EqualityOperator) {
    FlatMap<std::string, std::string> myMap;
    myMap["one"] = "1";
    myMap["two"] = "2";
    myMap["three"] = "3";

    FlatMap<std::string, std::string>::FlatMapIterator it = myMap.begin();
    FlatMap<std::string, std::string>::FlatMapIterator it2 = myMap.begin();
    EXPECT_TRUE(it == it2);

    ++it;
    EXPECT_TRUE(it != it2);
}

}  // namespace

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
