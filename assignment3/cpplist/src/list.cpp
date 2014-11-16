#include "list.h"
#include "apply.h"
#include "reduce.h"

#include <iostream>

// complete the constructor!
List::List(): _size{ 0 }, _head{ new List_Node( - 1 ) } {
    _head -> setNext( _head );
}

// Copy constructor assumes that (this) is NULL.
List::List( const List &other ): _size{ other.length() }, _head{ new List_Node( -1 ) } {
    List_Node *currentNode = _head;
    for ( size_t i = 0 ; i < other.length() ; i ++ ) {
        List_Node *newNode = new List_Node{ other.value( i ) };
        
        currentNode -> setNext( newNode );
        currentNode = newNode;
    }
    currentNode -> setNext( _head );
}

// Copy assignment assumes that (this) has been initilized.
List& List::operator=( const List &other ) {
    if ( this != &other ){
         _size = other._size;
        size_t i = 0;
        List_Node *currentNode = _head;
        while ( i < _size ) {
            List_Node *newNode = new List_Node( other.value( i++ ) );
            currentNode -> setNext ( newNode );
            currentNode = newNode;
        }
        currentNode -> setNext ( _head );
    }
    return *this;
}

// complete the destructor, as necessary
List::~List() {
    List_Node *thisNode = _head -> next();
    while ( thisNode != _head ) {
        List_Node *nextNode = thisNode -> next();
        delete thisNode;
        thisNode = nextNode;
    }
    _size = 0;
    delete _head;
}

size_t List::length() const {
    // you fill out!
    return _size;
}

// Throw ListOutOfBounds() if pos >= length().
int& List::value( size_t pos ) {
    // you fill out!
    if ( pos >=  _size ) {
        throw ListOutOfBounds();
    } else {
        List_Node *node = _head -> next();
        while ( pos-- ) {
            node = node -> next();
        }
        return node -> getValue();
    }
}

// Throw ListOutOfBounds() if pos >= length().
int List::value( size_t pos ) const {
    // you fill out!
    if ( pos >=  _size ) {
        throw ListOutOfBounds();
    } else {
        List_Node *node = _head -> next();
        while ( pos-- ) {
            node = node -> next();
        }
        return node -> getValue();
    }
}

void List::append( int theValue ) {
    // you fill out!
    List_Node *node = _head;
    while ( node -> next() != _head ){
        node = node -> next();
    }
    List_Node *newNode = new List_Node( theValue );
    node -> setNext( newNode );
    newNode -> setNext( _head );
    _size ++;
}

void List::deleteAll( int theValue ) {
    // you fill out!
    List_Node *thisNode = _head;
    while ( thisNode -> next() != _head ){
        List_Node *nextNode = thisNode -> next();
        if ( nextNode -> getValue() == theValue ) {
            thisNode -> setNext( nextNode -> next() );
            _size --;
            delete nextNode;
        } else {
            thisNode -> setNext( nextNode );
        }
        thisNode = nextNode;
    }
}


void List::insertBefore( int theValue, int before ) {
    // you fill out!
    List_Node *thisNode = _head;
    while ( thisNode -> next() != _head ){
        List_Node *nextNode = thisNode -> next();
        if ( nextNode -> getValue() == before ) {
            List_Node *newNode = new List_Node( theValue );
            newNode -> setNext( nextNode );
            thisNode -> setNext( newNode );
            _size ++;
            return ;
        }
    }
}

// See apply.cpp
void List::apply( const ApplyFunction &interface ) {
    interface.apply( *this );
}

// See reduce.cpp
int List::reduce( const ReduceFunction &interface ) const {
    return interface.reduce( *this );
}

List::iterator List::begin() { return iterator{ _head }; }
List::const_iterator List::begin() const { return const_iterator{ _head }; }
List::iterator List::back() { return iterator{ _head }; }
List::const_iterator List::back() const { return const_iterator{ _head }; }
List::iterator List::end() { return iterator{ _head }; }
List::const_iterator List::end() const { return const_iterator{ _head }; }

List::iterator List::find( iterator s, iterator t, int needle ) {
    for( auto it = s; it != t; ++it ) {
        if( *it == needle ) {
            return it;
        }
    }
    return t;
}

// Already written for you, but kind of slow on large
// lists. Only for debugging purposes (function will
// not be tested on the grader)
void List::print() const {
    std::cout << "{ ";
    for( size_t p = 0; p < length() - 1; ++p ) {
        std::cout << value( p ) << " -> ";
    }
    if( length() > 0 ) {
        std::cout << value( length() - 1 ) << " ";
    }
    std::cout << "}\n";
}

int List::equals( int *array ) const {
    List_Node *node = _head -> next();
    size_t i = 0;
    while ( node != _head ) {
        if ( node -> getValue() != array[ i ++ ] ) {
//            printf( "Value is :%d. Array is: %d\n", node -> getValue(), array[i - 1] );
            return 0;
        }
        node = node -> next();
    }
    return 1;
}
