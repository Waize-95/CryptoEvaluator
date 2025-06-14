#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include<iostream>
using namespace std;

template <typename T>
class Dynamic_array
{
private:
  T *arr;
  int len;
  int cap;

  // Doubles the current capacity when needed
  void double_capacity() {
    if (cap == 0) {
        cap = 1;
    } else {
        cap = 2 * cap;
    }
    
    T *temparr = new T[cap];
    for (int i = 0; i < len; i++) {
        temparr[i] = arr[i];
    }
    
    delete[] arr;
    arr = temparr;
  }

public:
  // constructors
  Dynamic_array() : len(0), cap(1), arr(new T[1]) {
    // Initialize with capacity=1 to avoid nullptr issues
    // cout<<"Default template constructor"<<endl;
  }

  Dynamic_array(int count, int value) : len(count), cap(count), arr(new T[cap])
  {
    // cout<<"Parameterized template constructor"<<endl;
    for (int i = 0; i < count; i++)
    {
      arr[i] = value;
    }
  }

  Dynamic_array(const Dynamic_array &other) : len(other.len), cap(other.cap), arr(new T[other.cap])
  {
    // cout<<"Copy template constructor"<<endl;
    for (int i = 0; i < len; i++)
    {
      this->arr[i] = other.arr[i];
    }
  }

  ~Dynamic_array()
  { 
    delete[] arr;
    arr = nullptr; // Good practice to set to nullptr after deletion
  }

  // operators
  Dynamic_array &operator=(const Dynamic_array &other)
  {
    // cout<<"Template = overloaded operator"<<endl;
    if (this != &other) { // Check for self-assignment
      // Delete existing array first
      delete[] arr;
      
      this->len = other.len;
      this->cap = other.cap;
      arr = new T[cap];
      
      for (int i = 0; i < other.len; i++)
      {
        this->arr[i] = other.arr[i];
      }
    }
    return *this;
  }

  T &operator[](int index)
  {
    if (index > -1 && index < len)
    {
      return arr[index];
    }
    else
    {
      return arr[0]; // This could still cause issues if len == 0
    }
  }

  const T &operator[](int index) const
  {
    if (index > -1 && index < len)
    {
      return arr[index];
    }
    else
    {
      return arr[0]; // This could still cause issues if len == 0
    }
  }

  bool operator==(const Dynamic_array &other) const
  {
    if (this->len != other.len)
    {
      return false;
    }
    for (int i = 0; i < other.len; i++)
    {
      if (this->arr[i] != other.arr[i])
      {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const Dynamic_array &other) const
  {
    if (this->len != other.len)
    {
      return true;
    }
    for (int i = 0; i < other.len; i++)
    {
      if (this->arr[i] != other.arr[i])
      {
        return true;
      }
    }
    return false;
  }

  Dynamic_array operator+(const Dynamic_array &other) const
  {
    Dynamic_array newarr;
    newarr.len = this->len + other.len;
    newarr.cap = newarr.len;
    delete[] newarr.arr; // Delete the default allocated array
    newarr.arr = new T[newarr.cap];
    
    int index = 0;
    for (int i = 0; i < this->len; i++)
    {
      newarr.arr[index++] = this->arr[i];
    }
    // newarr.arr[index++]=' ';
    for (int i = 0; i < other.len; i++)
    {
      newarr.arr[index++] = other.arr[i];
    }
    return newarr;
  }
  T* begin() {
      return arr;         // pointer to first element
  }

  T* end() {
      return arr+len;  // pointer to one past the last element
  }

  const T* begin() const {
      return arr;
  }

  const T* end() const {
      return arr+len;
  }

  Dynamic_array &operator+=(const Dynamic_array &other)
  {
    if (this->len + other.len > this->cap)
    {
      int newCap = this->len + other.len;
      T *temparr = new T[newCap];
      for (int i = 0; i < this->len; i++) {
        temparr[i] = this->arr[i];
      }
      delete[] arr;
      arr = temparr;
      cap = newCap;
    }
    
    for (int i = this->len, j = 0; j < other.len; i++, j++)
    {
      this->arr[i] = other.arr[j];
    }
    len = len + other.len;
    return *this;
  }

  void print()
  {
    for (int i = 0; i < len; i++)
    {
      cout << arr[i] << " ";
    }
    cout << endl;
  }

  void push(T value) {
    // Double capacity if needed
    if (len + 1 > cap) {
        double_capacity();
    }
    
    // Add the value and increment length
    arr[len] = value;
    len++;
  }

  void pop()
  {
    if (len > 0) {
      this->len = this->len - 1;
    }
  }

  void insert_at(int index, T value)
  {
    if (index < 0 || index > len) {
      return; // Invalid index
    }
    
    // Check if we need more space
    if (len + 1 > cap) {
      double_capacity();
    }
    
    // Shift elements to make room
    for (int i = len; i > index; i--) {
      arr[i] = arr[i-1];
    }
    
    arr[index] = value;
    len++; // Fixed: actually increment length
  }

  void delete_at(int index)
  {
    if (index < 0 || index >= len) {
      return; // Invalid index
    }
    
    for (int i = index; i < this->len - 1; i++)
    {
      this->arr[i] = this->arr[i + 1];
    }
    this->len--;
  }

  void reserve(int new_capacity)
  {
    if (new_capacity <= cap) {
      return; // No need to reserve less space
    }
    
    cap = new_capacity;
    T *temparr = new T[cap];
    for (int i = 0; i < len; i++)
    {
      temparr[i] = this->arr[i];
    }
    delete[] arr;
    arr = temparr;
  }

  void clear()
  {
    // Keep the array but reset length
    len = 0;
  }

  void swap(Dynamic_array &other)
  {
    // Efficiently swap pointers and values instead of copying data
    T* temp_arr = this->arr;
    int temp_len = this->len;
    int temp_cap = this->cap;
    
    this->arr = other.arr;
    this->len = other.len;
    this->cap = other.cap;
    
    other.arr = temp_arr;
    other.len = temp_len;
    other.cap = temp_cap;
  }

  void shrink_to_fit()
  {
    if (cap > len && len > 0)
    {
      cap = len;
      T *newarr = new T[cap];
      for (int i = 0; i < len; i++)
      {
        newarr[i] = arr[i];
      }
      delete[] arr;
      arr = newarr;
    }
  }

  void reverse()
  {
    for (int i = 0; i < len / 2; i++)
    {
      T temp = arr[i];
      arr[i] = arr[len - 1 - i];
      arr[len - 1 - i] = temp;
    }
  }

  bool empty() const
  {
    return (this->len == 0);
  }

  int size() const
  {
    return len;
  }

  T &at(int index)
  {
    if (index > -1 && index < len)
    {
      return arr[index];
    }
    else
    {
      throw std::out_of_range("Index out of bounds");
    }
  }

  const T &at(int index) const
  {
    if (index > -1 && index < len)
    {
      return arr[index];
    }
    else
    {
      throw std::out_of_range("Index out of bounds");
    }
  }

  T &front()
  {
    if (len > 0) {
      return this->arr[0];
    }
    throw std::out_of_range("Array is empty");
  }

  const T &front() const
  {
    if (len > 0) {
      return this->arr[0];
    }
    throw std::out_of_range("Array is empty");
  }

  T &back()
  {
    if (len > 0) {
      return this->arr[len - 1];
    }
    throw std::out_of_range("Array is empty");
  }

  const T &back() const
  {
    if (len > 0) {
      return this->arr[len - 1];
    }
    throw std::out_of_range("Array is empty");
  }

  int find(T value) const
  {
    for (int i = 0; i < this->len; i++)
    {
      if (this->arr[i] == value)
      {
        return i;
      }
    }
    return -1; // Not found
  }
};
#endif //DYNAMIC_ARRAY