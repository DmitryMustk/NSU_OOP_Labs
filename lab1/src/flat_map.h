#ifndef FLAT_MAP_H
#define FLAT_MAP_H

#include <algorithm>
#include <string>



class FlatMap {
public:
    struct KeyValue {
        std::string key;
        std::string value;
    };

    class FlatMapIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = KeyValue;
        using difference_type = std::ptrdiff_t;
        using pointer = KeyValue*;
        using reference = KeyValue&;

        FlatMapIterator(pointer ptr);
        FlatMapIterator& operator++() ;
        FlatMapIterator operator++(int);
        reference operator*() const;
        pointer operator->();
        bool operator==(const FlatMapIterator& other) const;
        bool operator!=(const FlatMapIterator& other) const;
    private:
        pointer ptr_;
    };
    FlatMap();
    friend void swap(FlatMap& first, FlatMap& second) noexcept;
    FlatMap(const FlatMap& other_map);
    FlatMap(FlatMap&& x) noexcept;
    ~FlatMap();
    FlatMap& operator=(const FlatMap& other_map);
    FlatMap& operator=(FlatMap&& x) noexcept;
    std::size_t size() const;
    std::string& operator[](const std::string& key);
    bool contains(const std::string& key);
    std::size_t erase(const std::string& key);
    void clear();
    FlatMapIterator begin();
    FlatMapIterator end();

private:
    KeyValue* data_;
    std::size_t size_;
    std::size_t capacity_;

    friend void swap(FlatMap& first, FlatMap& second) noexcept;
    std::size_t binary_search(const std::string& key);
    void reserve(std::size_t new_capacity);

};

#endif  // FLAT_MAP_H
