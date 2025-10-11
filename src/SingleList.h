// Created by Franz Seckel on 11.10.2025.
#pragma once
#include <memory>
#include <stdexcept>

template <typename T>
class SingleList {
    struct Node {
        T data;
        Node* next = nullptr;
        explicit Node(const T& data) : data(data) {}
    };

public:
    // Aliases:
    using valueType = T;
    using sizeType = size_t;
    using reference = valueType&;
    using constReference = const valueType&;
    using pointer = valueType*;
    using constPointer = const valueType*;

    // Constructors / Assignment / Destructor:
    constexpr SingleList() noexcept = default;

    SingleList(std::initializer_list<valueType> initList) {
        Node* currentNode = nullptr;
        for (const valueType& value : initList) {
            if (!head_) head_ = currentNode = new Node(value);
            else currentNode = currentNode->next = new Node(value);
        }
        tail_ = currentNode;
        size_ = initList.size();
    }
    SingleList(const SingleList& other) { copyFrom(other); }
    SingleList(SingleList&& other) noexcept { moveFrom(other); }
    ~SingleList() { clear(); }

    SingleList& operator=(const SingleList& other) {
        if (this != &other) { clear(); copyFrom(other); }
        return *this;
    }
    SingleList& operator=(SingleList&& other) noexcept {
        if (this != &other) { clear(); moveFrom(other); }
        return *this;
    }

    // Size:
    sizeType size() const noexcept { return size_; }
    bool isEmpty() const noexcept { return size_ == 0; }

    // Element Access:
    reference front() { return head_->data; }
    constReference front() const { return head_->data; }

    reference back() { return tail_->data; }
    constReference back() const { return tail_->data; }

    reference operator[](const sizeType index) {
        Node* currentNode = head_;
        for (sizeType i = 0; i < index; ++i) currentNode = currentNode->next;
        return currentNode->data;
    }
    constReference operator[](const sizeType index) const {
        Node* currentNode = head_;
        for (sizeType i = 0; i < index; ++i) currentNode = currentNode->next;
        return currentNode->data;
    }

    reference at(const sizeType index) {
        if (index >= size_) throw std::out_of_range("SingleList::at");
        Node* current = head_;
        for (sizeType i = 0; i < index; ++i) current = current->next;
        return current->data;
    }
    constReference at(const sizeType index) const {
        if (index >= size_) throw std::out_of_range("SingleList::at");
        Node* current = head_;
        for (sizeType i = 0; i < index; ++i) current = current->next;
        return current->data;
    }

    // Modifiers:
    void insertFirst(const valueType& value) {
        Node* newNode = new Node(value);
        newNode->next = head_;
        head_ = newNode;
        if (!tail_) tail_ = newNode;
        ++size_;
    }
    void insertLast(const valueType& value) {
        Node* newNode = new Node(value);
        if (tail_) tail_->next = newNode;
        else head_ = newNode;
        tail_ = newNode;
        ++size_;
    }
    void insertAt(const sizeType index, const valueType& value) {
        if (index == 0) return insertFirst(value);
        if (index == size_) return insertLast(value);
        if (index > size_) return;
        Node* newNode = new Node(value);
        Node* currentNode = head_;
        sizeType i = 0;
        while (currentNode) {
            if (i++ == index - 1) {
                newNode->next = currentNode->next;
                currentNode->next = newNode;
                ++size_;
                break;
            }
            currentNode = currentNode->next;
        }
    }

    void removeFirst() {
        if (!head_) return;
        const Node* temp = head_;
        head_ = head_->next;
        delete temp;
        --size_;
    }
    void removeLast() {
        if (size_ == 0) return;
        if (size_ == 1) {
            delete head_;
            head_ = tail_ = nullptr;
        } else {
            Node* currentNode = head_;
            while (currentNode->next->next) currentNode = currentNode->next;
            const Node* temp = currentNode->next;
            tail_ = currentNode;
            tail_->next = nullptr;
            delete temp;
        }
        --size_;
    }
    void removeAt(const sizeType index) {
        if (index == 0) return removeFirst();
        if (index == size_ - 1) return removeLast();
        if (index >= size_) return;
        Node* currentNode = head_;
        sizeType i = 0;
        while (currentNode) {
            if (i++ == index - 1) {
                const Node* temp = currentNode->next;
                currentNode->next = currentNode->next->next;
                delete temp;
                --size_;
                break;
            }
            currentNode = currentNode->next;
        }
    }

    void update(const sizeType index, const valueType& value) {
        if (index >= size_) return;
        Node* currentNode = head_;
        sizeType i = 0;
        while (currentNode) {
            if (i++ == index) {
                currentNode->data = value;
                break;
            }
            currentNode = currentNode->next;
        }
    }
    void clear() {
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

    // Comparison Operators:
    bool operator==(const SingleList& other) const noexcept {
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
    bool operator!=(const SingleList& other) const noexcept { return !(*this == other); }
    bool operator<(const SingleList& other) const noexcept {
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
    bool operator>(const SingleList& other) const noexcept { return other < *this; }
    bool operator<=(const SingleList& other) const noexcept { return !(other < *this); }
    bool operator>=(const SingleList& other) const noexcept { return !(*this < other); }

    // Iterators:
    class iterator {
        Node* current;
    public:
        explicit iterator(Node* node) : current(node) {}
        reference operator*() const { return current->data; }
        pointer operator->() const { return &current->data; }
        iterator& operator++() noexcept { current = current->next; return *this; }
        iterator operator++(int) noexcept { iterator tmp = *this; ++(*this); return tmp; }
        bool operator==(const iterator& other) const noexcept { return current == other.current; }
        bool operator!=(const iterator& other) const noexcept { return current != other.current; }
    };

    class constIterator {
        const Node* current;
    public:
        explicit constIterator(const Node* node) : current(node) {}
        constReference operator*() const { return current->data; }
        constPointer operator->() const { return &current->data; }
        constIterator& operator++() noexcept { current = current->next; return *this; }
        constIterator operator++(int) noexcept { constIterator tmp = *this; ++(*this); return tmp; }
        bool operator==(const constIterator& other) const noexcept { return current == other.current; }
        bool operator!=(const constIterator& other) const noexcept { return current != other.current; }
    };

    iterator begin() { return iterator(head_); }
    constIterator begin() const { return constIterator(head_); }
    constIterator cbegin() const { return constIterator(head_); }

    iterator end() { return iterator(nullptr); }
    constIterator end() const { return constIterator(nullptr); }
    constIterator cend() const { return constIterator(nullptr); }

    iterator find(const valueType& value) {
        Node* currentNode = head_;
        while (currentNode) {
            if (currentNode->data == value) return iterator(currentNode);
            currentNode = currentNode->next;
        }
        return iterator(nullptr);
    }

private:
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
    sizeType size_ = 0;

    void copyFrom(const SingleList& other) {
        Node* currentNode = head_ = nullptr;
        Node* otherNode = other.head_;
        while (otherNode) {
            if (!head_) head_ = currentNode = new Node(otherNode->data);
            else currentNode = currentNode->next = new Node(otherNode->data);
            otherNode = otherNode->next;
        }
        tail_ = currentNode;
        size_ = other.size_;
    }

    void moveFrom(SingleList&& other) noexcept {
        head_ = std::exchange(other.head_, nullptr);
        tail_ = std::exchange(other.tail_, nullptr);
        size_ = std::exchange(other.size_, 0);
    }
};
