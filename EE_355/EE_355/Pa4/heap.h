#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <algorithm>
#include <stdexcept>

template <typename T, typename Comparator >
class Heap
{
 public:
   /// Constructs an m-ary heap for any m >= 2
 Heap();

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

  /// returns the size of the heap
  unsigned int size() const;

 private:
  std::vector<T> _store;
  Comparator _c;
};

template <typename T, typename Comparator>
Heap<T,Comparator>::Heap() : 
  _store(),
  _c()
{
  
}

template <typename T, typename Comparator>
Heap<T,Comparator>::~Heap()
{
  
}

template <typename T, typename Comparator>
void Heap<T,Comparator>::push(const T& item)
{
  _store.push_back(item);
  std::push_heap( _store.begin(), _store.end(), _c);
}

template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return _store.front();
}

/// Removes the top element
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  std::pop_heap( _store.begin(), _store.end(), _c );
  _store.pop_back();
}

/// returns true if the heap is empty
template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const
{
  return _store.empty();
}

/// returns the size
template <typename T, typename Comparator>
unsigned int Heap<T,Comparator>::size() const
{
  return _store.size();
}


#endif

