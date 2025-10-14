// Created by Franz Seckel on 12.10.2025.
#pragma once
#include <memory>

template <typename T>
class AbstractList {
public:
    // Aliases:
    using valueType = T;
    using sizeType = size_t;
    using reference = valueType&;
    using constReference = const valueType&;
    using pointer = valueType*;
    using constPointer = const valueType*;

    // Capacity:
    virtual sizeType size() const noexcept { return size_; }
    virtual bool isEmpty() const noexcept { return size_ == 0; }

    // Element Access:
    virtual reference front() noexcept = 0;
    virtual constReference front() const noexcept = 0;

    virtual reference back() noexcept = 0;
    virtual constReference back() const noexcept = 0;

    virtual reference at(sizeType index) = 0;
    virtual constReference at(sizeType index) const = 0;

    // Modifiers:
    virtual void insertAt(sizeType index, const valueType& value) = 0;
    virtual void insertFirst(const valueType& value) { insertAt(0, value); }
    virtual void insertLast(const valueType& value) { insertAt(size_, value); }

    virtual void removeAt(sizeType index) noexcept = 0;
    virtual void removeFirst() noexcept { removeAt(0); }
    virtual void removeLast() noexcept { removeAt(size_ - 1); }

    virtual void update(sizeType index, const valueType& value) noexcept = 0;
    virtual void clear() noexcept = 0;

    // Comparison Operators:
    virtual bool operator==(const AbstractList& other) const noexcept = 0;
    virtual bool operator<(const AbstractList& other) const noexcept = 0;
    bool operator!=(const AbstractList& other) const noexcept { return !(*this == other); }
    bool operator>(const AbstractList& other) const noexcept { return other < *this; }
    bool operator<=(const AbstractList& other) const noexcept { return !(other < *this); }
    bool operator>=(const AbstractList& other) const noexcept { return !(*this < other); }

protected:
    sizeType size_ = 0;

    AbstractList() noexcept = default;
    virtual ~AbstractList() noexcept = default;
};
