#include "list.h"
#include <iostream>

using std::cout;
using std::endl;

myList::myList()
{
}

myList::~myList()
{
  while (start != nullptr)
  {
    pop_back();
  }
}

void myList::push_back(Level* level)
{
  Element* tmp = new Element{level, nullptr, nullptr};

  // list is empty
  if (empty())
  {
    start = tmp;
    m_size++;
    return;
  }

  // search last Element
  Element* current = start;
  while (current->next != nullptr)
  {
    // advance current pointer by one element
    current = current->next;
  }
  tmp->previous = current;          //previous node for doubly linked list
  current->next = tmp;
  m_size++;
}

void myList::print() const
{
  // In order to iterate over the list, we need a "current element" pointer
  // which is then advanced by one element in each iteration
  Element* current = start;
  while (current != nullptr)
  {
    cout << current->data << " ";
    current = current->next;
  }
  cout << endl;
}

void myList::pop_back()
{
  // list is already empty
  if (start == nullptr)
  {
    return;
  }

  // list has single element
  if (start->next == nullptr)
  {
    delete start;
    start = nullptr;
    return;
  }

  // if list has 2 or more elements, look for the second last element
  Element* current = start;
  while (current->next->next != nullptr)
  {
    current = current->next;
  }
  delete current->next;
  current->next = nullptr;
  m_size--;
}

std::size_t myList::size() const
{
  return m_size;
}

bool myList::empty() const
{
  return m_size == 0;
  // Alternatively: return start == nullptr;
}
void myList::push_front(Level *level) {
    //list is empty
    if(start == nullptr) {
        Element* tmp = new Element{level, nullptr, nullptr};
        start = tmp;
        return;
    }
    Element* tmp = new Element{level, start, nullptr};
    start->previous = tmp;       //set previous node for current start node to tmp
    start = tmp;        //set start node of the list to tmp

}
void myList::pop_front() {
    if(start == nullptr) {
        return;         //throw exeception here?
    }
    Element* tmp = start;
    start = start->next;
    //if there's only one Element then start->next will be nullptr
    if(start == nullptr) {
        delete tmp;
        m_size--;
        return;
    }
    else {
        start->previous = nullptr;
        delete tmp;
        m_size--;
    }
}
myList::iterator& myList::iterator::operator ++() {
    current = current->next;
    return *this;
}
myList::iterator& myList::iterator::operator--() {
    current = current->previous;
    return *this;
}
Level*& myList::iterator::operator*() {
    return current->data;
}
bool myList::iterator::operator==(const iterator& data) {
    if(current == data.current)
        return true;
    else return false;
}
bool myList::iterator::operator!=(const iterator& data) {
    if(current != data.current) {
        return true;
    }
    else return false;
}
void myList::iterator::operator=(const iterator& data) {
    current = data.current;
}

myList::iterator myList::begin() {
    iterator begin;
    begin.current = start;
    return begin;
}
myList::iterator myList::end() {
    iterator end;
    if(start != nullptr) {
        while(start->next != nullptr) {
            start = start->next;
        }
        end.current = start;
    }
    return end;
}
