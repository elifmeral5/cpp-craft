/*Title: Map.cpp
  Author: Prof. Dixon
  Date: 4/17/2025
  Description: This class defines the Map class
  Map is a templated associative container that stores
  key–value pairs in sorted order using a singly linked
  list, supporting insertion, lookup, update, and removal
  with O(n) traversal.
*/
#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <stdexcept>
#include "Node.cpp"
using namespace std;

template <typename K, typename V>
class Map {
public:
  // Name: Map()
  // Description: Default constructs an empty map.
  // Preconditions: None.
  // Postconditions: m_head is set to nullptr; m_size is initialized to 0.
  Map();
  // Name: ~Map()
  // Description: Destroys the map, freeing all nodes.
  // Preconditions: None.
  // Postconditions: All nodes are deleted; m_head is nullptr; m_size is 0.
  ~Map();
  // Name: Map(const Map& other)
  // Description: Copy constructor; deep copies another map’s contents.
  // Preconditions: other must be a valid Map<K,V>.
  // Postconditions: This map contains the same key/value pairs, in order.
  Map(const Map& other);
  // Name: operator=(const Map& other)
  // Description: Assignment operator; clears this map and deep copies other.
  // Preconditions: other is a valid Map<K,V>; self-assignment is handled.
  // Postconditions: This map contains a copy of other’s elements.
  Map<K,V>& operator=(const Map& other);
  // Name: Insert(const K& key, const V& value)
  // Description: Inserts or updates a key → value pair, keeping
  //              nodes ordered by key.
  // Preconditions: key and value are valid; map may be empty.
  // Postconditions: New node inserted at sorted position, or
  //                 existing node’s value updated; m_size adjusted.
  void Insert(const K& key, const V& value);
  // Name: Update(const K& key, const V& value)
  // Description: Changes the value for an existing key.
  // Preconditions: key must exist in the map.
  // Postconditions: Corresponding node’s value is set to
  //                 value; throws out_of_range if key not found.
  void Update(const K& key, const V& value);
  // Name: ValueAt(const K& key) const
  // Description: Retrieves a const reference to the value for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns reference to the value;
  //                 throws out_of_range if not found.
  const V& ValueAt(const K& key) const;
  // Name: At(const K& key) const
  // Description: Returns a pointer to the node for key.
  // Preconditions: key must exist in the map.
  // Postconditions: Returns pointer to the Node<K,V>;
  //                 throws out_of_range if not found.
  Node<K,V>* At(const K& key) const;
  // Name: GetSize() const
  // Description: Reports the number of key‑value pairs in the map.
  // Preconditions: None.
  // Postconditions: Returns the value of m_size.
  int GetSize() const;
  // Name: IsEmpty() const
  // Description: Checks whether the map contains no elements.
  // Preconditions: None.
  // Postconditions: Returns true if m_size == 0
  //                 (m_head == nullptr); false otherwise.
  bool IsEmpty() const;
  // Name: Display() const
  // Description: Prints each key:value pair to cout, one per line.
  // Preconditions: ostream cout is available.
  // Postconditions: Map contents are written to standard output.
  void Display() const;
  // Name: operator<<
  // Description: Streams all key:value pairs into os, one per line.
  // Preconditions: os is a valid ostream; map is a valid Map<K,V>.
  // Postconditions: os contains serialized map contents;
  //                returns os by reference.
  // PROVIDED
  friend ostream& operator<<(ostream& os, const Map<K, V>& map){
    Node<K,V>* current = map.m_head;
    while (current != nullptr) {
      os << current->GetKey() << ":" << current->GetValue() << endl;
      current = current->GetNext();
    }
    return os;
  }
private:
  // Name: Clear()
  // Description: Deletes all nodes in the linked list,
  //              freeing their memory and resetting the map.
  // Preconditions: None.
  // Postconditions: All dynamically allocated nodes are deleted;
  //                 m_head is set to nullptr; m_size is reset to 0.
  void Clear();  
  Node<K,V>* m_head; //Pointer to the first node in the Map
  int m_size; //Tracks the size of the Map (number of nodes)
};
#endif
//********IMPLEMENT MAP.CPP HERE DUE TO TEMPLATED CLASS*********

// Map()
// Constructor
template <typename K, typename V>
Map<K, V>::Map() {
  m_head = nullptr;  // initialize to null
  m_size = 0;        // initialize size to 0
}

//~Map() - Destructor 
// Deallocated allocated memory
template <typename K, typename V>
Map<K, V>::~Map() {
  // sets current to head pointer
  Node<K, V>* current = m_head;
  // until current is at null it deletes pointers
  while (current != nullptr) {
    Node<K, V>* next = current->GetNext();
    delete current;
    current = next;
  }
  //sets to null and 0 to finish
  m_head = nullptr;
  m_size = 0;
}


// Map(const Map<K, V>& other)
// Copy constructor
template <typename K, typename V>
Map<K, V>::Map(const Map<K, V>& other) {
  m_size = 0;        // Initialize size to 0 first
  m_head = nullptr;  // Initialize head to nullptr
  
  // Copy each node from the other map
  Node<K, V>* current = other.m_head;
  while (current != nullptr) {
    Insert(current->GetKey(), current->GetValue());
    current = current->GetNext();
  }
}

// operator=(const Map<K,V>& other)
template <typename K, typename V>
Map<K,V>& Map<K,V>::operator=(const Map<K,V>& other) {
  // avoid re-copying if assigning to itself
  if (this != &other) {

    // Delete all existing nodes in the current map
    Clear();
    // Pointer to traverse the other map
    Node<K, V>* current = other.m_head;

    // Traverse the other map and insert each key-value pair into this map
    while (current != nullptr) {
      // Copy
      Insert(current->GetKey(), current->GetValue());
      // Next Node
      current = current->GetNext();
    }
  }

  // Return reference to the current obect
  return *this;
  
}

// Insert(const K& key, const V& value)
template <typename K, typename V>
void Map<K, V>::Insert(const K& key, const V& value) {
  // Create a new node with the given key and value
  Node<K, V>* newNode = new Node<K, V>(key, value);

  // Empty list or insert at the beginning (head)
  if (m_head == nullptr || m_head->GetKey() > key) {

    // Link new node to current head
    newNode->SetNext(m_head);
    // Update head to point to new node
    m_head = newNode;
    //  Insert somewhere after the head
  } else {
    Node<K, V>* current = m_head;

    // Traverse the list to find the correct place to insert
    while (current->GetNext() != nullptr && current->GetNext()->GetKey() < key) {
      current = current->GetNext();
    }
    // Key already exists in the list then  update the value
    if (current->GetNext() != nullptr && current->GetNext()->GetKey() == key) {
      current->GetNext()->SetValue(value);
      delete newNode;

      // insert new node in correct position
    } else {
      newNode->SetNext(current->GetNext());
      current->SetNext(newNode);
    }
  }
  // Increment map size
  ++m_size;
}

// Update(const K& key, const V& value)
template <typename K, typename V>
void Map<K, V>::Update(const K& key, const V& value) {
  // Start at the head of the linked list
  Node<K, V>* current = m_head;
  // Traverse the list until the end
  while (current != nullptr) {
    // If the current node's key matches
    if (current->GetKey() == key) {
      current->SetValue(value); // Update value
      return;
    }
    // Move to the next node in the list
    current = current->GetNext(); 
  }
  throw out_of_range("Key not found.");
}


template <typename K, typename V>
const V& Map<K, V>::ValueAt(const K& key) const {
  // Start at the beginning of the linked list
  Node<K, V>* current = m_head;

  // Traverse through each node in the list
  while (current != nullptr) {
    // Check if the current node's key matches the given key
    if (current->GetKey() == key) {
      // Return the associated value
      return current->GetValue();
    }
    // Go to next node
    current = current->GetNext();
  }
  throw out_of_range("Key not found.");
}

// At(const K& key) const
template <typename K, typename V>
Node<K, V>* Map<K, V>::At(const K& key) const {
  // Start at the head of the linked list
  Node<K, V>* current = m_head;

   // Traverse the list node by node
  while (current != nullptr) {
    // If the current node's key matches the one we're looking for
    if (current->GetKey() == key) {
      // Return a pointer to the matching node
      return current;
    }
    // Go to next node
    current = current->GetNext();
  }
  throw out_of_range("Key not found.");
}

// GetSize() const
// Gets size
template <typename K, typename V>
int Map<K, V>::GetSize() const {
  return m_size;
}

// IsEmpty() const
// Checks if empty 
template <typename K, typename V>
bool Map<K, V>::IsEmpty() const {
  if (m_size == 0){
    return true;
  }
  else{
    return false;
  }
}


// Display() const
// Displays key and value
template <typename K, typename V>
void Map<K, V>::Display() const {
  Node<K, V>* current = m_head;
  while (current != nullptr) {
    cout << current->GetKey() << ":" << current->GetValue() << endl;
    current = current->GetNext();
  }
}

// Clear()
// Deletes all nodes in the linked list,
template <typename K, typename V>
void Map<K, V>::Clear() {
  Node<K, V>* current = m_head;
  while (current != nullptr) {
    Node<K, V>* temp = current;
    current = current->GetNext();
    delete temp;
  }
  m_head = nullptr;
  m_size = 0;
}
