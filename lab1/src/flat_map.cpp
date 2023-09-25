#include "flat_map.h"

FlatMap::FlatMap() : data(nullptr), size_(0), capacity_(0) {}

FlatMap::FlatMap(const FlatMap& other_map) : size_(other_map.size_), capacity_(other_map.capacity_) {
    data = new KeyValue[capacity_];
    for (std::size_t i = 0; i < size_; ++i) {
        data[i] = other_map.data[i];
    }
}

FlatMap::~FlatMap() {
    delete[] data;
    size_ = 0;
    capacity_ = 0;
}

FlatMap& FlatMap::operator=(const FlatMap& other_map) {
    if (this == &other_map)
        return *this;

    KeyValue* new_data = new KeyValue[other_map.capacity_];
    for (std::size_t i = 0; i < other_map.size_; ++i) {
        new_data[i] = other_map.data[i];
    }

    delete[] data;
    capacity_ = other_map.capacity_;
    size_ = other_map.size_;
    data = new_data;

    return *this;
}

std::size_t FlatMap::size() const {
    return size_;
}

std::string& FlatMap::operator[](const std::string& key) {
    std::size_t index = binarySearch(key);

    if (index < size_ && data[index].key == key) {
        return data[index].value;
    }

    if (size_ == capacity_) {
        reserve(size_ * 2 + 1);
    }

    for (std::size_t i = size_; i > index; --i) {
        data[i] = data[i - 1];
    }

    data[index].key = key;
    data[index].value = "";
    ++size_;
    return data[index].value;
}

bool FlatMap::contains(const std::string& key) {
    std::size_t index = FlatMap::binarySearch(key);
    return (index < size_ && data[index].key == key);
}

std::size_t FlatMap::erase(const std::string& key) {
    std::size_t index = FlatMap::binarySearch(key);

    if (index < size_ && data[index].key == key) {
        for (std::size_t i = index; i < size_ - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size_;
        return 1;
    }
    return 0;
}

void FlatMap::clear() {
    delete[] data;
    data = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void FlatMap::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }
    KeyValue* new_data = new KeyValue[new_capacity];
    for (std::size_t i = 0; i < size_; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
}

std::size_t FlatMap::binarySearch(const std::string& key) const {
    if (size_ == 0)
        return 0;

    std::size_t left = 0;
    std::size_t right = size_ - 1;

    while (left <= right) {
        std::size_t middle = left + (right - left) / 2;
        if (data[middle].key == key)
            return middle;
        if (data[middle].key < key)
            left = middle + 1;
        else
            right = middle - 1;
    }
    return left;
}
