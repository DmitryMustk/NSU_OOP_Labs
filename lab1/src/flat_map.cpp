#include "flat_map.h"

FlatMap::FlatMap() : data_(nullptr), size_(0), capacity_(0) {}

FlatMap::FlatMap(const FlatMap& other_map) : data_(nullptr), size_(0), capacity_(0) {
    FlatMap temp;
    temp.reserve(other_map.capacity_);
    temp.size_ = other_map.size_;
    std::copy(other_map.data_, other_map.data_ + other_map.size_, temp.data_);

    swap(*this, temp);
}

FlatMap::~FlatMap() {
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
}

FlatMap& FlatMap::operator=(const FlatMap& other_map) {
    if (this == &other_map)
        return *this;

    FlatMap temp;
    temp.reserve(other_map.capacity_);
    temp.size_ = other_map.size_;
    std::copy(other_map.data_, other_map.data_ + other_map.size_, temp.data_);

    swap(*this, temp);
    return *this;
}

std::size_t FlatMap::size() const {
    return size_;
}

std::string& FlatMap::operator[](const std::string& key) {
    std::size_t index = binary_search(key);

    if (index < size_ && data_[index].key == key) {
        return data_[index].value;
    }

    if (size_ == capacity_) {
        reserve(size_ * 2 + 1);
    }

    for (std::size_t i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
    }

    data_[index].key = key;
    data_[index].value = "";
    ++size_;
    return data_[index].value;
}

bool FlatMap::contains(const std::string& key) {
    std::size_t index = FlatMap::binary_search(key);
    return (index < size_ && data_[index].key == key);
}

std::size_t FlatMap::erase(const std::string& key) {
    std::size_t index = FlatMap::binary_search(key);

    if (index < size_ && data_[index].key == key) {
        for (std::size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
        return 1;
    }
    return 0;
}

void FlatMap::clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

void FlatMap::reserve(std::size_t new_capacity) {
    if (new_capacity <= capacity_) {
        return;
    }

    FlatMap temp;
    temp.data_ = new KeyValue[new_capacity];
    temp.capacity_ = new_capacity;
    temp.size_ = size_;
    std::copy(data_, data_ + size_, temp.data_);

    swap(*this, temp);
}

std::size_t FlatMap::binary_search(const std::string& key) {
    if (size_ == 0)
        return 0;
    KeyValue* lower_bound =
        std::lower_bound(data_, data_ + size_, key, [](const KeyValue& kv, const std::string& k) { return kv.key < k; });
    return lower_bound - data_;
}

FlatMap::FlatMap(FlatMap&& x) noexcept: data_(x.data_), size_(x.size_), capacity_(x.capacity_) {
    x.data_ = nullptr;
    x.size_ = 0;
    x.capacity_ = 0;
}

FlatMap& FlatMap::operator=(FlatMap&& x) noexcept {
    if(this == &x){
        return *this;
    }

    delete[] data_;

    data_ = x.data_;
    size_ = x.size_;
    capacity_ = x.capacity_;

    x.data_ = nullptr;
    x.size_ = 0;
    x.capacity_ = 0;

    return *this;
}
void swap(FlatMap& first, FlatMap& second) noexcept{
    std::swap(first.data_, second.data_);
    std::swap(first.size_, second.size_);
    std::swap(first.capacity_, second.capacity_);
}
