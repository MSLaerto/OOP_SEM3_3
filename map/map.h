/**
 * @file map.h
 * @brief This file contains the map class template definition.
 * @author Maksim Baranov
 * @version 1.2
 * @date 2023-12-15
 */
#ifndef MLAB3_MAP_H
#define MLAB3_MAP_H

#include <initializer_list>
#include <functional>
#include <utility>
#include <limits>

template<typename Key, typename T, typename Compare = std::less<Key>>
class map;

template<typename Key, typename T>
struct Node{
    std::pair<const Key, T> data_ = {};
    Node* left_;
    Node* right_;
    Node* parent_;

    Node() = default;
    Node(const Key& key, const T& value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
            : data_(key, value), left_(left), right_(right), parent_(parent) {}
};

template<typename Key, typename T, bool is_const, bool is_reversed>
class map_iterator{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<const Key, T>;
    using reference = std::conditional_t<is_const, const value_type, value_type>&;
    using pointer = std::conditional_t<is_const, const value_type, value_type>*;

    using NodePtr = std::conditional_t<is_const, const Node<Key, T>*, Node<Key, T>*>;

    friend map<Key, T>;
    friend map_iterator<Key, T, !is_const, is_reversed>;

    map_iterator() noexcept = default;
    map_iterator(NodePtr node) noexcept : current_(node) {}

    template<bool other_const, bool other_reversed>
    map_iterator(const map_iterator<Key, T, other_const, other_reversed>& other) noexcept
    requires (is_const >= other_const && is_reversed == other_reversed)
    {
        current_ = other.current_;
    }

    template<bool other_const, bool other_reversed>
    map_iterator& operator=(const map_iterator<Key, T, other_const, other_reversed>& other) noexcept
    requires (is_const >= other_const && is_reversed == other_reversed)
    {
        current_ = other.current_;
        return *this;
    }

    template<bool other_const, bool other_reversed>
    map_iterator(map_iterator<Key, T, other_const, other_reversed>&& other) noexcept
    requires (is_const >= other_const && is_reversed == other_reversed)
    {
        current_ = other.current_;
        other.current_ = nullptr;
    }

    template<bool other_const, bool other_reversed>
    map_iterator& operator=(map_iterator<Key, T, other_const, other_reversed>&& other) noexcept
    requires (is_const >= other_const && is_reversed == other_reversed)
    {
        current_ = other.current_;
        other.current_ = nullptr;
        return *this;
    }

    reference operator*() const noexcept { return current_->data_; }
    pointer operator->() const noexcept { return &current_->data_; }

    map_iterator& operator++() noexcept {
        inc();
        return *this;
    }

    map_iterator operator++(int) noexcept {
        map_iterator temp(*this);
        inc();
        return temp;
    }

    map_iterator& operator--() noexcept {
        inc();
        return *this;
    }

    map_iterator operator--(int) noexcept {
        map_iterator temp(*this);
        inc();
        return temp;
    }

    template<bool other_const, bool other_reversed>
    bool operator==(const map_iterator<Key, T, other_const, other_reversed>& other) const noexcept { return current_ == other.current_; }

    template<bool other_const, bool other_reversed>
    bool operator!=(const map_iterator<Key, T, other_const, other_reversed>& other) const noexcept { return current_ != other.current_; }


private:
    NodePtr current_;

    void inc() noexcept {
        if constexpr (is_reversed) {
            if (current_->left_ != nullptr) {
                current_ = current_->left_;
                while (current_->right_ != nullptr) {
                    current_ = current_->right_;
                }
            } else {
                NodePtr parent = current_->parent_;
                while (parent != nullptr && current_ == parent->left_) {
                    current_ = parent;
                    parent = parent->parent_;
                }
                current_ = parent;
            }
        } else {
            if (current_->right_ != nullptr) {
                current_ = current_->right_;
                while (current_->left_ != nullptr) {
                    current_ = current_->left_;
                }
            } else {
                NodePtr parent = current_->parent_;
                while (parent != nullptr && current_ == parent->right_) {
                    current_ = parent;
                    parent = parent->parent_;
                }
                current_ = parent;
            }
        }
    }
};

/**
 * @class map
 * @brief The map class template represents a map data structure that stores key-value pairs in a sorted order based on the keys.
 *
 * This class template uses a binary search tree (BST) as the underlying data structure to store the key-value pairs. The keys are sorted based on the comparison function provided by the Compare template parameter.
 */
template<typename Key, typename T, typename Compare>
class map{
public:
    using key_type = Key;
    using mapped_type =	T;
    using value_type = std::pair<const Key, T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = map_iterator<key_type, mapped_type, false, false>;
    using const_iterator = map_iterator<key_type, mapped_type, true, false>;
    using reverse_iterator = map_iterator<key_type, mapped_type, false, true>;
    using const_reverse_iterator = map_iterator<key_type, mapped_type, true, true>;
    using node_type = Node<key_type, mapped_type>;

    /**
     * @brief Default constructor for the map class template.
     */
    map() : root_(nullptr), size_(0), comp_() {}

    /**
     * @brief Constructs a map object from a range of key-value pairs.
     * @tparam InputIt The type of the input iterator.
     * @param first The beginning of the range.
     * @param last The end of the range.
     * @param comp The comparison function to use for sorting the keys (default is Compare()).
     */
    template<class InputIt>
    map(InputIt first, InputIt last, const Compare& comp = Compare())
            : root_(nullptr), size_(0), comp_(comp) {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    /**
     * @brief Constructs a map object from another map object.
     * @param other The map object to copy.
     */
    map(const map& other) : root_(nullptr), size_(0), comp_(other.comp_) {
        for (const auto& element : other) {
            insert(element);
        }
    }

    /**
     * @brief Constructs a map object by moving another map object.
     * @param other The map object to move.
     */
    map(map&& other) noexcept : root_(other.root_), size_(other.size_), comp_(std::move(other.comp_)) {
        other.root_ = nullptr;
        other.size_ = 0;
    }

    /**
     * @brief Constructs a map object from an initializer list of key-value pairs.
     * @param init The initializer list of key-value pairs.
     * @param comp The comparison function to use for sorting the keys (default is Compare()).
     */
    map(std::initializer_list<value_type> init, const Compare& comp = Compare())
            : root_(nullptr), size_(0), comp_(comp) {
        for (const auto& element : init) {
            insert(element);
        }
    }

    /**
     * @brief Assigns the contents of another map object to this map object.
     * @param other The map object to copy.
     * @return A reference to this map object.
     */
    map& operator=(const map& other) {
        if (this != &other) {
            clear();
            for (const auto& element : other) {
                insert(element);
            }
        }
        return *this;
    }

    /**
     * @brief Moves the contents of another map object to this map object.
     * @param other The map object to move.
     * @return A reference to this map object.
     */
    map& operator=(map&& other) noexcept {
        if (this != &other) {
            clear();
            root_ = other.root_;
            size_ = other.size_;
            comp_ = std::move(other.comp_);
            other.root_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }

    /**
     * @brief Destructor for the map class template.
     */
    ~map() {
        clear();
    }

    /**
     * @brief Inserts a key-value pair into the map.
     * @param value The key-value pair to insert.
     * @return A pair containing an iterator to the inserted element and a boolean indicating whether the insertion was successful.
     */
    std::pair<iterator, bool> insert(const value_type& value) {
        auto* new_node = new Node<Key, T>(value.first, value.second);
        Node<Key, T>* parent = nullptr;
        Node<Key, T>* current = root_;
        while (current != nullptr) {
            parent = current;
            if (comp_(value.first, current->data_.first)) {
                current = current->left_;
            } else if (comp_(current->data_.first, value.first)) {
                current = current->right_;
            } else {
                delete new_node;
                return {iterator(const_cast<Node<Key, T>*>(current)), false};
            }
        }
        new_node->parent_ = parent;
        if (parent == nullptr) {
            root_ = new_node;
        } else if (comp_(value.first, parent->data_.first)) {
            parent->left_ = new_node;
        } else {
            parent->right_ = new_node;
        }
        ++size_;
        return {iterator(new_node), true};
    }

    /**
     * @brief Finds a key-value pair with the specified key in the map.
     * @param key The key to search for.
     * @return An iterator to the key-value pair if found, otherwise an iterator to the end of the map.
     */
    iterator find(const key_type& key) {
        Node<Key, T>* current = root_;
        while (current != nullptr) {
            if (comp_(key, current->data_.first)) {
                current = current->left_;
            } else if (comp_(current->data_.first, key)) {
                current = current->right_;
            } else {
                return iterator(current);
            }
        }
        return end();
    }

    /**
     * @brief Finds a key-value pair with the specified key in the map.
     * @param key The key to search for.
     * @return A const iterator to the key-value pair if found, otherwise a const iterator to the end of the map.
     */
    const_iterator find(const key_type& key) const {
        Node<Key, T>* current = root_;
        while (current != nullptr) {
            if (comp_(key, current->data_.first)) {
                current = current->left_;
            } else if (comp_(current->data_.first, key)) {
                current = current->right_;
            } else {
                return const_iterator(current);
            }
        }
        return cend();
    }

    /**
     * @brief Swaps the contents of this map object with another map object.
     * @param other The map object to swap with.
     */
    void swap(map& other) noexcept {
        std::swap(root_, other.root_);
        std::swap(size_, other.size_);
        std::swap(comp_, other.comp_);
    }

    /**
     * @brief Erases a key-value pair from the map.
     * @param pos An iterator to the key-value pair to erase.
     * @return An iterator to the next element after the erased element.
     */
    iterator erase(iterator pos)
    {
        if (pos == end())
            return end();

        node_type* node = pos.current_;
        iterator res = ++iterator(node);
        if (node->left_ == nullptr)
            transplant(node, node->right_);
        else if (node->right_ == nullptr)
            transplant(node, node->left_);
        else
        {
            node_type* next = node->right_;
            while (next->left_ != nullptr)
                next = next->left_;
            if (next->parent_ != node)
            {
                transplant(next, next->right_);
                next->right_ = node->right_;
                next->right_->parent_ = next;
            }
            transplant(node, next);
            next->left_ = node->left_;
            next->left_->parent_ = next;
        }

        delete node;
        size_--;

        return res;
    }

    /**
     * @brief Erases a key-value pair from the map.
     * @param pos A const iterator to the key-value pair to erase.
     * @return An iterator to the next element after the erased element.
     */
    iterator erase(const_iterator pos)
    {
        if (pos == cend())
            return end();

        node_type* node = const_cast<node_type*>(pos.current_);
        iterator res = ++iterator(node);
        if (node->left_ == nullptr)
            transplant(node, node->right_);
        else if (node->right_ == nullptr)
            transplant(node, node->left_);
        else
        {
            node_type* next = node->right_;
            while (next->left_ != nullptr)
                next = next->left_;
            if (next->parent_ != node)
            {
                transplant(next, next->right_);
                next->right_ = node->right_;
                next->right_->parent_ = next;
            }
            transplant(node, next);
            next->left_ = node->left_;
            next->left_->parent_ = next;
        }

        delete node;
        size_--;

        return res;
    }

    /**
     * @brief Erases a key-value pair with the specified key from the map.
     * @param key The key of the key-value pair to erase.
     * @return The number of elements erased (0 or 1).
     */
    size_type erase(const Key& key)
    {
        iterator pos = find(key);
        if (pos == end())
            return 0;
        erase(pos);
        return 1;
    }

    /**
     * @brief Erases a range of key-value pairs from the map.
     * @param first A const iterator to the first key-value pair to erase.
     * @param last A const iterator to the last key-value pair to erase.
     * @return An iterator to the first element after the erased range.
     */
    iterator erase(const_iterator first, const_iterator last) {
        if (first == last) {
            return begin();
        }
        while (first != last) {
            first = erase(first);
        }
        return begin();
    }

    /**
     * @brief Returns the number of elements in the map.
     * @return The number of elements in the map.
     */
    size_type size() const noexcept {
        return size_;
    }

    /**
     * @brief Checks whether the map is empty.
     * @return True if the map is empty, false otherwise.
     */
    bool empty() const noexcept {
        return size_ == 0;
    }

    /**
     * @brief Clears the contents of the map.
     */
    void clear() {
        delete_nodes(root_);
        root_ = nullptr;
        size_ = 0;
    }

    /**
     * @brief Counts the number of key-value pairs with the specified key in the map.
     * @param key The key to count.
     * @return The number of key-value pairs with the specified key in the map.
     */
    size_type count(const key_type& key) const {
        Node<Key, T>* current = root_;
        while (current != nullptr) {
            if (comp_(key, current->data_.first)) {
                current = current->left_;
            } else if (comp_(current->data_.first, key)) {
                current = current->right_;
            } else {
                return 1;
            }
        }
        return 0;
    }

    /**
     * @brief Accesses the value associated with the specified key.
     * @param key The key to access.
     * @return A reference to the value associated with the specified key.
     * @throw std::out_of_range if the key is not found.
     */
    T& at(const key_type& key) {
        Node<Key, T>* current = root_;
        while (current != nullptr) {
            if (comp_(key, current->data_.first)) {
                current = current->left_;
            } else if (comp_(current->data_.first, key)) {
                current = current->right_;
            } else {
                return current->data_.second;
            }
        }
        throw std::out_of_range("Key not found");
    }

    /**
     * @brief Accesses the value associated with the specified key.
     * @param key The key to access.
     * @return A const reference to the value associated with the specified key.
     * @throw std::out_of_range if the key is not found.
     */
    const T& at(const key_type& key) const {
        Node<Key, T>* current = root_;
        while (current != nullptr) {
            if (comp_(key, current->data_.first)) {
                current = current->left_;
            } else if (comp_(current->data_.first, key)) {
                current = current->right_;
            } else {
                return current->data_.second;
            }
        }
        throw std::out_of_range("Key not found");
    }

    /**
     * @brief Accesses the value associated with the specified key.
     * @param key The key to access.
     * @return A reference to the value associated with the specified key. If the key is not found, a new key-value pair is inserted with a default-constructed value.
     */
    T& operator[](const Key& key) {
        Node<Key, T>* node = root_;
        Node<Key, T>* parent = nullptr;
        while (node != nullptr) {
            if (comp_(key, node->data_.first)) {
                parent = node;
                node = node->left_;
            }
            else if (comp_(node->data_.first, key)) {
                parent = node;
                node = node->right_;
            }
            else {
                return node->data_.second;
            }
        }

        node = new Node<Key, T>(key, T(), parent);
        if (parent == nullptr) {
            root_ = node;
        }
        else if (comp_(key, parent->data_.first)) {
            parent->left_ = node;
        }
        else {
            parent->right_ = node;
        }
        ++size_;
        return node->data_.second;
    }

    /**
     * @brief Accesses the value associated with the specified key.
     * @param key The key to access.
     * @return A reference to the value associated with the specified key. If the key is not found, a new key-value pair is inserted with a move-constructed value.
     */
    T& operator[](Key&& key) {
        Node<Key, T>* node = root_;
        Node<Key, T>* parent = nullptr;
        while (node != nullptr) {
            if (comp_(key, node->data_.first)) {
                parent = node;
                node = node->left_;
            }
            else if (comp_(node->data_.first, key)) {
                parent = node;
                node = node->right_;
            }
            else {
                return node->data_.second;
            }
        }
        node = new Node<Key, T>(std::move(key), T(), parent);
        if (parent == nullptr) {
            root_ = node;
        }
        else if (comp_(key, parent->data_.first)) {
            parent->left_ = node;
        }
        else {
            parent->right_ = node;
        }
        ++size_;
        return node->data_.second;
    }

    /**
     * @brief Returns an iterator to the first element in the map.
     * @return An iterator to the first element in the map.
     */
    iterator begin() noexcept {
        Node<Key, T>* current = root_;
        while (current != nullptr && current->left_ != nullptr) {
            current = current->left_;
        }
        return iterator(current);
    }

    /**
     * @brief Returns a const iterator to the first element in the map.
     * @return A const iterator to the first element in the map.
     */
    const_iterator begin() const noexcept {
        Node<Key, T>* current = root_;
        while (current != nullptr && current->left_ != nullptr) {
            current = current->left_;
        }
        return const_iterator(current);
    }

    /**
     * @brief Returns a const iterator to the first element in the map.
     * @return A const iterator to the first element in the map.
     */
    const_iterator cbegin() const noexcept {
        Node<Key, T>* current = root_;
        while (current != nullptr && current->left_ != nullptr) {
            current = current->left_;
        }
        return const_iterator(current);
    }

    /**
     * @brief Returns a reverse iterator to the first element in the map.
     * @return A reverse iterator to the first element in the map.
     */
    reverse_iterator rbegin() noexcept {
        Node<Key, T>* current = root_;
        while (current != nullptr && current->right_ != nullptr) {
            current = current->right_;
        }
        return reverse_iterator(current);
    }

    /**
     * @brief Returns a const reverse iterator to the first element in the map.
     * @return A const reverse iterator to the first element in the map.
     */
    const_reverse_iterator rbegin() const noexcept {
        Node<Key, T>* current = root_;
        while (current != nullptr && current->right_ != nullptr) {
            current = current->right_;
        }
        return const_reverse_iterator(current);
    }

    /**
     * @brief Returns a const reverse iterator to the first element in the map.
     * @return A const reverse iterator to the first element in the map.
     */
    const_reverse_iterator crbegin() const noexcept {
        Node<Key, T>* current = root_;
        while (current != nullptr && current->right_ != nullptr) {
            current = current->right_;
        }
        return const_reverse_iterator(current);
    }

    /**
     * @brief Returns an iterator to the end of the map.
     * @return An iterator to the end of the map.
     */
    iterator end() noexcept {
        return iterator(nullptr);
    }

    /**
     * @brief Returns a const iterator to the end of the map.
     * @return A const iterator to the end of the map.
     */
    const_iterator end() const noexcept {
        return const_iterator(nullptr);
    }

    /**
     * @brief Returns a const iterator to the end of the map.
     * @return A const iterator to the end of the map.
     */
    const_iterator cend() const noexcept {
        return const_iterator(nullptr);
    }

    /**
     * @brief Returns a reverse iterator to the end of the map.
     * @return A reverse iterator to the end of the map.
     */
    reverse_iterator rend() noexcept {
        return reverse_iterator(nullptr);
    }

    /**
     * @brief Returns a const reverse iterator to the end of the map.
     * @return A const reverse iterator to the end of the map.
     */
    const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(nullptr);
    }

    /**
     * @brief Returns a const reverse iterator to the end of the map.
     * @return A const reverse iterator to the end of the map.
     */
    const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(nullptr);
    }

private:
    Node<Key, T>* root_;
    size_type size_;
    Compare comp_;

    /**
     * @brief Deletes all nodes in the map.
     * @param node The root node of the subtree to delete.
     */
    void delete_nodes(Node<Key, T>* node) {
        if (node == nullptr) {
            return;
        }
        delete_nodes(node->left_);
        delete_nodes(node->right_);
        delete node;
    }

    /**
     * @brief Transplants one subtree with another in the map.
     * @param u The root node of the subtree to replace.
     * @param v The root node of the subtree to replace it with.
     */
    void transplant(Node<Key, T>* u, Node<Key, T>* v) {
        if (u->parent_ == nullptr) {
            root_ = v;
        } else if (u == u->parent_->left_) {
            u->parent_->left_ = v;
        } else {
            u->parent_->right_ = v;
        }
        if (v != nullptr) {
            v->parent_ = u->parent_;
        }
    }

};


#endif //MLAB3_MAP_H
