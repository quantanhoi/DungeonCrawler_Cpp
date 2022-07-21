#ifndef LIST_H
#define LIST_H
#include<iostream>
#include<cstddef>
class Level;
class myList
{
private:
    struct Element
    {
    Level* data;
    Element* next;
    Element* previous;
    };
protected:
    Element* start     = nullptr;
    std::size_t m_size = 0;
public:
    myList();
    ~myList();
    void push_back(Level* level);
    void pop_back();
    void push_front(Level* level);
    void pop_front();
    int& back();
    std::size_t size() const;
    bool empty() const;

    void print() const;

    //from this
    class iterator {
    public:
        iterator& operator ++();
        iterator& operator--();
        Level*& operator*();
        bool operator==(const iterator&);
        bool operator!=(const iterator&);
        void operator=(const iterator&);
        friend myList;
    protected:
        Element* current;
    };
    iterator begin();
    iterator end();
    iterator next();
    bool hasNext();
    // to this
protected:


};


#endif // LIST_H
