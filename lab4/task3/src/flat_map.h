#ifndef FLAT_MAP_H
#define FLAT_MAP_H

#include <algorithm>
#include <stdexcept>
#include <string>

template <class Key, class Value>
class FlatMap {
public:
    struct KeyValue {
        Key key;
        Value value;
    };

    class FlatMapIterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = KeyValue;
        using difference_type = std::ptrdiff_t;
        using pointer = KeyValue*;
        using reference = KeyValue&;

        FlatMapIterator(pointer ptr);
        FlatMapIterator& operator++();
        FlatMapIterator operator++(int);
        reference operator*() const;
        pointer operator->() const;
        bool operator==(const FlatMapIterator& other) const;
        bool operator!=(const FlatMapIterator& other) const;

    private:
        pointer ptr_;
    };

    FlatMap();
    FlatMap(const FlatMap& other_map);
    FlatMap(FlatMap&& x) noexcept;
    ~FlatMap();
    FlatMap& operator=(const FlatMap& other_map);
    FlatMap& operator=(FlatMap&& x) noexcept;
    std::size_t size() const;
    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;
    bool contains(const Key& key) const;
    std::size_t erase(const Key& key);
    void clear();
    FlatMapIterator begin();
    FlatMapIterator end();

private:
    KeyValue* data_;
    std::size_t size_;
    std::size_t capacity_;

    void swap(FlatMap& first, FlatMap& second) noexcept;
    std::size_t binary_search(const Key& key) const;
    void reserve(std::size_t new_capacity);
};

template <class Key, class Value>
FlatMap<Key, Value>::FlatMap() : data_(nullptr), size_(0), capacity_(0) {}

template <class Key, class Value>
FlatMap<Key, Value>::FlatMap(const FlatMap& other_map) : data_(nullptr), size_(0), capacity_(0) {
    FlatMap temp;
    temp.reserve(other_map.capacity_);
    temp.size_ = other_map.size_;
    std::copy(other_map.data_, other_map.data_ + other_map.size_, temp.data_);

    swap(*this, temp);
}

template <class Key, class Value>
FlatMap<Key, Value>::~FlatMap() {
    delete[] data_;
    size_ = 0;
    capacity_ = 0;
}

template <class Key, class Value>
FlatMap<Key, Value>& FlatMap<Key, Value>::operator=(const FlatMap<Key, Value>& other_map) {
    if (this == &other_map)
        return *this;

    FlatMap temp(other_map);
    swap(*this, temp);
    return *this;
}

template <class Key, class Value>
std::size_t FlatMap<Key, Value>::size() const {
    return size_;
}

template <class Key, class Value>
Value& FlatMap<Key, Value>::operator[](const Key& key) {
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
    data_[index].value = Value();  
    ++size_;
    return data_[index].value;
}

template <class Key, class Value>
const Value& FlatMap<Key, Value>::operator[](const Key& key) const {
    std::size_t index = binary_search(key);

    if (index < size_ && data_[index].key == key) {
        return data_[index].value;
    } else {
        throw std::out_of_range("Key not found in FlatMap");
    }
}

template <class Key, class Value>
bool FlatMap<Key, Value>::contains(const Key& key) const {
    std::size_t index = binary_search(key);
    return (index < size_ && data_[index].key == key);
}

template <class Key, class Value>
std::size_t FlatMap<Key, Value>::erase(const Key& key) {
    std::size_t index = binary_search(key);

    if (index < size_ && data_[index].key == key) {
        for (std::size_t i = index; i < size_ - 1; ++i) {
            data_[i] = data_[i + 1];
        }
        --size_;
        return 1;
    }
    return 0;
}

template <class Key, class Value>
void FlatMap<Key, Value>::clear() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
}

template <class Key, class Value>
void FlatMap<Key, Value>::reserve(std::size_t new_capacity) {
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

template <class Key, class Value>
std::size_t FlatMap<Key, Value>::binary_search(const Key& key) const {
    if (size_ == 0)
        return 0;
    KeyValue* lower_bound =
        std::lower_bound(data_, data_ + size_, key, [](const KeyValue& kv, const Key& k) { return kv.key < k; });
    return lower_bound - data_;
}

template <class Key, class Value>
FlatMap<Key, Value>::FlatMap(FlatMap<Key, Value>&& x) noexcept : data_(x.data_), size_(x.size_), capacity_(x.capacity_) {
    x.data_ = nullptr;
    x.size_ = 0;
    x.capacity_ = 0;
}

template <class Key, class Value>
FlatMap<Key, Value>& FlatMap<Key, Value>::operator=(FlatMap<Key, Value>&& x) noexcept {
    if (this == &x) {
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

template <class Key, class Value>
void FlatMap<Key, Value>::swap(FlatMap<Key, Value>& first, FlatMap<Key, Value>& second) noexcept {
    using std::swap;
    swap(first.data_, second.data_);
    swap(first.size_, second.size_);
    swap(first.capacity_, second.capacity_);
}

// FlatMapIterator definitions
template <class Key, class Value>
FlatMap<Key, Value>::FlatMapIterator::FlatMapIterator(pointer ptr) : ptr_(ptr) {}

template <class Key, class Value>
typename FlatMap<Key, Value>::FlatMapIterator& FlatMap<Key, Value>::FlatMapIterator::operator++() {
    ++ptr_;
    return *this;
}

template <class Key, class Value>
typename FlatMap<Key, Value>::FlatMapIterator FlatMap<Key, Value>::FlatMapIterator::operator++(int) {
    FlatMapIterator temp = *this;
    ++ptr_;
    return temp;
}

template <class Key, class Value>
typename FlatMap<Key, Value>::FlatMapIterator::reference FlatMap<Key, Value>::FlatMapIterator::operator*() const {
    return *ptr_;
}

template <class Key, class Value>
typename FlatMap<Key, Value>::FlatMapIterator::pointer FlatMap<Key, Value>::FlatMapIterator::operator->() const{
    return ptr_;
}

template <class Key, class Value>
bool FlatMap<Key, Value>::FlatMapIterator::operator==(const FlatMapIterator& other) const {
    return ptr_ == other.ptr_;
}

template <class Key, class Value>
bool FlatMap<Key, Value>::FlatMapIterator::operator!=(const FlatMapIterator& other) const {
    return ptr_ != other.ptr_;
}

template <class Key, class Value>
typename FlatMap<Key, Value>::FlatMapIterator FlatMap<Key, Value>::begin() {
    return FlatMapIterator(data_);
}

template <class Key, class Value>
typename FlatMap<Key, Value>::FlatMapIterator FlatMap<Key, Value>::end() {
    return FlatMapIterator(data_ + size_);
}

#endif  // FLAT_MAP_H
