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

    // Constructors / Destructor:
    AbstractList(const AbstractList&) = delete;
    AbstractList& operator=(const AbstractList&) = delete;
    AbstractList(AbstractList&&) noexcept = delete;
    AbstractList& operator=(AbstractList&&) noexcept = delete;
    virtual ~AbstractList() noexcept = default;

    // Size:
    virtual sizeType size() const noexcept = 0;
    virtual bool isEmpty() const noexcept = 0;

    // Element Access:
    virtual reference front() noexcept = 0;
    virtual constReference front() const noexcept = 0;

    virtual reference back() noexcept = 0;
    virtual constReference back() const noexcept = 0;

    virtual reference at(sizeType index) = 0;
    virtual constReference at(sizeType index) const = 0;

    // Modifiers:
    virtual void insertFirst(const valueType& value) = 0;
    virtual void insertLast(const valueType& value) = 0;
    virtual void insertAt(sizeType index, const valueType& value) = 0;

    virtual void removeFirst() noexcept = 0;
    virtual void removeLast() noexcept = 0;
    virtual void removeAt(sizeType index) noexcept = 0;

    virtual void update(sizeType index, const valueType& value) noexcept = 0;
    virtual void clear() noexcept = 0;
};
