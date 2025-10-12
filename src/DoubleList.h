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

    DoubleList(std::initializer_list<valueType> initList) : AbstractList<valueType>() {
        Node *currentNode = head_;
        for (const valueType &value: initList) {
            if (!head_) head_ = currentNode = new Node(value);
            else {
                currentNode->next = new Node(value);
                currentNode->next->prev = currentNode;
                currentNode = currentNode->next;
            }
        }
        tail_ = currentNode;
        size_ = initList.size();
    }
    DoubleList(const DoubleList& other) : AbstractList<valueType>() { copyFrom(other); }
    DoubleList(DoubleList&& other) noexcept : AbstractList<valueType>() { moveFrom(other); }

    DoubleList& operator=(const DoubleList& other) {
        if (this != &other) copyFrom(other);
        return *this;
    }
    DoubleList& operator=(DoubleList&& other) noexcept {
        if (this != &other) { clear(); moveFrom(other); }
        return *this;
    }

    ~DoubleList() noexcept override { clear(); }

    // Size:
    sizeType size() const noexcept override { return size_; }
    bool isEmpty() const noexcept override { return size_ == 0; }

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
        return getNodeAt(index)->data;
    }
    constReference at(const sizeType index) const override {
        if (index >= size_) throw std::out_of_range("DoubleList::at");
        return getNodeAt(index)->data;
    }

    // Modifiers:
    void insertFirst(const valueType& value) override {
        Node* newNode = new Node(value);
        if (head_) {
            newNode->next = head_;
            head_->prev = newNode;
        }
        else tail_ = newNode;
        head_ = newNode;
        ++size_;
    }
    void insertLast(const valueType& value) override {
        Node* newNode = new Node(value);
        if (tail_) {
            newNode->prev = tail_;
            tail_->next = newNode;
        }
        else head_ = newNode;
        tail_ = newNode;
        ++size_;
    }
    void insertAt(const sizeType index, const valueType& value) override {
        if (index > size_) return;
        if (index == 0) return insertFirst(value);
        if (index == size_) return insertLast(value);
        Node* newNode = new Node(value);
        Node* node = getNodeAt(index);
        newNode->next = node;
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;
        ++size_;
    }

    void removeFirst() noexcept override {
        if (size_ == 0) return;
        if (size_ == 1) {
            delete head_;
            head_ = tail_ = nullptr;
        } else {
            const Node* temp = head_;
            head_ = head_->next;
            head_->prev = nullptr;
            delete temp;
        }
        --size_;
    }
    void removeLast() noexcept override {
        if (size_ == 0) return;
        if (size_ == 1) {
            delete head_;
            head_ = tail_ = nullptr;
        } else {
            const Node* temp = tail_;
            tail_ = tail_->prev;
            tail_->next = nullptr;
            delete temp;
        }
        --size_;
    }
    void removeAt(const sizeType index) noexcept override {
        if (index >= size_) return;
        if (index == 0) return removeFirst();
        if (index == size_ - 1) return removeLast();
        Node* node = getNodeAt(index);
        const Node* temp = node;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete temp;
        --size_;
    }

    void update(const sizeType index, const valueType& value) noexcept override {
        if (index >= size_) return;
        getNodeAt(index)->data = value;
    }
    void clear() noexcept override {
        Node* currentNode = head_;
        while (currentNode) {
            const Node* temp = currentNode;
            currentNode = currentNode->next;
            delete temp;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0;
    }

    // Comparison Operator:
    bool operator==(const DoubleList& other) const noexcept {
        if (size_ != other.size_) return false;
        Node* currentNode = head_;
        Node* otherNode = other.head_;
        while (currentNode && otherNode) {
            if (currentNode->data != otherNode->data) return false;
            currentNode = currentNode->next;
            otherNode = otherNode->next;
        }
        return true;
    }
    bool operator!=(const DoubleList& other) const noexcept { return !(*this == other); }
    bool operator<(const DoubleList& other) const noexcept {
        Node* currentNode = head_;
        Node* otherNode = other.head_;
        while (currentNode && otherNode) {
            if (currentNode->data < otherNode->data) return true;
            if (currentNode->data > otherNode->data) return false;
            currentNode = currentNode->next;
            otherNode = otherNode->next;
        }
        return currentNode == nullptr && otherNode != nullptr;
    }
    bool operator>(const DoubleList& other) const noexcept { return other < *this; }
    bool operator<=(const DoubleList& other) const noexcept { return !(other < *this); }
    bool operator>=(const DoubleList& other) const noexcept { return !(*this < other); }

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
        Node* currentNode = head_;
        Node* otherNode = other.head_;
        while (otherNode) {
            if (!head_) head_ = currentNode = new Node(otherNode->data);
            else {
                currentNode->next = new Node(otherNode->data);
                currentNode->next->prev = currentNode;
                currentNode = currentNode->next;
            }
            otherNode = otherNode->next;
        }
        tail_ = currentNode;
        size_ = other.size_;
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
