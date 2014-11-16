#ifndef _6S096_CPPLIST_H
#define _6S096_CPPLIST_H
// So that we have size_t defined
#include <cstddef>
#include <stdexcept>
#include "list_node.h"

// Forward declaration of apply/reduce types
class ApplyFunction;
class ReduceFunction;

// Write all your implementations in the source file!
// Do feel free to add some more declarations here,
// if needed.

class List {
    // ... put whatever private data members you need here
    // can also add any private member functions you'd like
    size_t _size;
    List_Node *_head;
public:
    // Can use outside as List::iterator type
    class iterator {
        friend class List;
        List_Node *_node;
    public:
        iterator( List_Node *theNode );
        iterator& operator++();
        int& operator*();
        bool operator==( const iterator &rhs );
        bool operator!=( const iterator &rhs );
    };
    // Can use outside as List::const_iterator type
    class const_iterator {
        friend class List;
        List_Node *_node;
    public:
        const_iterator( List_Node *theNode );
        const_iterator& operator++();
        const int& operator*();
        bool operator==( const const_iterator &rhs );
        bool operator!=( const const_iterator &rhs );
    };
    
    iterator begin();
    const_iterator begin() const;
    iterator back();
    const_iterator back() const;
    iterator end();
    const_iterator end() const;
    
    iterator find( iterator s, iterator t, int needle );
    
    
    // The empty constructor should create an empty list (length 0)
    List();
    
    List( const List &other );
    
    List& operator= ( const List &other );
    
    // The destructor should clean up everything- no memory leaks!
    ~List();
    
    // Returns the length of the linked list
    size_t length() const;
    
    // Return a reference to a value at position 'pos' in
    // the linked list (0 is the first element, 1 is the
    // second, and so on.)
    int& value( size_t pos );
    
    // Returns the value at position 'pos' in the linked
    // list; is const so that we can still read from const Lists.
    int value( size_t pos ) const;
    
    // As before: append a node with value 'value' to the
    // end of the linked list.
    void append( int value );
    
    // As before: delete all nodes with value 'value' from
    // the linked list.
    void deleteAll( int value );
    
    // As before: insert a node with value 'value' before the
    // first occurrence of value 'before'. If value 'before'
    // does not exist in the list, do nothing.
    void insertBefore( int value, int before );
    
    // Apply the ApplyFunction object to the linked list.
    // (see include/apply.h and src/apply.cpp)
    void apply( const ApplyFunction &interface );
    
    // Apply the ReduceFunction object to the linked list.
    // (see include/reduce.h and src/reduce.cpp)
    int reduce( const ReduceFunction &interface ) const;
    
    // Already implemented for you (see src/list.cpp)
    void print() const;
    
    // you can add more functions here- for example,
    // a faster way of traversing the list might be
    // useful...the current reduce/apply are rather
    // slow for large lists.
    
    int equals( int *array ) const;
};

// Exception to throw if given a bad position in list
class ListOutOfBounds : public std::range_error {
public:
    explicit ListOutOfBounds() : std::range_error( "List index out of bounds" ) {}
};

#endif // _6S096_CPPLIST_H