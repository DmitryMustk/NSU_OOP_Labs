#include "flat_map.h"

FlatMap::FlatMap() : data(nullptr), size_(0), capacity_(0) {}

FlatMap::FlatMap(const FlatMap& other_map) : size_(other_map.size_), capacity_(other_map.capacity_) {
    data = new KeyValue[other_map.size_ + 1];
    std::copy(other_map.data, other_map.data + other_map.size_, data);
}

FlatMap::~FlatMap() {
    delete[] data;
    size_ = 0;
    capacity_ = 0;
}

FlatMap& FlatMap::operator=(const FlatMap& other_map) {
    if (this == &other_map)
        return *this;

    KeyValue* new_data = new KeyValue[other_map.size_];
    std::copy(other_map.data, other_map.data + other_map.size_, new_data);

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
    std::copy(data, data + size_, new_data);
    delete[] data;
    data = new_data;
    capacity_ = new_capacity;
}

std::size_t FlatMap::binarySearch(const std::string& key) {
    if (size_ == 0)
        return 0;
    KeyValue* lower_bound =
        std::lower_bound(data, data + size_, key, [](const KeyValue& kv, const std::string& k) { return kv.key < k; });
    return lower_bound - data;
}

FlatMap::FlatMap(FlatMap&& x) noexcept: data(x.data), size_(x.size_), capacity_(x.capacity_) {
    x.data = nullptr;
    x.size_ = 0;
    x.capacity_ = 0;
}
