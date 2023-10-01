#ifndef FLAT_MAP_H
#define FLAT_MAP_H

#include <algorithm>
#include <string>

class FlatMap {
   public:
    FlatMap();
    FlatMap(const FlatMap& other_map);
    FlatMap(FlatMap&& x) noexcept;
    ~FlatMap();
    FlatMap& operator=(const FlatMap& other_map);
    std::size_t size() const;
    std::string& operator[](const std::string& key);
    bool contains(const std::string& key);
    std::size_t erase(const std::string& key);
    void clear();

   private:
    struct KeyValue {
        std::string key;
        std::string value;
    };
    KeyValue* data;
    std::size_t size_;
    std::size_t capacity_;

    std::size_t binarySearch(const std::string& key);
    void reserve(std::size_t new_capacity);
};

#endif  // FLAT_MAP_H
