#pragma once
#include <vector>
#include <iostream>
#define LOGF std::cerr << __FUNCTION__ << " " << __LINE__ << std::endl

template <typename T>
class LinkedList 
{
public:
  struct Node 
  {
    T value;
    Node* next = nullptr;
  };

  ~LinkedList();

  void PushFront(const T& value);
  void InsertAfter(Node* node, const T& value);
  void RemoveAfter(Node* node);
  void PopFront();

  Node* GetHead() { return head; }
  const Node* GetHead() const { return head; }

private:
  bool IsEmpty() const;
  void SetHead(Node* node);
  Node* CreateNode(const T& value);

private:
  Node* head = nullptr;
};

template <typename T>
LinkedList<T>::~LinkedList()
{
  while( !IsEmpty() )
    PopFront();
}

template <typename T>
void LinkedList<T>::PushFront(const T& value)
{
  Node* temp = CreateNode(value);
  temp->next = head;
  SetHead( temp );
}

template <typename T>
void LinkedList<T>::PopFront()
{
  if( IsEmpty() )
    return;
  Node* temp = head->next;
  delete head;
  SetHead( temp );
}

template <typename T>
bool LinkedList<T>::IsEmpty() const
{
  return head == nullptr;
}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& value)
{
  if( node == nullptr )
  {
    this->PushFront( value );
    return;
  }
  Node* temp = CreateNode(value); 
  temp->next = node->next;
  node->next = temp;
}

template<typename T>
void LinkedList<T>::SetHead(Node* node)
{
  head = node;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::CreateNode(const T& value)
{
  Node* temp = new Node;
  temp->value = value;
  return temp; 
}

template <typename T>
void LinkedList<T>::RemoveAfter(Node* node)
{
  if( node == nullptr )
    return PopFront();
  
  if( node->next == nullptr )
    return;
 
  Node* temp = node->next->next;
  delete node->next;
  node->next = temp;
}


template <typename T>
std::vector<T> ToVector(const LinkedList<T>& list) 
{
  std::vector<T> result;
  for (auto node = list.GetHead(); node; node = node->next) 
    result.push_back(node->value);
  
  return result;
}


