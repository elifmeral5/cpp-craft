#ifndef NODE_CPP
#define NODE_CPP

#include <iostream>
using namespace std;

template<typename K, typename V>
class Node {
public:
  // Node class functions (used by Map)

  // Name: Node(const K& key, const V& value, Node<K,V>* next = nullptr)
  // Description: Constructs a node holding a key-value pair and
  //              an optional link to the next node.
  // Preconditions: key and value must be valid objects;
  //              next can be nullptr or a valid node pointer.
  // Postconditions: m_key is initialized to key;
  //              m_value to value; m_next to next.
  Node(const K& key, const V& value, Node<K,V>* next = nullptr);
  // Name: GetKey() const
  // Description: Retrieves the key stored in this node.
  // Preconditions: None.
  // Postconditions: Returns a const reference to m_key.
  const K& GetKey() const;
  // Name: GetValue() const
  // Description: Retrieves the value stored in this node.
  // Preconditions: None.
  // Postconditions: Returns a const reference to m_value.
  const V& GetValue() const;
  // Name: GetNext() const
  // Description: Gets the pointer to the next node in the linked list.
  // Preconditions: None.
  // Postconditions: Returns m_next (may be nullptr if at end of list).
  Node<K,V>* GetNext() const;
  // Name: SetValue(const V& value)
  // Description: Updates the stored value in this node.
  // Preconditions: 'value' must be a valid V object.
  // Postconditions: m_value is set to value.
  void SetValue(const V& value);
  // Name: SetNext(Node<K,V>* next)
  // Description: Updates the link to the next node in the list.
  // Preconditions: 'next' is either nullptr or points to a valid node.
  // Postconditions: m_next is set to next.
  void SetNext(Node<K,V>* next);
  // Name: operator<<
  // Description: Prints this node's key and value in
  //              "key:value" format to an ostream.
  // Preconditions: 'os' must be a valid ostream.
  // Postconditions: Outputs "key:value" to os and returns os.
  friend ostream& operator<<(ostream& out, const Node<K,V>& node){
    out << node.GetKey() << ':' << node.GetValue();
    return out;
  }
private:
  K m_key; //Key  (used for ordering)
  V m_value; //Value
  Node<K,V>* m_next; //Pointer to next node
};
#endif

//**********IMPLEMENT NODE.CPP HERE AS IT IS TEMPLATED************

// Node(const K& key, const V& value, Node<K,V>* next)
// Constrtuctr
template<typename K, typename V>
Node<K,V>::Node(const K& key, const V& value, Node<K,V>* next) {
  m_key = key;       //inititalizes to key 
  m_value = value;   //inititalizes to value
  m_next = next;     //inititalizes to next
}


// GetKey()
// Gets the key
template<typename K, typename V>
const K& Node<K,V>::GetKey() const {
  return m_key;
}

// GetValue()
// Gets the value
template<typename K, typename V>
const V& Node<K,V>::GetValue() const {
  return m_value;
}

// GetNext()
// Gets the next node
template<typename K, typename V>
Node<K,V>* Node<K,V>::GetNext() const {
  return m_next;
}

// SetValue(const V& value)
// Sets the value
template<typename K, typename V>
void Node<K,V>::SetValue(const V& value) {
  m_value = value;
}

// SetNext(Node<K,V>* next)
// sets next Node
template<typename K, typename V>
void Node<K,V>::SetNext(Node<K,V>* next) {
  m_next = next;
}
