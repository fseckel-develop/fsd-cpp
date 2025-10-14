// Created by Franz Seckel on 12.10.2025.
#pragma once
#include "AbstractList.h"

template<typename T>
class DoubleList final : public AbstractList<T> {
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
        explicit Node(const T& data) : data(data) {}
    };

public:
    // Aliases:
    using typename AbstractList<T>::valueType;
    using typename AbstractList<T>::sizeType;
    using typename AbstractList<T>::reference;
    using typename AbstractList<T>::constReference;
    using typename AbstractList<T>::pointer;
    using typename AbstractList<T>::constPointer;

    // Constructors / Assignment / Destructor:
    DoubleList() noexcept = default;
    DoubleList(std::initializer_list<T> initList) : AbstractList<T>() {
        for (const auto& value : initList) insertLast(value);
    }
    DoubleList(const DoubleList& other) : AbstractList<valueType>() { copyFrom(other); }
    DoubleList(DoubleList&& other) noexcept : AbstractList<valueType>() { moveFrom(std::move(other)); }
    using AbstractList<T>::AbstractList; // Constructor with Initializer List

    DoubleList& operator=(const DoubleList& other) {
        if (this != &other) copyFrom(other);
        return *this;
    }
    DoubleList& operator=(DoubleList&& other) noexcept {
        if (this != &other) { clear(); moveFrom(std::move(other)); }
        return *this;
    }

    ~DoubleList() noexcept override { clear(); }

    // Element Access:
    reference front() noexcept override { return head_->data; }
    constReference front() const noexcept override { return head_->data; }

    reference back() noexcept override { return tail_->data; }
    constReference back() const noexcept override { return tail_->data; }

    reference operator[](const sizeType index) {
        assert(index < size_ && "DoubleList::operator[] index out of range");
        return getNodeAt(index)->data;
    }
    constReference operator[](const sizeType index) const {
        assert(index < size_ && "DoubleList::operator[] index out of range");
        return getNodeAt(index)->data;
    }

    reference at(const sizeType index) override {
        if (index >= size_) throw std::out_of_range("DoubleList::at");
        return (*this)[index];
    }
    constReference at(const sizeType index) const override {
        if (index >= size_) throw std::out_of_range("DoubleList::at");
        return (*this)[index];
    }

    // Modifiers:
    void insertAt(const sizeType index, const valueType& value) override {
        if (index > size_) return;
        Node* newNode = new Node(value);
        if (index == 0) {
            newNode->next = head_;
            if (head_) head_->prev = newNode;
            else tail_ = newNode;
            head_ = newNode;
        }
        else if (index == size_) {
            newNode->prev = tail_;
            if (tail_) tail_->next = newNode;
            else head_ = newNode;
            tail_ = newNode;
        }
        else {
            Node* node = getNodeAt(index);
            newNode->next = node;
            newNode->prev = node->prev;
            node->prev->next = newNode;
            node->prev = newNode;
        }
        ++size_;
    }

    void removeAt(const sizeType index) noexcept override {
        if (index >= size_) return;
        if (index == 0) {
            const Node* target = head_;
            head_ = head_->next;
            if (head_) head_->prev = nullptr;
            else tail_ = nullptr;
            delete target;
        }
        else if (index == size_ - 1) {
            const Node* target = tail_;
            tail_ = tail_->prev;
            if (tail_) tail_->next = nullptr;
            else head_ = nullptr;
            delete target;
        }
        else {
            Node* target = getNodeAt(index);
            target->prev->next = target->next;
            target->next->prev = target->prev;
            delete target;
        }
        --size_;
    }

    void update(const sizeType index, const valueType& value) noexcept override {
        if (index >= size_) return;
        getNodeAt(index)->data = value;
    }
    void clear() noexcept override {
        Node* currentNode = head_;
        while (currentNode) {
            const Node* target = currentNode;
            currentNode = currentNode->next;
            delete target;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    // Comparison Operator:
    bool operator==(const AbstractList<valueType>& other) const noexcept override {
        const auto* otherList = dynamic_cast<const DoubleList*>(&other); // NOLINT
        if (!otherList) return false;
        if (size_ != otherList->size_) return false;
        const Node* currentNode = head_;
        const Node* otherNode = otherList->head_;
        while (currentNode && otherNode) {
            if (currentNode->data != otherNode->data) return false;
            currentNode = currentNode->next;
            otherNode = otherNode->next;
        }
        return true;
    }
    bool operator<(const AbstractList<valueType>& other) const noexcept override {
        const auto* otherList = dynamic_cast<const DoubleList*>(&other);
        if (!otherList) return false;
        const Node* currentNode = head_;
        const Node* otherNode = otherList->head_;
        while (currentNode && otherNode) {
            if (currentNode->data < otherNode->data) return true;
            if (currentNode->data > otherNode->data) return false;
            currentNode = currentNode->next;
            otherNode = otherNode->next;
        }
        return currentNode == nullptr && otherNode != nullptr;
    }

    // Iterators:
    class iterator {
        Node* current_;
    public:
        explicit iterator(Node* node) : current_(node) {}
        reference operator*() const noexcept { return current_->data; }
        pointer operator->() const noexcept { return &current_->data; }
        iterator& operator++() noexcept { current_ = current_->next; return *this; }
        iterator operator++(int) noexcept { iterator temp = *this; current_ = current_->next; return temp; }
        iterator& operator--() noexcept { current_ = current_->prev; return *this; }
        iterator operator--(int) noexcept { iterator temp = *this; current_ = current_->prev; return temp; }
        bool operator==(const iterator& other) const noexcept { return current_ == other.current_; }
        bool operator!=(const iterator& other) const noexcept { return current_ != other.current_; }
    };

    class constIterator {
        const Node* current_;
    public:
        explicit constIterator(const Node* node) : current_(node) {}
        constReference operator*() const noexcept { return current_->data; }
        constPointer operator->() const noexcept { return &current_->data; }
        constIterator& operator++() noexcept { current_ = current_->next; return *this; }
        constIterator operator++(int) noexcept { constIterator temp = *this; current_ = current_->next; return temp; }
        constIterator& operator--() noexcept { current_ = current_->prev; return *this; }
        constIterator operator--(int) noexcept { constIterator temp = *this; current_ = current_->prev; return temp; }
        bool operator==(const constIterator& other) const noexcept { return current_ == other.current_; }
        bool operator!=(const constIterator& other) const noexcept { return current_ != other.current_; }
    };

    class reverseIterator {
        Node* current_;
    public:
        explicit reverseIterator(Node* node) : current_(node) {}
        reference operator*() const noexcept { return current_->data; }
        pointer operator->() const noexcept { return &current_->data; }
        reverseIterator& operator++() noexcept { current_ = current_->prev; return *this; }
        reverseIterator operator++(int) noexcept { reverseIterator temp = *this; current_ = current_->prev; return temp; }
        reverseIterator& operator--() noexcept { current_ = current_->next; return *this; }
        reverseIterator operator--(int) noexcept { reverseIterator temp = *this; current_ = current_->next; return temp; }
        bool operator==(const reverseIterator& other) const noexcept { return current_ == other.current_; }
        bool operator!=(const reverseIterator& other) const noexcept { return current_ != other.current_; }
    };

    class constReverseIterator {
        const Node* current_;
    public:
        explicit constReverseIterator(const Node* node) : current_(node) {}
        constReference operator*() const noexcept { return current_->data; }
        constPointer operator->() const noexcept { return &current_->data; }
        constReverseIterator& operator++() noexcept { current_ = current_->prev; return *this; }
        constReverseIterator operator++(int) noexcept { constReverseIterator temp = *this; current_ = current_->prev; return temp; }
        constReverseIterator& operator--() noexcept { current_ = current_->next; return *this; }
        constReverseIterator operator--(int) noexcept { constReverseIterator temp = *this; current_ = current_->next; return temp; }
        bool operator==(const constReverseIterator& other) const noexcept { return current_ == other.current_; }
        bool operator!=(const constReverseIterator& other) const noexcept { return current_ != other.current_; }
    };

    iterator begin() noexcept { return iterator(head_); }
    constIterator begin() const noexcept { return constIterator(head_); }
    constIterator cbegin() const noexcept { return constIterator(head_); }

    iterator end() noexcept { return iterator(nullptr); }
    constIterator end() const noexcept { return constIterator(nullptr); }
    constIterator cend() const noexcept { return constIterator(nullptr); }

    reverseIterator rbegin() noexcept { return reverseIterator(tail_); }
    constReverseIterator rbegin() const noexcept { return constReverseIterator(tail_); }
    constReverseIterator crbegin() const noexcept { return constReverseIterator(tail_); }

    reverseIterator rend() noexcept { return reverseIterator(nullptr); }
    constReverseIterator rend() const noexcept { return constReverseIterator(nullptr); }
    constReverseIterator crend() const noexcept { return constReverseIterator(nullptr); }

    iterator find(const valueType& value) noexcept {
        Node* currentNode = head_;
        while (currentNode) {
            if (currentNode->data == value) return iterator(currentNode);
            currentNode = currentNode->next;
        }
        return iterator(nullptr);
    }
    constIterator find(const valueType& value) const noexcept {
        const Node* currentNode = head_;
        while (currentNode) {
            if (currentNode->data == value) return constIterator(currentNode);
            currentNode = currentNode->next;
        }
        return constIterator(nullptr);
    }

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    sizeType size_ = 0;

    void copyFrom(const DoubleList& other) {
        clear();
        for (const auto& value : other) { insertLast(value); }
    }

    void moveFrom(DoubleList&& other) noexcept {
        head_ = std::exchange(other.head_, nullptr);
        tail_ = std::exchange(other.tail_, nullptr);
        size_ = std::exchange(other.size_, 0);
    }

    Node* getNodeAt(const sizeType index) const noexcept {
        if (index >= size_) return nullptr;
        Node* currentNode;
        if (index < size_ / 2) {
            currentNode = head_;
            for (sizeType i = 0; i < index; ++i) currentNode = currentNode->next;
        }
        else {
            currentNode = tail_;
            for (sizeType i = size_ - 1; i > index; --i) currentNode = currentNode->prev;
        }
        return currentNode;
    }
};
