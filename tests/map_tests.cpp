#define CATCH_CONFIG_MAIN
#include "../map/map.h"
#include "Catch/Catch.hpp"
#include <vector>

TEST_CASE("Map basic functionality") {

    static_assert(std::bidirectional_iterator<map_iterator<int, int, false, false>>);
    static_assert(std::bidirectional_iterator<map_iterator<int, int, true, false>>);
    static_assert(std::bidirectional_iterator<map_iterator<int, int, false, true>>);
    static_assert(std::bidirectional_iterator<map_iterator<int, int, true, true>>);

    SECTION("Constructor") {
        map<int, std::string> map;
        REQUIRE(map.empty());
        REQUIRE(map.size() == 0);
    }

    SECTION("Constructor and assignment operators") {
        map<int, std::string> default_map;
        CHECK(default_map.empty());

        map<int, std::string> copy_map(default_map);
        CHECK(copy_map.empty());

        map<int, std::string> move_map(std::move(default_map));
        CHECK(move_map.empty());

        map<int, std::string> init_list_map = {{1, "one"}, {2, "two"}, {3, "three"}};
        CHECK(init_list_map.size() == 3);

        std::initializer_list<std::pair<int, std::string>> init_list = {{1, "one"}, {2, "two"}, {3, "three"}};
        map<int, std::string> range_map(init_list.begin(), init_list.end());
        CHECK(range_map.size() == 3);

        map<int, std::string> copy_assign_map;
        copy_assign_map = init_list_map;
        CHECK(copy_assign_map.size() == 3);

        map<int, std::string> move_assign_map;
        move_assign_map = std::move(init_list_map);
        CHECK(move_assign_map.size() == 3);
    }

    SECTION("Iterator methods") {
        map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

        map_iterator<int, std::string, false, false> it(map.begin());
        map_iterator<int, std::string, false, false> copy_it(it);
        CHECK((*copy_it).first == std::make_pair(1, "one").first);
        CHECK((*copy_it).second == std::make_pair(1, "one").second);

        map_iterator<int, std::string, false, false> move_it(std::move(it));
        CHECK((*move_it).first == std::make_pair(1, "one").first);
        CHECK((*move_it).second == std::make_pair(1, "one").second);

        map_iterator<int, std::string, false, false> copy_assign_it;
        copy_assign_it = it;
        CHECK((*copy_assign_it).first == std::make_pair(1, "one").first);
        CHECK((*copy_assign_it).second == std::make_pair(1, "one").second);

        map_iterator<int, std::string, false, false> move_assign_it;
        move_assign_it = std::move(it);
        CHECK((*move_assign_it).first == std::make_pair(1, "one").first);
        CHECK((*move_assign_it).second == std::make_pair(1, "one").second);

        ++it;
        CHECK((*it).first == std::make_pair(2, "two").first);
        CHECK((*it).second == std::make_pair(2, "two").second);

        map_iterator<int, std::string, false, false> temp_it = it++;
        CHECK((*temp_it).first == std::make_pair(2, "two").first);
        CHECK((*temp_it).second == std::make_pair(2, "two").second);

        CHECK((*it).first == std::make_pair(3, "three").first);
        CHECK((*it).second == std::make_pair(3, "three").second);
    }

    SECTION("Insert") {
        map<int, std::string> map;
        map.insert({1, "one"});
        map.insert({2, "two"});
        map.insert({3, "three"});

        REQUIRE(map.size() == 3);
        REQUIRE(!map.empty());

        REQUIRE(map.find(1)->second == "one");
        REQUIRE(map.find(2)->second == "two");
        REQUIRE(map.find(3)->second == "three");
    }

    SECTION("Find") {
        map<int, std::string> map;
        map.insert({1, "one"});
        map.insert({2, "two"});
        map.insert({3, "three"});

        REQUIRE(map.find(1) != map.end());
        REQUIRE(map.find(4) == map.end());
    }

    SECTION("Erase") {
        map<int, std::string> map;
        map.insert({1, "one"});
        map.insert({2, "two"});
        map.insert({3, "three"});

        map.erase(2);

        REQUIRE(map.size() == 2);
        REQUIRE(map.find(2) == map.end());
        REQUIRE(map.find(1) != map.end());
        REQUIRE(map.find(3) != map.end());
    }

    SECTION("Clear") {
        map<int, std::string> map;
        map.insert({1, "one"});
        map.insert({2, "two"});
        map.insert({3, "three"});

        map.clear();

        REQUIRE(map.empty());
        REQUIRE(map.size() == 0);
    }

    SECTION("Iterator") {
        map<int, std::string> map;
        std::vector<std::string> strs {"one", "two", "three"};
        map.insert({1, "one"});
        map.insert({2, "two"});
        map.insert({3, "three"});

        int i = 1;
        for (const auto& elem : map) {
            REQUIRE(elem.first == i);
            REQUIRE(elem.second == strs[i-1]);
            i++;
        }
    }

    SECTION("Operator[]") {
        map<int, std::string> map;
        map[1] = "one";
        map[2] = "two";
        map[3] = "three";

        REQUIRE(map.size() == 3);
        REQUIRE(!map.empty());

        REQUIRE(map[1] == "one");
        REQUIRE(map[2] == "two");
        REQUIRE(map[3] == "three");
    }

    SECTION("Container methods") {
        map<int, std::string> map1;

        map1.insert({1, "one"});
        map1.insert({2, "two"});
        map1.insert({3, "three"});
        CHECK(map1.size() == 3);

        auto it = map1.find(2);
        CHECK((*it).first == std::make_pair(2, "two").first);
        CHECK((*it).second == std::make_pair(2, "two").second);

        map<int, std::string> other_map = {{4, "four"}, {5, "five"}, {6, "six"}};
        map1.swap(other_map);
        CHECK(map1.size() == 3);
        CHECK(other_map.size() == 3);

        it = map1.find(4);
        map1.erase(it);
        CHECK(map1.size() == 2);

        for(auto &it: map1){
            std::cout << it.first << std::endl;
        }

        it = map1.find(5);
        auto end_it = map1.find(6);
        map1.erase(it, ++end_it);
        CHECK(map1.size() == 0);

        CHECK(map1.count(6) == 0);

        REQUIRE_THROWS(map1.at(1) == "one");

        map1[7] = "seven";
        CHECK(map1.size() == 1);
        CHECK(map1.at(7) == "seven");
    }

    SECTION("Access methods") {
        map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

        auto it = map.rbegin();
        ++it;
        CHECK((*it).first == std::make_pair(2, "two").first);
        CHECK((*it).second == std::make_pair(2, "two").second);

        CHECK((*map.cbegin()).first == std::make_pair(1, "one").first);
        CHECK((*map.cbegin()).second == std::make_pair(1, "one").second);

        auto it1 = map.crbegin();
        ++it1;
        CHECK((*it1).first == std::make_pair(2, "two").first);
        CHECK((*it1).second == std::make_pair(2, "two").second);

        auto rit = map.rbegin();
        CHECK((*rit).first == std::make_pair(3, "three").first);
        CHECK((*rit).second == std::make_pair(3, "three").second);

        auto crit = map.crbegin();
        CHECK((*crit).first == std::make_pair(3, "three").first);
        CHECK((*crit).second == std::make_pair(3, "three").second);

        CHECK(map[2] == "two");
    }

}
